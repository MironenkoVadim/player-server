#include "player.hpp"

#include "surok_marks_reader.hpp"
#include "surok_adsb_reader.hpp"
#include "surok_marks_server.hpp"
#include "surok_adsb_server.hpp"

#include <myx/backports/qt/common.hpp>
#include <myx/filesystem/paths.hpp>

#include <QDataStream>
#include <QTextStream>
#include <QTime>
#include <QDir>
#include <QCryptographicHash>
#include <QTextCodec>
#include <QTemporaryFile>
#include <QThread>
#include <math.h>


namespace MF = myx::filesystem;

Player::Player()
{
	m_readers[FileFormat::SurokMarks] = createReader( FileFormat::SurokMarks );
	m_readers[FileFormat::SurokAdsb] = createReader( FileFormat::SurokAdsb );
	m_servers[FileFormat::SurokMarks] = createServer( FileFormat::SurokMarks );
	m_servers[FileFormat::SurokAdsb] = createServer( FileFormat::SurokAdsb );

	m_server = new QTcpServer();
	connect( m_server, &QTcpServer::newConnection, this, &Player::newConnection );
	if ( !m_server->listen( QHostAddress::Any, 7500 ) )
	{
		qDebug() << "Server error. Unable to start the server:" << m_server->errorString();
		m_server->close();
		return;
	}
	else
	{
		qDebug() << "Server is running on player";
	}
//	connect( m_readers.value( FileFormat::SurokAdsb ), &BaseReader::signalAdsb, this, &Player::readFile );
//	connect( m_readers.value( FileFormat::SurokAdsb ), &BaseReader::signalMarks, this, &Player::readFile );
	connect( m_readers.value( FileFormat::SurokMarks )->timerMarks(), &QTimer::timeout, this, &Player::readFile );

	connect( m_readers.value( FileFormat::SurokAdsb )->timerAdsb(), &QTimer::timeout, this, &Player::readFile );
}


void Player::newConnection()
{
	qDebug() << "Connected!";
	QTcpSocket* socket = m_server->nextPendingConnection();
	if ( socket == nullptr ) { return; }
	connect( socket, &QTcpSocket::disconnected, this, &Player::disconnectClient );
	connect( socket, &QTcpSocket::readyRead, this, &Player::readClient );
} // SurokAdsbServer::newConnection


void Player::disconnectClient()
{
	qDebug() << "Disconnect";
	auto* client = qobject_cast< QTcpSocket* >( sender() );
	if ( client == nullptr ) { return; }
	client->deleteLater();
	for ( auto& readers : m_readers )
	{
		readers->file().close();
	}
} // SurokAdsbServer::disconnectClient


void Player::readClient()
{
	auto* client = qobject_cast< QTcpSocket* >( sender() );
	if ( client == nullptr ) { return; }
	qDebug() << client->bytesAvailable();

	QByteArray  block = client->readAll();
	QDataStream in( block );
	readQByteArray( block );
} // SurokAdsbServer::readClient


BaseReader* Player::createReader( FileFormat id )
{
	if ( id == FileFormat::SurokMarks ) { return( new SurokMarksReader() ); }
	if ( id == FileFormat::SurokAdsb ) { return( new SurokAdsbReader() ); }
	return( nullptr );
}


BaseServer* Player::createServer( FileFormat id )
{
	if ( id == FileFormat::SurokMarks ) { return( new SurokMarksServer() ); }
	if ( id == FileFormat::SurokAdsb ) { return( new SurokAdsbServer() ); }
	return( nullptr );
}


void Player::readQByteArray( QByteArray ba )
{
	QJsonDocument jdoc = QJsonDocument::fromBinaryData( ba );
	QJsonObject json   = jdoc.object();

	if ( json.contains( "dir_name" ) )
	{
		m_dirName = json.value( "dir_name" ).toString();
	}
	if ( json.contains( "createQuery" ) )
	{
		auto readers = m_readers.value( FileFormat::SurokAdsb );
		QString nameFiles = readers->checkDir( m_dirName );

		QList< QString > sendList;
		for ( auto& str : readers->fileList() )
		{
			if ( ( str == "." ) || ( str == ".." ) ) { continue; }
			QStringList partsName = str.split( "." );
			QString lastBit       = partsName.at( partsName.size()-1 );
			if ( ( lastBit == "txt" ) || ( lastBit == "index" ) ) { continue; }
			sendList.append( str );
		}
		QString returnSL;
		for ( auto& strLess : sendList )
		{
			if ( readers->fileList().contains( strLess + ".index" ) )
			{
				returnSL.append( QString::number( sendList.indexOf( strLess ) ) );
				returnSL.append( "|" );
			}
			else
			{
				continue;
			}
		}
		QStringList keyList;
		QStringList valueList;
		keyList.append( "get_directory" );
		keyList.append( "indexing_list_file" );

		valueList.append( nameFiles );
		valueList.append( returnSL );
		auto qbN = readers->fillingJsonObject( keyList, valueList );
		if ( qbN != nullptr )
		{
			sendToClient( qbN );
		}
	}
	if ( json.contains( "sendSelectedFile" ) )
	{
		for ( auto& readers : m_readers )
		{
			QStringList parts = json.value( "sendSelectedFile" ).toString().split(".");
			QString lastBit = parts.at( parts.size()-1 ); // расширение выбранного файла
			if ( lastBit == readers->extension() )
			{
				qDebug() << "match";
				readers->setActive( true );
			}
			m_socket = qobject_cast< QTcpSocket* >( sender() );
			if ( m_socket == nullptr ) { return; }
			readers->checkDir( m_dirName );
			readers->file().setFileName( m_dirName + QString( "/%1" )
										 .arg( json.value( "sendSelectedFile" ).toString() ) );
			readers->file().open( QIODevice::ReadOnly );
			qDebug() << readers->fileList() << "str:" << json.value( "sendSelectedFile" ).toString() + ".index";
			if ( readers->fileList().contains( json.value( "sendSelectedFile" ).toString() + ".index" ) )
			{
				auto qb = readers->fillingJsonObject( "index_exists", "true" );
				if ( qb != nullptr ) sendToClient( qb );
			}
			else
			{
				auto qb = readers->fillingJsonObject( "index_exists", "false" );
				if ( qb != nullptr ) sendToClient( qb );
			}
		}
	}
	for ( auto& readers : m_readers )
	{
		if ( !readers->file().isOpen() )
		{
			return;
		}
	}
	if ( json.contains( "index_file" ) )
	{
		for ( auto& readers: m_readers )
		{
			if ( readers->active() )
			{
				m_checkIndex = false;
				QStringList parts = readers->file().fileName().split("/");
				QString lastBit = parts.at( parts.size()-1 );
				qDebug() << "lastBit" << lastBit;
				if ( readers->dirWriteAble() )
				{
					readers->idxFile().setFileName( m_dirName + "/" + lastBit + ".index" );
				}
				else
				{
					QDir dir;
					readers->idxFile().setFileName( dir.temp().dirName() + "/" + lastBit + ".index" );
				}
				readers->idxFile().open( QIODevice::ReadWrite );

				auto a = readers->readCreateIndex();
				readers->setHash( a );

				QByteArray  ba;
				QDataStream ds( &ba, QIODevice::WriteOnly );
				ds << readers->hash();

				if ( readers->idxFile().isWritable() )
				{
					if ( readers->dirWriteAble() )
					{
						qDebug() << "size1: " << readers->idxFile().size();
						readers->idxFile().write( ba );
						qDebug() << "size2: " << readers->idxFile().size();
					}
				}

				QList< QString > sendList;
				for ( auto& str : readers->fileList() )
				{
					if ( ( str == "." ) || ( str == ".." ) ) { continue; }
					QStringList partsName = str.split( "." );
					QString lastBit       = partsName.at( partsName.size()-1 );
					if ( ( lastBit == "txt" ) || ( lastBit == "index" ) ) { continue; }
					sendList.append( str );
				}
				auto qb = readers->fillingJsonObject( "indexing_file_success", QString::number(
							   sendList.indexOf( lastBit ) ) );
				qDebug() << "index" << QString::number( sendList.indexOf( lastBit ) );
				m_checkIndex = true;
				sendToClient( qb );
			}
		}
	}
	if ( json.contains( "play_file" ) )
	{
		m_socket = qobject_cast< QTcpSocket* >( sender() );
		if ( m_socket == nullptr ) { return; }
		for ( auto& readers: m_readers )
		{
			if ( readers->active() )
			{
//				m_dstream.setDevice( &readers->file() );

				QStringList parts = readers->file().fileName().split("/");
				QString lastBit = parts.at( parts.size()-1 );

				if ( readers->fileList().contains( lastBit + ".txt" ) && !readers->indexDebug() )
				{
					QFile file_txt( readers->file().fileName() + ".txt" );
					file_txt.open( QIODevice::ReadOnly );
					QByteArray qb_txt;
					qb_txt = file_txt.readAll();

					auto socket = m_servers.value( readers->id() )->tcpSocket();
					m_servers.value( readers->id() )->port();
					if ( socket->state() == QTcpSocket::ConnectedState )
					{
						qDebug() << "send txt file size: " << m_socket->write( qb_txt );
					}
				}

				if ( readers->fileList().contains( lastBit + ".index" ) && !readers->indexDebug() )
				{
					auto qb = readers->fillingJsonObject( "indexing_hide_elements", "false" );
					sendToClient( qb );
					m_checkIndex = true;
					auto a = readers->readCreateIndex();
					readers->setHash( a );
				}

				if ( !m_checkIndex )
				{
					auto qb = readers->fillingJsonObject( "indexing_hide_elements", "true" );
					sendToClient( qb );
					readFile();
				}
				else
				{
					QByteArray  ba;
					QDataStream ds( &ba, QIODevice::WriteOnly );
					for( auto& hashIndex : readers->hash() )
					{
						ds << hashIndex;
						if ( readers->idxFile().isWritable() )
						{
							if ( readers->dirWriteAble() )
							{
								qDebug() << "size1: " << readers->idxFile().size();
								readers->idxFile().write( ba );
								qDebug() << "size2: " << readers->idxFile().size();
							}
						}
					}
					if ( !readers->indexDebug() )
					{
						readers->shiftFile( 0 );
						readFile();
					}
					else
					{
						qDebug() << "m_file.pos()" << readers->file().pos();
						readers->shiftFile( static_cast< int > ( readers->file().pos() ) );
						readFile();
					}
				}
			}
		}
	}
	if ( json.contains( "debugging" ) )
	{
		for ( auto& readers: m_readers )
		{
			if ( readers->active() )
			{
				readers->timerMarks()->stop();
				readers->timerAdsb()->stop();
				readers->debugEvent();
			}
		}
	}

	if ( json.contains( "offset_slider" ) )
	{
		for ( auto& readers: m_readers )
		{
			if ( readers->active() )
			{
				qDebug() << "offset_slider" << json.value( "offset_slider" ).toString().toInt();
				readers->shiftFile( json.value( "offset_slider" ).toString().toInt() );
			}
		}
	}

	if ( json.contains( "stop_file" ) )
	{
		for ( auto& readers: m_readers )
		{
			if ( readers->active() )
			{
				m_checkIndex = false;
				readers->setActive( false );
				readers->dstream().device()->reset();
				readers->file().close();
				readers->timerMarks()->stop();
				readers->timerAdsb()->stop();
				auto qb = readers->fillingJsonObject( "value_slider", QString::number( 0 ) );
				sendToClient( qb );
			}
		}
	}

	if ( json.contains( "boost_read" ) )
	{
		for ( auto& readers: m_readers )
		{
			if ( readers->active() )
			{
				readers->setBoostRead( json.value( "boost_read" ).toString().toInt() );
			}
		}
	}

	if ( json.contains( "time_offset" ) )
	{
		QTime valueTime;
		for ( auto& readers: m_readers )
		{
			if ( readers->active() )
			{
				readers->setTimeOffset( valueTime.fromString( json.value( "time_offset" ).toString() ).second() );
			}
		}
	}

	if ( json.contains( "coordinate_offset" ) )
	{
		for ( auto& readers: m_readers )
		{
			if ( readers->active() )
			{
				readers->setCoordinateOffset( json.value( "coordinate_offset" ).toString().toInt() );
			}
		}
	}
} // Player::readQByteArray


void Player::readFile()
{
	for ( auto& readers: m_readers )
	{
		if ( readers->active() )
		{
			auto socket = m_servers.value( readers->id() )->tcpSocket();
			m_servers.value( readers->id() )->port();

			readers->readFromFileTimer();

			if ( readers->returnValue().second != nullptr && m_socket != nullptr )
			{
				qDebug() << "send size: " << m_socket->write( readers->returnValue().second );
			}
			qDebug() << socket->state() << m_servers.value( readers->id() )->port() << readers->id();
			if ( socket->state() == QTcpSocket::ConnectedState )
			{
				qDebug() << "send to primary marks size: " << readers->returnValue().first << socket->write( readers->returnValue().first );
			}
		}
	}
} // Player::readFile


void Player::sendToClient( QByteArray qb )
{
	auto* client = qobject_cast< QTcpSocket* >( sender() );
	if ( client == nullptr )
	{
		qDebug() << client;
		return;
	}
	qDebug() << "send size: " << client->write( qb );
	client->flush();
} // Player::sendToClient

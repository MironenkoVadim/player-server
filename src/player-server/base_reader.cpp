#include "base_reader.hpp"

/*QByteArray*/QString BaseReader::checkDir( QString path )
{
	m_fileList.clear();
	bool  checkExec { true };
	QDir dir( QString( "%1/" )
			  .arg( path ) );
	if ( !dir.exists() )
	{
		qWarning( "The directory does not exist" );
		checkExec = false;
	}
	if ( dir.Writable )
	{
		setDirWriteAble( true );
	}

	QByteArray result;
	result.clear();
	QString str;
	str.clear();

	if ( checkExec )
	{
		dir.setFilter( QDir::Files | QDir::AllDirs );
		dir.setSorting( QDir::Size | QDir::Reversed );
		QFileInfoList list = dir.entryInfoList();

		int max_size = 0;
		for ( auto& finfo : list )
		{
			QString name = finfo.fileName();
			int size     = name.size();

			if ( size > max_size )
			{
				max_size = size;
			}
		}

		for ( int i( 0 ); i < list.size(); ++i )
		{
			QFileInfo fileInfo = list.at( i );
//			/*QString*/ str        = fileInfo.fileName();
			str.append( fileInfo.fileName() );
			m_fileList += fileInfo.fileName();
			str.append( "|" );

			result.append( str.toUtf8() );
			result.append( "|" );
		}
	}
	qDebug() << "str" << str;
//	auto qbN = fillingJsonObject( "get_directory", str );
	return str;
} // Server::checkServer


void BaseReader::shiftFile( int _value )
{
	if ( !m_indexDebug )
	{
		qDebug() << "_value" << _value << ( _value * ( m_number / 100.0 ) );
		auto tmpPair = m_hash.value( static_cast< int >( _value * ( std::max_element( m_hash.begin() , m_hash.end()).key() / 100 ) ) );
		m_file.seek( tmpPair.second );
		m_dstream.setDevice( &m_file );
	}
	qDebug() << "position: " << m_file.pos();
}


void BaseReader::debugEvent()
{
	for ( const auto& pairH : m_hash )
	{
		if ( pairH.second == m_file.pos() )
		{
			m_file.seek( m_file.pos() );
			m_indexDebug = true;
		}
	}
}


QByteArray BaseReader::fillingJsonObject( QString key, QString value )
{
	QJsonObject json;
	json[key] = value;
	QJsonDocument jdoc( json );
	qDebug() << "jdoc" << jdoc;
	QByteArray ja( jdoc.toBinaryData() );
	QByteArray result;
	result.clear();
	result.append( ja );
	return result;
}

QByteArray BaseReader::fillingJsonObject( QStringList key, QStringList value )
{
	QByteArray result;
	result.clear();
	QJsonDocument jsonDoc;
	QJsonObject json;
	for( int i( 0 ); i < key.size(); i++ )
	{
		json[ key[ i ] ] = value[ i ];
	}
	jsonDoc.setObject( json );
	QByteArray ja( jsonDoc.toBinaryData() );
	result.append( ja );
	return result;
}

QPair< QByteArray, QByteArray > BaseReader::returnValue()
{
    return m_returnValue;
}

void BaseReader::setReturnValue( const QPair< QByteArray, QByteArray > &returnValue )
{
	m_returnValue = returnValue;
}

QTimer* BaseReader::timerMarks()
{
	return &m_timerMarks;
}

QTimer* BaseReader::timerAdsb()
{
	return &m_timerAdsb;
}

int BaseReader::boostRead()
{
	return m_boostRead;
}

void BaseReader::setBoostRead(int boostRead)
{
	m_boostRead = boostRead;
}

QHash<int, QPair<VTC::TimeSpec64, int> >& BaseReader::hash()
{
	return m_hash;
}

void BaseReader::setHash(const QHash<int, QPair<VTC::TimeSpec64, int> > &hash)
{
	m_hash = hash;
}

QDataStream& BaseReader::dstream()
{
	return m_dstream;
}


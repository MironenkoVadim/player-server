#include "surok_marks_server.hpp"

SurokMarksServer::SurokMarksServer()
{
//	m_server = new QTcpServer();
	setPort( 7222 );
	if ( !server()->listen( QHostAddress::Any, port() ) )
	{
		qDebug() << "Server error. Unable to start the server:" << server()->errorString();
		server()->close();
		return;
	}
	else
	{
		qDebug() << "Server is running on mark";
		qDebug() << port();
	}
	connect( server(), &QTcpServer::newConnection, this, &SurokMarksServer::newConnection );
//	server()->close();
}


void SurokMarksServer::newConnection()
{
	qDebug() << "Marks client connected!";
	QTcpSocket* socket = server()->nextPendingConnection();
	setTcpSocket( socket );
	if ( tcpSocket() == nullptr ) { return; }
	connect( tcpSocket(), static_cast< void ( QTcpSocket::* )( QTcpSocket::SocketError ) >( &QTcpSocket::error ),
				 this, &SurokMarksServer::clientMarksError );
	connect( tcpSocket(), &QTcpSocket::disconnected, this, &SurokMarksServer::disconnectClient );
} // SurokMarksServer::newConnection


void SurokMarksServer::clientMarksError( QAbstractSocket::SocketError socketError )
{
	Q_UNUSED( socketError )
	auto* client = qobject_cast< QTcpSocket* >( sender() );
	if ( client == nullptr ) { return; }
	client->disconnectFromHost();
}


void SurokMarksServer::disconnectClient()
{
	qCritical() << "disconnect Marks client";
	auto* client = qobject_cast< QTcpSocket* >( sender() );
	if ( client == nullptr ) { return; }
	client->deleteLater();
}


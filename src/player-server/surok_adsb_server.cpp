#include "surok_adsb_server.hpp"


SurokAdsbServer::SurokAdsbServer()
{
//	m_server = new QTcpServer();
	setPort( 7701 );
	if ( !server()->listen( QHostAddress::Any, port() ) )
	{
		qDebug() << "Server error. Unable to start the server:" << server()->errorString();
		server()->close();
		return;
	}
	else
	{
		qDebug() << "Server is running on adsb";
		qDebug() << port();
	}
	connect( server(), &QTcpServer::newConnection, this, &SurokAdsbServer::newConnection );
//	server()->close();
	udpSocket()->bind( QHostAddress::LocalHost, port() );
	connect( udpSocket(), &QUdpSocket::readyRead, this, &SurokAdsbServer::newConnection );
}


void SurokAdsbServer::newConnection()
{
	qDebug() << "Adsb client connected!";
	QTcpSocket* socket = server()->nextPendingConnection();
	setTcpSocket( socket );
	if ( tcpSocket() == nullptr ) { return; }
	connect( tcpSocket(), static_cast< void ( QTcpSocket::* )( QTcpSocket::SocketError ) >( &QTcpSocket::error ),
				 this, &SurokAdsbServer::clientMarksError );
	connect( tcpSocket(), &QTcpSocket::disconnected, this, &SurokAdsbServer::disconnectClient );

	setKey( FileFormat::SurokAdsb );
} // SurokAdsbServer::newConnection


void SurokAdsbServer::clientMarksError( QAbstractSocket::SocketError socketError )
{
	Q_UNUSED( socketError )
	auto* client = qobject_cast< QTcpSocket* >( sender() );
	if ( client == nullptr ) { return; }
	client->disconnectFromHost();
}


void SurokAdsbServer::disconnectClient()
{
	qCritical() << "disconnect Adsb client";
	auto* client = qobject_cast< QTcpSocket* >( sender() );
	if ( client == nullptr ) { return; }
	client->deleteLater();
}

QTcpSocket *SurokAdsbServer::socketAdsb()
{
	return m_socketAdsb;
}

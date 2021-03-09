#include "base_server.hpp"


BaseServer::BaseServer()
{
	m_server = new QTcpServer();
	m_udpSocket = new QUdpSocket();
	m_tcpSocket = new QTcpSocket();
}


QTcpServer *BaseServer::server()
{
	return m_server;
}


QUdpSocket *BaseServer::udpSocket()
{
	return m_udpSocket;
}


quint16 BaseServer::port() const
{
	return m_port;
}


void BaseServer::setPort( const quint16 &port )
{
	m_port = port;
}


QString BaseServer::host() const
{
	return m_host;
}


void BaseServer::setHost( const QString &host )
{
	m_host = host;
}

FileFormat BaseServer::key()
{
	return m_key;
}

void BaseServer::setKey(const FileFormat &key)
{
	m_key = key;
}

void BaseServer::setTcpSocket( QTcpSocket *tcpSocket )
{
	m_tcpSocket = tcpSocket;
}

QTcpSocket *BaseServer::tcpSocket()
{
	return m_tcpSocket;
}


BaseServer::~BaseServer()
{
	if ( m_server ) { m_server->deleteLater(); }
	if ( m_udpSocket ) { m_udpSocket->deleteLater(); }
	if ( m_tcpSocket ) { m_tcpSocket->deleteLater(); }
}

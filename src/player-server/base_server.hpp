#ifndef BASE_SERVER_HPP_
#define BASE_SERVER_HPP_

#pragma once

#include <cstdint>

#include "file_format.hpp"

#include <QString>
#include <QTcpServer>

#include <QUdpSocket>
#include <QTcpSocket>
#include <QDataStream>

class BaseServer : public QObject
{
	Q_OBJECT

public:
	BaseServer();
	BaseServer( const BaseServer& ) = delete;
	BaseServer& operator =( const BaseServer& ) = delete;
	virtual ~BaseServer() = 0;

	QTcpServer* server();
	QUdpSocket* udpSocket();
	QTcpSocket *tcpSocket();

	quint16 port() const;
	void setPort( const quint16 &port );

	QString host() const;
	void setHost( const QString &host );

	FileFormat key();
	void setKey( const FileFormat &key );

	void setTcpSocket( QTcpSocket *tcpSocket );

private:
	FileFormat  m_key;
	QString     m_host;
	quint16     m_port { 0 };

	/*QList< QTcpSocket* >*/ QTcpSocket* m_tcpSocket { nullptr };
	QUdpSocket* m_udpSocket { nullptr };

	QTcpServer* m_server { nullptr };
};


#endif // ifndef BASE_SERVER_HPP_

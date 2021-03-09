#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#pragma once

#include "base_reader.hpp"
#include "base_server.hpp"
#include "file_format.hpp"

#include <veer/protocols/preproc/marks_packet.hpp>
#include <veer/protocols/tracking/adsb_tracks_packet.hpp>

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMultiHash>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

namespace VTC = veer::types::common;

class Player : public QObject
{
	Q_OBJECT

	using MarksData      = veer::protocols::preproc::MarksData;
	using SpectrumData      = veer::protocols::preproc::SpectrumsData;
	using AdsbTracksData = veer::protocols::tracking::AdsbTracksData;

public:
	Player();
	BaseReader* createReader( FileFormat id );
	BaseServer* createServer( FileFormat id );

	Q_SLOT void newConnection();
	Q_SLOT void disconnectClient();
	Q_SLOT void readClient();

	void readQByteArray( QByteArray ba );
	void readFile();
	void sendToClient( QByteArray qb );

	bool        m_checkIndex { false };
	QTimer      m_timer;

	QString     m_dirName{ "" };
	QList < QMultiHash < int, QPair< VTC::TimeSpec64, int > > > m_listHashIndex;

	QTcpSocket*                      m_socket;
	QTcpServer*                      m_server;

	QHash< FileFormat, BaseReader* > m_readers;
	QHash< FileFormat, BaseServer* > m_servers;
}; // class Player

#endif // ifndef PLAYER_HPP_

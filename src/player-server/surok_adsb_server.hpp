#ifndef SUROK_ADSB_SERVER_HPP_
#define SUROK_ADSB_SERVER_HPP_

#pragma once

#include "base_server.hpp"
//#include "player.hpp"
#include <veer/protocols/tracking/adsb_tracks_packet.hpp>

#include <cstdint>

#include <QString>

namespace VPT = veer::protocols::tracking;

class SurokAdsbServer : public BaseServer
{
public:
	SurokAdsbServer();
	Q_SLOT void newConnection();
	Q_SLOT void clientMarksError( QAbstractSocket::SocketError );
	Q_SLOT void disconnectClient();
//	Q_SIGNAL void connectAdsbEvent();
	QTcpSocket *socketAdsb();

private:
	//	Player*     m_player { nullptr };
	QTcpSocket* m_socketAdsb { nullptr };
};


#endif // ifndef SUROK_ADSB_SERVER_HPP_

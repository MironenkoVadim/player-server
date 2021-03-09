#ifndef SUROK_MARKS_SERVER_HPP_
#define SUROK_MARKS_SERVER_HPP_

#pragma once

#include "base_server.hpp"
//#include "player.hpp"
#include <cstdint>

#include <QString>

class SurokMarksServer : public BaseServer
{
public:
	SurokMarksServer();
	Q_SLOT void newConnection();
	Q_SLOT void clientMarksError( QAbstractSocket::SocketError );
	Q_SLOT void disconnectClient();
//	Q_SIGNAL void connectMarkEvent();
private:
//	Player*     m_player { nullptr };
};


#endif // ifndef SUROK_MARKS_SERVER_HPP_

#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#pragma once

#include "player.hpp"
#include "surok_marks_server.hpp"
#include "surok_adsb_server.hpp"


class Application
{
public:
	Application();
	~Application();
	void startProcess();

private:
	Player*     m_player { nullptr };
	void readSettings();
};


#endif // ifndef APPLICATION_HPP_

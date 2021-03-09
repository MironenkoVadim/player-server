#include "application.hpp"
#include "cmlib_private_config.hpp"
#include "player.hpp"

#include <myx/filesystem/paths.hpp>

#include <QSettings>

namespace MF = myx::filesystem;

Application::Application()
{
}


Application::~Application()
{
	if ( m_player ) { m_player->deleteLater(); }
}


void Application::startProcess()
{
	readSettings();
	m_player = new Player();
}


void Application::readSettings()
{
	MF::Paths& paths = MF::Paths::instance();
	paths.init( CMLIB_PROJECT_NAME, QStringLiteral( "conf" ) );

	auto* settings = new QSettings( paths.configFilePath(), QSettings::IniFormat );

	settings->sync();
	settings->deleteLater();
}

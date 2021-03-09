#include "application.hpp"
#include "cmlib_private_config.hpp"

#include <myx/qt/translators.hpp>
#include <myx/backports/qt/common.hpp>

#include <QCoreApplication>
#include <QSettings>

namespace MQ = myx::qt;

int main( int argc, char* argv[] )
{
	QCoreApplication app( argc, argv );

	QCoreApplication::setOrganizationName( QStringLiteral( CMLIB_ORGANIZATION_NAME ) );
	QCoreApplication::setApplicationName( QStringLiteral( CMLIB_PROJECT_NAME ) );
	QCoreApplication::setApplicationVersion( QStringLiteral( PLAYER_SERVER_VERSION_STR ) );

	MQ::QTranslatorsList tl;
	MQ::append_translators( tl, CMLIB_PROJECT_NAME );

	Application application;
	application.startProcess();

	return( app.exec() );
} // main

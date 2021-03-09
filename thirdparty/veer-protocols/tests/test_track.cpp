#include "test_track.hpp"

#include <veer/protocols/tracking/base_track.hpp>

#include <QDebug>

namespace C   = veer::common;
namespace TC  = veer::types::common;
namespace TT  = veer::types::tracking;
namespace PB  = veer::protocols::base;
namespace PBC = veer::protocols::base::constants;
namespace PT  = veer::protocols::tracking;
//namespace PTC = veer::protocols::tracking::constants;

void TestTrack::testTarget()
{
	QByteArray  data;
	QDataStream ds( &data, QIODevice::ReadWrite );
	PT::Target  inTarget;

	QVERIFY( inTarget.number()       == UINT16_MAX );
	QVERIFY( inTarget.type()         == TT::TargetType::Undefined );
	QVERIFY( std::isnan( inTarget.position().x() ) );
	QVERIFY( std::isnan( inTarget.position().y() ) );
	QVERIFY( std::isnan( inTarget.position().h() ) );
	QVERIFY( std::isnan( inTarget.velocity().x() ) );
	QVERIFY( std::isnan( inTarget.velocity().y() ) );
	QVERIFY( std::isnan( inTarget.velocity().h() ) );
	QVERIFY( std::isnan( inTarget.acceleration() ) );

	inTarget.setNumber( 111 );
	inTarget.setType( TT::TargetType::CruiseMissile );
	inTarget.setPosition( { 6, 5, 4 } );
	inTarget.setVelocity( { 1, 2, 3 } );
	inTarget.setAcceleration( 9 );

	// Запись в поток и сброс указателя на начало потока для последующего чтения
	ds << inTarget;
	ds.device()->reset();

	PT::Target outTarget;

	outTarget.setNumber( 33 );
	outTarget.setType( TT::TargetType::Airplane );
	outTarget.setPosition( { 5, 6, 7 } );
	outTarget.setVelocity( { 9, 8, 7 } );
	outTarget.setAcceleration( 2 );

	QVERIFY( outTarget.number()       == 33 );
	QVERIFY( outTarget.type()         == TT::TargetType::Airplane );
	QVERIFY( outTarget.position()     == TC::CartesianPoint3F( 5, 6, 7 ) );
	QVERIFY( outTarget.velocity()     == TC::CartesianVelocity( 9, 8, 7 ) );
	QVERIFY( outTarget.acceleration() == 2 );

	// Чтение из потока
	#if QT_VERSION >= 50700
	ds.startTransaction();
	#endif
	ds >> outTarget;
	#if QT_VERSION >= 50700
	if ( !ds.commitTransaction() ) { QFAIL( "Can't read from QDataStream" ); }
	#endif

	QVERIFY( inTarget.number()       == outTarget.number() );
	QVERIFY( inTarget.type()         == outTarget.type() );
	QVERIFY( inTarget.position()     == outTarget.position() );
	QVERIFY( inTarget.velocity()     == outTarget.velocity() );
	QVERIFY( inTarget.acceleration() == outTarget.acceleration() );
} // TestTrack::testTarget


void TestTrack::testBaseTrack()
{
	QByteArray  data;
	QDataStream ds( &data, QIODevice::ReadWrite );
	PT::BaseTrack inTrack;

	QVERIFY( inTrack.number()             == UINT32_MAX );
	QVERIFY( inTrack.externalNumber()     == UINT16_MAX );
	QVERIFY( inTrack.formingTime()        == TC::TimeSpec64( 0 ) );
	QVERIFY( inTrack.captureTime()        == TC::TimeSpec64( 0 ) );
	QVERIFY( inTrack.trackingTime()       == TC::TimeSpec64( 0 ) );
	QVERIFY( inTrack.trackingSteps()      == UINT16_MAX );
	QVERIFY( inTrack.confirmationsCount() == UINT16_MAX );
	QVERIFY( inTrack.missesCount()        == UINT8_MAX );
	QVERIFY( inTrack.trackingCode()       == UINT8_MAX );
	QVERIFY( inTrack.infoSources()        == TT::InfoSources::Undefined );
	QVERIFY( inTrack.maneuverType()       == TT::ManeuverType::Lack );
	QVERIFY( inTrack.trackStatus()        == TT::TrackStatus::Reset );
} // TestTrack::testBaseTrack


QTEST_MAIN( TestTrack )

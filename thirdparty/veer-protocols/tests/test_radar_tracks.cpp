//-V::550,2008

#include "test_radar_tracks.hpp"

#include <veer/protocols/tracking/radar_tracks_packet.hpp>

#include <QDebug>

namespace C   = veer::common;
namespace TC  = veer::types::common;
namespace TT  = veer::types::tracking;
namespace PB  = veer::protocols::base;
namespace PBC = veer::protocols::base::constants;
namespace PT  = veer::protocols::tracking;
namespace PTC = veer::protocols::tracking::constants;


void TestRadarTracks::testRadarTracksHeaderPack()
{
	QByteArray  data;
	QDataStream ds( &data, QIODevice::ReadWrite );
	PT::Target  t;

	PT::RadarTracksPacketHeader tracksIn;

	// Проверка инициализации по умолчанию
	QVERIFY( tracksIn.marker()      == PBC::HeaderMarker );
	QVERIFY( tracksIn.baseVersion() == PTC::RadarTracksPacketVersion );
	QVERIFY( tracksIn.type()        == TC::CodogramType::RadarTracksPack );
	QVERIFY( tracksIn.size()        == sizeof( PT::RadarTracksPacketHeader ) );
	QVERIFY( tracksIn.dataSize()    == sizeof( PT::RadarTracksPacketHeader ) - sizeof( PB::Header ) );

//	tracksIn.setPeriodsCount( 4096 );
//	tracksIn.setPeriodTime( 1e-6f );
//	tracksIn.setSendingTime();
//	tracksIn.setCycleNumber( 121212 );
//	tracksIn.setEmissionDirection( TR::EmissionDirection::First | TR::EmissionDirection::Second );
//	tracksIn.setEmissionPattern( TR::EmissionPattern::Cycling42 );
//	tracksIn.setZonesCount( 2 );

//	TR::ControlZone nearZone;
//	nearZone.setNumber( 0 );
//	nearZone.setMarksCount( 2 );
//	nearZone.setNearEdge( 2.0f );
//	nearZone.setFarEdge( 20.0f );
//	nearZone.setCarrier( 56.042e6f );
//	nearZone.setVelocityLimit( 400 );
//	nearZone.setDeviation( 0.2e6 );
//	nearZone.setSnr( 90 );

//	std::array< PP::Mark, 2 > nearZoneMarks;

//	nearZoneMarks[0].setPosition( rp );
//	nearZoneMarks[0].setVelocity( TC::DopplerVelocity( 1 ) );
//	nearZoneMarks[0].setPositionStdDev( rp );
//	nearZoneMarks[0].setVelocityStdDev( TC::DopplerVelocity( 1 ) );
//	nearZoneMarks[0].setSnr( 33 );
//	nearZoneMarks[0].setThreshold( 1e-6f );
//	nearZoneMarks[0].setDistanceIndex( 1 );
//	nearZoneMarks[0].setAzimuthIndex( 1 );
//	nearZoneMarks[0].setDopplerIndex( 1 );

//	nearZoneMarks[1].setPosition( rp );
//	nearZoneMarks[1].setVelocity( TC::DopplerVelocity( 2 ) );
//	nearZoneMarks[1].setPositionStdDev( rp );
//	nearZoneMarks[1].setVelocityStdDev( TC::DopplerVelocity( 2 ) );
//	nearZoneMarks[1].setSnr( 33 );
//	nearZoneMarks[1].setThreshold( 1e-6f );
//	nearZoneMarks[1].setDistanceIndex( 2 );
//	nearZoneMarks[1].setAzimuthIndex( 2 );
//	nearZoneMarks[1].setDopplerIndex( 2 );

//	TR::ControlZone farZone;
//	farZone.setNumber( 1 );
//	farZone.setMarksCount( 3 );
//	farZone.setNearEdge( 2.0f );
//	farZone.setFarEdge( 20.0f );
//	farZone.setCarrier( 56.042e6f );
//	farZone.setVelocityLimit( 400 );
//	farZone.setDeviation( 0.2e6 );
//	farZone.setSnr( 90 );

//	std::array< PP::Mark, 3 > farZoneMarks;

//	farZoneMarks[0].setPosition( rp );
//	farZoneMarks[0].setVelocity( TC::DopplerVelocity( 3 ) );
//	farZoneMarks[0].setPositionStdDev( rp );
//	farZoneMarks[0].setVelocityStdDev( TC::DopplerVelocity( 3 ) );
//	farZoneMarks[0].setSnr( 33 );
//	farZoneMarks[0].setThreshold( 1e-6f );
//	farZoneMarks[0].setDistanceIndex( 3 );
//	farZoneMarks[0].setAzimuthIndex( 3 );
//	farZoneMarks[0].setDopplerIndex( 3 );

//	farZoneMarks[1].setPosition( rp );
//	farZoneMarks[1].setVelocity( TC::DopplerVelocity( 4 ) );
//	farZoneMarks[1].setPositionStdDev( rp );
//	farZoneMarks[1].setVelocityStdDev( TC::DopplerVelocity( 4 ) );
//	farZoneMarks[1].setSnr( 33 );
//	farZoneMarks[1].setThreshold( 1e-6f );
//	farZoneMarks[1].setDistanceIndex( 4 );
//	farZoneMarks[1].setAzimuthIndex( 4 );
//	farZoneMarks[1].setDopplerIndex( 4 );

//	farZoneMarks[2].setPosition( rp );
//	farZoneMarks[2].setVelocity( TC::DopplerVelocity( 5 ) );
//	farZoneMarks[2].setPositionStdDev( rp );
//	farZoneMarks[2].setVelocityStdDev( TC::DopplerVelocity( 5 ) );
//	farZoneMarks[2].setSnr( 33 );
//	farZoneMarks[2].setThreshold( 1e-6f );
//	farZoneMarks[2].setDistanceIndex( 5 );
//	farZoneMarks[2].setAzimuthIndex( 5 );
//	farZoneMarks[2].setDopplerIndex( 5 );

//	// Запись в поток и сброс указателя на начало потока для последующего чтения
//	ds << tracksIn;
//	ds << nearZone;
//	for ( const auto& m: nearZoneMarks )
//	{
//		ds << m;
//	}

//	ds << farZone;
//	for ( const auto& m: farZoneMarks )
//	{
//		ds << m;
//	}
//	ds << PPC::MarksPacketEndMarker;

//	ds.device()->reset();

//	PP::MarksPacketHeader marksOut;

//	// Полная чистка структуры
//	char* eraser = reinterpret_cast< char* >( &marksOut );
//	memset( eraser, 0, sizeof( marksOut ) );

//	QVERIFY( marksOut.marker()      == 0 );
//	QVERIFY( marksOut.baseVersion() == 0 );
//	QVERIFY( marksOut.type()        == PB::CodogramType::Zero );
//	QVERIFY( marksOut.size()        == sizeof( PB::Header ) );
//	QVERIFY( marksOut.dataSize()    == 0 );

//	// Чтение из потока
//    #if QT_VERSION >= 50700
//	ds.startTransaction();
//    #endif
//	ds >> marksOut;

//	std::vector< std::pair< TR::ControlZone, std::vector< PP::Mark >  > > zones;
//	zones.resize( marksOut.zonesCount() );

//	for ( auto zit = zones.begin(); zit != zones.end(); ++zit )
//	{
//		ds >> zit->first;

//		zit->second.resize( zit->first.marksCount() );
//		for ( auto mit = zit->second.begin(); mit != zit->second.end(); ++mit )
//		{
//			ds >> *mit;
//		}
//	}

//	PP::MarksPacketFooter footer;
//	ds >> footer.endMarker;

//    #if QT_VERSION >= 50700
//	if ( !ds.commitTransaction() ) { QFAIL( "Can't read from QDataStream" ); }
//    #endif

//	// Проверка на соответствие оригиналу
//	QVERIFY( marksOut.marker()      == tracksIn.marker() );
//	QVERIFY( marksOut.baseVersion() == tracksIn.baseVersion() );
//	QVERIFY( marksOut.type()        == tracksIn.type() );
//	QVERIFY( marksOut.size()        == tracksIn.size() );
//	QVERIFY( marksOut.dataSize()    == tracksIn.dataSize() );

//	QVERIFY( zones[0].first.number()        == nearZone.number() );
//	QVERIFY( zones[0].first.marksCount()    == nearZone.marksCount() );
//	QVERIFY( zones[0].first.nearEdge()      == nearZone.nearEdge() );
//	QVERIFY( zones[0].first.farEdge()       == nearZone.farEdge() );
//	QVERIFY( zones[0].first.carrier()       == nearZone.carrier() );
//	QVERIFY( zones[0].first.velocityLimit() == nearZone.velocityLimit() );
//	QVERIFY( zones[0].first.deviation()     == nearZone.deviation() );
//	QVERIFY( zones[0].first.snr()           == nearZone.snr() );

//	QVERIFY( zones[0].second[0].position()       == nearZoneMarks[0].position() );
//	QVERIFY( zones[0].second[0].velocity()       == nearZoneMarks[0].velocity() );
//	QVERIFY( zones[0].second[0].positionStdDev() == nearZoneMarks[0].positionStdDev() );
//	QVERIFY( zones[0].second[0].velocityStdDev() == nearZoneMarks[0].velocityStdDev() );
//	QVERIFY( zones[0].second[0].snr()            == nearZoneMarks[0].snr() );
//	QVERIFY( zones[0].second[0].threshold()      == nearZoneMarks[0].threshold() );
//	QVERIFY( zones[0].second[0].distanceIndex()  == nearZoneMarks[0].distanceIndex() );
//	QVERIFY( zones[0].second[0].azimuthIndex()   == nearZoneMarks[0].azimuthIndex() );
//	QVERIFY( zones[0].second[0].dopplerIndex()   == nearZoneMarks[0].dopplerIndex() );

//	QVERIFY( zones[0].second[1].position()       == nearZoneMarks[1].position() );
//	QVERIFY( zones[0].second[1].velocity()       == nearZoneMarks[1].velocity() );
//	QVERIFY( zones[0].second[1].positionStdDev() == nearZoneMarks[1].positionStdDev() );
//	QVERIFY( zones[0].second[1].velocityStdDev() == nearZoneMarks[1].velocityStdDev() );
//	QVERIFY( zones[0].second[1].snr()            == nearZoneMarks[1].snr() );
//	QVERIFY( zones[0].second[1].threshold()      == nearZoneMarks[1].threshold() );
//	QVERIFY( zones[0].second[1].distanceIndex()  == nearZoneMarks[1].distanceIndex() );
//	QVERIFY( zones[0].second[1].azimuthIndex()   == nearZoneMarks[1].azimuthIndex() );
//	QVERIFY( zones[0].second[1].dopplerIndex()   == nearZoneMarks[1].dopplerIndex() );

//	QVERIFY( zones[1].first.number()        == farZone.number() );
//	QVERIFY( zones[1].first.marksCount()    == farZone.marksCount() );
//	QVERIFY( zones[1].first.nearEdge()      == farZone.nearEdge() );
//	QVERIFY( zones[1].first.farEdge()       == farZone.farEdge() );
//	QVERIFY( zones[1].first.carrier()       == farZone.carrier() );
//	QVERIFY( zones[1].first.velocityLimit() == farZone.velocityLimit() );
//	QVERIFY( zones[1].first.deviation()     == farZone.deviation() );
//	QVERIFY( zones[1].first.snr()           == farZone.snr() );

//	QVERIFY( zones[1].second[0].position()       == farZoneMarks[0].position() );
//	QVERIFY( zones[1].second[0].velocity()       == farZoneMarks[0].velocity() );
//	QVERIFY( zones[1].second[0].positionStdDev() == farZoneMarks[0].positionStdDev() );
//	QVERIFY( zones[1].second[0].velocityStdDev() == farZoneMarks[0].velocityStdDev() );
//	QVERIFY( zones[1].second[0].snr()            == farZoneMarks[0].snr() );
//	QVERIFY( zones[1].second[0].threshold()      == farZoneMarks[0].threshold() );
//	QVERIFY( zones[1].second[0].distanceIndex()  == farZoneMarks[0].distanceIndex() );
//	QVERIFY( zones[1].second[0].azimuthIndex()   == farZoneMarks[0].azimuthIndex() );
//	QVERIFY( zones[1].second[0].dopplerIndex()   == farZoneMarks[0].dopplerIndex() );

//	QVERIFY( zones[1].second[1].position()       == farZoneMarks[1].position() );
//	QVERIFY( zones[1].second[1].velocity()       == farZoneMarks[1].velocity() );
//	QVERIFY( zones[1].second[1].positionStdDev() == farZoneMarks[1].positionStdDev() );
//	QVERIFY( zones[1].second[1].velocityStdDev() == farZoneMarks[1].velocityStdDev() );
//	QVERIFY( zones[1].second[1].snr()            == farZoneMarks[1].snr() );
//	QVERIFY( zones[1].second[1].threshold()      == farZoneMarks[1].threshold() );
//	QVERIFY( zones[1].second[1].distanceIndex()  == farZoneMarks[1].distanceIndex() );
//	QVERIFY( zones[1].second[1].azimuthIndex()   == farZoneMarks[1].azimuthIndex() );
//	QVERIFY( zones[1].second[1].dopplerIndex()   == farZoneMarks[1].dopplerIndex() );

//	QVERIFY( zones[1].second[2].position()       == farZoneMarks[2].position() );
//	QVERIFY( zones[1].second[2].velocity()       == farZoneMarks[2].velocity() );
//	QVERIFY( zones[1].second[2].positionStdDev() == farZoneMarks[2].positionStdDev() );
//	QVERIFY( zones[1].second[2].velocityStdDev() == farZoneMarks[2].velocityStdDev() );
//	QVERIFY( zones[1].second[2].snr()            == farZoneMarks[2].snr() );
//	QVERIFY( zones[1].second[2].threshold()      == farZoneMarks[2].threshold() );
//	QVERIFY( zones[1].second[2].distanceIndex()  == farZoneMarks[2].distanceIndex() );
//	QVERIFY( zones[1].second[2].azimuthIndex()   == farZoneMarks[2].azimuthIndex() );
//	QVERIFY( zones[1].second[2].dopplerIndex()   == farZoneMarks[2].dopplerIndex() );
} // TestRadarTracks::testRadarTracksHeaderPack


void TestRadarTracks::testRadarTracks() // -V2008
{
//	QByteArray  data;
//	QDataStream ds( &data, QIODevice::ReadWrite );
//	TC::RadarPoint3F rp { 41, 42, 43 };

//	PP::MarksData tracksIn;

//	// Проверка инициализации по умолчанию
//	QVERIFY( tracksIn.header().marker()      == PBC::HeaderMarker );
//	QVERIFY( tracksIn.header().baseVersion() == PBC::HeaderInfoVersion );
//	QVERIFY( tracksIn.header().type()        == PB::CodogramType::RadarTracksPack );
//	QVERIFY( tracksIn.header().size()        == sizeof( PP::MarksPacketHeader ) );
//	QVERIFY( tracksIn.header().dataSize()    == sizeof( PP::MarksPacketHeader ) - sizeof( PB::Header ) );

//	tracksIn.header().setPeriodsCount( 4096 );
//	tracksIn.header().setPeriodTime( 1e-6f );
//	tracksIn.header().setSendingTime();
//	tracksIn.header().setCycleNumber( 121212 );
//	tracksIn.header().setEmissionDirection( TR::EmissionDirection::First | TR::EmissionDirection::Second );
//	tracksIn.header().setEmissionPattern( TR::EmissionPattern::Cycling42 );
//	tracksIn.header().setZonesCount( 2 );

//	// Делаем 2 зоны
//	PP::ZonesVector& inZones = tracksIn.zones();
//	inZones.resize( 2 );

//	TR::ControlZone& nearZone = inZones.at( 0 ).first;
//	nearZone.setNumber( 0 );
//	nearZone.setMarksCount( 2 );
//	nearZone.setNearEdge( 2.0f );
//	nearZone.setFarEdge( 20.0f );
//	nearZone.setCarrier( 56.042e6f );
//	nearZone.setVelocityLimit( 400 );
//	nearZone.setDeviation( 0.2e6 );
//	nearZone.setSnr( 90 );

//	std::vector< PP::Mark >& nearZoneMarks = inZones.at( 0 ).second;
//	nearZoneMarks.resize( nearZone.marksCount() );

//	nearZoneMarks[0].setPosition( rp );
//	nearZoneMarks[0].setVelocity( TC::DopplerVelocity( 1 ) );
//	nearZoneMarks[0].setPositionStdDev( rp );
//	nearZoneMarks[0].setVelocityStdDev( TC::DopplerVelocity( 1 ) );
//	nearZoneMarks[0].setSnr( 33 );
//	nearZoneMarks[0].setThreshold( 1e-6f );
//	nearZoneMarks[0].setDistanceIndex( 1 );
//	nearZoneMarks[0].setAzimuthIndex( 1 );
//	nearZoneMarks[0].setDopplerIndex( 1 );

//	nearZoneMarks[1].setPosition( rp );
//	nearZoneMarks[1].setVelocity( TC::DopplerVelocity( 2 ) );
//	nearZoneMarks[1].setPositionStdDev( rp );
//	nearZoneMarks[1].setVelocityStdDev( TC::DopplerVelocity( 2 ) );
//	nearZoneMarks[1].setSnr( 33 );
//	nearZoneMarks[1].setThreshold( 1e-6f );
//	nearZoneMarks[1].setDistanceIndex( 2 );
//	nearZoneMarks[1].setAzimuthIndex( 2 );
//	nearZoneMarks[1].setDopplerIndex( 2 );

//	TR::ControlZone& farZone = tracksIn.zones().at( 1 ).first;
//	farZone.setNumber( 1 );
//	farZone.setMarksCount( 3 );
//	farZone.setNearEdge( 2.0f );
//	farZone.setFarEdge( 20.0f );
//	farZone.setCarrier( 56.042e6f );
//	farZone.setVelocityLimit( 400 );
//	farZone.setDeviation( 0.2e6 );
//	farZone.setSnr( 90 );

//	std::vector< PP::Mark >& farZoneMarks = tracksIn.zones().at( 1 ).second;
//	farZoneMarks.resize( farZone.marksCount() );

//	farZoneMarks[0].setPosition( rp );
//	farZoneMarks[0].setVelocity( TC::DopplerVelocity( 3 ) );
//	farZoneMarks[0].setPositionStdDev( rp );
//	farZoneMarks[0].setVelocityStdDev( TC::DopplerVelocity( 3 ) );
//	farZoneMarks[0].setSnr( 33 );
//	farZoneMarks[0].setThreshold( 1e-6f );
//	farZoneMarks[0].setDistanceIndex( 3 );
//	farZoneMarks[0].setAzimuthIndex( 3 );
//	farZoneMarks[0].setDopplerIndex( 3 );

//	farZoneMarks[1].setPosition( rp );
//	farZoneMarks[1].setVelocity( TC::DopplerVelocity( 4 ) );
//	farZoneMarks[1].setPositionStdDev( rp );
//	farZoneMarks[1].setVelocityStdDev( TC::DopplerVelocity( 4 ) );
//	farZoneMarks[1].setSnr( 33 );
//	farZoneMarks[1].setThreshold( 1e-6f );
//	farZoneMarks[1].setDistanceIndex( 4 );
//	farZoneMarks[1].setAzimuthIndex( 4 );
//	farZoneMarks[1].setDopplerIndex( 4 );

//	farZoneMarks[2].setPosition( rp );
//	farZoneMarks[2].setVelocity( TC::DopplerVelocity( 5 ) );
//	farZoneMarks[2].setPositionStdDev( rp );
//	farZoneMarks[2].setVelocityStdDev( TC::DopplerVelocity( 5 ) );
//	farZoneMarks[2].setSnr( 33 );
//	farZoneMarks[2].setThreshold( 1e-6f );
//	farZoneMarks[2].setDistanceIndex( 5 );
//	farZoneMarks[2].setAzimuthIndex( 5 );
//	farZoneMarks[2].setDopplerIndex( 5 );

//	ds << tracksIn;
//	ds.device()->reset();

//	PP::MarksData marksOut;

//	// Полная чистка структуры
//	char* eraser = reinterpret_cast< char* >( &marksOut );
//	memset( eraser, 0, sizeof( marksOut ) );

//	QVERIFY( marksOut.header().marker()      == 0 );
//	QVERIFY( marksOut.header().baseVersion() == 0 );
//	QVERIFY( marksOut.header().type()        == PB::CodogramType::Zero );
//	QVERIFY( marksOut.header().size()        == sizeof( PB::Header ) );
//	QVERIFY( marksOut.header().dataSize()    == 0 );

//	// Чтение из потока
//    #if QT_VERSION >= 50700
//	ds.startTransaction();
//    #endif

//	ds >> marksOut;

//    #if QT_VERSION >= 50700
//	if ( !ds.commitTransaction() ) { QFAIL( "Can't read from QDataStream" ); }
//    #endif

//	// Проверка на соответствие оригиналу
//	QVERIFY( marksOut.header().marker()      == tracksIn.header().marker() );
//	QVERIFY( marksOut.header().baseVersion() == tracksIn.header().baseVersion() );
//	QVERIFY( marksOut.header().type()        == tracksIn.header().type() );
//	QVERIFY( marksOut.header().size()        == tracksIn.header().size() );
//	QVERIFY( marksOut.header().dataSize()    == tracksIn.header().dataSize() );

//	auto zonesCount = marksOut.header().zonesCount();
//	for ( auto i = 0; i < zonesCount; ++i )
//	{
//		const TR::ControlZone& inZone  = tracksIn.zones().at( i ).first;
//		const TR::ControlZone& outZone = marksOut.zones().at( i ).first;

//		QVERIFY( inZone.number()        == outZone.number() );
//		QVERIFY( inZone.marksCount()    == outZone.marksCount() );
//		QVERIFY( inZone.nearEdge()      == outZone.nearEdge() );
//		QVERIFY( inZone.farEdge()       == outZone.farEdge() );
//		QVERIFY( inZone.carrier()       == outZone.carrier() );
//		QVERIFY( inZone.velocityLimit() == outZone.velocityLimit() );
//		QVERIFY( inZone.deviation()     == outZone.deviation() );
//		QVERIFY( inZone.snr()           == outZone.snr() );

//		auto marksCount = outZone.marksCount();
//		for ( auto j = 0; j < marksCount; ++j )
//		{
//			const PP::Mark& inMark  = tracksIn.zones().at( i ).second.at( j );
//			const PP::Mark& outMark = marksOut.zones().at( i ).second.at( j );

//			QVERIFY( inMark.position()       == outMark.position() );
//			QVERIFY( inMark.velocity()       == outMark.velocity() );
//			QVERIFY( inMark.positionStdDev() == outMark.positionStdDev() );
//			QVERIFY( inMark.velocityStdDev() == outMark.velocityStdDev() );
//			QVERIFY( inMark.snr()            == outMark.snr() );
//			QVERIFY( inMark.threshold()      == outMark.threshold() );
//			QVERIFY( inMark.distanceIndex()  == outMark.distanceIndex() );
//			QVERIFY( inMark.azimuthIndex()   == outMark.azimuthIndex() );
//			QVERIFY( inMark.dopplerIndex()   == outMark.dopplerIndex() );
//		}
//	}
} // TestRadarTracks::testDataStream


QTEST_MAIN( TestRadarTracks )

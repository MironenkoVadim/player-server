//-V::550,2008

#include "test_spectrums.hpp"

#include <veer/types/radar/zone.hpp>
#include <veer/protocols/preproc/spectrums_packet.hpp>

#include <QDebug>

namespace TC  = veer::types::common;
namespace TP  = veer::types::preproc;
namespace TR  = veer::types::radar;
namespace PB  = veer::protocols::base;
namespace PBC = veer::protocols::base::constants;
namespace PP  = veer::protocols::preproc;
namespace PPC = veer::protocols::preproc::constants;


void TestSpectrums::testSpectrums() // -V2008
{
	QByteArray  data;
	QDataStream ds( &data, QIODevice::ReadWrite );
	TC::RadarPoint3F rp { 41, 42, 43 };

	PP::SpectrumsData spectrumsIn;

	// Проверка инициализации по умолчанию
	QVERIFY( spectrumsIn.header().marker()      == PBC::HeaderMarker );
	QVERIFY( spectrumsIn.header().baseVersion() == PBC::HeaderInfoVersion );
	QVERIFY( spectrumsIn.header().type()        == TC::CodogramType::SpectrumsPack );
	QVERIFY( spectrumsIn.header().size()        == sizeof( PP::SpectrumsPacketHeader ) );
	QVERIFY( spectrumsIn.header().dataSize()    == sizeof( PP::SpectrumsPacketHeader ) - sizeof( PB::Header ) );

	spectrumsIn.header().setPeriodsCount( 4096 );
	spectrumsIn.header().setPeriodTime( 1e-6f );
	spectrumsIn.header().setSendingTime();
	spectrumsIn.header().setCycleNumber( 121212 );
	spectrumsIn.header().setEmissionDirection( TR::EmissionDirection::First | TR::EmissionDirection::Second );
	spectrumsIn.header().setEmissionPattern( TR::EmissionPattern::Cycling42 );
	spectrumsIn.header().setZonesCount( 2 );
	spectrumsIn.header().setBlocksCount( 2 );

	// Делаем 2 зоны
	PP::SpectrumsVector& inZones = spectrumsIn.zones();
	inZones.resize( 2 );

	TR::ControlZone& nearZone = std::get< 0 >( inZones.at( 0 ) );
	nearZone.setNumber( 0 );
	nearZone.setMarksCount( 2 );
	nearZone.setSpectrumsCount( 1 );
	nearZone.setNearEdge( 2.0f );
	nearZone.setFarEdge( 20.0f );
	nearZone.setCarrier( 56.042e6f );
	nearZone.setVelocityLimit( 400 );
	nearZone.setDeviation( 0.2e6 );
	nearZone.setSnr( 90 );

	std::vector< TP::Mark >& nearZoneMarks = std::get< 1 >( inZones.at( 0 ) );
	nearZoneMarks.resize( nearZone.marksCount() );

	nearZoneMarks[0].setPosition( rp );
	nearZoneMarks[0].setVelocity( TC::DopplerVelocity( 1 ) );
	nearZoneMarks[0].setPositionStdDev( rp );
	nearZoneMarks[0].setVelocityStdDev( TC::DopplerVelocity( 1 ) );
	nearZoneMarks[0].setSnr( 33 );
	nearZoneMarks[0].setThreshold( 1e-6f );
	nearZoneMarks[0].setDistanceIndex( 1 );
	nearZoneMarks[0].setAzimuthIndex( 1 );
	nearZoneMarks[0].setDopplerIndex( 1 );
	nearZoneMarks[0].setZoneNumber( 1 );

	nearZoneMarks[1].setPosition( rp );
	nearZoneMarks[1].setVelocity( TC::DopplerVelocity( 2 ) );
	nearZoneMarks[1].setPositionStdDev( rp );
	nearZoneMarks[1].setVelocityStdDev( TC::DopplerVelocity( 2 ) );
	nearZoneMarks[1].setSnr( 33 );
	nearZoneMarks[1].setThreshold( 1e-6f );
	nearZoneMarks[1].setDistanceIndex( 2 );
	nearZoneMarks[1].setAzimuthIndex( 2 );
	nearZoneMarks[1].setDopplerIndex( 2 );
	nearZoneMarks[1].setZoneNumber( 1 );

	std::vector< TP::Spectrum >& nearZoneSpectrums = std::get< 2 >( inZones.at( 0 ) );
	nearZoneSpectrums.resize( nearZone.spectrumsCount() );
	nearZoneSpectrums[0].setData( nullptr, 0 );

	TR::ControlZone& farZone = std::get< 0 >( spectrumsIn.zones().at( 1 ) );
	farZone.setNumber( 1 );
	farZone.setMarksCount( 3 );
	farZone.setSpectrumsCount( 2 );
	farZone.setNearEdge( 2.0f );
	farZone.setFarEdge( 20.0f );
	farZone.setCarrier( 56.042e6f );
	farZone.setVelocityLimit( 400 );
	farZone.setDeviation( 0.2e6 );
	farZone.setSnr( 90 );

	std::vector< TP::Mark >& farZoneMarks = std::get< 1 >( spectrumsIn.zones().at( 1 ) );
	farZoneMarks.resize( farZone.marksCount() );

	farZoneMarks[0].setPosition( rp );
	farZoneMarks[0].setVelocity( TC::DopplerVelocity( 3 ) );
	farZoneMarks[0].setPositionStdDev( rp );
	farZoneMarks[0].setVelocityStdDev( TC::DopplerVelocity( 3 ) );
	farZoneMarks[0].setSnr( 33 );
	farZoneMarks[0].setThreshold( 1e-6f );
	farZoneMarks[0].setDistanceIndex( 3 );
	farZoneMarks[0].setAzimuthIndex( 3 );
	farZoneMarks[0].setDopplerIndex( 3 );
	farZoneMarks[0].setZoneNumber( 2 );

	farZoneMarks[1].setPosition( rp );
	farZoneMarks[1].setVelocity( TC::DopplerVelocity( 4 ) );
	farZoneMarks[1].setPositionStdDev( rp );
	farZoneMarks[1].setVelocityStdDev( TC::DopplerVelocity( 4 ) );
	farZoneMarks[1].setSnr( 33 );
	farZoneMarks[1].setThreshold( 1e-6f );
	farZoneMarks[1].setDistanceIndex( 4 );
	farZoneMarks[1].setAzimuthIndex( 4 );
	farZoneMarks[1].setDopplerIndex( 4 );
	farZoneMarks[1].setZoneNumber( 2 );

	farZoneMarks[2].setPosition( rp );
	farZoneMarks[2].setVelocity( TC::DopplerVelocity( 5 ) );
	farZoneMarks[2].setPositionStdDev( rp );
	farZoneMarks[2].setVelocityStdDev( TC::DopplerVelocity( 5 ) );
	farZoneMarks[2].setSnr( 33 );
	farZoneMarks[2].setThreshold( 1e-6f );
	farZoneMarks[2].setDistanceIndex( 5 );
	farZoneMarks[2].setAzimuthIndex( 5 );
	farZoneMarks[2].setDopplerIndex( 5 );
	farZoneMarks[2].setZoneNumber( 2 );

	std::vector< TP::Spectrum >& farZoneSpectrums = std::get< 2 >( inZones.at( 1 ) );
	farZoneSpectrums.resize( farZone.spectrumsCount() );
	std::complex< double > d1[2] = { 1.0, 2.0 };
	farZoneSpectrums[0].setData( d1, sizeof( d1 ) );
	std::complex< double > d2[4] = { 1.0, 2.0, 4.0, -8.0 };
	farZoneSpectrums[1].setData( d2, sizeof( d2 ) );

	ds << spectrumsIn;
	QVERIFY( spectrumsIn.size() == sizeof( PP::SpectrumsPacketHeader ) + sizeof( PP::SpectrumsPacketFooter ) +
	         2 * sizeof( TR::ControlZone ) + ( 2 + 3 ) * sizeof( TP::Mark ) +
	         ( 1 + 2 ) * ( sizeof( TP::Spectrum ) - sizeof( std::complex< double >* ) ) + sizeof( d1 ) + sizeof( d2 ) +
	         2 * ( sizeof( TP::AdaptiveThreshold ) - sizeof( double* ) ) );

	QVERIFY( spectrumsIn.dataSize() == sizeof( PP::SpectrumsPacketHeader ) + sizeof( PP::SpectrumsPacketFooter ) - sizeof( PB::Header ) +
	         2 * sizeof( TR::ControlZone ) + ( 2 + 3 ) * sizeof( TP::Mark ) +
	         ( 1 + 2 ) * ( sizeof( TP::Spectrum ) - sizeof( std::complex< double >* ) ) + sizeof( d1 ) + sizeof( d2 ) +
	         2 * ( sizeof( TP::AdaptiveThreshold ) - sizeof( double* ) ) );

	ds.device()->reset();

	PP::SpectrumsData spectrumsOut;

	// Полная чистка структуры
	char* eraser = reinterpret_cast< char* >( &spectrumsOut );
	memset( eraser, 0, sizeof( spectrumsOut ) );

	QVERIFY( spectrumsOut.header().marker()      == 0 );
	QVERIFY( spectrumsOut.header().baseVersion() == 0 );
	QVERIFY( spectrumsOut.header().type()        == TC::CodogramType::Zero );
	QVERIFY( spectrumsOut.header().size()        == sizeof( PB::Header ) );
	QVERIFY( spectrumsOut.header().dataSize()    == 0 );

	// Чтение из потока
	#if QT_VERSION >= 50700
	ds.startTransaction();
	#endif

	ds >> spectrumsOut;

	#if QT_VERSION >= 50700
	if ( !ds.commitTransaction() ) { QFAIL( "Can't read from QDataStream" ); }
	#endif

	// Проверка на соответствие оригиналу
	QVERIFY( spectrumsOut.header().marker()      == spectrumsIn.header().marker() );
	QVERIFY( spectrumsOut.header().baseVersion() == spectrumsIn.header().baseVersion() );
	QVERIFY( spectrumsOut.header().type()        == spectrumsIn.header().type() );
	QVERIFY( spectrumsOut.header().size()        == spectrumsIn.header().size() );
	QVERIFY( spectrumsOut.header().dataSize()    == spectrumsIn.header().dataSize() );

	auto blocksCount = spectrumsOut.header().blocksCount();
	for ( auto i = 0; i < blocksCount; ++i )
	{
		const TR::ControlZone& inZone  = std::get< 0 >( spectrumsIn.zones().at( i ) );
		const TR::ControlZone& outZone = std::get< 0 >( spectrumsOut.zones().at( i ) );

		QVERIFY( inZone.number()        == outZone.number() );
		QVERIFY( inZone.marksCount()    == outZone.marksCount() );
		QVERIFY( inZone.nearEdge()      == outZone.nearEdge() );
		QVERIFY( inZone.farEdge()       == outZone.farEdge() );
		QVERIFY( inZone.carrier()       == outZone.carrier() );
		QVERIFY( inZone.velocityLimit() == outZone.velocityLimit() );
		QVERIFY( inZone.deviation()     == outZone.deviation() );
		QVERIFY( inZone.snr()           == outZone.snr() );

		auto marksCount = outZone.marksCount();
		for ( auto j = 0; j < marksCount; ++j )
		{
			const TP::Mark& inMark  = std::get< 1 >( spectrumsIn.zones().at( i ) ).at( j );
			const TP::Mark& outMark = std::get< 1 >( spectrumsOut.zones().at( i ) ).at( j );

			QVERIFY( inMark.position()       == outMark.position() );
			QVERIFY( inMark.velocity()       == outMark.velocity() );
			QVERIFY( inMark.positionStdDev() == outMark.positionStdDev() );
			QVERIFY( inMark.velocityStdDev() == outMark.velocityStdDev() );
			QVERIFY( inMark.snr()            == outMark.snr() );
			QVERIFY( inMark.threshold()      == outMark.threshold() );
			QVERIFY( inMark.distanceIndex()  == outMark.distanceIndex() );
			QVERIFY( inMark.azimuthIndex()   == outMark.azimuthIndex() );
			QVERIFY( inMark.dopplerIndex()   == outMark.dopplerIndex() );
			QVERIFY( inMark.zoneNumber()     == outMark.zoneNumber() );
		}

		auto spectrumsCount = outZone.spectrumsCount();
		for ( auto j = 0; j < spectrumsCount; ++j )
		{
			const auto& inSpectum  = std::get< 2 >( spectrumsIn.zones().at( i ) ).at( j );
			const auto& outSpectum = std::get< 2 >( spectrumsOut.zones().at( i ) ).at( j );

			for ( size_t k = 0; k < inSpectum.dataSize() / sizeof( std::complex< double > ); ++k )
			{
				QVERIFY( inSpectum.data()[k] == outSpectum.data()[k] );
			}
		}
	}
} // TestSpectrums::testDataStream


QTEST_MAIN( TestSpectrums )

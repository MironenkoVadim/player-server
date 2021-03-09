#ifndef VEER_PROTOCOLS_PREPROC_QT_SPECTRUMS_PACKET_HPP_
#define VEER_PROTOCOLS_PREPROC_QT_SPECTRUMS_PACKET_HPP_

#pragma once

#include <veer/protocols/preproc/spectrums_packet.hpp>

namespace veer::protocols::preproc {

inline QDataStream& operator<<( QDataStream& ds, const SpectrumsPacketHeader& value )
{
	const VPB::Header& bh { value };
	ds << bh;

	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_version;
	ds << value.m_periodsCount;
	ds << value.m_periodDuration;
	ds << value.m_periodStartTime;
	ds << value.m_sendingTime;
	ds << value.m_cycleNumber;
	ds << value.m_emissionDirection;
	ds << value.m_emissionPattern;
	ds << value.m_zonesCount;
	ds << value.m_blocksCount;
	ds << value.m_samplingFrequency;

	ds.setFloatingPointPrecision( prec );
	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, SpectrumsPacketHeader& value )
{
	VPB::Header& bh { static_cast< VPB::Header& >( value ) };
	ds >> bh;

	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_version;
	ds >> value.m_periodsCount;
	ds >> value.m_periodDuration;
	ds >> value.m_periodStartTime;
	ds >> value.m_sendingTime;
	ds >> value.m_cycleNumber;
	ds >> value.m_emissionDirection;
	ds >> value.m_emissionPattern;
	ds >> value.m_zonesCount;
	ds >> value.m_blocksCount;
	ds >> value.m_samplingFrequency;

	ds.setFloatingPointPrecision( prec );
	return( ds );
} // >>


inline QDataStream& operator<<( QDataStream& ds, SpectrumsData& value )
{
	value.updateSize();
	ds << value.m_header;

	for ( auto& zone: value.m_zones )
	{
		VTR::ControlZone& cz            = std::get< 0 >( zone );
		std::vector< VTP::Mark >& m     = std::get< 1 >( zone );
		std::vector< VTP::Spectrum >& s = std::get< 2 >( zone );
		VTP::AdaptiveThreshold& t       = std::get< 3 >( zone );
		cz.setMarksCount( static_cast< quint16 >( m.size() ) );
		cz.setSpectrumsCount( static_cast< quint16 >( s.size() ) );
		ds << cz;
		for ( const auto& mark: m )
		{
			ds << mark;
		}

		for ( const auto& spectrum: s )
		{
			ds << spectrum;
		}
		ds << t;
	}
	ds << value.m_footer.endMarker;

	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, SpectrumsData& value )
{
	ds >> value.m_header;

	value.m_zones.resize( value.m_header.blocksCount() );
	for ( auto zit = value.m_zones.begin(); zit != value.m_zones.end(); ++zit )
	{
		VTR::ControlZone& cz            = std::get< 0 >( *zit );
		std::vector< VTP::Mark >& m     = std::get< 1 >( *zit );
		std::vector< VTP::Spectrum >& s = std::get< 2 >( *zit );
		VTP::AdaptiveThreshold& t       = std::get< 3 >( *zit );

		ds >> cz;
		m.resize( cz.marksCount() );
		for ( auto mit = m.begin(); mit != m.end(); ++mit )
		{
			ds >> *mit;
		}

		s.resize( cz.spectrumsCount() );
		for ( auto sit = s.begin(); sit != s.end(); ++sit )
		{
			ds >> *sit;
		}
		ds >> t;
	}

	ds >> value.m_footer.endMarker;

	return( ds );
} // >>

} // namespace veer::protocols::preproc


#endif // ifndef VEER_PROTOCOLS_PREPROC_QT_SPECTRUMS_PACKET_HPP_

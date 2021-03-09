#ifndef VEER_PROTOCOLS_TRACKING_QT_MRT_TRACK_HPP_
#define VEER_PROTOCOLS_TRACKING_QT_MRT_TRACK_HPP_

#pragma once

#include <veer/protocols/tracking/mrt_track.hpp>

namespace veer::protocols::tracking {

inline QDataStream& operator<<( QDataStream& ds, const MrtTrack& value )
{
	const BaseTrack& bt { value };
	ds << bt;

	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::DoublePrecision );

	for ( const auto d: value.m_planarCM )
	{
		ds << d;
	}
	for ( const auto d: value.m_heightCM )
	{
		ds << d;
	}

	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );
	ds << value.m_averageSnr;

	ds.setFloatingPointPrecision( prec );

	ds << value.m_adsbInfo;

	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, MrtTrack& value )
{
	BaseTrack& bt { static_cast< BaseTrack& >( value ) };
	ds >> bt;

	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::DoublePrecision );
	for ( auto& d: value.m_planarCM )
	{
		ds >> d;
	}
	for ( auto& d: value.m_heightCM )
	{
		ds >> d;
	}

	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );
	ds >> value.m_averageSnr;

	ds.setFloatingPointPrecision( prec );

	ds >> value.m_adsbInfo;
	return( ds );
} // >>

} // namespace veer::protocols::tracking

#endif // ifndef VEER_PROTOCOLS_TRACKING_QT_MRT_TRACK_HPP_

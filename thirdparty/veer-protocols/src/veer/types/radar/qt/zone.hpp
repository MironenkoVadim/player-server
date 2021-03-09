#ifndef VEER_TYPES_RADAR_QT_ZONE_HPP_
#define VEER_TYPES_RADAR_QT_ZONE_HPP_

#pragma once

#include <veer/types/radar/zone.hpp>

namespace veer::types::radar {

inline QDataStream& operator<<( QDataStream& ds, const ControlZone& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_number;
	ds << value.m_version;
	ds << value.m_marksCount;
	if ( value.m_version >= 3 )
	{
		ds << value.m_spectrumsCount;
		ds << value.m_stub;
	}
	ds << value.m_nearEdge;
	ds << value.m_farEdge;
	ds << value.m_carrier;
	ds << value.m_velocityLimit;
	ds << value.m_deviation;
	ds << value.m_snr;

	if ( value.m_version >= 2 )
	{
		ds << value.m_pulseTime;
		ds << value.m_distanceChannels;
	}

	ds.setFloatingPointPrecision( prec );
	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, ControlZone& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_number;
	ds >> value.m_version;
	ds >> value.m_marksCount;
	if ( value.m_version >= 3 )
	{
		ds >> value.m_spectrumsCount;
		ds >> value.m_stub;
	}
	ds >> value.m_nearEdge;
	ds >> value.m_farEdge;
	ds >> value.m_carrier;
	ds >> value.m_velocityLimit;
	ds >> value.m_deviation;
	ds >> value.m_snr;

	if ( value.m_version >= 2 )
	{
		ds >> value.m_pulseTime;
		ds >> value.m_distanceChannels;
	}

	ds.setFloatingPointPrecision( prec );
	return( ds );
} // >>

} // namespace veer::types::radar

#endif // ifndef VEER_TYPES_QT_RADAR_ZONE_HPP_

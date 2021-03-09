#ifndef VEER_PROTOCOLS_KSA_ALMAZ_QT_RADAR_TRACK_HPP_
#define VEER_PROTOCOLS_KSA_ALMAZ_QT_RADAR_TRACK_HPP_

#pragma once

#include <veer/protocols/ksa/almaz/radar_track.hpp>

namespace veer::protocols::ksa::almaz {

inline QDebug operator<<( QDebug dbg, const RadarTrack value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPKA::RadarTrack: = [";
	dbg << "id = " << value.m_u3.id;
	dbg << "ciPlane = " << value.m_u3.ciPlane;
	dbg << "count = " << value.m_u3.count;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const RadarTrack& value )
{
	const Header& bh { value };
	ds << bh;

	ds << value.m_w3;
	ds << value.m_w4;
	ds << value.m_w5;
	ds << value.m_w6;
	ds << value.m_w7;
	ds << value.m_w8;
	ds << value.m_w9;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, RadarTrack& value )
{
	Header& bh { static_cast< Header& >( value ) };
	ds >> bh;

	ds >> value.m_w3;
	ds >> value.m_w4;
	ds >> value.m_w5;
	ds >> value.m_w6;
	ds >> value.m_w7;
	ds >> value.m_w8;
	ds >> value.m_w9;

	return( ds );
}

} // namespace veer::protocols::ksa::almaz

#endif // ifndef VEER_PROTOCOLS_KSA_ALMAZ_QT_RADAR_TRACK_HPP_

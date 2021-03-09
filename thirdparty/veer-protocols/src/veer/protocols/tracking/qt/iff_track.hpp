#ifndef VEER_PROTOCOLS_TRACKING_IFF_TRACK_HPP_
#define VEER_PROTOCOLS_TRACKING_IFF_TRACK_HPP_

#pragma once

#include <veer/protocols/tracking/iff_track.hpp>

namespace veer::protocols::tracking {

inline QDataStream& operator<<( QDataStream& ds, const IffTrack& value )
{
	const BaseTrack& bt { value };
	ds << bt;
	ds << value.m_iffInfo;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, IffTrack& value )
{
	BaseTrack& bt { static_cast< BaseTrack& >( value ) };
	ds >> bt;
	ds >> value.m_iffInfo;

	return( ds );
}

} // namespace veer::protocols::tracking

#endif // ifndef VEER_PROTOCOLS_TRACKING_QT_IFF_TRACK_HPP_

#ifndef VEER_PROTOCOLS_TRACKING_QT_ADSB_TRACK_HPP_
#define VEER_PROTOCOLS_TRACKING_QT_ADSB_TRACK_HPP_

#pragma once

#include <veer/protocols/tracking/adsb_track.hpp>

namespace veer::protocols::tracking {

inline QDebug operator<<( QDebug dbg, const AdsbTrack& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPT::AdsbTrack: = [";
	dbg << "m_adsbInfo = " << value.m_adsbInfo;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const AdsbTrack& value )
{
	const BaseTrack& bt { value };
	ds << bt;
	ds << value.m_adsbInfo;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, AdsbTrack& value )
{
	BaseTrack& bt { static_cast< BaseTrack& >( value ) };
	ds >> bt;
	ds >> value.m_adsbInfo;

	return( ds );
}

} // namespace veer::protocols::tracking

#endif // ifndef VEER_PROTOCOLS_TRACKING_QT_ADSB_TRACK_HPP_

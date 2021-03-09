#ifndef VEER_TYPES_TRACKING_QT_TRACK_STATUS_HPP_
#define VEER_TYPES_TRACKING_QT_TRACK_STATUS_HPP_

#pragma once

#include <veer/types/tracking/track_status.hpp>

namespace veer::types::tracking {

inline QDebug operator<<( QDebug dbg, const TrackStatus& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTT::TrackStatus: = [";
	dbg << bin << static_cast< int >( value );
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, TrackStatus value )
{
	ds << static_cast< std::underlying_type_t< TrackStatus > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, TrackStatus& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< TrackStatus >( t );
	return ( ds );
}

} // namespace veer::types::tracking

#endif // ifndef VEER_TYPES_TRACKING_QT_TRACK_STATUS_HPP_

#ifndef VEER_TYPES_TRACKING_QT_MANEUVER_TYPE_HPP_
#define VEER_TYPES_TRACKING_QT_MANEUVER_TYPE_HPP_

#pragma once

#include <veer/types/tracking/maneuver_type.hpp>

namespace veer::types::tracking {

inline QDebug operator<<( QDebug dbg, const ManeuverType& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTT::ManeuverType: = [";
	dbg << bin << static_cast< int >( value );
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, ManeuverType value )
{
	ds << static_cast< std::underlying_type_t< ManeuverType > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, ManeuverType& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< ManeuverType >( t );
	return ( ds );
}

} // namespace veer::types::tracking

#endif // ifndef VEER_TYPES_TRACKING_QT_MANEUVER_TYPE_HPP_

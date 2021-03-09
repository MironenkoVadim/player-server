#ifndef VEER_TYPES_TRACKING_QT_TARGET_TYPE_HPP_
#define VEER_TYPES_TRACKING_QT_TARGET_TYPE_HPP_

#pragma once

#include <veer/types/tracking/target_type.hpp>

namespace veer::types::tracking {

inline QDebug operator<<( QDebug dbg, const TargetType& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPT::TargetType: = [";
	dbg << bin << static_cast< int >( value );
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, TargetType value )
{
	ds << static_cast< std::underlying_type_t< TargetType > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, TargetType& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< TargetType >( t );
	return ( ds );
}

} // namespace veer::types::tracking

#endif // ifndef VEER_TYPES_TRACKING_QT_TARGET_TYPE_HPP_

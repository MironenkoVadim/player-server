#ifndef VEER_TYPES_TRACKING_QT_INFO_SOURCES_HPP_
#define VEER_TYPES_TRACKING_QT_INFO_SOURCES_HPP_

#pragma once

#include <veer/types/tracking/info_sources.hpp>

namespace veer::types::tracking {

inline QDebug operator<<( QDebug dbg, const InfoSources& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTT::InfoSources: = [";
	dbg << bin << static_cast< int >( value );
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, InfoSources value )
{
	ds << static_cast< std::underlying_type_t< InfoSources > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, InfoSources& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< InfoSources >( t );
	return ( ds );
}

} // namespace veer::types::tracking

#endif // ifndef VEER_TYPES_TRACKING_QT_INFO_SOURCES_HPP_

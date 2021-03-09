#ifndef VEER_TYPES_RADAR_QT_EMISSION_PATTERN_HPP_
#define VEER_TYPES_RADAR_QT_EMISSION_PATTERN_HPP_

#pragma once

#include <veer/types/radar/emission_pattern.hpp>

namespace veer::types::radar {

inline QDataStream& operator<<( QDataStream& ds, EmissionPattern value )
{
	ds << static_cast< std::underlying_type_t< EmissionPattern > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, EmissionPattern& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< EmissionPattern >( t );
	return ( ds );
}

} // namespace veer::types::radar

#endif // ifndef VEER_TYPES_RADAR_QT_EMISSION_PATTERN_HPP_

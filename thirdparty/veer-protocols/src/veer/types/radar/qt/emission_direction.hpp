#ifndef VEER_TYPES_RADAR_QT_EMISSION_DIRECTION_HPP_
#define VEER_TYPES_RADAR_QT_EMISSION_DIRECTION_HPP_

#pragma once

#include <veer/types/radar/emission_direction.hpp>

namespace veer::types::radar {

inline QDataStream& operator<<( QDataStream& ds, EmissionDirection value )
{
	ds << static_cast< std::underlying_type_t< EmissionDirection > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, EmissionDirection& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< EmissionDirection >( t );
	return ( ds );
}

} // namespace veer::types::radar

#endif // ifndef VEER_TYPES_RADAR_QT_EMISSION_DIRECTION_HPP_

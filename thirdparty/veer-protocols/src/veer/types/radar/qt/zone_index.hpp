#ifndef VEER_TYPES_RADAR_QT_ZONE_INDEX_HPP_
#define VEER_TYPES_RADAR_QT_ZONE_INDEX_HPP_

#pragma once

#include <veer/types/radar/zone_index.hpp>

namespace veer::types::radar {

inline QDataStream& operator<<( QDataStream& ds, ZoneIndex value )
{
	ds << static_cast< std::underlying_type_t< ZoneIndex > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, ZoneIndex& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< ZoneIndex >( t );
	return ( ds );
}

} // namespace veer::types::radar
#endif // ifndef VEER_TYPES_RADAR_QT_ZONE_INDEX_HPP_

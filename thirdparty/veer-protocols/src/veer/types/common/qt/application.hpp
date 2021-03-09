#ifndef VEER_TYPES_COMMON_QT_APPLICATION_HPP_
#define VEER_TYPES_COMMON_QT_APPLICATION_HPP_

#pragma once

#include <veer/types/common/application.hpp>

namespace veer::types::common {

inline QDataStream& operator<<( QDataStream& ds, Application value )
{
	ds << static_cast< std::underlying_type_t< Application > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Application& value )
{
	quint16 t { 0 }; ds >> t; value = static_cast< Application >( t );
	return ( ds );
}

} // namespace veer::types::common


#endif // ifndef VEER_TYPES_COMMON_QT_APPLICATION_HPP_

#ifndef VEER_TYPES_COMMON_QT_CODOGRAM_TYPES_HPP_
#define VEER_TYPES_COMMON_QT_CODOGRAM_TYPES_HPP_

#pragma once

#include <veer/types/common/codogram_type.hpp>

namespace veer::types::common {

inline QDataStream& operator<<( QDataStream& ds, CodogramType value )
{
	ds << static_cast< typename std::underlying_type< CodogramType >::type >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, CodogramType& value )
{
	quint16 t { 0 }; ds >> t; value = static_cast< CodogramType >( t );
	return ( ds );
}

} // namespace veer::types::common

#endif // ifndef VEER_TYPES_COMMON_QT_CODOGRAM_TYPES_HPP_

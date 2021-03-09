#ifndef VEER_TYPES_COMMON_QT_ERROR_CODES_HPP_
#define VEER_TYPES_COMMON_QT_ERROR_CODES_HPP_

#pragma once

#include <veer/types/common/error_codes.hpp>

namespace veer::types::common {

QString errorCodeToQString( ErrorCode value )
{
	static QStringList errorsList =
	{
		"OK",
		"Error"
	};
	auto v = static_cast< typename std::underlying_type< ErrorCode >::type >( value );
	if ( v >= errorsList.size() )
	{
		return( "Error code is not exist" );
	}
	else
	{
		return( errorsList[v] );
	}
}


inline QDataStream& operator<<( QDataStream& ds, ErrorCode value )
{
	ds << static_cast< typename std::underlying_type< ErrorCode >::type >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, ErrorCode& value )
{
	quint16 t { 0 }; ds >> t; value = static_cast< ErrorCode >( t );
	return ( ds );
}

} // namespace veer::types::common


#endif // ifndef VEER_TYPES_COMMON_QT_ERROR_CODES_HPP_

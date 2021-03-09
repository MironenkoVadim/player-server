#ifndef VEER_PROTOCOLS_BASE_QT_ERROR_HPP_
#define VEER_PROTOCOLS_BASE_QT_ERROR_HPP_

#pragma once

#include <veer/protocols/base/error.hpp>

namespace veer::protocols::base {

inline QDataStream& operator<<( QDataStream& ds, const Error& value )
{
	const Header& bh { value };
	ds << bh;

	ds << value.m_version;
	ds << value.m_code;
	ds << value.m_info;
	ds << value.m_errorTime;
	ds << value.m_endMarker;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Error& value )
{
	Header& bh { static_cast< Header& >( value ) };
	ds >> bh;

	ds >> value.m_version;
	ds >> value.m_code;
	ds >> value.m_info;
	ds >> value.m_errorTime;
	ds >> value.m_endMarker;

	return( ds );
}

} // namespace veer::protocols::base

#endif // ifndef VEER_PROTOCOLS_BASE_QT_ERROR_HPP_

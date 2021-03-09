#ifndef VEER_PROTOCOLS_BASE_QT_PING_HPP_
#define VEER_PROTOCOLS_BASE_QT_PING_HPP_

#pragma once

#include <veer/protocols/base/ping.hpp>

namespace veer::protocols::base {

inline QDataStream& operator<<( QDataStream& ds, const PingHeaderless& value )
{
	ds << value.m_version;
	ds << value.m_code;
	ds << value.m_requestTime;
	ds << value.m_endMarker;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, PingHeaderless& value )
{
	ds >> value.m_version;
	ds >> value.m_code;
	ds >> value.m_requestTime;
	ds >> value.m_endMarker;

	return( ds );
}


inline QDataStream& operator<<( QDataStream& ds, const Ping& value )
{
	const Header& bh { value };
	ds << bh;

	ds << value.m_version;
	ds << value.m_code;
	ds << value.m_requestTime;
	ds << value.m_endMarker;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Ping& value )
{
	Header& bh { static_cast< Header& >( value ) };
	ds >> bh;

	ds >> value.m_version;
	ds >> value.m_code;
	ds >> value.m_requestTime;
	ds >> value.m_endMarker;

	return( ds );
}

} // namespace veer::protocols::base

#endif // ifndef VEER_PROTOCOLS_BASE_QT_PING_HPP_

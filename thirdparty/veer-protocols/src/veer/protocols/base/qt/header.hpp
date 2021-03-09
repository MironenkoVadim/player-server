#ifndef VEER_PROTOCOLS_BASE_QT_HEADER_HPP_
#define VEER_PROTOCOLS_BASE_QT_HEADER_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>

namespace veer::protocols::base {

inline QDataStream& operator<<( QDataStream& ds, const Header& value )
{
	ds << value.m_marker;
	ds << value.m_baseVersion;
	ds << value.m_type;
	ds << value.m_source;
	ds << value.m_destination;
	ds << value.m_size;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Header& value )
{
	ds >> value.m_marker;
	ds >> value.m_baseVersion;
	ds >> value.m_type;
	ds >> value.m_source;
	ds >> value.m_destination;
	ds >> value.m_size;

	return( ds );
}

} // namespace veer::protocols::base

#endif // ifndef VEER_PROTOCOLS_BASE_QT_HEADER_HPP_

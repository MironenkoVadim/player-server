#ifndef VEER_PROTOCOLS_AFC_SUROK_QT_TIME_SOURCE_HPP_
#define VEER_PROTOCOLS_AFC_SUROK_QT_TIME_SOURCE_HPP_

#pragma once

#include <veer/protocols/afc/surok/time_source.hpp>

namespace veer::protocols::afc::surok {

inline QDataStream& operator<<( QDataStream& ds, const TimeSource& value )
{
	const VPB::Header& bh { value };
	ds << bh;

	ds << value.m_version;
	ds << value.m_status;
	ds << value.m_color;
	ds << value.m_responseTime;
	ds << value.m_endMarker;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, TimeSource& value )
{
	VPB::Header& bh { static_cast< VPB::Header& >( value ) };
	ds >> bh;

	ds >> value.m_version;
	ds >> value.m_status;
	ds >> value.m_color;
	ds >> value.m_responseTime;
	ds >> value.m_endMarker;

	return( ds );
}

} // namespace veer::protocols::afc::surok

#endif // ifndef VEER_PROTOCOLS_AFC_SUROK_QT_TIME_SOURCE_HPP_

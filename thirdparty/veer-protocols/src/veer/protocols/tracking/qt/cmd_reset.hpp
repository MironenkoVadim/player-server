#ifndef VEER_PROTOCOLS_TRACKING_QT_CMD_RESET_HPP_
#define VEER_PROTOCOLS_TRACKING_QT_CMD_RESET_HPP_

#pragma once

#include <veer/protocols/tracking/cmd_reset.hpp>

namespace veer::protocols::tracking {

inline QDataStream& operator<<( QDataStream& ds, const CmdReset& value )
{
	const VPB::Header& bh { value };
	ds << bh;

	ds << value.m_version;
	ds << value.m_infoSources;
	ds << value.m_stub;
	ds << value.m_number;
	ds << value.m_endMarker;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, CmdReset& value )
{
	VPB::Header& bh { static_cast< VPB::Header& >( value ) };
	ds >> bh;

	ds >> value.m_version;
	ds >> value.m_infoSources;
	ds >> value.m_stub;
	ds >> value.m_number;
	ds >> value.m_endMarker;

	return( ds );
}

} // namespace veer::protocols::tracking
#endif // ifndef VEER_PROTOCOLS_TRACKING_QT_CMD_RESET_HPP_

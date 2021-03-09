#ifndef VEER_PROTOCOLS_TRACKING_QT_CMD_RENUMBER_HPP_
#define VEER_PROTOCOLS_TRACKING_QT_CMD_RENUMBER_HPP_

#pragma once

#include <veer/protocols/tracking/cmd_renumber.hpp>

namespace veer::protocols::tracking {

inline QDataStream& operator<<( QDataStream& ds, const CmdRenumber& value )
{
	const VPB::Header& bh { value };
	ds << bh;

	ds << value.m_version;
	ds << value.m_infoSources;
	ds << value.m_stub;
	ds << value.m_oldNumber;
	ds << value.m_newNumber;
	ds << value.m_endMarker;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, CmdRenumber& value )
{
	VPB::Header& bh { static_cast< VPB::Header& >( value ) };
	ds >> bh;

	ds >> value.m_version;
	ds >> value.m_infoSources;
	ds >> value.m_stub;
	ds >> value.m_oldNumber;
	ds >> value.m_newNumber;
	ds >> value.m_endMarker;

	return( ds );
}

} // namespace veer::protocols::tracking


#endif // ifndef VEER_PROTOCOLS_TRACKING_QT_CMD_RENUMBER_HPP_

#ifndef VEER_PROTOCOLS_CONTROL_QT_RECEIVING_ANTENNA_HPP_
#define VEER_PROTOCOLS_CONTROL_QT_RECEIVING_ANTENNA_HPP_

#pragma once

#include <veer/protocols/control/receiving_antenna.hpp>

namespace veer::protocols::control {

inline QDataStream& operator<<( QDataStream& ds, const ReceivingAntenna& value )
{
	const VPB::Header& bh { value };
	ds << bh;

	ds << value.m_version;
	ds << value.m_stub;
	ds << value.m_position;
	ds << value.m_mainDirection;
	ds << value.m_additionalDirection;
	ds << value.m_endMarker;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, ReceivingAntenna& value )
{
	VPB::Header& bh { static_cast< VPB::Header& >( value ) };
	ds >> bh;

	ds >> value.m_version;
	ds >> value.m_stub;
	ds >> value.m_position;
	ds >> value.m_mainDirection;
	ds >> value.m_additionalDirection;
	ds >> value.m_endMarker;

	return( ds );
}

} // namespace veer::protocols::control

#endif // ifndef VEER_PROTOCOLS_CONTROL_QT_RECEIVING_ANTENNA_HPP_

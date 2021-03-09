#ifndef VEER_PROTOCOLS_CONTROL_GATE_QT_HEADER_HPP_
#define VEER_PROTOCOLS_CONTROL_GATE_QT_HEADER_HPP_

#pragma once

#include <veer/protocols/control/gate/header.hpp>

namespace veer::protocols::control::gate {

inline QDataStream& operator<<( QDataStream& ds, Header value )
{
//	ds.writeRawData( reinterpret_cast< char* >( &value ), sizeof( Header ) );

	ds << value.m_senderId;
	ds << value.m_receiverId;
	ds << value.m_messageTypeId;
	ds << value.m_messageSeqNumber;
	ds << value.m_packetSize;
	ds << value.m_packetNumber;
	ds << value.m_magic;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Header& value )
{
//	ds.readRawData( reinterpret_cast< char* >( &value ), sizeof( Header ) );
	ds >> value.m_senderId;
	ds >> value.m_receiverId;
	ds >> value.m_messageTypeId;
	ds >> value.m_messageSeqNumber;
	ds >> value.m_packetSize;
	ds >> value.m_packetNumber;
	ds >> value.m_magic;

	return( ds );
}

} // namespace veer::protocols::control::gate

#endif // ifndef VEER_PROTOCOLS_CONTROL_GATE_QT_HEADER_HPP_

#ifndef VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_QT_COMMAND_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_QT_COMMAND_HPP_

#pragma once

#include <veer/protocols/control/surok/amplifier/command.hpp>

namespace veer::protocols::control::surok::amplifier {

inline QDataStream& operator<<( QDataStream& ds, const Command& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds << value.m_startMarker;
	ds << value.m_controlFlags;
	ds << value.m_channelFlags;
	ds << value.m_mode;
	ds << value.m_crc;
	ds << value.m_endMarker;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Command& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds >> value.m_startMarker;
	ds >> value.m_controlFlags;
	ds >> value.m_channelFlags;
	ds >> value.m_mode;
	ds >> value.m_crc;
	ds >> value.m_endMarker;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDebug operator<<( QDebug dbg, Command value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSA::Command: = [";
	dbg << "startMarker = " << static_cast< int >( value.m_startMarker );
	dbg << ", controlFlags = " << value.m_controlFlags;
	dbg << ", channelFlags = " << value.m_channelFlags;
	dbg << ", counter = " << static_cast< int >( value.m_bf.counter );
	dbg << ", pattern = " << static_cast< int >( value.m_bf.pattern );
	dbg << ", crc = " << static_cast< int >( value.m_crc );
	dbg << ", endMarker = " << static_cast< int >( value.m_endMarker );
	dbg << "])";

	return( dbg );
}

} // namespace veer::protocols::control::surok::amplifier

#endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_QT_COMMAND_HPP_

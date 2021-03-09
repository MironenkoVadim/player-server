#ifndef VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_QT_COMMAND_HPP_
#define VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_QT_COMMAND_HPP_

#pragma once

#include <veer/protocols/control/gate/receiver/command.hpp>

namespace veer::protocols::control::gate::receiver {

inline QDataStream& operator<<( QDataStream& ds, Mode value )
{
	ds << static_cast< std::underlying_type_t< Mode > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Mode& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< Mode >( t );
	return ( ds );
}


inline QDataStream& operator<<( QDataStream& ds, Flags value )
{
	ds << static_cast< std::underlying_type_t< Flags > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Flags& value )
{
	quint16 t { 0 }; ds >> t; value = static_cast< Flags >( t );
	return ( ds );
}


inline QDataStream& operator<<( QDataStream& ds, FCMode value )
{
	ds << static_cast< std::underlying_type_t< FCMode > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, FCMode& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< FCMode >( t );
	return ( ds );
}


inline QDataStream& operator<<( QDataStream& ds, Command value )
{
//	ds.writeRawData( reinterpret_cast< char* >( &value ), sizeof( Command ) );
	ds << value.m_id;
	ds << value.m_time;
	ds << value.m_mode;
	ds << value.m_flags;
	ds << value.m_fcMode;
	ds << value.m_period;
	ds << value.m_spectr;
	ds << value.m_zsCount;
	ds << value.m_recvCount;
	ds << value.m_isCount;
	ds << value.m_calibrTime;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Command& value )
{
//	ds.readRawData( reinterpret_cast< char* >( &value ), sizeof( Command ) );
	ds >> value.m_id;
	ds >> value.m_time;
	ds >> value.m_mode;
	ds >> value.m_flags;
	ds >> value.m_fcMode;
	ds >> value.m_period;
	ds >> value.m_spectr;
	ds >> value.m_zsCount;
	ds >> value.m_recvCount;
	ds >> value.m_isCount;
	ds >> value.m_calibrTime;

	return( ds );
}

} // namespace veer::protocols::control::gate::receiver

#endif // ifndef VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_QT_COMMAND_HPP_

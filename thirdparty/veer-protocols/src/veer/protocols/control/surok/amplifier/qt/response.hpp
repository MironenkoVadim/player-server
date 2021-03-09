#ifndef VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_QT_RESPONSE_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_QT_RESPONSE_HPP_

#pragma once

#include <veer/protocols/control/surok/amplifier/response.hpp>

namespace veer::protocols::control::surok::amplifier {

inline QDebug operator<<( QDebug dbg, const ChannelResponse value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSA::ChannelResponse: = [";

	dbg << "blockingState = " << value.m_s1.blockingState;
	dbg << ", dummyEmission = " << value.m_s1.dummyEmission;
	dbg << ", emissionState = " << value.m_s1.emissionState;
	dbg << ", powerState = " << value.m_s1.powerState;
	dbg << ", temperatureState = " << value.m_s1.temperatureState;
	dbg << ", bit7 = " << value.m_s1.bit7;
	dbg << ", swr1State = " << value.m_s2.swr1State;
	dbg << ", swr2State = " << value.m_s2.swr2State;
	dbg << ", u48State = " << value.m_s2.u48State;
	dbg << ", emissionChannelState = " << value.m_s2.emissionChannelState;
	dbg << ", zsState = " << value.m_s2.zsState;
	dbg << ", u12State = " << value.m_s2.u12State;

	dbg << ", m_power1 = " << static_cast< int >( value.m_power1 );
	dbg << ", m_power2 = " << static_cast< int >( value.m_power2 );
	dbg << ", m_swr1 = " << static_cast< int >( value.m_swr1 );
	dbg << ", m_swr2 = " << static_cast< int >( value.m_swr2 );
	dbg << ", m_phase1 = " << static_cast< int >( value.m_phase1 );
	dbg << ", m_phase2 = " << static_cast< int >( value.m_phase2 );

	dbg << "])";

	return( dbg );
} // <<


inline QDataStream& operator<<( QDataStream& ds, const ChannelResponse& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds << value.m_state1;
	ds << value.m_state2;
	ds << value.m_power1;
	ds << value.m_power2;
	ds << value.m_swr1;
	ds << value.m_swr2;
	ds << value.m_phase1;
	ds << value.m_phase2;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, ChannelResponse& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds >> value.m_state1;
	ds >> value.m_state2;
	ds >> value.m_power1;
	ds >> value.m_power2;
	ds >> value.m_swr1;
	ds >> value.m_swr2;
	ds >> value.m_phase1;
	ds >> value.m_phase2;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDebug operator<<( QDebug dbg, const Response value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSA::Response: = [";
	dbg << "m_startMarker = " << static_cast< int >( value.m_startMarker );
	dbg << ", remoteControl = " << value.m_c.remoteControl;
	dbg << ", localControl = " << value.m_c.localControl;
	dbg << ", on = " << value.m_c.on;
	dbg << ", off = " << value.m_c.off;
	dbg << ", f1Changed = " << value.m_c.f1Changed;
	dbg << ", f2Changed = " << value.m_c.f2Changed;
	dbg << ", bit6 = " << value.m_c.bit6;
	dbg << ", bit7 = " << value.m_c.bit7;

	dbg << ", uPowerState = " << value.m_s.uPowerState;
	dbg << ", uCMState = " << value.m_s.uCMState;
	dbg << ", zsState = " << value.m_s.zsState;
	dbg << ", bit3 = " << value.m_s.bit3;
	dbg << ", u4CMState = " << value.m_s.u4CMState;
	dbg << ", u4CMB003State = " << value.m_s.u4CMB003State;
	dbg << ", bit6 = " << value.m_s.bit6;
	dbg << ", bit7 = " << value.m_s.bit7;

	//dbg << ", m_channels = " << m_channels;
	dbg << ", m_crc = " << value.m_crc;
	dbg << ", m_endMarker = " << static_cast< int >( value.m_endMarker );
	dbg << "])";

	return( dbg );
} // <<


inline QDataStream& operator<<( QDataStream& ds, const Response& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds << value.m_startMarker;
	ds << value.m_control;
	ds << value.m_state;
	ds << value.m_channels[0];
	ds << value.m_channels[1];
	ds << value.m_channels[2];
	ds << value.m_channels[3];
	ds << value.m_crc;
	ds << value.m_endMarker;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Response& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds >> value.m_startMarker;
	ds >> value.m_control;
	ds >> value.m_state;
	ds >> value.m_channels[0];
	ds >> value.m_channels[1];
	ds >> value.m_channels[2];
	ds >> value.m_channels[3];
	ds >> value.m_crc;
	ds >> value.m_endMarker;

	ds.setByteOrder( bo );
	return( ds );
}

} // namespace veer::protocols::control::surok::amplifier

#endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_QT_RESPONSE_HPP_

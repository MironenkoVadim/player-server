#ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_RESPONSE_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_RESPONSE_HPP_

#pragma once

#include <veer/protocols/control/surok/receiver/response.hpp>

namespace veer::protocols::control::surok::receiver {

inline QDebug operator<<( QDebug dbg, const Response value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::Response: = [";
	dbg << "b0031 = " << value.m_s1.b0031;
	dbg << ", b0032 = " << value.m_s1.b0032;
	dbg << ", b0033 = " << value.m_s1.b0033;
	dbg << ", b0034 = " << value.m_s1.b0034;
	dbg << ", b0035 = " << value.m_s1.b0035;
	dbg << ", b0036 = " << value.m_s1.b0036;
	dbg << ", b002 = " << value.m_s1.b002;
	dbg << ", bus = " << value.m_s1.bus;

	dbg << ", ch1 = " << value.m_s2.ch1;
	dbg << ", ch2 = " << value.m_s2.ch2;
	dbg << ", ch3 = " << value.m_s2.ch3;
	dbg << ", ch4 = " << value.m_s2.ch4;
	dbg << ", ch5 = " << value.m_s2.ch5;
	dbg << ", ch6 = " << value.m_s2.ch6;
	dbg << ", ch7 = " << value.m_s2.ch7;
	dbg << ", ch8 = " << value.m_s2.ch8;

	dbg << ", ch9 = " << value.m_s3.ch9;
	dbg << ", ch10 = " << value.m_s3.ch10;
	dbg << ", ch11 = " << value.m_s3.ch11;
	dbg << ", ch12 = " << value.m_s3.ch12;
	dbg << ", gen = " << value.m_s3.gen;
	dbg << ", reserve = " << value.m_s3.reserve;
	dbg << "])";

	return( dbg );
} // <<


inline QDataStream& operator<<( QDataStream& ds, Response value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds << value.m_code;
	ds << value.m_state1;
	ds << value.m_state2;
	ds << value.m_state3;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Response& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds >> value.m_code;
	ds >> value.m_state1;
	ds >> value.m_state2;
	ds >> value.m_state3;

	ds.setByteOrder( bo );
	return( ds );
}

} // namespace veer::protocols::control::surok::receiver


#endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_RESPONSE_HPP_

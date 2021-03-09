#ifndef VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_QT_RESPONSE_HPP_
#define VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_QT_RESPONSE_HPP_

#pragma once

#include <veer/protocols/control/gate/receiver/response.hpp>


namespace veer::protocols::control::gate::receiver {

inline QDataStream& operator<<( QDataStream& ds, const Response& value )
{
	ds << value.m_state;
	ds << value.m_mode;
	ds << value.m_b001;
	ds << value.m_b0021;
	ds << value.m_b0022;
	ds << value.m_b0031;
	ds << value.m_b0032;
	ds << value.m_b0033;
	ds << value.m_b0034;
	ds << value.m_b0035;
	ds << value.m_b0036;
	ds << value.m_b004;
	ds << value.m_b0051;
	ds << value.m_b0052;
	ds << value.m_b006;
	ds << value.m_additionalAntenna;
	ds << value.m_mainAntenna;

	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, Response& value )
{
	ds >> value.m_state;
	ds >> value.m_mode;
	ds >> value.m_b001;
	ds >> value.m_b0021;
	ds >> value.m_b0022;
	ds >> value.m_b0031;
	ds >> value.m_b0032;
	ds >> value.m_b0033;
	ds >> value.m_b0034;
	ds >> value.m_b0035;
	ds >> value.m_b0036;
	ds >> value.m_b004;
	ds >> value.m_b0051;
	ds >> value.m_b0052;
	ds >> value.m_b006;
	ds >> value.m_additionalAntenna;
	ds >> value.m_mainAntenna;

	return( ds );
} // >>

} // namespace veer::protocols::control::gate::receiver

#endif // ifndef VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_QT_RESPONSE_HPP_

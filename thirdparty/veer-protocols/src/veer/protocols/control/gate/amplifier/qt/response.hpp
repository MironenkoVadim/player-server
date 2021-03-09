#ifndef VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_QT_RESPONSE_HPP_
#define VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_QT_RESPONSE_HPP_

#pragma once

#include <veer/protocols/control/gate/amplifier/response.hpp>

namespace veer::protocols::control::gate::amplifier {

inline QDataStream& operator<<( QDataStream& ds, const Response& value )
{
	ds << value.m_state;
	ds << value.m_mode;
	ds << value.m_ls;
	ds << value.m_b6011;
	ds << value.m_b6012;
	ds << value.m_b6013;
	ds << value.m_b6014;
	ds << value.m_b6021;
	ds << value.m_b6022;
	ds << value.m_b6023;
	ds << value.m_b6024;
	ds << value.m_b603;
	ds << value.m_b605;
	ds << value.m_temp1;
	ds << value.m_temp2;
	ds << value.m_temp3;
	ds << value.m_temp4;
	ds << value.m_power1;
	ds << value.m_power2;
	ds << value.m_power3;
	ds << value.m_power4;
	ds << value.m_ls1;
	ds << value.m_ls2;
	ds << value.m_ls3;
	ds << value.m_ls4;

	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, Response& value )
{
	ds >> value.m_state;
	ds >> value.m_mode;
	ds >> value.m_ls;
	ds >> value.m_b6011;
	ds >> value.m_b6012;
	ds >> value.m_b6013;
	ds >> value.m_b6014;
	ds >> value.m_b6021;
	ds >> value.m_b6022;
	ds >> value.m_b6023;
	ds >> value.m_b6024;
	ds >> value.m_b603;
	ds >> value.m_b605;
	ds >> value.m_temp1;
	ds >> value.m_temp2;
	ds >> value.m_temp3;
	ds >> value.m_temp4;
	ds >> value.m_power1;
	ds >> value.m_power2;
	ds >> value.m_power3;
	ds >> value.m_power4;
	ds >> value.m_ls1;
	ds >> value.m_ls2;
	ds >> value.m_ls3;
	ds >> value.m_ls4;

	return( ds );
} // >>

} // namespace veer::protocols::control::gate::amplifier

#endif // ifndef VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_QT_RESPONSE_HPP_

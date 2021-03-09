#ifndef VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_QT_COMMAND_HPP_
#define VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_QT_COMMAND_HPP_

#pragma once

#include <veer/protocols/control/gate/amplifier/command.hpp>

namespace veer::protocols::control::gate::amplifier {

inline QDataStream& operator<<( QDataStream& ds, const Command& value )
{
	ds << value.m_id;
	ds << value.m_sec;
	ds << value.m_nsec;
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
	ds >> value.m_id;
	ds >> value.m_sec;
	ds >> value.m_nsec;
	ds >> value.m_period;
	ds >> value.m_spectr;
	ds >> value.m_zsCount;
	ds >> value.m_recvCount;
	ds >> value.m_isCount;
	ds >> value.m_calibrTime;

	return( ds );
}

} // namespace veer::protocols::control::gate::amplifier


#endif // ifndef VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_QT_COMMAND_HPP_

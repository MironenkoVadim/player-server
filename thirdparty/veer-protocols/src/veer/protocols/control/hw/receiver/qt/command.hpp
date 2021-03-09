#ifndef VEER_PROTOCOLS_CONTROL_HW_RECEIVER_QT_COMMAND_HPP_
#define VEER_PROTOCOLS_CONTROL_HW_RECEIVER_QT_COMMAND_HPP_

#pragma once

#include <veer/protocols/control/hw/receiver/command.hpp>

namespace veer::protocols::control::hw::receiver {

inline QDataStream& operator<<( QDataStream& ds, const Command& value )
{
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Command& value )
{
	return( ds );
}

} // namespace veer::protocols::control::hw::receiver

#endif // ifndef VEER_PROTOCOLS_CONTROL_HW_RECEIVER_QT_COMMAND_HPP_

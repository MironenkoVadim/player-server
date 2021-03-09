#ifndef VEER_PROTOCOLS_CONTROL_HW_RECEIVER_QT_RESPONSE_HPP_
#define VEER_PROTOCOLS_CONTROL_HW_RECEIVER_QT_RESPONSE_HPP_

#pragma once

#include <veer/protocols/control/hw/receiver/response.hpp>

namespace veer::protocols::control::hw::receiver {

inline QDataStream& operator<<( QDataStream& ds, const Response& value )
{
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Response& value )
{
	return( ds );
}

} // namespace veer::protocols::control::hw::receiver


#endif // ifndef VEER_PROTOCOLS_CONTROL_HW_RECEIVER_QT_RESPONSE_HPP_

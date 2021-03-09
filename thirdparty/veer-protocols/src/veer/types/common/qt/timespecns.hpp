#ifndef VEER_TYPES_COMMON_QT_TIMESPECNS_HPP_
#define VEER_TYPES_COMMON_QT_TIMESPECNS_HPP_

#pragma once

#include <veer/types/common/timespecns.hpp>

namespace veer::types::common {

inline QDataStream& operator<<( QDataStream& ds, TimeSpecNs value )
{
	ds << value.m_nsec;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, TimeSpecNs& value )
{
	ds >> value.m_nsec;

	return( ds );
}


inline QDebug operator<<( QDebug dbg, TimeSpecNs value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTC::TimeSpecNs: = [";
	dbg << "sec = " << value.m_nsec / VC::G;
	dbg << ", nsec =" << value.m_nsec % VC::G;
	dbg << "])";
	return( dbg );
}

} // namespace veer::types::common

#endif // ifndef VEER_TYPES_COMMON_QT_TIMESPECNS_HPP_

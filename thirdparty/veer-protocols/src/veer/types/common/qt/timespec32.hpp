#ifndef VEER_TYPES_COMMON_QT_TIMESPEC32_HPP_
#define VEER_TYPES_COMMON_QT_TIMESPEC32_HPP_

#pragma once

#include <veer/types/common/timespec32.hpp>

namespace veer::types::common {

inline QDataStream& operator<<( QDataStream& ds, TimeSpec32 value )
{
	ds << value.m_sec;
	ds << value.m_nsec;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, TimeSpec32& value )
{
	ds >> value.m_sec;
	ds >> value.m_nsec;

	return( ds );
}


inline QDebug operator<<( QDebug dbg, TimeSpec32 value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTC::TimeSpec32: = [";
	dbg << "sec = " << value.m_sec;
	dbg << ", nsec =" << value.m_nsec;
	dbg << "])";
	return( dbg );
}

} // namespace veer::types::common

#endif // ifndef VEER_TYPES_COMMON_QT_TIMESPEC32_HPP_

#ifndef VEER_TYPES_RADAR_SUROK_QT_COMMON_HPP_
#define VEER_TYPES_RADAR_SUROK_QT_COMMON_HPP_

#pragma once

#include <veer/types/radar/surok/qt/common.hpp>

namespace veer::types::radar::surok {

inline QDebug operator<<( QDebug dbg, ControlFlags value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTRS::ControlFlags: = [";

	dbg << "serialControl = " << value.m_bf.serialControl;
	dbg << ", manualControl = " << value.m_bf.manualControl;
	dbg << ", on = " << value.m_bf.on;
	dbg << ", off = " << value.m_bf.off;
	dbg << ", temperatureReset = " << value.m_bf.temperatureReset;
	dbg << ", voltageReset = " << value.m_bf.voltageReset;
	dbg << ", strob1Reset = " << value.m_bf.strob1Reset;
	dbg << ", strob2Reset = " << value.m_bf.strob2Reset;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, ControlFlags value )
{
	ds << value.m_value;
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, ControlFlags& value )
{
	ds >> value.m_value;
	return ( ds );
}


inline QDebug operator<<( QDebug dbg, ChannelFlags value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTRS::ChannelFlags: = [";
	dbg << "block1 = " << value.m_bf.block1;
	dbg << ", block2 = " << value.m_bf.block2;
	dbg << ", block3 = " << value.m_bf.block3;
	dbg << ", block4 = " << value.m_bf.block4;
	dbg << ", antenna1 = " << value.m_bf.antenna1;
	dbg << ", antenna2 = " << value.m_bf.antenna2;
	dbg << ", antenna3 = " << value.m_bf.antenna3;
	dbg << ", antenna4 = " << value.m_bf.antenna4;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, ChannelFlags value )
{
	ds << value.m_value;
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, ChannelFlags& value )
{
	ds << value.m_value;
	return( ds );
}

} // namespace veer::types::radar::surok

#endif // ifndef VEER_TYPES_RADAR_SUROK_QT_COMMON_HPP_

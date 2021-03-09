#ifndef VEER_PROTOCOLS_KSA_ALMAZ_QT_CONTROL_MESSAGE_HPP_
#define VEER_PROTOCOLS_KSA_ALMAZ_QT_CONTROL_MESSAGE_HPP_

#pragma once

#include <veer/protocols/ksa/almaz/control_message.hpp>

namespace veer::protocols::ksa::almaz {

inline QDebug operator<<( QDebug dbg, const ControlMessage& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPKA::ControlMessage: = [";
	dbg << "controlCode = " << value.m_u9.controlCode;
	dbg << "])";
	return ( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const ControlMessage& value )
{
	const Header& bh { value };
	ds << bh;

	ds << value.m_w3;
	ds << value.m_w4;
	ds << value.m_w5;
	ds << value.m_w6;
	ds << value.m_w7;
	ds << value.m_w8;
	ds << value.m_w9;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, ControlMessage& value )
{
	Header& bh { static_cast< Header& >( value ) };
	ds >> bh;

	ds >> value.m_w3;
	ds >> value.m_w4;
	ds >> value.m_w5;
	ds >> value.m_w6;
	ds >> value.m_w7;
	ds >> value.m_w8;
	ds >> value.m_w9;

	return( ds );
}

} // namespace veer::protocols::ksa::almaz


#endif // ifndef VEER_PROTOCOLS_KSA_ALMAZ_QT_CONTROL_MESSAGE_HPP_

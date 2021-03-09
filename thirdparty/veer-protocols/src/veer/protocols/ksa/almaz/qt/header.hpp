#ifndef VEER_PROTOCOLS_KSA_ALMAZ_QT_HEADER_HPP_
#define VEER_PROTOCOLS_KSA_ALMAZ_QT_HEADER_HPP_

#pragma once

#include <veer/protocols/ksa/almaz/header.hpp>

namespace veer::protocols::ksa::almaz {

inline QDebug operator<<( QDebug dbg, const Header value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPKA::Header: = [";
	dbg << "startMarker = " << static_cast< int >( value.m_w1 );
	dbg << ", delay = " << static_cast< int >( value.m_u2.delay );
	dbg << ", messageType = " << static_cast< int >( value.m_u2.messageType );
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, Header value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::BigEndian );

	ds << value.m_w1;
	ds << value.m_w2;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Header& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::BigEndian );

	ds >> value.m_w1;
	ds >> value.m_w2;

	ds.setByteOrder( bo );
	return( ds );
}

} // namespace veer::protocols::ksa::almaz

#endif // ifndef VEER_PROTOCOLS_KSA_ALMAZ_QT_HEADER_HPP_

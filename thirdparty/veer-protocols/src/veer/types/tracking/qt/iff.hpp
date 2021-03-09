#ifndef VEER_TYPES_TRACKING_QT_IFF_HPP_
#define VEER_TYPES_TRACKING_QT_IFF_HPP_

#pragma once

#include <veer/types/tracking/iff.hpp>

namespace veer::types::tracking {

inline QDataStream& operator<<( QDataStream& ds, IffMode value )
{
	ds << static_cast< std::underlying_type_t< IffMode > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, IffMode& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< IffMode >( t );
	return ( ds );
}


inline QDataStream& operator<<( QDataStream& ds, IffTag value )
{
	ds << static_cast< std::underlying_type_t< IffTag > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, IffTag& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< IffTag >( t );
	return ( ds );
}


inline QDataStream& operator<<( QDataStream& ds, const IffInfo& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_id;
	ds << value.m_fuelLoad;
	ds << value.m_mode;
	ds << value.m_tag;
	ds << value.m_isRequest;
	ds << value.m_isUpdate;
	ds << value.m_isAlert;
	ds << value.m_stub1;
	ds << value.m_stub2;
	ds << value.m_stub3;

	ds.setFloatingPointPrecision( prec );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, IffInfo& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_id;
	ds >> value.m_fuelLoad;
	ds >> value.m_mode;
	ds >> value.m_tag;
	ds >> value.m_isRequest;
	ds >> value.m_isUpdate;
	ds >> value.m_isAlert;
	ds >> value.m_stub1;
	ds >> value.m_stub2;
	ds >> value.m_stub3;

	ds.setFloatingPointPrecision( prec );
	return( ds );
}

} // namespace veer::types::tracking

#endif // ifndef VEER_TYPES_TRACKING_QT_IFF_HPP_

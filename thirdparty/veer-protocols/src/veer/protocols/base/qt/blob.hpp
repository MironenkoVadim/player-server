#ifndef VEER_PROTOCOLS_BASE_QT_BLOB_HPP_
#define VEER_PROTOCOLS_BASE_QT_BLOB_HPP_

#pragma once

#include <veer/protocols/base/blob.hpp>

namespace veer::protocols::base {

inline QDataStream& operator<<( QDataStream& ds, const Blob& value )
{
	const Header& bh { value };
	ds << bh;

	ds << value.m_version;
	ds << value.m_code;
	ds << value.m_size;
	if ( value.m_size > 0 ) { ds.writeRawData( value.m_data, value.m_size ); }
	ds << value.m_endMarker;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Blob& value )
{
	Header& bh { static_cast< Header& >( value ) };
	ds >> bh;

	ds >> value.m_version;
	ds >> value.m_code;
	ds >> value.m_size;
	delete value.m_data;
	if ( value.m_size > 0 )
	{
		value.m_data = new char[value.m_size];
		ds.readRawData( value.m_data, value.m_size );
	}
	else
	{
		value.m_data = nullptr;
	}

	ds >> value.m_endMarker;

	return( ds );
} // >>

} // namespace veer::protocols::base

#endif // ifndef VEER_PROTOCOLS_BASE_QT_BLOB_HPP_

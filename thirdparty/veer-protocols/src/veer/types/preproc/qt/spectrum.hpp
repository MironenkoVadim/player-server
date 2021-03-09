#ifndef VEER_TYPES_PREPROC_QT_SPECTRUM_HPP_
#define VEER_TYPES_PREPROC_QT_SPECTRUM_HPP_

#pragma once

#include <veer/types/preproc/spectrum.hpp>

namespace veer::types::preproc {

inline QDataStream& operator<<( QDataStream& ds, const Spectrum& value )
{
	ds << value.m_zoneNumber;
	ds << value.m_number;
	ds << value.m_isPrimary;
	ds << value.m_stub;
	ds << value.m_dataSize;

	if ( ( value.m_dataSize > 0 ) && ( value.m_data != nullptr ) )
	{
		ds.writeRawData( reinterpret_cast< char* >( value.m_data ), value.m_dataSize );
	}

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Spectrum& value )
{
	ds >> value.m_zoneNumber;
	ds >> value.m_number;
	ds >> value.m_isPrimary;
	ds >> value.m_stub;
	ds >> value.m_dataSize;

	if ( value.m_dataSize > 0 )
	{
		value.m_data = reinterpret_cast< std::complex< double >* >( aligned_alloc( getpagesize(), value.m_dataSize ) );
		ds.readRawData( reinterpret_cast< char* >( value.m_data ), value.m_dataSize );
	}
	else
	{
		value.m_data = nullptr;
	}

	return( ds );
}


inline QDebug operator<<( QDebug dbg, const Spectrum& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTP::Spectrum: = [";
	dbg << "zoneNumber = " << static_cast< int >( value.m_zoneNumber );
	dbg << ", number = " << static_cast< int >( value.m_number );
	dbg << ", isPrimary = " << static_cast< int >( value.m_isPrimary );
	dbg << ", dataSize = " << value.m_dataSize;
	dbg << "])";
	return ( dbg );
}

} // namespace veer::types::preproc


#endif // ifndef VEER_TYPES_PREPROC_QT_SPECTRUM_HPP_

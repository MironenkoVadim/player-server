#ifndef VEER_TYPES_PREPROC_QT_ADAPTIVE_THRESHOLD_HPP_
#define VEER_TYPES_PREPROC_QT_ADAPTIVE_THRESHOLD_HPP_

#pragma once

#include <veer/types/preproc/adaptive_threshold.hpp>

namespace veer::types::preproc {

inline QDataStream& operator<<( QDataStream& ds, const AdaptiveThreshold& value )
{
	ds << value.m_zoneNumber;
	ds << value.m_stub;
	ds << value.m_dataSize;

	if ( ( value.m_dataSize > 0 ) && ( value.m_data != nullptr ) )
	{
		ds.writeRawData( reinterpret_cast< char* >( value.m_data ), value.m_dataSize );
	}

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, AdaptiveThreshold& value )
{
	ds >> value.m_zoneNumber;
	ds >> value.m_stub;
	ds >> value.m_dataSize;

	if ( value.m_dataSize > 0 )
	{
		value.m_data = reinterpret_cast< double* >( aligned_alloc( getpagesize(), value.m_dataSize ) );
		ds.readRawData( reinterpret_cast< char* >( value.m_data ), value.m_dataSize );
	}
	else
	{
		value.m_data = nullptr;
	}

	return( ds );
}


inline QDebug operator<<( QDebug dbg, const AdaptiveThreshold& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTP::AdaptiveThreshold: = [";
	dbg << "zoneNumber = " << static_cast< int >( value.m_zoneNumber );
	dbg << ", dataSize = " << value.m_dataSize;
	dbg << "])";
	return ( dbg );
}

} // namespace veer::types::preproc

#endif // ifndef VEER_TYPES_PREPROC_QT_ADAPTIVE_THRESHOLD_HPP_

#ifndef VEER_TYPES_PREPROC_QT_MARK_TYPES_HPP_
#define VEER_TYPES_PREPROC_QT_MARK_TYPES_HPP_

#pragma once

#include <veer/types/preproc/mark_types.hpp>

namespace veer::types::preproc {

inline QDataStream& operator<<( QDataStream& ds, MarkTypes value )
{
	ds << static_cast< std::underlying_type_t< MarkTypes > >( value );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, MarkTypes& value )
{
	quint8 t { 0 }; ds >> t; value = static_cast< MarkTypes >( t );
	return ( ds );
}


inline QDebug operator<<( QDebug dbg, const MarkTypes& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTP::MarkTypes: = [";
	dbg << bin << static_cast< int >( value );
	dbg << "])";

	return( dbg );
}

} // namespace veer::types::preproc
// Обязательно в глобальной области видимости

#endif // ifndef VEER_TYPES_PREPROC_QT_MARK_TYPES_HPP_

#ifndef VEER_TYPES_TRACKING_QT_ADSB_HPP_
#define VEER_TYPES_TRACKING_QT_ADSB_HPP_

#pragma once

#include <veer/types/tracking/adsb.hpp>

namespace veer::types::tracking {

inline QDebug operator<<( QDebug dbg, AdsbInfo value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTT::AdsbInfo: = [";
	dbg << "m_id = " << value.m_id;
	dbg << ", m_barHeight = " << value.m_barHeight;
	dbg << ", m_isAnswer = " << static_cast< bool >( value.m_isAnswer );
	dbg << ", m_isUpdate = " << static_cast< bool >( value.m_isUpdate );
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const AdsbInfo& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_id;
	ds << value.m_barHeight;
	ds << value.m_stubf;
	ds << value.m_isAnswer;
	ds << value.m_isUpdate;
	ds << value.m_stub;

	ds.setFloatingPointPrecision( prec );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, AdsbInfo& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_id;
	ds >> value.m_barHeight;
	ds >> value.m_stubf;
	ds >> value.m_isAnswer;
	ds >> value.m_isUpdate;
	ds >> value.m_stub;

	ds.setFloatingPointPrecision( prec );
	return( ds );
}

} // namespace veer::types::tracking

#endif // ifndef VEER_TYPES_TRACKING_QT_ADSB_HPP_

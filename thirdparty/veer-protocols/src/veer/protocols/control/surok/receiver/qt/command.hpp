#ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_COMMAND_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_COMMAND_HPP_

#pragma once

#include <veer/protocols/control/surok/receiver/command.hpp>

namespace veer::protocols::control::surok::receiver {

inline QDebug operator<<( QDebug dbg, const Mode& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::Mode: = [";
	dbg << bin << static_cast< int >( value );
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, Mode value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds << static_cast< typename std::underlying_type< Mode >::type >( value );

	ds.setByteOrder( bo );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Mode& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	quint8 t { 0 }; ds >> t; value = static_cast< Mode >( t );

	ds.setByteOrder( bo );
	return ( ds );
}


inline QDebug operator<<( QDebug dbg, const Flags& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::Flags: = [";
	dbg << bin << static_cast< int >( value );
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, Flags value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds << static_cast< typename std::underlying_type< Flags >::type >( value );

	ds.setByteOrder( bo );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Flags& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	quint8 t { 0 }; ds >> t; value = static_cast< Flags >( t );

	ds.setByteOrder( bo );
	return ( ds );
}


inline QDebug operator<<( QDebug dbg, const PatternControl value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::PatternControl: = [";
	dbg << "counter = " << static_cast< int >( value.m_s.counter );
	dbg << ", pattern = " << static_cast< int >( value.m_s.pattern );
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, PatternControl value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds << value.m_mode;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, PatternControl& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds >> value.m_mode;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDebug operator<<( QDebug dbg, const DeviationControl value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::DeviationControl: = [";
	dbg << "d1 = " << value.m_s.d1;
	dbg << ", d2 = " << value.m_s.d2;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, DeviationControl value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds << value.m_mode;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, DeviationControl& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds >> value.m_mode;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDebug operator<<( QDebug dbg, const ModeId value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::ModeId: = [";
	dbg << "rand = " << value.m_s.rand;
	dbg << ", id = " << value.m_s.id;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, ModeId value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds << value.m_mode;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, ModeId& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );

	ds >> value.m_mode;

	ds.setByteOrder( bo );
	return( ds );
}


inline QDebug operator<<( QDebug dbg, const Command value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::Command: = [";
	dbg << "m_mode = " << value.m_mode;
	dbg << ", m_flags = " << value.m_flags;
	dbg << ", m_risingEdgeTime = " << static_cast< int >( value.m_risingEdgeTime );
	dbg << ", m_fallingEdgeTime = " << static_cast< int >( value.m_fallingEdgeTime );
	dbg << ", m_pulseTime1 = " << static_cast< int >( value.m_pulseTime1 );
	dbg << ", m_pulseTime2 = " << static_cast< int >( value.m_pulseTime2 );
	dbg << ", m_receivingTime1 = " << value.m_receivingTime1;
	dbg << ", m_receivingTime2 = " << value.m_receivingTime2;
	dbg << ", m_freq1 = " << value.m_freq1;
	dbg << ", m_freq2 = " << value.m_freq2;
	dbg << ", m_pulsesGap = " << static_cast< int >( value.m_pulsesGap );
	dbg << ", m_bandwidth = " << static_cast< int >( value.m_bandwidth );
	dbg << ", m_attenuator = " << static_cast< int >( value.m_attenuator );
	dbg << ", m_pattern = " << value.m_pattern;
	dbg << ", m_csFreq = " << value.m_csFreq;
	dbg << ", m_csDelay = " << value.m_csDelay;
	dbg << ", m_csAmplitude = " << value.m_csAmplitude;
	dbg << ", m_startDelay = " << static_cast< int >( value.m_startDelay );
	dbg << ", m_finishDelay = " << static_cast< int >( value.m_finishDelay );
	dbg << ", m_receivingTimeBoth = " << value.m_receivingTimeBoth;
	dbg << ", m_modeId = " << value.m_modeId;
	dbg << ", m_deviation = " << value.m_deviation;
	dbg << ", m_distanceChannel = " << value.m_distanceChannel;
	dbg << ", m_stub1 = " << static_cast< int >( value.m_stub1 );
	dbg << ", m_stub2 = " << value.m_stub2;
	dbg << ", m_falseAlert1 = " << value.m_falseAlert1;
	dbg << ", m_falseAlert2 = " << value.m_falseAlert2;
	dbg << ", m_userThreshold1 = " << value.m_userThreshold1;
	dbg << ", m_userThreshold2 = " << value.m_userThreshold2;
	dbg << ", m_searchZoneStart1 = " << value.m_searchZoneStart1;
	dbg << ", m_searchZoneStart2 = " << value.m_searchZoneStart2;
	dbg << ", m_convolutionPart1 = " << value.m_convolutionPart1;
	dbg << ", m_convolutionPart2 = " << value.m_convolutionPart2;
	dbg << ", m_softAttenuator1 = " << value.m_softAttenuator1;
	dbg << ", m_softAttenuator2 = " << value.m_softAttenuator2;
	dbg << ", m_rejectedFilters1 = " << value.m_rejectedFilters1;
	dbg << ", m_rejectedFilters2 = " << value.m_rejectedFilters2;
	dbg << ", m_smoothWindow1 = " << static_cast< int >( value.m_smoothWindow1 );
	dbg << ", m_smoothWindow2 = " << static_cast< int >( value.m_smoothWindow2 );
	dbg << ", m_convolution1 = " << static_cast< int >( value.m_convolution1 );
	dbg << ", m_convolution2 = " << static_cast< int >( value.m_convolution2 );
	dbg << ", m_user1 = " << value.m_user1;
	dbg << ", m_user2 = " << value.m_user2;
	dbg << ", m_user3 = " << value.m_user3;
	dbg << ", m_zeroes1 = " << value.m_zeroes1;
	dbg << ", m_zeroes2 = " << value.m_zeroes2;
	dbg << ", m_zeroes3 = " << value.m_zeroes3;
	dbg << ", m_zeroes4 = " << value.m_zeroes4;
	dbg << "])";

	return( dbg );
} // <<


inline QDataStream& operator<<( QDataStream& ds, const Command& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_mode;
	ds << value.m_flags;
	ds << value.m_risingEdgeTime;
	ds << value.m_fallingEdgeTime;
	ds << value.m_pulseTime1;
	ds << value.m_pulseTime2;
	ds << value.m_receivingTime1;
	ds << value.m_receivingTime2;
	ds << value.m_freq1;
	ds << value.m_freq2;
	ds << value.m_pulsesGap;
	ds << value.m_bandwidth;
	ds << value.m_attenuator;
	ds << value.m_pattern;
	ds << value.m_csFreq;
	ds << value.m_csDelay;
	ds << value.m_csAmplitude;
	ds << value.m_startDelay;
	ds << value.m_finishDelay;
	ds << value.m_receivingTimeBoth;
	ds << value.m_modeId;
	ds << value.m_deviation;
	ds << value.m_distanceChannel;
	ds << value.m_stub1;
	ds << value.m_stub2;
	ds << value.m_falseAlert1;
	ds << value.m_falseAlert2;
	ds << value.m_userThreshold1;
	ds << value.m_userThreshold2;
	ds << value.m_searchZoneStart1;
	ds << value.m_searchZoneStart2;
	ds << value.m_convolutionPart1;
	ds << value.m_convolutionPart2;
	ds << value.m_softAttenuator1;
	ds << value.m_softAttenuator2;
	ds << value.m_rejectedFilters1;
	ds << value.m_rejectedFilters2;
	ds << value.m_smoothWindow1;
	ds << value.m_smoothWindow2;
	ds << value.m_convolution1;
	ds << value.m_convolution2;
	ds << value.m_user1;
	ds << value.m_user2;
	ds << value.m_user3;
	ds << value.m_zeroes1;
	ds << value.m_zeroes2;
	ds << value.m_zeroes3;
	ds << value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, Command& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_mode;
	ds >> value.m_flags;
	ds >> value.m_risingEdgeTime;
	ds >> value.m_fallingEdgeTime;
	ds >> value.m_pulseTime1;
	ds >> value.m_pulseTime2;
	ds >> value.m_receivingTime1;
	ds >> value.m_receivingTime2;
	ds >> value.m_freq1;
	ds >> value.m_freq2;
	ds >> value.m_pulsesGap;
	ds >> value.m_bandwidth;
	ds >> value.m_attenuator;
	ds >> value.m_pattern;
	ds >> value.m_csFreq;
	ds >> value.m_csDelay;
	ds >> value.m_csAmplitude;
	ds >> value.m_startDelay;
	ds >> value.m_finishDelay;
	ds >> value.m_receivingTimeBoth;
	ds >> value.m_modeId;
	ds >> value.m_deviation;
	ds >> value.m_distanceChannel;
	ds >> value.m_stub1;
	ds >> value.m_stub2;
	ds >> value.m_falseAlert1;
	ds >> value.m_falseAlert2;
	ds >> value.m_userThreshold1;
	ds >> value.m_userThreshold2;
	ds >> value.m_searchZoneStart1;
	ds >> value.m_searchZoneStart2;
	ds >> value.m_convolutionPart1;
	ds >> value.m_convolutionPart2;
	ds >> value.m_softAttenuator1;
	ds >> value.m_softAttenuator2;
	ds >> value.m_rejectedFilters1;
	ds >> value.m_rejectedFilters2;
	ds >> value.m_smoothWindow1;
	ds >> value.m_smoothWindow2;
	ds >> value.m_convolution1;
	ds >> value.m_convolution2;
	ds >> value.m_user1;
	ds >> value.m_user2;
	ds >> value.m_user3;
	ds >> value.m_zeroes1;
	ds >> value.m_zeroes2;
	ds >> value.m_zeroes3;
	ds >> value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // >>

} // namespace veer::protocols::control::surok::receiver


#endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_COMMAND_HPP_

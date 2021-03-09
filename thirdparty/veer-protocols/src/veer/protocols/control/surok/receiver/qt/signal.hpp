#ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_SIGNAL_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_SIGNAL_HPP_

#pragma once

#include <veer/protocols/control/surok/receiver/signal.hpp>

namespace veer::protocols::control::surok::receiver {

inline QDebug operator<<( QDebug dbg, const SignalHeader1 value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::SignalHeader1: = [";
	dbg << "mark32 = " << value.m_mark32;
	dbg << ", mark16 = " << value.m_mark16;
	dbg << ", adc1 = " << static_cast< quint32 >( value.m_adc1 );
	dbg << ", pattern = " << value.m_pattern;
	dbg << ", modeId = " << value.m_modeId;
	dbg << ", wordsCount = " << value.m_wordsCount;
	dbg << ", counter = " << value.m_counter;
	dbg << ", falseAlert1 = " << value.m_falseAlert1;
	dbg << ", falseAlert2 = " << value.m_falseAlert2;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const SignalHeader1& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_mark32;
	ds << value.m_mark16;
	ds << value.m_adc1;
	ds << value.m_pattern;
	ds << value.m_modeId;
	ds << value.m_wordsCount;
	ds << value.m_counter;
	ds << value.m_falseAlert1;
	ds << value.m_falseAlert2;
	ds << value.m_zeroes2;
	ds << value.m_zeroes3;
	ds << value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, SignalHeader1& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_mark32;
	ds >> value.m_mark16;
	ds >> value.m_adc1;
	ds >> value.m_pattern;
	ds >> value.m_modeId;
	ds >> value.m_wordsCount;
	ds >> value.m_counter;
	ds >> value.m_falseAlert1;
	ds >> value.m_falseAlert2;
	ds >> value.m_zeroes2;
	ds >> value.m_zeroes3;
	ds >> value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // >>


inline QDebug operator<<( QDebug dbg, const SignalHeader2 value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::SignalHeader2: = [";
	dbg << "mark32 = " << value.m_mark32;
	dbg << ", mark16 = " << value.m_mark16;
	dbg << ", adc2 = " << static_cast< quint32 >( value.m_adc2 );
	dbg << ", pulsesGap = " << static_cast< quint32 >( value.m_pulsesGap );
	dbg << ", freq1 = " << value.m_freq1;
	dbg << ", freq2 = " << value.m_freq2;
	dbg << ", counter = " << value.m_counter;
	dbg << ", userThreshold1 = " << value.m_userThreshold1;
	dbg << ", userThreshold2 = " << value.m_userThreshold2;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const SignalHeader2& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_mark32;
	ds << value.m_mark16;
	ds << value.m_adc2;
	ds << value.m_pulsesGap;
	ds << value.m_freq1;
	ds << value.m_freq2;
	ds << value.m_counter;
	ds << value.m_userThreshold1;
	ds << value.m_userThreshold2;
	ds << value.m_zeroes2;
	ds << value.m_zeroes3;
	ds << value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, SignalHeader2& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_mark32;
	ds >> value.m_mark16;
	ds >> value.m_adc2;
	ds >> value.m_pulsesGap;
	ds >> value.m_freq1;
	ds >> value.m_freq2;
	ds >> value.m_counter;
	ds >> value.m_userThreshold1;
	ds >> value.m_userThreshold2;
	ds >> value.m_zeroes2;
	ds >> value.m_zeroes3;
	ds >> value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // >>


inline QDebug operator<<( QDebug dbg, const SignalHeader3 value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::SignalHeader3: = [";
	dbg << "mark32 = " << value.m_mark32;
	dbg << ", mark16 = " << value.m_mark16;
	dbg << ", adc3 = " << static_cast< quint32 >( value.m_adc3 );
	dbg << ", pulseTime2 = " << static_cast< quint32 >( value.m_pulseTime2 );
	dbg << ", pulseTime1 = " << value.m_pulseTime1;
	dbg << ", outputSpeed = " << value.m_outputSpeed;
	dbg << ", counter = " << value.m_counter;
	dbg << ", searchZoneStart1 = " << value.m_searchZoneStart1;
	dbg << ", searchZoneStart2 = " << value.m_searchZoneStart2;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const SignalHeader3& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_mark32;
	ds << value.m_mark16;
	ds << value.m_adc3;
	ds << value.m_pulseTime2;
	ds << value.m_pulseTime1;
	ds << value.m_outputSpeed;
	ds << value.m_counter;
	ds << value.m_searchZoneStart1;
	ds << value.m_searchZoneStart2;
	ds << value.m_zeroes2;
	ds << value.m_zeroes3;
	ds << value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, SignalHeader3& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_mark32;
	ds >> value.m_mark16;
	ds >> value.m_adc3;
	ds >> value.m_pulseTime2;
	ds >> value.m_pulseTime1;
	ds >> value.m_outputSpeed;
	ds >> value.m_counter;
	ds >> value.m_searchZoneStart1;
	ds >> value.m_searchZoneStart2;
	ds >> value.m_zeroes2;
	ds >> value.m_zeroes3;
	ds >> value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // >>


inline QDebug operator<<( QDebug dbg, const SignalHeader4 value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::SignalHeader4: = [";
	dbg << "mark32 = " << value.m_mark32;
	dbg << ", mark16 = " << value.m_mark16;
	dbg << ", adc4 = " << static_cast< quint32 >( value.m_adc4 );
	dbg << ", risingEdgeTime = " << static_cast< quint32 >( value.m_risingEdgeTime );
	dbg << ", samples2 = " << value.m_samples2;
	dbg << ", samples1 = " << value.m_samples1;
	dbg << ", counter = " << value.m_counter;
	dbg << ", asyncNoiseThreshold1 = " << value.m_asyncNoiseThreshold1;
	dbg << ", asyncNoiseThreshold2 = " << value.m_asyncNoiseThreshold2;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const SignalHeader4& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_mark32;
	ds << value.m_mark16;
	ds << value.m_adc4;
	ds << value.m_risingEdgeTime;
	ds << value.m_samples2;
	ds << value.m_samples1;
	ds << value.m_counter;
	ds << value.m_asyncNoiseThreshold1;
	ds << value.m_asyncNoiseThreshold2;
	ds << value.m_zeroes2;
	ds << value.m_zeroes3;
	ds << value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, SignalHeader4& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_mark32;
	ds >> value.m_mark16;
	ds >> value.m_adc4;
	ds >> value.m_risingEdgeTime;
	ds >> value.m_samples2;
	ds >> value.m_samples1;
	ds >> value.m_counter;
	ds >> value.m_asyncNoiseThreshold1;
	ds >> value.m_asyncNoiseThreshold2;
	ds >> value.m_zeroes2;
	ds >> value.m_zeroes3;
	ds >> value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // >>


inline QDebug operator<<( QDebug dbg, const SignalHeader5 value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::SignalHeader5: = [";
	dbg << "mark32 = " << value.m_mark32;
	dbg << ", mark16 = " << value.m_mark16;
	dbg << ", adc5 = " << static_cast< quint32 >( value.m_adc5 );
	dbg << ", fallingEdgeTime = " << static_cast< quint32 >( value.m_fallingEdgeTime );
	dbg << ", startDelay = " << static_cast< quint32 >( value.m_startDelay );
	dbg << ", finishDelay = " << static_cast< quint32 >( value.m_finishDelay );
	dbg << ", crossSamples = " << value.m_crossSamples;
	dbg << ", counter = " << value.m_counter;
	dbg << ", softAttenuator1 = " << value.m_softAttenuator1;
	dbg << ", softAttenuator2 = " << value.m_softAttenuator2;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const SignalHeader5& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_mark32;
	ds << value.m_mark16;
	ds << value.m_adc5;
	ds << value.m_fallingEdgeTime;
	ds << value.m_startDelay;
	ds << value.m_finishDelay;
	ds << value.m_crossSamples;
	ds << value.m_counter;
	ds << value.m_softAttenuator1;
	ds << value.m_softAttenuator2;
	ds << value.m_zeroes2;
	ds << value.m_zeroes3;
	ds << value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, SignalHeader5& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_mark32;
	ds >> value.m_mark16;
	ds >> value.m_adc5;
	ds >> value.m_fallingEdgeTime;
	ds >> value.m_startDelay;
	ds >> value.m_finishDelay;
	ds >> value.m_crossSamples;
	ds >> value.m_counter;
	ds >> value.m_softAttenuator1;
	ds >> value.m_softAttenuator2;
	ds >> value.m_zeroes2;
	ds >> value.m_zeroes3;
	ds >> value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // >>


inline QDebug operator<<( QDebug dbg, const SignalHeader6 value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCSR::SignalHeader6: = [";
	dbg << "mark32 = " << value.m_mark32;
	dbg << ", mark16 = " << value.m_mark16;
	dbg << ", adc6 = " << static_cast< quint32 >( value.m_adc6 );
	dbg << ", deviation1 = " << value.m_deviation1;
	dbg << ", deviation2 = " << value.m_deviation2;
	dbg << ", counter = " << value.m_counter;
	dbg << ", rejectedFilters1 = " << value.m_rejectedFilters1;
	dbg << ", rejectedFilters2 = " << value.m_rejectedFilters2;
	dbg << ", windowFunction1 = " << static_cast< quint32 >( value.m_windowFunction1 );
	dbg << ", windowFunction2 = " << static_cast< quint32 >( value.m_windowFunction2 );
	dbg << ", convolution1 = " << static_cast< quint32 >( value.m_convolution1 );
	dbg << ", convolution2 = " << static_cast< quint32 >( value.m_convolution2 );
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const SignalHeader6& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_mark32;
	ds << value.m_mark16;
	ds << value.m_adc6;
	ds << value.m_stub1;
	ds << value.m_deviation1;
	ds << value.m_deviation2;
	ds << value.m_counter;
	ds << value.m_rejectedFilters1;
	ds << value.m_rejectedFilters2;
	ds << value.m_windowFunction1;
	ds << value.m_windowFunction2;
	ds << value.m_convolution1;
	ds << value.m_convolution2;
	ds << value.m_zeroes2;
	ds << value.m_zeroes3;
	ds << value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, SignalHeader6& value )
{
	QDataStream::ByteOrder bo { ds.byteOrder() };
	ds.setByteOrder( QDataStream::LittleEndian );
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_mark32;
	ds >> value.m_mark16;
	ds >> value.m_adc6;
	ds >> value.m_stub1;
	ds >> value.m_deviation1;
	ds >> value.m_deviation2;
	ds >> value.m_counter;
	ds >> value.m_rejectedFilters1;
	ds >> value.m_rejectedFilters2;
	ds >> value.m_windowFunction1;
	ds >> value.m_windowFunction2;
	ds >> value.m_convolution1;
	ds >> value.m_convolution2;
	ds >> value.m_zeroes2;
	ds >> value.m_zeroes3;
	ds >> value.m_zeroes4;

	ds.setFloatingPointPrecision( prec );
	ds.setByteOrder( bo );
	return( ds );
} // >>

} // namespace veer::protocols::control::surok::receiver

#endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_SIGNAL_HPP_

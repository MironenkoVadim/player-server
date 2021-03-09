#ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_SIGNAL_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_SIGNAL_HPP_

#pragma once

#include <veer/common/limits.hpp>
#include <veer/protocols/control/surok/receiver/command.hpp>
#include <veer/common/config.hpp>

namespace veer::protocols::control::surok::receiver {

namespace constants
{

constexpr quint32 SignalHeaderMarker32      { 0xABCD8811 };
constexpr quint16 SignalHeaderMarker16      { 0x1188 };

} // namespace constants


namespace C  = constants;
namespace VC = veer::common;

#pragma pack(push, 1)


class SignalHeader1
{
public:
	bool isMarkerValid()
	{
		return( ( m_mark32 == C::SignalHeaderMarker32 ) && ( m_mark16 == C::SignalHeaderMarker16 ) );
	}

	quint8 adc1() { return( m_adc1 ); }
	quint8 pattern() const { return( m_pattern.pattern() ); }
	quint8 modeId() const { return( m_modeId.id() ); }
	quint16 wordsCount() const { return( m_wordsCount ); }
	quint32 counter() const { return( m_counter ); }
	float falseAlert1() const { return( m_falseAlert1 ); }
	float falseAlert2() const { return( m_falseAlert2 ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const SignalHeader1& value );
	friend QDataStream& operator>>( QDataStream& ds, SignalHeader1& value );
	friend QDebug operator<<( QDebug dbg, const SignalHeader1 value );
	#endif

private:
	quint32        m_mark32 { C::SignalHeaderMarker32 }; /*!< Стартовый маркер 32 бита */
	quint16        m_mark16 { C::SignalHeaderMarker16 }; /*!< Стартовый маркер 16 бит */
	quint8         m_adc1   { UINT8_MAX };               /*!< Перегрузка АЦП */
	PatternControl m_pattern;                            /*!< Шаблон излучения передатчика */
	ModeId         m_modeId;                             /*!< Номер режима */
	quint16        m_wordsCount  { UINT16_MAX };         /*!< Количество слов */
	quint32        m_counter     { UINT32_MAX };         /*!< Счётчик */
	float          m_falseAlert1 { VC::FloatNAN };
	float          m_falseAlert2 { VC::FloatNAN };
	quint64        m_zeroes2 { UINT64_MAX };
	quint64        m_zeroes3 { UINT64_MAX };
	quint64        m_zeroes4 { UINT64_MAX };
}; // class SignalHeader1

class SignalHeader2
{
public:
	bool isMarkerValid()
	{
		return( ( m_mark32 == C::SignalHeaderMarker32 ) && ( m_mark16 == C::SignalHeaderMarker16 ) );
	}

	quint8 adc2() { return( m_adc2 ); }
	quint8 pulsesGap() const { return( m_pulsesGap ); }
	quint16 freq1() const { return( m_freq1 ); }
	quint16 freq2() const { return( m_freq2 ); }
	quint32 counter() const { return( m_counter ); }
	float userThreshold1() const { return( m_userThreshold1 ); }
	float userThreshold2() const { return( m_userThreshold2 ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const SignalHeader2& value );
	friend QDataStream& operator>>( QDataStream& ds, SignalHeader2& value );
	friend QDebug operator<<( QDebug dbg, const SignalHeader2 value );
	#endif

private:
	quint32 m_mark32 { C::SignalHeaderMarker32 }; /*!< Стартовый маркер 32 бита */
	quint16 m_mark16 { C::SignalHeaderMarker16 }; /*!< Стартовый маркер 16 бит */
	quint8  m_adc2      { UINT8_MAX };            /*!< Перегрузка АЦП */
	quint8  m_pulsesGap { UINT8_MAX };            /*!< Пауза между импульсами, мкс */
	quint16 m_freq1     { UINT16_MAX };           /*!< Опорная частота ЛЧМ */
	quint16 m_freq2     { UINT16_MAX };           /*!< Опорная частота SIN */
	quint32 m_counter   { UINT32_MAX };           /*!< Счётчик */
	float   m_userThreshold1 { VC::FloatNAN };
	float   m_userThreshold2 { VC::FloatNAN };
	quint64 m_zeroes2 { UINT64_MAX };
	quint64 m_zeroes3 { UINT64_MAX };
	quint64 m_zeroes4 { UINT64_MAX };
}; // class SignalHeader1


class SignalHeader3
{
public:
	bool isMarkerValid()
	{
		return( ( m_mark32 == C::SignalHeaderMarker32 ) && ( m_mark16 == C::SignalHeaderMarker16 ) );
	}

	quint8 adc3() { return( m_adc3 ); }
	quint8 pulseTime2() const { return( m_pulseTime2 ); }
	quint16 pulseTime1() const { return( m_pulseTime1 ); }
	quint16 outputSpeed() const { return( m_outputSpeed ); }
	quint32 counter() const { return( m_counter ); }
	float searchZoneStart1() const { return( m_searchZoneStart1 ); }
	float searchZoneStart2() const { return( m_searchZoneStart2 ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const SignalHeader3& value );
	friend QDataStream& operator>>( QDataStream& ds, SignalHeader3& value );
	friend QDebug operator<<( QDebug dbg, const SignalHeader3 value );
	#endif

private:
	quint32 m_mark32 { C::SignalHeaderMarker32 }; /*!< Стартовый маркер 32 бита */
	quint16 m_mark16 { C::SignalHeaderMarker16 }; /*!< Стартовый маркер 16 бит */
	quint8  m_adc3        { UINT8_MAX };          /*!< Перегрузка АЦП */
	quint8  m_pulseTime2  { UINT8_MAX };          /*!< Длительность SIN, мкс */
	quint16 m_pulseTime1  { UINT16_MAX };         /*!< Длительность ЛЧМ, (0, 1, 2...5) -> (0, 100, 200...500) мкс */
	quint16 m_outputSpeed { UINT16_MAX };         /*!< Делитель частоты дискретизации: 20e6 / i */
	quint32 m_counter     { UINT32_MAX };         /*!< Счётчик */
	float   m_searchZoneStart1 { VC::FloatNAN };
	float   m_searchZoneStart2 { VC::FloatNAN };
	quint64 m_zeroes2 { UINT64_MAX };
	quint64 m_zeroes3 { UINT64_MAX };
	quint64 m_zeroes4 { UINT64_MAX };
}; // class SignalHeader1


class SignalHeader4
{
public:
	bool isMarkerValid()
	{
		return( ( m_mark32 == C::SignalHeaderMarker32 ) && ( m_mark16 == C::SignalHeaderMarker16 ) );
	}

	quint8 adc4() { return( m_adc4 ); }
	quint8 risingEdgeTime() const { return( m_risingEdgeTime ); }
	quint16 samples2() const { return( m_samples2 ); }
	quint16 samples1() const { return( m_samples1 ); }
	quint32 counter() const { return( m_counter ); }
	float asyncNoiseThreshold1() const { return( m_asyncNoiseThreshold1 ); }
	float asyncNoiseThreshold2() const { return( m_asyncNoiseThreshold2 ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const SignalHeader4& value );
	friend QDataStream& operator>>( QDataStream& ds, SignalHeader4& value );
	friend QDebug operator<<( QDebug dbg, const SignalHeader4 value );
	#endif

private:
	quint32 m_mark32 { C::SignalHeaderMarker32 }; /*!< Стартовый маркер 32 бита */
	quint16 m_mark16 { C::SignalHeaderMarker16 }; /*!< Стартовый маркер 16 бит */
	quint8  m_adc4           { UINT8_MAX };       /*!< Перегрузка АЦП */
	quint8  m_risingEdgeTime { UINT8_MAX };       /*!< Длительность переднего фронта, мкс (5..) */
	quint16 m_samples2       { UINT16_MAX };      /*!< Количество отсчётов SIN */
	quint16 m_samples1       { UINT16_MAX };      /*!< Количество отсчётов ЛЧМ */
	quint32 m_counter        { UINT32_MAX };      /*!< Счётчик */
	float   m_asyncNoiseThreshold1 { VC::FloatNAN };
	float   m_asyncNoiseThreshold2 { VC::FloatNAN };
	quint64 m_zeroes2 { UINT64_MAX };
	quint64 m_zeroes3 { UINT64_MAX };
	quint64 m_zeroes4 { UINT64_MAX };
}; // class SignalHeader1


class SignalHeader5
{
public:
	bool isMarkerValid()
	{
		return( ( m_mark32 == C::SignalHeaderMarker32 ) && ( m_mark16 == C::SignalHeaderMarker16 ) );
	}

	quint8 adc5() { return( m_adc5 ); }
	quint8 fallingEdgeTime() const { return( m_fallingEdgeTime ); }
	quint8 startDelay() const { return( m_startDelay ); }
	quint8 finishDelay() const { return( m_finishDelay ); }
	quint16 crossSamples() const { return( m_crossSamples ); }
	quint32 counter() const { return( m_counter ); }
	float softAttenuator1() const { return( m_softAttenuator1 ); }
	float softAttenuator2() const { return( m_softAttenuator2 ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const SignalHeader5& value );
	friend QDataStream& operator>>( QDataStream& ds, SignalHeader5& value );
	friend QDebug operator<<( QDebug dbg, const SignalHeader5 value );
	#endif

private:
	quint32 m_mark32 { C::SignalHeaderMarker32 }; /*!< Стартовый маркер 32 бита */
	quint16 m_mark16 { C::SignalHeaderMarker16 }; /*!< Стартовый маркер 16 бит */
	quint8  m_adc5           { UINT8_MAX };       /*!< Перегрузка АЦП */
	quint8  m_fallingEdgeTime;                    /*!< Длительность заднего фронта, мкс (1..) */
	quint8  m_startDelay;                         /*!< Пауза перед началом дискретизации, мкс */
	quint8  m_finishDelay;                        /*!< Пауза после окончания дискретизации, мкс */
	quint16 m_crossSamples;                       /*!< Количество одновременно принимаемых отсчётов ЛЧМ и SIN */
	quint32 m_counter;                            /*!< Счётчик */
	float   m_softAttenuator1;
	float   m_softAttenuator2;
	quint64 m_zeroes2 { UINT64_MAX };
	quint64 m_zeroes3 { UINT64_MAX };
	quint64 m_zeroes4 { UINT64_MAX };
}; // class SignalHeader1

class SignalHeader6
{
public:
	bool isMarkerValid()
	{
		return( ( m_mark32 == C::SignalHeaderMarker32 ) && ( m_mark16 == C::SignalHeaderMarker16 ) );
	}

	quint8 adc6() { return( m_adc6 ); }
	quint16 deviation1() const { return( m_deviation1 ); }
	quint16 deviation2() const { return( m_deviation2 ); }
	quint32 counter() const { return( m_counter ); }
	quint16 rejectedFilters1() const { return( m_rejectedFilters1 ); }
	quint16 rejectedFilters2() const { return( m_rejectedFilters2 ); }
	quint8 windowFunction1() const { return( m_windowFunction1 ); }
	quint8 windowFunction2() const { return( m_windowFunction2 ); }
	quint8 convolution1() const { return( m_convolution1 ); }
	quint8 convolution2() const { return( m_convolution2 ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const SignalHeader6& value );
	friend QDataStream& operator>>( QDataStream& ds, SignalHeader6& value );

	friend QDebug operator<<( QDebug dbg, const SignalHeader6 value );
	#endif

private:
	quint32 m_mark32 { C::SignalHeaderMarker32 }; /*!< Стартовый маркер 32 бита */
	quint16 m_mark16 { C::SignalHeaderMarker16 }; /*!< Стартовый маркер 16 бит */
	quint8  m_adc6         { UINT8_MAX };         /*!< Перегрузка АЦП */
	quint8  m_stub1        { UINT8_MAX };
	quint16 m_deviation1   { UINT16_MAX };        /*!< Девиация первого импульса */
	quint16 m_deviation2   { UINT16_MAX };        /*!< Девиация второго импульса */
	quint32 m_counter      { UINT32_MAX };        /*!< Счётчик */
	quint16 m_rejectedFilters1 { UINT16_MAX };
	quint16 m_rejectedFilters2 { UINT16_MAX };
	quint8  m_windowFunction1  { UINT8_MAX };
	quint8  m_windowFunction2  { UINT8_MAX };
	quint8  m_convolution1     { UINT8_MAX };
	quint8  m_convolution2     { UINT8_MAX };

	quint64 m_zeroes2 { UINT64_MAX };
	quint64 m_zeroes3 { UINT64_MAX };
	quint64 m_zeroes4 { UINT64_MAX };
}; // class SignalHeader1

#pragma pack(pop)

} // namespace veer::protocols::control::surok::receiver

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/surok/receiver/qt/signal.hpp>
#endif

static_assert( sizeof( veer::protocols::control::surok::receiver::SignalHeader1 ) == 48,
               "Invalid size of class veer::protocols::control::receiver::SignalHeader1" );

static_assert( sizeof( veer::protocols::control::surok::receiver::SignalHeader2 ) == 48,
               "Invalid size of class veer::protocols::control::receiver::SignalHeader2" );

static_assert( sizeof( veer::protocols::control::surok::receiver::SignalHeader3 ) == 48,
               "Invalid size of class veer::protocols::control::receiver::SignalHeader3" );

static_assert( sizeof( veer::protocols::control::surok::receiver::SignalHeader4 ) == 48,
               "Invalid size of class veer::protocols::control::receiver::SignalHeader4" );

static_assert( sizeof( veer::protocols::control::surok::receiver::SignalHeader5 ) == 48,
               "Invalid size of class veer::protocols::control::receiver::SignalHeader5" );

static_assert( sizeof( veer::protocols::control::surok::receiver::SignalHeader6 ) == 48,
               "Invalid size of class veer::protocols::control::receiver::SignalHeader6" );

#endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_SIGNAL_HPP_

#ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_COMMAND_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_COMMAND_HPP_

#pragma once

#include <veer/common/enum_bitmask_operations.hpp>
#include <veer/types/common/timespec32.hpp>

namespace veer::protocols::control::surok::receiver {

namespace VTC = veer::types::common;

#pragma pack(push, 1)


/*! Команды для приёмника */
enum class Mode : quint8
{
	CheckBoot  = 0x00, /*!< Проверка загрузки */
	ToggleLed  = 0x01, /*!< Переключение индикации */
	ReadSerial = 0x02, /*!< Чтение данных с выхода приёмника через последовательный порт */
	FC         = 0x04, /*!< Функциональный контроль */
	RCS        = 0x08, /*!< Поиск резервных каналов */
	Location   = 0x10  /*!< Настройка и переход в режим обнаружения */
};

enum class Flags : quint8
{
	Unset      = 0x00, /*!< Зондирующий сигнал выключен */
	RawIS      = 0x01, /*!< Гладкий имитационный сигнал */
	RawCS      = 0x02, /*!< Гладкий контрольный сигнал */
	PulseZS    = 0x03, /*!< Импульсный зондирующий сигнал */
	PulseIS    = 0x04, /*!< Импульсный имитационный сигнал */
	PulseCS    = 0x05, /*!< Импульсный контрольный сигнал */
	Imitator   = 0x06, /*!< Включить имитатор */
	SendToBus  = 0x08, /*!< Отправлять сигнал на шину */
	Anntenna   = 0x10, /*!< Включение антенны */
	Attenuator = 0x20, /*!< Аттенюатор */
	DigitalKey = 0x40, /*!< Цифровой ключ */
	TestMode   = 0x80  /*!< Тестовый режим */
};

class PatternControl
{
public:
	quint8 counter() const { return( m_s.counter ); }
	void setCounter( quint8 value ) { m_s.counter = value & 0xF; }

	quint8 pattern() const { return( m_s.pattern ); }
	void setPattern( quint8 value ) { m_s.pattern = value & 0xF; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, PatternControl value );
	friend QDataStream& operator>>( QDataStream& ds, PatternControl& value );
	friend QDebug operator<<( QDebug dbg, const PatternControl value );
	#endif

private:
	union
	{
		quint8 m_mode { 12 + ( 4 << 4 ) };
		struct
		{
			#ifdef LITTLE_ENDIAN
			quint8 counter : 4; //!< Количество периодов обзора, после которого происходит переключение схемы излучения (2^counter)
			quint8 pattern : 4; //!< Варианты схем излучения
			#endif
		} m_s;
	};
}; // class PatternControl


class DeviationControl
{
public:
	bool isLfm1() const { return ( m_s.d1 > 0 ); }
	double d1() const { return( m_s.d1 * 1e5 ); }
	void setD1( double value )
	{
		if ( value < 0 ) { value = 0; }
		if ( value > 400e3 ) { value = 400e3; }
		m_s.d1 = std::lround( value * 1e-5 ) & 0x7;
	}

	bool isLfm2() const { return ( m_s.d2 > 0 ); }
	double d2() const { return( m_s.d2 * 1e5 ); }
	void setD2( double value )
	{
		if ( value < 0 ) { value = 0; }
		if ( value > 400e3 ) { value = 400e3; }
		m_s.d2 = std::lround( value * 1e-5 ) & 0x7;
	}

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, DeviationControl value );
	friend QDataStream& operator>>( QDataStream& ds, DeviationControl& value );
	friend QDebug operator<<( QDebug dbg, const DeviationControl value );
	#endif

private:
	union
	{
		quint8 m_mode { 2 };
		struct
		{
			#ifdef LITTLE_ENDIAN
			unsigned d1   : 3;
			unsigned d2   : 3;
			unsigned stub : 2;
			#endif
		} m_s;
	};
}; // class DeviationControl

class ModeId
{
public:
	quint16 rand() const { return( m_s.rand ); }
	void setRand( quint16 value ) { m_s.rand = value & 0x1FFF; }

	quint8 id() const { return( m_s.id ); }
	void setId( quint8 value ) { m_s.id = value & 0x7; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, ModeId value );
	friend QDataStream& operator>>( QDataStream& ds, ModeId& value );
	friend QDebug operator<<( QDebug dbg, const ModeId value );
	#endif

private:
	union
	{
		quint16 m_mode { 0 };
		struct
		{
			#ifdef LITTLE_ENDIAN
			unsigned rand : 13;
			unsigned id   : 3;
			#endif
		} m_s;
	};
}; // class WorkId

class Command
{
public:

	Mode mode() const { return( m_mode ); }
	void setMode( Mode value ) { m_mode = value; }

	Flags flags() const { return( m_flags ); }
	void setFlags( Flags value ) { m_flags = value; }

	double risingEdgeTime() const { return( m_risingEdgeTime * 1e-6 ); }
	void setRisingEdgeTime( double value )
	{
		if ( value < 5e-6 ) { value = 5e-6; }
		if ( value > 20e-6 ) { value = 20e-6; }
		m_risingEdgeTime = std::lround( value * 1e6 );
	}

	double fallingEdgeTime() const { return( m_fallingEdgeTime * 1e-6 ); }
	void setFallingEdgeTime( double value )
	{
		if ( value < 1e-6 ) { value = 1e-6; }
		if ( value > 20e-6 ) { value = 20e-6; }
		m_fallingEdgeTime = std::lround( value * 1e6 );
	}

	double deviation1() const { return( m_deviation.d1() ); }
	bool isLfm1() const { return ( m_deviation.isLfm1() ); }

	double pulseTime1() const
	{
		if ( isLfm1() )
		{
			switch ( m_pulseTime1 )
			{
			case 1:
				return ( 100e-6 );

			case 2:
				return ( 200e-6 );

			case 3:
				return ( 300e-6 );

			case 4:
				return ( 400e-6 );

			case 5:
				return ( 50e-6 );

			case 6:
				return ( 40e-6 );

			case 7:
				return ( 30e-6 );

			default:
				return ( 0.0 );
			} // switch
		}
		return( m_pulseTime1 * 1e-6 );
	} // pulseTime1

	void setPulseDeviationAndTime1( double deviation, double time )
	{
		m_deviation.setD1( deviation );
		if ( time < 0 ) { time = 0; }
		if ( isLfm1() )
		{
			if ( std::abs( time - 100e-6 ) < 5e-6 ) { m_pulseTime1 = 1; return; }
			if ( std::abs( time - 200e-6 ) < 5e-6 ) { m_pulseTime1 = 2; return; }
			if ( std::abs( time - 300e-6 ) < 5e-6 ) { m_pulseTime1 = 3; return; }
			if ( std::abs( time - 400e-6 ) < 5e-6 ) { m_pulseTime1 = 4; return; }
			if ( std::abs( time - 50e-6 ) < 5e-6 ) { m_pulseTime1 = 5; return; }
			if ( std::abs( time - 40e-6 ) < 5e-6 ) { m_pulseTime1 = 6; return; }
			if ( std::abs( time - 30e-6 ) < 5e-6 ) { m_pulseTime1 = 7; return; }
			m_pulseTime1 = 0;
		}
		else
		{
			if ( time < 3e-6 ) { time = 0; }
			else
			{
				if ( time < 4.5e-6 ) { time = 4e-6; }
				else
				{
					if ( time < 7.5e-6 ) { time = 5e-6; }
					else { time = 10e-6; } }
			}

			m_pulseTime1 = std::lround( time * 1e6 );
		}
	} // setPulseTime1

	double deviation2() const { return( m_deviation.d2() ); }
	bool isLfm2() const { return ( m_deviation.isLfm2() ); }

	double pulseTime2() const
	{
		if ( isLfm2() )
		{
			switch ( m_pulseTime2 )
			{
			case 1:
				return ( 100e-6 );

			case 2:
				return ( 200e-6 );

			case 3:
				return ( 300e-6 );

			case 4:
				return ( 400e-6 );

			case 5:
				return ( 50e-6 );

			case 6:
				return ( 40e-6 );

			case 7:
				return ( 30e-6 );

			default:
				return ( 0.0 );
			} // switch
		}
		return( m_pulseTime2 * 1e-6 );
	} // pulseTime2

	void setPulseDeviationAndTime2( double deviation, double time )
	{
		m_deviation.setD2( deviation );
		if ( time < 0 ) { time = 0; }
		if ( isLfm2() )
		{
			if ( std::abs( time - 100e-6 ) < 5e-6 ) { m_pulseTime2 = 1; return; }
			if ( std::abs( time - 200e-6 ) < 5e-6 ) { m_pulseTime2 = 2; return; }
			if ( std::abs( time - 300e-6 ) < 5e-6 ) { m_pulseTime2 = 3; return; }
			if ( std::abs( time - 400e-6 ) < 5e-6 ) { m_pulseTime2 = 4; return; }
			if ( std::abs( time - 50e-6 ) < 5e-6 ) { m_pulseTime2 = 5; return; }
			if ( std::abs( time - 40e-6 ) < 5e-6 ) { m_pulseTime2 = 6; return; }
			if ( std::abs( time - 30e-6 ) < 5e-6 ) { m_pulseTime2 = 7; return; }
			m_pulseTime2 = 0;
		}
		else
		{
			if ( time < 3e-6 ) { time = 0; }
			else
			{
				if ( time < 4.5e-6 ) { time = 4e-6; }
				else
				{
					if ( time < 7.5e-6 ) { time = 5e-6; }
					else { time = 10e-6; } }
			}
			m_pulseTime2 = std::lround( time * 1e6 );
		}
	} // setPulseTime2

	double receivingTime1() const { return( m_receivingTime1 * 1e-6 ); }
	void setReceivingTime1( double value )
	{
		if ( value < 0 ) { value = 0; }
		m_receivingTime1 = std::lround( value * 1e6 );
	}

	double receivingTime2() const { return( m_receivingTime2 * 1e-6 ); }
	void setReceivingTime2( double value )
	{
		if ( value < 0 ) { value = 0; }
		m_receivingTime2 = std::lround( value * 1e6 );
	}

	double freq1() const { return( ( m_freq1 + 5e3 ) * 10e3 ); }
	void setFreq1( double value )
	{
		if ( value < 50e6 ) { value = 50e6; }
		if ( value > 70e6 ) { value = 70e6; }
		m_freq1 = std::lround( ( value / 10e3 ) - 5e3 );
	}

	double freq2() const { return( ( m_freq2 + 5e3 ) * 10e3 ); }
	void setFreq2( double value )
	{
		if ( value < 50e6 ) { value = 50e6; }
		if ( value > 70e6 ) { value = 70e6; }
		m_freq2 = std::lround( ( value / 10e3 ) - 5e3 );
	}

	double pulsesGap() const { return( m_pulsesGap * 1e-6 ); }
	void setPulsesGap( double value )
	{
		if ( value < 0 ) { value = 0; }
		m_pulsesGap = std::lround( value * 1e6 );
	}

	double bandwidth() const { return( m_bandwidth * 100e3 ); }
	void setBandwidth( double value )
	{
		if ( value < 100e3 ) { value = 100e3; }
		m_bandwidth = std::lround( value / 100e3 );
	}

	int attenuator() const { return( m_attenuator ); }
	void setAttenuator( int value ) { m_attenuator = static_cast< quint8 >( value & 0xFF ); }

	quint8 pattern() const { return( m_pattern.pattern() ); }
	void setPattern( quint8 value ) { m_pattern.setPattern( value & 0xF ); }

	quint8 counter() const { return( m_pattern.counter() ); }
	void setCounter( quint8 value )
	{
		if ( value < 8 ) { value = 8; }
		m_pattern.setCounter( value & 0xF );
	}

	double csFreq() const { return ( ( m_csFreq + 5e3 ) * 10e3 ); }
	void setCsFreq( double value )
	{
		if ( value < 50e6 ) { value = 50e6; }
		if ( value > 70e6 ) { value = 70e6; }
		m_csFreq = std::lround( ( value / 10e3 ) - 5e3 );
	}

	double csDelay() const { return( m_csDelay * 1e-6 ); }
	void setCsDelay( double value )
	{
		if ( value < 0 ) { value = 0; }
		m_csDelay = std::lround( value * 1e6 );
	}

	int csAmplitude() const { return( m_csAmplitude ); }
	void setCsAmplitude( int value ) { m_csAmplitude = static_cast< quint16 >( value & 0xFFFF ); }

	double startDelay() const { return( m_startDelay * 1e-6 ); }
	void setStartDelay( double value )
	{
		if ( value < 5e-6 ) { value = 5e-6; }
		m_startDelay = std::lround( value * 1e6 );
	}

	double finishDelay() const { return( m_finishDelay * 1e-6 ); }
	void setFinishDelay( double value )
	{
		if ( value < 5e-6 ) { value = 5e-6; }
		m_finishDelay = std::lround( value * 1e6 );
	}

	double receivingTimeBoth() const { return( m_receivingTimeBoth * 1e-6 ); }
	void setReceivingTimeBoth( double value )
	{
		if ( value < 0 ) { value = 0; }
		m_receivingTimeBoth = std::lround( value * 1e6 );
	}

	quint8 modeId() const { return( m_modeId.id() ); }
	void setModeId( quint8 value ) { m_modeId.setId( value & 0x7 ); }

	quint16 rand() const { return( m_modeId.rand() ); }
	void setRand( int value ) { m_modeId.setRand( value & 0x1FFF ); }


	quint16 distanceChannel() const { return( m_distanceChannel ); }
	void setDistanceChannel( quint16 value ) { m_distanceChannel = value; }

	float falseAlert1() const { return( m_falseAlert1 ); }
	void setFalseAlert1( float value ) { m_falseAlert1 = value; }

	float falseAlert2() const { return( m_falseAlert2 ); }
	void setFalseAlert2( float value ) { m_falseAlert2 = value; }

	float userThreshold1() const { return( m_userThreshold1 ); }
	void setUserThreshold1( float value ) { m_userThreshold1 = value; }

	float userThreshold2() const { return( m_userThreshold2 ); }
	void setUserThreshold2( float value ) { m_userThreshold2 = value; }

	float searchZoneStart1() const { return( m_searchZoneStart1 ); }
	void setSearchZoneStart1( float value ) { m_searchZoneStart1 = value; }

	float searchZoneStart2() const { return( m_searchZoneStart2 ); }
	void setSearchZoneStart2( float value ) { m_searchZoneStart2 = value; }

	float convolutionPart1() const { return( m_convolutionPart1 ); }
	void setConvolutionPart1( float value ) { m_convolutionPart1 = value; }

	float convolutionPart2() const { return( m_convolutionPart2 ); }
	void setConvolutionPart2( float value ) { m_convolutionPart2 = value; }

	float softAttenuator1() const { return( m_softAttenuator1 ); }
	void setSoftAttenuator1( float value ) { m_softAttenuator1 = value; }

	float softAttenuator2() const { return( m_softAttenuator2 ); }
	void setSoftAttenuator2( float value ) { m_softAttenuator2 = value; }

	quint16 rejectedFilters1() const { return( m_rejectedFilters1 ); }
	void setRejectedFilters1( quint16 value ) { m_rejectedFilters1 = value; }

	quint16 rejectedFilters2() const { return( m_rejectedFilters2 ); }
	void setRejectedFilters2( quint16 value ) { m_rejectedFilters2 = value; }

	quint8 smoothWindow1() const { return( m_smoothWindow1 ); }
	void setSmoothWindow1( quint8 value ) { m_smoothWindow1 = value; }

	quint8 smoothWindow2() const { return( m_smoothWindow2 ); }
	void setSmoothWindow2( quint8 value ) { m_smoothWindow2 = value; }

	quint8 convolution1() const { return( m_convolution1 ); }
	void setConvolution1( quint8 value ) { m_convolution1 = value; }

	quint8 convolution2() const { return( m_convolution2 ); }
	void setConvolution2( quint8 value ) { m_convolution2 = value; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Command& value );
	friend QDataStream& operator>>( QDataStream& ds, Command& value );
	friend QDebug operator<<( QDebug dbg, const Command value );
	#endif

private:
	Mode             m_mode { Mode::CheckBoot };  /*!< Набор исполняемых команд */
	Flags            m_flags { Flags::Unset };    /*!< Дополнительные флаги */
	quint8           m_risingEdgeTime { 5 };      /*!< Длительность переднего фронта, мкс (5..) */
	quint8           m_fallingEdgeTime { 1 };     /*!< Длительность заднего фронта, мкс (1..) */
	quint8           m_pulseTime1 { 2 };          /*!< Длительность первого ЗС, (0, 1, 2...5) -> (0, 100, 200...500) мкс */
	quint8           m_pulseTime2 { 5 };          /*!< Длительность второго ЗС, мкс */
	quint16          m_receivingTime1 { 0 };      /*!< Время приёма первого ЗС, мкс */
	quint16          m_receivingTime2 { 200 };    /*!< Время приёма второго ЗС, мкс */
	quint16          m_freq1 { 100 };             /*!< Опорная частота первого ЗС, */
	quint16          m_freq2 { 200 };             /*!< Опорная частота второго ЗС */
	quint8           m_pulsesGap { 5 };           /*!< Пауза между импульсами, мкс */
	quint8           m_bandwidth { 2 };           /*!< Полоса пропускания, (1, 2, 3, 4, 5) -> (100, 200, 312.5, 400, 500) кГц */
	quint8           m_attenuator { 0 };          /*!< Аттенюатор, дБ */
	PatternControl   m_pattern;                   /*!< Шаблон излучения передатчика */
	quint16          m_csFreq { 100 };            /*!< Частота КС */
	quint16          m_csDelay { 200 };           /*!< Задержка КС */
	quint16          m_csAmplitude { 255 };       /*!< Амплитуда КС */
	quint8           m_startDelay { 10 };         /*!< Пауза перед началом дискретизации, мкс */
	quint8           m_finishDelay { 10 };        /*!< Пауза после окончания дискретизации, мкс */
	quint16          m_receivingTimeBoth { 250 }; /*!< Время совместного приема */
	ModeId           m_modeId;                    /*!< Идентификатор текущего режима */
	DeviationControl m_deviation;                 /*!< Управление девиацией */
	quint16          m_distanceChannel { 0 };     /*!< Номер канала дальности для построения межпериодного спектра, 1...N, 0 - нормальный режим чтения данных по UART */
	quint8           m_stub1 { 0 };
	quint16          m_stub2 { 0 };
	float            m_falseAlert1 { 1e-5F };     //!< Вероятность ложной тревоги
	float            m_falseAlert2 { 1e-5F };     //!< Вероятность ложной тревоги
	float            m_userThreshold1 { 1.0F };   //!< Программный порог
	float            m_userThreshold2 { 1.0F };   //!< Программный порог
	float            m_searchZoneStart1 { 0.0F }; //!< Начало зоны обзора
	float            m_searchZoneStart2 { 0.0F }; //!< Начало зоны обзора
	float            m_convolutionPart1 { 1.0F }; //!< Свёртка по части импульса
	float            m_convolutionPart2 { 1.0F }; //!< Свёртка по части импульса
	float            m_softAttenuator1 { 50.0F }; //!< Программный аттенюатор
	float            m_softAttenuator2 { 50.0F }; //!< Программный аттенюатор
	quint16          m_rejectedFilters1 { 4 };    //!< Количество фильтров для режекции по скорости
	quint16          m_rejectedFilters2 { 4 };    //!< Количество фильтров для режекции по скорости
	quint8           m_smoothWindow1 { 6 };       //!< Параметры окна сглаживания
	quint8           m_smoothWindow2 { 6 };       //!< Параметры окна сглаживания
	quint8           m_convolution1 { 1 };        //!< Вкл. / выкл. программной свёртки
	quint8           m_convolution2 { 1 };        //!< Вкл. / выкл. программной свёртки
	quint32          m_user1 { 0 };
	quint32          m_user2 { 0 };
	quint32          m_user3 { 0 };
	quint64          m_zeroes1 { 0 };
	quint64          m_zeroes2 { 0 };
	quint64          m_zeroes3 { 0 };
	quint64          m_zeroes4 { 0 };
}; // class Command

#pragma pack(pop)

} // namespace veer::protocols::control::surok::receiver

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/surok/receiver/qt/command.hpp>
#endif

ENABLE_BITMASK_OPERATORS( veer::protocols::control::surok::receiver::Mode )
ENABLE_BITMASK_OPERATORS( veer::protocols::control::surok::receiver::Flags )

static_assert( sizeof( veer::protocols::control::surok::receiver::Command ) == 128,
               "Invalid size of class veer::protocols::control::surok::receiver::Command" );


#endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_COMMAND_HPP_

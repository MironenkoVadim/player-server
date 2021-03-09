#ifndef VEER_PROTOCOLS_PREPROC_SIGNAL_PACKET_HPP_
#define VEER_PROTOCOLS_PREPROC_SIGNAL_PACKET_HPP_

#pragma once

#include <veer/common/limits.hpp>
#include <veer/common/config.hpp>

namespace veer::protocols::preproc {

namespace constants
{

constexpr quint32 SignalHeaderMarker1 { 0xAACC3355 };
constexpr quint32 SignalHeaderMarker2 { 0x5533CCAA };
constexpr quint32 SignalHeaderMarker3 { 0xBBDD2244 };
constexpr quint32 SignalHeaderMarker4 { 0x4422DDBB };
constexpr quint32 SignalFooterMarker1 { 0x99FF1177 };
constexpr quint32 SignalFooterMarker2 { 0x7711FF99 };
constexpr quint32 SignalFooterMarker3 { 0x88EE0066 };
constexpr quint32 SignalFooterMarker4 { 0x6600EE88 };

constexpr quint16 SignalProtocolVersion { 11 };

} // namespace constants

namespace C  = constants;
namespace VC = veer::common;

#pragma pack(push, 1)


class SignalPacketHeader
{
public:
	bool areMarkersValid()
	{
		return ( ( m_marker1 == C::SignalHeaderMarker1 ) &&
		         ( m_marker2 == C::SignalHeaderMarker2 ) &&
		         ( m_marker3 == C::SignalHeaderMarker3 ) &&
		         ( m_marker4 == C::SignalHeaderMarker4 ) );
	}

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const SignalPacketHeader& value );
	friend QDataStream& operator>>( QDataStream& ds, SignalPacketHeader& value );
	#endif

private:
	//! Предопределенное значение: 0xAACC3355
	quint32 m_marker1 { C::SignalHeaderMarker1 };

	//! Предопределенное значение: 0x5533CCAA
	quint32 m_marker2 { C::SignalHeaderMarker2 };

	//! Размер заголовка, байт
	//! 1 гр. (Параметры обработки и обмена, меняется без переинициализации)
	quint16 m_headerSize { UINT16_MAX };

	//! Версия протокола
	//! 1 гр. (Параметры обработки и обмена, меняется без переинициализации)
	quint16 m_version { C::SignalProtocolVersion };

	//! Количество переданных блоков накопления
	//! 1 гр. (Параметры обработки и обмена, меняется без переинициализации)
	quint32 m_counter { UINT32_MAX };

	//! Время, мс (QDateTime::toMSecsSinceEpoch)
	//! 1 гр. (Параметры обработки и обмена, меняется без переинициализации)
	qint64 m_currentTime { INT64_MAX };

	//! Наличие излучения в 1-ом азимутальном секторе
	//! 1 гр. (Параметры обработки и обмена, меняется без переинициализации)
	quint8 m_pulseIn1Sector { UINT8_MAX };

	//! Наличие излучения во 2-ом азимутальном секторе
	//! 1 гр. (Параметры обработки и обмена, меняется без переинициализации)
	quint8 m_pulseIn2Sector { UINT8_MAX };

	//! Наличие излучения в 3-ем азимутальном секторе
	//! 1 гр. (Параметры обработки и обмена, меняется без переинициализации)
	quint8 m_pulseIn3Sector { UINT8_MAX };

	//! Наличие излучения в 4-ом азимутальном секторе
	//! 1 гр. (Параметры обработки и обмена, меняется без переинициализации)
	quint8 m_pulseIn4Sector { UINT8_MAX };

	//! Контрольная сумма для первого блока параметров
	quint32 m_crc1Block  { UINT32_MAX };


	//! Несущая частота, Гц
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	double m_carrierFreq { VC::DoubleNAN };

	//! Частота дискретизации, Гц
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	double m_samplingFreq { VC::DoubleNAN };

	//! Период повторения, с
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	double m_repetitionPeriod { VC::DoubleNAN };

	//! Пороговый коэффициент, зависящий от вероятности ложной тревоги
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	double m_falseAlertProbability { VC::DoubleNAN };

	//! Корректирующий пороговый коэффициент
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	double m_thresholdUser { VC::DoubleNAN };

	//! Часть ЛЧМ сигнала для обработки
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	double m_lfmPart { VC::DoubleNAN };

	//! Диэлектрическая проницаемость почвы
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	double m_epsilon { VC::DoubleNAN };

	//! Удельная электрическая проводимость почвы
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	double m_sigma { VC::DoubleNAN };

	//! Среднеквадратичное отклонение неровностей, взятое как сигма 35% высоты
	//! отклонения от вершины до основания при синусоидальной форме отклонения
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	double m_sigmaRough { VC::DoubleNAN };

	//! Номер режима работы
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	quint8 m_modeNumber { UINT8_MAX };

	//! Признак первичке проводить сжатие (свертку) ЛЧМ-сигнала
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	quint8 m_withConvolution { UINT8_MAX };

	//! Размер окна сглаживания для режекции несинхронной импульсной помехи
	//! (количество точек фильтра)
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	quint8 m_windowFunction { UINT8_MAX };

	//! Способ передачи данных
	//! (0 - без накопления периодов, 1 - с накоплением)
	//! 2 гр. (Параметры обработки, меняется без переинициализации)
	quint8 m_withAccumulation { UINT8_MAX };

	//! Контрольная сумма для второго блока параметров
	quint32 m_crc2Block  { UINT32_MAX };


	//! Время излучения, с
	//! 3 гр. (Параметры обработки, изменение требует переинициализации структур)
	double m_pulseTime { VC::DoubleNAN };

	//! Девиация импульса, Гц
	//! 3 гр. (Параметры обработки, изменение требует переинициализации структур)
	double m_deviation { VC::DoubleNAN };

	//! Время от окончания излучения импульса до начала приёма данных, с
	//! 3 гр. (Параметры обработки, изменение требует переинициализации структур)
	double m_receivingDelay { VC::DoubleNAN };

	//! Начало зоны обзора, м
	//! 3 гр. (Параметры обработки, изменение требует переинициализации структур)
	double m_searchZoneStart { VC::DoubleNAN };

	//! Количество каналов по дальности
	//! 3 гр. (Параметры обработки, изменение требует переинициализации структур)
	quint16 m_distanceChannels { UINT16_MAX };

	//! Количество каналов накопления
	//! 3 гр. (Параметры обработки, изменение требует переинициализации структур)
	quint16 m_accumulationChannels { UINT16_MAX };

	//! Коэффициент подавления боковых лепестков при фильтрации
	//! по когерентному наколению, дБ
	//! 3 гр. (Параметры обработки, изменение требует переинициализации структур)
	float m_attenuation { VC::FloatNAN };

	//! Количество фильтров с края спектра, содержащих пассивную помеху
	//! 3 гр. (Параметры обработки, изменение требует переинициализации структур)
	quint16 m_rejectedVelocityFilters { UINT16_MAX };

	//! Часть дальней дистанции поля для определения среднего уровня шума (в процентах)
	//! 3 гр. (Параметры обработки, изменение требует переинициализации структур)
	quint16 m_noiseDistance { UINT16_MAX };

	//! Контрольная сумма для третьего блока параметров
	quint32 m_crc3Block { UINT32_MAX };


	//! Угол поворота вибраторов между этажами, рад
	//! 4 гр. (Константы, предопределено)
	float angleBetweenFloors { VC::FloatNAN };

	//! Высота первого этажа антенны, м
	//! 4 гр. (Константы, предопределено)
	float distanceToFirstFloor { VC::FloatNAN };

	//! Расстояние между этажами антенны, м
	//! 4 гр. (Константы, предопределено)
	float distanceBetweenFloors { VC::FloatNAN };

	//! Длина плеча вибратора, м
	//! 4 гр. (Константы, предопределено)
	float halfDipoleLength { VC::FloatNAN };

	//! Количество угломестных каналов
	//! 4 гр. (Константы, предопределено)
	quint16 elevationChannels { UINT16_MAX };

	//! Количество азимутальных каналов
	//! 4 гр. (Константы, предопределено)
	quint16 azimuthChannels { UINT16_MAX };

	//! Контрольная сумма для четвертого блока параметров
	quint32 crc4Block { UINT32_MAX };


	//! Предопределенное значение: 0xBBDD2244
	quint32 m_marker3 { C::SignalHeaderMarker3 };

	//! Предопределенное значение: 0x4422DDBB
	quint32 m_marker4 { C::SignalHeaderMarker4 };
}; // class SignalPacketHeader


class SignalPacketFooter
{
public:
	bool areMarkersValid()
	{
		return ( ( m_marker1 == C::SignalFooterMarker1 ) &&
		         ( m_marker2 == C::SignalFooterMarker2 ) &&
		         ( m_marker3 == C::SignalFooterMarker3 ) &&
		         ( m_marker4 == C::SignalFooterMarker4 ) );
	}

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const SignalPacketFooter& value );
	friend QDataStream& operator>>( QDataStream& ds, SignalPacketFooter& value );
	#endif

private:
	//! Предопределенное значение: 0x99FF1177
	quint32 m_marker1 { C::SignalFooterMarker1 };

	//! Предопределенное значение: 0x7711FF99
	quint32 m_marker2 { C::SignalFooterMarker2 };

	//! Корректность данных
	quint8 m_dataCorrect { UINT8_MAX };

	quint8 m_stub1 { 0 };

	quint16 m_stub2 { 0 };

	quint32 m_stub3 { 0 };

	//! Предопределенное значение: 0x88EE0066
	quint32 m_marker3 { C::SignalFooterMarker3 };

	//! Предопределенное значение: 0x6600EE88
	quint32 m_marker4 { C::SignalFooterMarker4 };
}; // class SignalPacketFooter


class SignalPacketData
{
public:
	SignalPacketHeader& header() { return( m_header ); }
	QByteArray& zones()          { return( m_signal ); }
	SignalPacketFooter& footer() { return( m_footer ); }

private:
	SignalPacketHeader m_header;
	QByteArray         m_signal;
	SignalPacketFooter m_footer;
};

#pragma pack(pop)

} // namespace veer::protocols::preproc

static_assert( sizeof( veer::protocols::preproc::SignalPacketHeader ) == 192,
               "Invalid size of struct veer::protocols::preproc::SignalPacketHeader" );

static_assert( sizeof( veer::protocols::preproc::SignalPacketFooter ) == 24,
               "Invalid size of struct veer::protocols::preproc::SignalPacketFooter" );


#endif // ifndef VEER_PROTOCOLS_PREPROC_MARKS_SIGNAL_HPP_

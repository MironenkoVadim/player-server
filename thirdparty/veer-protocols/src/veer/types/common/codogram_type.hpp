#ifndef VEER_TYPES_COMMON_CODOGRAM_TYPES_HPP_
#define VEER_TYPES_COMMON_CODOGRAM_TYPES_HPP_

#pragma once

#include <veer/common/config.hpp>


namespace veer::types::common {

enum class CodogramType : quint16
{
	Zero                = 0x0000,
	Error               = 0x0001, //!< Ошибка
	Blob                = 0x0010, //!< Произвольные данные
	Ping                = 0x0020, //!< Тестовый запрос
	Pong                = 0x0021, //!< Ответ на тестовый запрос
	FrequenciesMask     = 0x0101, //!< Маска разрешённых / запрещённых частот
	ReceivingAntenna    = 0x0111, //!< Параметры приёмной антенны
	MarksPack           = 0x0211, //!< Набор отметок
	NoiseMarksPack      = 0x0212, //!< Набор шумовых отметок
	SpectrumsRequest    = 0x0230, //!< Запрос набора спектров
	SpectrumsPack       = 0x0231, //!< Набор спектров
	TracksPack          = 0x0301, //!< Набор трасс
	RadarTracksPack     = 0x0302, //!< Набор трасс от радара
	AdsbTracksPack      = 0x0305, //!< Набор трасс от АЗН-В
	MrtTracksPack       = 0x0309, //!< Набор трасс от третички
	ImitatorTargetsPack = 0x0311, //!< Набор трасс имитатора
	ImitatorParameters  = 0x0312, //!< Параметры имитатора
	CmdResetTrack       = 0x0501, //!< Сброс трассы
	CmdRenumberTrack    = 0x0502, //!< Изменение номера трассы
	AfcTimeSource       = 0x0801, //!< Результат функционального контроля сервера времени
	AfcCompFc           = 0x0811, //!< Результат функционального контроля ПЭВМ функционального контроля
	AfcCompServer       = 0x0812, //!< Результат функционального контроля сервера
	AfcCompTows         = 0x0813, //!< Результат функционального контроля технологического рабочего места
	AfcCompXows         = 0x0814, //!< Результат функционального контроля удалённого рабочего места
	AfcSummary          = 0x0888, //!< Результат обобщённого технического состояния
	Undefined           = 0xFFFF
};

} // namespace veer::types::common

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/common/qt/codogram_type.hpp>
#endif

static_assert( sizeof( veer::types::common::CodogramType ) == 2,
               "Invalid size of enum veer::types::common::CodogramTypes" );

#endif // ifndef VEER_TYPES_COMMON_CODOGRAM_TYPES_HPP_

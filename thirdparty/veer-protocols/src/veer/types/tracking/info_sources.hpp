#ifndef VEER_TYPES_TRACKING_INFO_SOURCES_HPP_
#define VEER_TYPES_TRACKING_INFO_SOURCES_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/backports/cpp/helpers.hpp>
#include <veer/common/enum_bitmask_operations.hpp>

namespace veer::types::tracking {

/*!
 * \brief Источники информации от ПОИ
 */
enum class InfoSources : quint8
{
	Zero        = 0,
	Radar       = 0x01, //!< Трасса РЛС
	Adsb        = 0x02, //!< Трасса АЗН-В
	Iff         = 0x04, //!< Трасса НРЗ
	Mrt         = 0x08, //!< Трасса, полученная в результате третичной обработки
	CommandPost = 0x10, //!< Трасса от КП
	Imitator    = 0x20, //!< Трасса от тестового имитатора
	Undefined   = 0xFF
};

} // namespace veer::types::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/tracking/qt/info_sources.hpp>
#endif

// Обязательно в глобальной области видимости
ENABLE_BITMASK_OPERATORS( veer::types::tracking::InfoSources )

#endif // ifndef VEER_TYPES_TRACKING_INFO_SOURCES_HPP_

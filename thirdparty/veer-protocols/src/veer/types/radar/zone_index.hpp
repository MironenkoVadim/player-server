#ifndef VEER_TYPES_RADAR_ZONE_INDEX_HPP_
#define VEER_TYPES_RADAR_ZONE_INDEX_HPP_

#pragma once

#include <veer/backports/cpp/helpers.hpp>
#include <veer/common/config.hpp>

namespace veer::types::radar {

/**
 * \brief Индексы зон обзора
 */

enum class ZoneIndex : quint8
{
	First   = 0x00,
	Near    = 0x00,
	Second  = 0x01,
	Far     = 0x01,
	Unknown = 0xFF
};

} // namespace veer::types::radar

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/radar/qt/zone_index.hpp>
#endif

static_assert( sizeof( veer::types::radar::ZoneIndex ) == 1,
               "Invalid size of enum veer::types::radar::ZoneIndex" );

#endif // ifndef VEER_TYPES_RADAR_ZONE_INDEX_HPP_

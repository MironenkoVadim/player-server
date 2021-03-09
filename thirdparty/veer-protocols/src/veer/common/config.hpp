#ifndef VEER_COMMON_CONFIG_HPP_
#define VEER_COMMON_CONFIG_HPP_

#pragma once

/*!
 * \file Общие настройки для проекта
 */

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )

#include <QDataStream>

#if !defined( QT_NO_DEBUG )
#include <QDebugStateSaver>
#endif

#else

#include <cstdint>

using quint8  = ::uint8_t;
using quint16 = ::uint16_t;
using quint32 = ::uint32_t;
using quint64 = ::uint64_t;
using qint8   = ::int8_t;
using qint16  = ::int16_t;
using qint32  = ::int32_t;
using qint64  = ::int64_t;

#endif // if !defined( VEER_PROTOCOLS_WITHOUT_QT )

#endif // VEER_COMMON_CONFIG_HPP_

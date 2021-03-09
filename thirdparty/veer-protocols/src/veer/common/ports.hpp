#ifndef VEER_COMMON_PORTS_HPP_
#define VEER_COMMON_PORTS_HPP_

#pragma once

/*!
 * \file Порты для сетевого обмена
 */

#include <cinttypes>

namespace veer::common::ports {

/**
 * \brief Порт, на который отправляются команды от РМО для управления передатчиком
 */
constexpr quint16 AmplifierCommand { 7311 };

/**
 * \brief Порт, на котором РМО принимает ответы от передатчика
 */
constexpr quint16 AmplifierResponse { 7314 };

/**
 * \brief Порт, на который отправляются команды от РМО для управления приёмником
 */
constexpr quint16 ReceiverCommand { 7321 };

/**
 * \brief Порт, на котором РМО принимает ответы от приёмника
 */
constexpr quint16 ReceiverResponse { 7324 };

/**
 * \brief Порт для выхода первички, обрабатывающей ближнюю зону
 */
constexpr quint16 PreprocessingNearZone { 7222 };

/**
 * \brief Порт для выхода первички, обрабатывающей дальнюю зону
 */
constexpr quint16 PreprocessingFarZone  { 7232 };

/**
 * \brief Базовый номер порта для подключения клиентов, принимающих спектры от первички.
 *        Номера для серверов первичной обработки вычисляются в зависимости от номера зоны обзора.
 */
constexpr quint16 PreprocessingSpectrumsBase { 7700 };

/**
 * \brief Порт для выхода программы поиска помех, обрабатывающей ближнюю зону
 */
constexpr quint16 NoiseDetectorNearZone { 7224 };

/**
 * \brief Порт для выхода программы поиска помех, обрабатывающей дальнюю зону
 */
constexpr quint16 NoiseDetectorFarZone  { 7234 };

/**
 * \brief Порт для выхода аккумулятора отметок
 */
constexpr quint16 MarksAccumulator      { 7252 };

/**
 * \brief Порт для выхода аккумулятора помеховых отметок
 */
constexpr quint16 NoiseMarksAccumulator { 7254 };

/**
 * \brief Порт для выхода вторички
 */
constexpr quint16 Tracking { 7261 };

/**
 * \brief Порт для выхода АЗН-В
 */
constexpr quint16 Adsb { 7263 };

/**
 * \brief Порт для выхода НРЗ
 */
constexpr quint16 Iff { 7265 };

/**
 * \brief Порт для выхода третички
 */
constexpr quint16 Mrt { 7269 };

/**
 * \brief Порт для выхода имитатора трасс
 */
constexpr quint16 TracksImitator { 7277 };

} // namespace veer::common::ports

#endif // ifndef VEER_COMMON_PORTS_HPP_

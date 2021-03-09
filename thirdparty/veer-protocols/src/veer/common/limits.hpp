#ifndef VEER_COMMON_LIMITS_HPP_
#define VEER_COMMON_LIMITS_HPP_

#pragma once

/*!
 * \file Глобальные передельные значения
 */

#include <veer/backports/compiler/gcc.hpp>

#include <limits>

namespace veer::common {

/**
 * \brief Константа, представляющая значение, не являющееся числом, для типа float
 */
constexpr float FloatNAN       { std::numeric_limits< float >::quiet_NaN() };

/**
 * \brief Константа, представляющая значение, не являющееся числом, для типа double
 */
constexpr double DoubleNAN     { std::numeric_limits< double >::quiet_NaN() };

/**
 * \brief Константа, представляющая значение, не являющееся числом, для типа long double
 */
constexpr long double LongDoubleNAN { std::numeric_limits< long double >::quiet_NaN() };

} // namespace veer::common

#endif // ifndef VEER_COMMON_LIMITS_HPP_

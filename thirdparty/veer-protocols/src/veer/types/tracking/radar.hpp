#ifndef VEER_TYPES_TRACKING_RADAR_HPP_
#define VEER_TYPES_TRACKING_RADAR_HPP_

#pragma once

#include <array>

namespace veer::types::tracking {

using PlanarCM = std::array< double, 10 >;
using HeightCM = std::array< double, 6 >;

} // namespace veer::types::tracking

#endif // ifndef VEER_TYPES_TRACKING_RADAR_HPP_

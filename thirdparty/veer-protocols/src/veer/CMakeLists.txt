# Название основной цели
set(TRGT veer)

set(TRGT_headers
  ${CMAKE_CURRENT_SOURCE_DIR}/backports/compiler/gcc.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/backports/cpp/helpers.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/backports/qt/common.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/common/config.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/common/const.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/common/enum_bitmask_operations.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/common/limits.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/common/ports.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/comp_fc.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/qt/comp_fc.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/comp_server.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/qt/comp_server.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/comp_tows.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/qt/comp_tows.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/comp_xows.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/qt/comp_xows.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/summary.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/qt/summary.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/time_source.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/afc/surok/qt/time_source.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/base/blob.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/base/error.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/base/header.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/base/ping.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/base/pong.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/base/qt/blob.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/base/qt/error.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/base/qt/header.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/base/qt/ping.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/base/qt/pong.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/gate/header.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/gate/receiver/command.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/gate/receiver/response.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/gate/amplifier/command.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/gate/amplifier/response.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/gate/qt/header.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/gate/amplifier/qt/command.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/gate/amplifier/qt/response.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/gate/receiver/qt/command.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/gate/receiver/qt/response.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/hw/receiver/command.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/hw/receiver/response.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/hw/receiver/qt/command.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/hw/receiver/qt/response.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/receiver/command.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/receiver/frequencies_mask.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/receiver/response.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/receiver/signal.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/receiver/qt/command.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/receiver/qt/frequencies_mask.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/receiver/qt/response.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/receiver/qt/signal.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/amplifier/command.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/amplifier/response.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/amplifier/qt/command.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/surok/amplifier/qt/response.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/receiving_antenna.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/control/qt/receiving_antenna.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/ksa/almaz/control_message.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/ksa/almaz/header.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/ksa/almaz/radar_track.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/ksa/almaz/qt/control_message.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/ksa/almaz/qt/header.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/ksa/almaz/qt/radar_track.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/preproc/marks_packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/preproc/signals_packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/preproc/spectrums_packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/preproc/spectrums_request.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/preproc/qt/marks_packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/preproc/qt/spectrums_packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/preproc/qt/spectrums_request.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/adsb_track.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/adsb_tracks_packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/base_track.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/cmd_reset.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/cmd_renumber.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/iff_track.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/mrt_track.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/mrt_tracks_packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/radar_track.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/radar_tracks_packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/target.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/qt/adsb_track.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/qt/adsb_tracks_packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/qt/base_track.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/qt/cmd_reset.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/qt/cmd_renumber.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/qt/iff_track.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/qt/mrt_track.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/qt/mrt_tracks_packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/qt/radar_track.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/qt/radar_tracks_packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/protocols/tracking/qt/target.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/application.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/qt/application.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/codogram_type.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/qt/codogram_type.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/error_codes.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/qt/error_codes.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/points.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/qt/points.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/timespec32.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/qt/timespec32.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/timespec64.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/qt/timespec64.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/timespecns.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/qt/timespecns.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/velocities.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/common/qt/velocities.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/types/preproc/adaptive_threshold.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/preproc/qt/adaptive_threshold.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/preproc/mark.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/preproc/qt/mark.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/preproc/mark_types.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/preproc/qt/mark_types.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/preproc/spectrum.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/preproc/qt/spectrum.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/types/radar/emission_direction.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/radar/qt/emission_direction.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/radar/emission_pattern.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/radar/qt/emission_pattern.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/radar/zone.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/radar/qt/zone.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/radar/zone_index.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/radar/qt/zone_index.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/types/radar/surok/common.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/radar/surok/qt/common.hpp

  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/adsb.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/qt/adsb.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/info_sources.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/qt/info_sources.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/iff.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/qt/iff.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/maneuver_type.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/qt/maneuver_type.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/radar.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/track_status.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/qt/track_status.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/target_type.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types/tracking/qt/target_type.hpp
  )

add_library(${TRGT} INTERFACE)
target_include_directories(${TRGT} INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(${TRGT} INTERFACE ${Qt5Core_INCLUDE_DIRS})

add_clang_tidy_check(${TRGT} ${TRGT_headers})
add_clang_analyze_check(${TRGT} ${TRGT_headers})
add_clazy_check(${TRGT} ${TRGT_headers})
add_pvs_check(${TRGT})

add_format_sources(${TRGT} ${TRGT_headers})

add_common_library(${TRGT}-fake OUTPUT_NAME ${TRGT}
                                SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/protocols/fake.cpp)
target_include_directories(${TRGT}-fake SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(${TRGT}-fake SYSTEM PUBLIC ${Qt5Core_INCLUDE_DIRS})

install(DIRECTORY backports common protocols types
        COMPONENT dev
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${TRGT})

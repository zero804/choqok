set(choqok_tinyarro_ws_SRCS
    tinyarro_ws.cpp
)

kconfig_add_kcfg_files(choqok_tinyarro_ws_SRCS tinyarro_ws_settings.kcfgc)

kcoreaddons_add_plugin(choqok_tinyarro_ws SOURCES ${choqok_tinyarro_ws_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_tinyarro_ws choqok_tinyarro_ws.desktop)

target_link_libraries(choqok_tinyarro_ws
PUBLIC
    Qt5::Core
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    choqok
)

set(kcm_choqok_tinyarro_ws_PART_SRCS
    tinyarro_ws_config.cpp
)

ki18n_wrap_ui(kcm_choqok_tinyarro_ws_PART_SRCS tinyarro_ws_prefs.ui)

kconfig_add_kcfg_files(kcm_choqok_tinyarro_ws_PART_SRCS tinyarro_ws_settings.kcfgc)

kcoreaddons_add_plugin(kcm_choqok_tinyarro_ws SOURCES ${kcm_choqok_tinyarro_ws_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(kcm_choqok_tinyarro_ws choqok_tinyarro_ws_config.desktop)

target_link_libraries(kcm_choqok_tinyarro_ws
PUBLIC
    Qt5::Core
    KF5::ConfigCore
    KF5::ConfigWidgets
    KF5::CoreAddons
    KF5::I18n
    choqok
)

install(FILES tinyarro_ws_settings.kcfg DESTINATION ${KCFG_INSTALL_DIR})

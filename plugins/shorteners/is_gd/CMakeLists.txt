set(choqok_is_gd_SRCS
    is_gd.cpp
)

kconfig_add_kcfg_files(choqok_is_gd_SRCS is_gd_settings.kcfgc)

kcoreaddons_add_plugin(choqok_is_gd SOURCES ${choqok_is_gd_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_is_gd choqok_is_gd.desktop)

target_link_libraries(choqok_is_gd
PUBLIC
    Qt5::Core
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    choqok
)

set(kcm_choqok_is_gd_PART_SRCS
    is_gd_config.cpp
)

ki18n_wrap_ui(kcm_choqok_is_gd_PART_SRCS is_gd_prefs.ui)

kconfig_add_kcfg_files(kcm_choqok_is_gd_PART_SRCS is_gd_settings.kcfgc)

kcoreaddons_add_plugin(kcm_choqok_is_gd SOURCES ${kcm_choqok_is_gd_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(kcm_choqok_is_gd choqok_is_gd_config.desktop)

target_link_libraries(kcm_choqok_is_gd
PUBLIC
    Qt5::Core
    KF5::ConfigWidgets
    KF5::CoreAddons
    KF5::I18n
    choqok
)

install(FILES is_gd_settings.kcfg DESTINATION ${KCFG_INSTALL_DIR})

set(choqok_yourls_SRCS
    yourls.cpp
)

kconfig_add_kcfg_files(choqok_yourls_SRCS yourlssettings.kcfgc)

kcoreaddons_add_plugin(choqok_yourls SOURCES ${choqok_yourls_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_yourls choqok_yourls.desktop)

target_link_libraries(choqok_yourls
PUBLIC
    Qt5::Core
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    choqok
)

set(kcm_choqok_yourls_PART_SRCS
    yourlsconfig.cpp
)

ki18n_wrap_ui(kcm_choqok_yourls_PART_SRCS yourlsprefs.ui)

kconfig_add_kcfg_files(kcm_choqok_yourls_PART_SRCS yourlssettings.kcfgc)

kcoreaddons_add_plugin(kcm_choqok_yourls SOURCES ${kcm_choqok_yourls_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(kcm_choqok_yourls choqok_yourls_config.desktop)

target_link_libraries(kcm_choqok_yourls
PUBLIC
    Qt5::Core
    KF5::ConfigWidgets
    KF5::CoreAddons
    KF5::I18n
    choqok
)

install(FILES yourlssettings.kcfg DESTINATION ${KCFG_INSTALL_DIR})

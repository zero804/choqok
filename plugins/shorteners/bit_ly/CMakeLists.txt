set(choqok_bit_ly_SRCS
    bit_ly.cpp
)

kconfig_add_kcfg_files(choqok_bit_ly_SRCS bit_ly_settings.kcfgc)

kcoreaddons_add_plugin(choqok_bit_ly SOURCES ${choqok_bit_ly_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_bit_ly choqok_bit_ly.desktop)

target_link_libraries(choqok_bit_ly
PUBLIC
    Qt5::Core
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    choqok
)

set(kcm_choqok_bit_ly_PART_SRCS
    bit_ly_config.cpp
)

ki18n_wrap_ui(kcm_choqok_bit_ly_PART_SRCS bit_ly_prefs.ui)

kconfig_add_kcfg_files(kcm_choqok_bit_ly_PART_SRCS bit_ly_settings.kcfgc)

kcoreaddons_add_plugin(kcm_choqok_bit_ly SOURCES ${kcm_choqok_bit_ly_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(kcm_choqok_bit_ly choqok_bit_ly_config.desktop)

target_link_libraries(kcm_choqok_bit_ly
PUBLIC
    Qt5::Core
    KF5::ConfigCore
    KF5::ConfigWidgets
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    KF5::WidgetsAddons
    choqok
)

install(FILES bit_ly_settings.kcfg DESTINATION ${KCFG_INSTALL_DIR})

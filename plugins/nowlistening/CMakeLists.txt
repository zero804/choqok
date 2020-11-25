include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_nowlistening_PART_SRCS
    mpris.cpp
    nowlistening.cpp
)

kconfig_add_kcfg_files(choqok_nowlistening_PART_SRCS nowlisteningsettings.kcfgc)

kcoreaddons_add_plugin(choqok_nowlistening SOURCES ${choqok_nowlistening_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_nowlistening choqok_nowlistening.desktop)

target_link_libraries(choqok_nowlistening
PUBLIC
    Qt5::Core
    Qt5::DBus
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::WidgetsAddons
    KF5::XmlGui
    choqok
)

set(kcm_choqok_nowlistening_PART_SRCS
    nowlisteningconfig.cpp
)

ki18n_wrap_ui(kcm_choqok_nowlistening_PART_SRCS nowlisteningprefs.ui)

kconfig_add_kcfg_files(kcm_choqok_nowlistening_PART_SRCS nowlisteningsettings.kcfgc)

kcoreaddons_add_plugin(kcm_choqok_nowlistening SOURCES ${kcm_choqok_nowlistening_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(kcm_choqok_nowlistening choqok_nowlistening_config.desktop)

target_link_libraries(kcm_choqok_nowlistening
PUBLIC
    Qt5::Widgets
    KF5::ConfigWidgets
    KF5::CoreAddons
    KF5::I18n
)

install(FILES nowlisteningsettings.kcfg DESTINATION ${KCFG_INSTALL_DIR})
install(FILES nowlisteningui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/choqok_nowlistening)

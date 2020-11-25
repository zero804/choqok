set(choqok_flickr_PART_SRCS
    flickr.cpp
)

kconfig_add_kcfg_files(choqok_flickr_PART_SRCS flickrsettings.kcfgc)

kcoreaddons_add_plugin(choqok_flickr SOURCES ${choqok_flickr_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_flickr choqok_flickr.desktop)

target_link_libraries(choqok_flickr
PUBLIC
    Qt5::Core
    Qt5::Xml
    KF5::ConfigWidgets
    KF5::CoreAddons
    KF5::KIOCore
    choqok
)

set(kcm_choqok_flickr_PART_SRCS
    flickrconfig.cpp
)

ki18n_wrap_ui(kcm_choqok_flickr_PART_SRCS flickrprefs.ui)

kconfig_add_kcfg_files(kcm_choqok_flickr_PART_SRCS flickrsettings.kcfgc)

kcoreaddons_add_plugin(kcm_choqok_flickr SOURCES ${kcm_choqok_flickr_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(kcm_choqok_flickr choqok_flickr_config.desktop)

target_link_libraries(kcm_choqok_flickr
PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Xml
    KF5::ConfigCore
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    KF5::WidgetsAddons
    choqok
)

install(FILES flickrsettings.kcfg DESTINATION ${KCFG_INSTALL_DIR})

add_subdirectory(icons)

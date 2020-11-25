include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_twitgoo_PART_SRCS
    twitgoo.cpp
)

kconfig_add_kcfg_files(choqok_twitgoo_PART_SRCS twitgoosettings.kcfgc)

kcoreaddons_add_plugin(choqok_twitgoo SOURCES ${choqok_twitgoo_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_twitgoo choqok_twitgoo.desktop)

target_link_libraries(choqok_twitgoo
PUBLIC
    Qt5::Core
    Qt5::NetworkAuth
    KF5::CoreAddons
    KF5::KIOCore
    choqok
    twitterapihelper
)

set(kcm_choqok_twitgoo_PART_SRCS
    twitgooconfig.cpp
)

ki18n_wrap_ui(kcm_choqok_twitgoo_PART_SRCS twitgooprefs.ui)

kconfig_add_kcfg_files(kcm_choqok_twitgoo_PART_SRCS twitgoosettings.kcfgc)

kcoreaddons_add_plugin(kcm_choqok_twitgoo SOURCES ${kcm_choqok_twitgoo_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(kcm_choqok_twitgoo choqok_twitgoo_config.desktop)

target_link_libraries(kcm_choqok_twitgoo
PUBLIC
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::WidgetsAddons
    choqok
)

install(FILES twitgoosettings.kcfg  DESTINATION ${KCFG_INSTALL_DIR})

add_subdirectory(icons)

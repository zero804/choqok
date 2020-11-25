include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_twitpic_PART_SRCS
    twitpic.cpp
)

# ki18n_wrap_ui(choqok_twitpic_PART_SRCS twitpicuploadimage_base.ui)

kconfig_add_kcfg_files(choqok_twitpic_PART_SRCS twitpicsettings.kcfgc)

kcoreaddons_add_plugin(choqok_twitpic SOURCES ${choqok_twitpic_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_twitpic choqok_twitpic.desktop)

target_link_libraries(choqok_twitpic
PUBLIC
    Qt5::Core
    Qt5::NetworkAuth
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    choqok
    twitterapihelper
)

set(kcm_choqok_twitpic_PART_SRCS
twitpicconfig.cpp )

ki18n_wrap_ui(kcm_choqok_twitpic_PART_SRCS twitpicprefs.ui)

kconfig_add_kcfg_files(kcm_choqok_twitpic_PART_SRCS twitpicsettings.kcfgc )

kcoreaddons_add_plugin(kcm_choqok_twitpic SOURCES ${kcm_choqok_twitpic_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(kcm_choqok_twitpic choqok_twitpic_config.desktop)

target_link_libraries(kcm_choqok_twitpic choqok)

install(FILES twitpicsettings.kcfg  DESTINATION ${KCFG_INSTALL_DIR})
# install( FILES twitpicui.rc  DESTINATION  ${DATA_INSTALL_DIR}/choqok_twitpic )

add_subdirectory(icons)

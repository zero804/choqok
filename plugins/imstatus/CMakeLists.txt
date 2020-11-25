find_package(TelepathyQt5)

if(TelepathyQt5_FOUND)
    add_definitions( -DTELEPATHY_FOUND )
endif()

include_directories(
    ${CHOQOK_INCLUDES}
    ${TELEPATHY_QT5_INCLUDE_DIR}
)

set(choqok_imstatus_PART_SRCS
    imqdbus.cpp
    imstatus.cpp
)

kconfig_add_kcfg_files(choqok_imstatus_PART_SRCS imstatussettings.kcfgc)

kcoreaddons_add_plugin(choqok_imstatus SOURCES ${choqok_imstatus_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_imstatus choqok_imstatus.desktop)

target_link_libraries(choqok_imstatus
PUBLIC
    Qt5::Core
    Qt5::DBus
    KF5::CoreAddons
    ${TELEPATHY_QT5_LIBRARIES}
    choqok
)

set(kcm_choqok_imstatus_PART_SRCS
    imqdbus.cpp
    imstatusconfig.cpp
)

ki18n_wrap_ui(kcm_choqok_imstatus_PART_SRCS imstatusprefs.ui)

kconfig_add_kcfg_files(kcm_choqok_imstatus_PART_SRCS imstatussettings.kcfgc)

kcoreaddons_add_plugin(kcm_choqok_imstatus SOURCES ${kcm_choqok_imstatus_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(kcm_choqok_imstatus choqok_imstatus_config.desktop)

target_link_libraries(kcm_choqok_imstatus
PUBLIC
    Qt5::Core
    Qt5::DBus
    KF5::ConfigWidgets
    KF5::CoreAddons
    KF5::I18n
    ${TELEPATHY_QT5_LIBRARIES}
)

install(FILES imstatussettings.kcfg DESTINATION ${KCFG_INSTALL_DIR})

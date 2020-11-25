include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_longurl_PART_SRCS
    longurl.cpp
)

# kconfig_add_kcfg_files(choqok_longurl_PART_SRCS longurlsettings.kcfgc)

kcoreaddons_add_plugin(choqok_longurl SOURCES ${choqok_longurl_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_longurl choqok_longurl.desktop)

target_link_libraries(choqok_longurl
PUBLIC
    Qt5::Core
    KF5::CoreAddons
    KF5::KIOCore
    KF5::KIOWidgets
    choqok
)

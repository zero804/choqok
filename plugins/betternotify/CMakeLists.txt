include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_notify_PART_SRCS
    mytextbrowser.cpp
    notification.cpp
    notify.cpp
    notifysettings.cpp
)

# kconfig_add_kcfg_files(choqok_notify_PART_SRCS betternotify.kcfgc)

kcoreaddons_add_plugin(choqok_betternotify SOURCES ${choqok_notify_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_betternotify choqok_notify.desktop)

target_link_libraries(choqok_betternotify
PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    KF5::ConfigCore
    KF5::CoreAddons
    KF5::I18n
    choqok
)

set(kcm_choqok_notify_PART_SRCS
    dummynotification.cpp
    notifyconfig.cpp
    notifysettings.cpp
)

ki18n_wrap_ui(kcm_choqok_notify_PART_SRCS notifyprefs.ui)

# kconfig_add_kcfg_files(kcm_choqok_notify_PART_SRCS betternotify.kcfgc)

kcoreaddons_add_plugin(kcm_choqok_betternotify SOURCES ${kcm_choqok_notify_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(kcm_choqok_betternotify choqok_notify_config.desktop)

target_link_libraries(kcm_choqok_betternotify
PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    KF5::ConfigCore
    KF5::ConfigWidgets
    KF5::I18n
    choqok
)

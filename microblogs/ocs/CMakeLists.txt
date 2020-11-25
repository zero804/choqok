include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_ocs_SRCS
    ocsaccount.cpp
    ocsdebug.cpp
    ocsmicroblog.cpp
    ocsconfigurewidget.cpp
)

ki18n_wrap_ui(choqok_ocs_SRCS
    ocsconfigurebase.ui
)

kcoreaddons_add_plugin(choqok_ocs SOURCES ${choqok_ocs_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_ocs choqok_ocs.desktop)

target_link_libraries(choqok_ocs
PUBLIC
    KF5::Attica
    KF5::ConfigCore
    KF5::CoreAddons
    KF5::I18n
    KF5::WidgetsAddons
    choqok
)

add_subdirectory(icons)

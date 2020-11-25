include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_filter_PART_SRCS
    addeditfilter.cpp
    configurefilters.cpp
    filter.cpp
    filtermanager.cpp
    filtersettings.cpp
)

ki18n_wrap_ui(choqok_filter_PART_SRCS addeditfilter_base.ui filterprefs.ui)

kcoreaddons_add_plugin(choqok_filter SOURCES ${choqok_filter_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_filter choqok_filter.desktop)

target_link_libraries(choqok_filter
PUBLIC
    Qt5::Core
    Qt5::Widgets
    KF5::ConfigCore
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    KF5::WidgetsAddons
    KF5::XmlGui
    choqok
    twitterapihelper
)

install(FILES filterui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/choqok_filter)

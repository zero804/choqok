include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_searchaction_PART_SRCS
    searchaction.cpp
)

kcoreaddons_add_plugin(choqok_searchaction SOURCES ${choqok_searchaction_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_searchaction choqok_searchaction.desktop)

target_link_libraries(choqok_searchaction
PUBLIC
    Qt5::Core
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::WidgetsAddons
    KF5::XmlGui
    choqok
    twitterapihelper
)

install(FILES searchactionui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/choqok_searchaction)

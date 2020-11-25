include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_quickfilter_PART_SRCS
    quickfilter.cpp
)

kcoreaddons_add_plugin(choqok_quickfilter SOURCES ${choqok_quickfilter_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_quickfilter choqok_quickfilter.desktop)

target_link_libraries(choqok_quickfilter
PUBLIC
    Qt5::Core
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    choqok
)

install(FILES quickfilterui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/choqok_quickfilter)

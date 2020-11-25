include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_imagepreview_PART_SRCS
    imagepreview.cpp
)

kcoreaddons_add_plugin(choqok_imagepreview SOURCES ${choqok_imagepreview_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_imagepreview choqok_imagepreview.desktop)

target_link_libraries(choqok_imagepreview
PUBLIC
    Qt5::Core
    Qt5::Gui
    KF5::CoreAddons
    choqok
)

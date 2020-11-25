include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_videopreview_PART_SRCS
    videopreview.cpp
)

kcoreaddons_add_plugin(choqok_videopreview SOURCES ${choqok_videopreview_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_videopreview choqok_videopreview.desktop)

target_link_libraries(choqok_videopreview
PUBLIC
    Qt5::Core
    KF5::CoreAddons
    KF5::KIOCore
    KF5::KIOWidgets
    choqok
)

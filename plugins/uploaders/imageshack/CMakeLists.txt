set(choqok_imageshack_PART_SRCS
    imageshack.cpp
)

kcoreaddons_add_plugin(choqok_imageshack SOURCES ${choqok_imageshack_PART_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_imageshack choqok_imageshack.desktop)

target_link_libraries(choqok_imageshack
PUBLIC
    Qt5::Core
    Qt5::Xml
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    choqok
)

add_subdirectory(icons)

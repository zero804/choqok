set(choqok_tighturl_SRCS
    tighturl.cpp
)

kcoreaddons_add_plugin(choqok_tighturl SOURCES ${choqok_tighturl_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_tighturl choqok_tighturl.desktop)

target_link_libraries(choqok_tighturl
PUBLIC
    Qt5::Core
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    choqok
)

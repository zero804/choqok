
include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_friendica_SRCS
    friendicadebug.cpp
    friendicaeditaccount.cpp
    friendicamicroblog.cpp
)

ki18n_wrap_ui(choqok_friendica_SRCS friendicaeditaccount_base.ui)

kcoreaddons_add_plugin(choqok_friendica SOURCES ${choqok_friendica_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_friendica choqok_friendica.desktop)

target_link_libraries(choqok_friendica
PUBLIC
    Qt5::Core
    Qt5::NetworkAuth
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    KF5::KIOWidgets
    choqok
    gnusocialapihelper
)

add_subdirectory(icons)

include_directories(
    ${CHOQOK_INCLUDES}
)

set(choqok_mastodon_SRCS
    mastodonaccount.cpp
    mastodoncomposerwidget.cpp
    mastodondebug.cpp
    mastodondmessagedialog.cpp
    mastodoneditaccountwidget.cpp
    mastodonmicroblog.cpp
    mastodonoauth.cpp
    mastodonoauthreplyhandler.cpp
    mastodonpost.cpp
    mastodonpostwidget.cpp
)

ki18n_wrap_ui(choqok_mastodon_SRCS
    mastodoneditaccountwidget.ui
)

kcoreaddons_add_plugin(choqok_mastodon SOURCES ${choqok_mastodon_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_mastodon choqok_mastodon.desktop)

target_link_libraries(choqok_mastodon
PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::NetworkAuth
    Qt5::Widgets
    KF5::I18n
    KF5::KIOCore
    KF5::KIOWidgets
    KF5::WidgetsAddons
    qca-qt5
    choqok
)

add_subdirectory(icons)

set(choqok_goo_gl_SRCS
    goo_gl.cpp
)

kcoreaddons_add_plugin(choqok_goo_gl SOURCES ${choqok_goo_gl_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_goo_gl choqok_goo_gl.desktop)

target_link_libraries(choqok_goo_gl
PUBLIC
    Qt5::Core
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    choqok
)

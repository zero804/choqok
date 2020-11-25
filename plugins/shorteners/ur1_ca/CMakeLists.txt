set(choqok_ur1_ca_SRCS
    ur1_ca.cpp
)

kcoreaddons_add_plugin(choqok_ur1_ca SOURCES ${choqok_ur1_ca_SRCS} INSTALL_NAMESPACE "choqok")

kcoreaddons_desktop_to_json(choqok_ur1_ca choqok_ur1_ca.desktop)

target_link_libraries(choqok_ur1_ca
PUBLIC
    Qt5::Core
    KF5::CoreAddons
    KF5::I18n
    KF5::KIOCore
    choqok
)

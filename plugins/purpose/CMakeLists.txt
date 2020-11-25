set(choqokplugin_SRCS purposeplugin.cpp)

qt5_add_dbus_interface(choqokplugin_SRCS org.kde.choqok.xml choqokinterface)

kcoreaddons_add_plugin(choqokplugin SOURCES ${choqokplugin_SRCS} INSTALL_NAMESPACE "kf5/purpose")

target_link_libraries(choqokplugin Qt5::DBus KF5::Purpose)

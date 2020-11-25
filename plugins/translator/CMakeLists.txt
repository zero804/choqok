
include_directories(
${CHOQOK_INCLUDES}
)

########### next target ###############

set( choqok_translator_PART_SRCS
sharedtools.cpp
translator.cpp )

kconfig_add_kcfg_files(choqok_translator_PART_SRCS translatorsettings.kcfgc)

kcoreaddons_add_plugin(choqok_translator SOURCES ${choqok_translator_PART_SRCS} INSTALL_NAMESPACE "choqok")

target_link_libraries(choqok_translator  KF5::KIOCore ${QJSON_LIBRARY} choqok)

install(FILES languagecodes DESTINATION ${DATA_INSTALL_DIR}/choqok)

########### next target ###############

set( kcm_choqok_translator_PART_SRCS
translatorconfig.cpp
sharedtools.cpp )

ki18n_wrap_ui(kcm_choqok_translator_PART_SRCS translatorprefs.ui )

kconfig_add_kcfg_files(kcm_choqok_translator_PART_SRCS translatorsettings.kcfgc )

kcoreaddons_add_plugin(kcm_choqok_translator SOURCES ${kcm_choqok_translator_PART_SRCS} INSTALL_NAMESPACE "choqok")

target_link_libraries(kcm_choqok_translator )

########### next target ###############

install( FILES translatorsettings.kcfg  DESTINATION ${KCFG_INSTALL_DIR})

#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 3.2)

#Name your project here
project(tcamprop)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(TCAMPROP_VERSION_MAJOR 0)
set(TCAMPROP_VERSION_MINOR 1)
set(TCAMPROP_VERSION_PATCH 0)

set(TCAMPROP_VERSION "${TCAMPROP_VERSION_MAJOR}.${TCAMPROP_VERSION_MINOR}.${TCAMPROP_VERSION_PATCH}" CACHE STRING "Version number")

set(default_build_type "Release")

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
    STRING "Choose the type of build." FORCE)

  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX "/usr/" CACHE PATH "Common prefix for all installed files." FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)


set(TCAMPROP_INSTALL_LIB "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "library installation path")
set(TCAMPROP_INSTALL_INCLUDE "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "header installation path")

add_subdirectory(src)

add_library( tcam::tcamprop ALIAS tcamprop )

# uninstall target
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

# create target uninstall to deinstall tiscamera
# if tiscamera is a subproject/module
# create uninstall-tcamprop instead
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
else()
  add_custom_target(uninstall-tcamprop
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

include(CPackComponent)

set(CPACK_COMPONENTS_ALL tcamprop)

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "The Imaging Source Europe GmbH <support@theimagingsource.com>")

set(CPACK_PACKAGE_DESCRIPTION "The Imaging Source tcamprop gobject introspection library")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Library used for gobject introspection.")
set(CPACK_PACKAGE_VENDOR "The Imaging Source Europe GmbH")
set(CPACK_PACKAGE_CONTACT "support@theimagingsource.com")
set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)

set(CPACK_PACKAGE_CHECKSUM "SHA512")

# based on current reference system
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libglib2.0-0 (>= 2.48.2), libgirepository-1.0-1 (>= 1.46.0)")

set(CPACK_SET_DESTDIR "on")
set(CPACK_GENERATOR "DEB")

set(CPACK_PACKAGE_VERSION_MAJOR "${TCAMPROP_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${TCAMPROP_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${TCAMPROP_VERSION_PATCH}")

include("git-helper")

git_commit_count(GIT_COMMIT_COUNT)
# ensure package version always increases
set(CPACK_DEBIAN_PACKAGE_VERSION "${TCAMPROP_VERSION}.${GIT_COMMIT_COUNT}")

set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/deb/postinst.in" "${CMAKE_CURRENT_BINARY_DIR}/deb/postinst")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/deb/prerm.in" "${CMAKE_CURRENT_BINARY_DIR}/deb/prerm")

set(CPACK_DEBIAN_PACKAGE_PROVIDES "tiscamera-tcamprop")

set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_BINARY_DIR}/deb/postinst;${CMAKE_CURRENT_BINARY_DIR}/deb/prerm;")


set(CPACK_PACKAGE_NAME "tiscamera-tcamprop")

include(package-name)

create_package_name(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}" "${TCAMPROP_VERSION}")

set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

# always last
include(CPack)

# A CMake module to generate LiteString packages.

# Set the CPack variables
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "Ian Duncan")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "dr8co@duck.com")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/dr8co/LiteString")

set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/Packages")

# Source package Generator variables
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_STRIP_FILES YES)
set(CPACK_SOURCE_IGNORE_FILES
        /.git
        /.idea
        /.github
        /.vscode
        /.cache
        /build
        /cmake-build-*
        /CMakeFiles
        /CMakeScripts
        /CMakeModules
        /CMakeLists.txt.user
        /CMakeCache.txt
        /CTestTestfile.cmake
        /Makefile
        /Makefile.in
        /CPackConfig.cmake
        /CPackSourceConfig.cmake
        /CPackSourceConfig.cmake
        /CPack
)

# Resource files
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/assets/welcome.txt")

set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_RPM_FILE_NAME RPM-DEFAULT)

# Set the package generator
if (WIN32)
    set(CPACK_GENERATOR "ZIP;INNOSETUP")
elseif (APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else ()
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
endif ()

# Set the package dependencies
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.38)")
set(CPACK_RPM_PACKAGE_REQUIRES "glibc >= 2.38")

# Use as many cores as available
set(CPACK_THREADS "0")

# Set the package architecture
set(CPACK_PACKAGE_ARCHITECTURE "all")

# Strip the binaries
set(CPACK_STRIP_FILES YES)

# Set the package license (RPM specific)
set(CPACK_RPM_PACKAGE_LICENSE "MIT")

# Set the section of the package
set(CPACK_DEBIAN_PACKAGE_SECTION "libs")

# Use the resource file for the license
set(CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE ON)

set(CPACK_PACKAGE_CHECKSUM "SHA256")

if (win32)
    # NSIS specific settings
    set(CPACK_NSIS_PACKAGE_NAME "${CPACK_PACKAGE_NAME}")
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME}")
    set(CPACK_NSIS_MODIFY_PATH ON)

    set(CPACK_NSIS_INSTALL_ROOT "C:\\Program Files\\${CPACK_PACKAGE_NAME}")
    set(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_CONTACT}")

    set(CPACK_NSIS_URL_INFO_ABOUT "${CPACK_PACKAGE_HOMEPAGE}")
    set(CPACK_NSIS_MODIFY_PATH ON)

    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    set(CPACK_NSIS_HELP_LINK "${CPACK_PACKAGE_HOMEPAGE}")
    set(CPACK_NSIS_MENU_LINKS "${CPACK_PACKAGE_HOMEPAGE}" "Home Page")

    # Inno setup specific settings
    set(CPACK_INNOSETUP_USE_CMAKE_BOOL_FORMAT ON)
    set(CPACK_INNOSETUP_INSTALL_ROOT "${CPACK_NSIS_INSTALL_ROOT}")

    set(CPACK_INNOSETUP_ALLOW_CUSTOM_DIRECTORY ON)
    set(CPACK_INNOSETUP_PROGRAM_MENU_FOLDER "${CPACK_PACKAGE_NAME}")

    set(CPACK_INNOSETUP_LANGUAGES "english;spanish;french;german;italian")
    set(CPACK_INNOSETUP_IGNORE_LICENSE_PAGE OFF)

    set(CPACK_INNOSETUP_IGNORE_README_PAGE OFF)
    set(CPACK_INNOSETUP_USE_MODERN_WIZARD ON)

    set(CPACK_INNOSETUP_MENU_LINKS "${CPACK_NSIS_MENU_LINKS}")

endif ()

set(CPACK_COMPONENTS_ALL libraries headers CMakeConfig pkgconfig)

set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "The LiteString libraries.")
set(CPACK_COMPONENT_LIBRARIES_REQUIRED ON)

set(CPACK_COMPONENT_CMAKECONFIG_DISPLAY_NAME "CMake Config")
set(CPACK_COMPONENT_CMAKECONFIG_DESCRIPTION "CMake configuration files.")

set(CPACK_COMPONENT_PKGCONFIG_DISPLAY_NAME "PkgConfig")
set(CPACK_COMPONENT_PKGCONFIG_DESCRIPTION "The LiteString library pkgconfig file.")

set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Headers")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION "Header files for LiteString.")
set(CPACK_COMPONENT_HEADERS_REQUIRED ON)

include(CPack)

find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_TESTING gnuradio-testing)

FIND_PATH(
    GR_TESTING_INCLUDE_DIRS
    NAMES gnuradio/testing/api.h
    HINTS $ENV{TESTING_DIR}/include
        ${PC_TESTING_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_TESTING_LIBRARIES
    NAMES gnuradio-testing
    HINTS $ENV{TESTING_DIR}/lib
        ${PC_TESTING_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-testingTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_TESTING DEFAULT_MSG GR_TESTING_LIBRARIES GR_TESTING_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_TESTING_LIBRARIES GR_TESTING_INCLUDE_DIRS)

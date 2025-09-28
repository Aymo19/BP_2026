find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_ERTOOLS gnuradio-ErTools)

FIND_PATH(
    GR_ERTOOLS_INCLUDE_DIRS
    NAMES gnuradio/ErTools/api.h
    HINTS $ENV{ERTOOLS_DIR}/include
        ${PC_ERTOOLS_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_ERTOOLS_LIBRARIES
    NAMES gnuradio-ErTools
    HINTS $ENV{ERTOOLS_DIR}/lib
        ${PC_ERTOOLS_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-ErToolsTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_ERTOOLS DEFAULT_MSG GR_ERTOOLS_LIBRARIES GR_ERTOOLS_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_ERTOOLS_LIBRARIES GR_ERTOOLS_INCLUDE_DIRS)

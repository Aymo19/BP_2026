find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_KODKAL gnuradio-KodKal)

FIND_PATH(
    GR_KODKAL_INCLUDE_DIRS
    NAMES gnuradio/KodKal/api.h
    HINTS $ENV{KODKAL_DIR}/include
        ${PC_KODKAL_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_KODKAL_LIBRARIES
    NAMES gnuradio-KodKal
    HINTS $ENV{KODKAL_DIR}/lib
        ${PC_KODKAL_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-KodKalTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_KODKAL DEFAULT_MSG GR_KODKAL_LIBRARIES GR_KODKAL_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_KODKAL_LIBRARIES GR_KODKAL_INCLUDE_DIRS)

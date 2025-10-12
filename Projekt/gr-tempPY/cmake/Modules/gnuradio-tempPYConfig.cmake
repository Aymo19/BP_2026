find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_TEMPPY gnuradio-tempPY)

FIND_PATH(
    GR_TEMPPY_INCLUDE_DIRS
    NAMES gnuradio/tempPY/api.h
    HINTS $ENV{TEMPPY_DIR}/include
        ${PC_TEMPPY_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_TEMPPY_LIBRARIES
    NAMES gnuradio-tempPY
    HINTS $ENV{TEMPPY_DIR}/lib
        ${PC_TEMPPY_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-tempPYTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_TEMPPY DEFAULT_MSG GR_TEMPPY_LIBRARIES GR_TEMPPY_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_TEMPPY_LIBRARIES GR_TEMPPY_INCLUDE_DIRS)

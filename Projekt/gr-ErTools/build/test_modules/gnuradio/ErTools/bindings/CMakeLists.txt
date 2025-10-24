# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT ErTools_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT ErTools_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################
list(APPEND ErTools_python_files
    BER_sync_python.cc
    BER_moje_python.cc python_bindings.cc)

gr_pybind_make_oot(ErTools ../../.. gr::ErTools "${ErTools_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET ErTools_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ErTools_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/ErTools/)

install(
    TARGETS ErTools_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/ErTools
    COMPONENT pythonapi)

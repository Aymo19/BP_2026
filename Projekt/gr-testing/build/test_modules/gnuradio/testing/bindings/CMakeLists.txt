# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT testing_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT testing_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND testing_python_files
    test_python.cc python_bindings.cc)

gr_pybind_make_oot(testing ../../.. gr::testing "${testing_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET testing_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:testing_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/testing/)

install(
    TARGETS testing_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/testing
    COMPONENT pythonapi)

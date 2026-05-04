# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT KodKal_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT KodKal_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND KodKal_python_files
    Koder_Opak_python.cc
    Dekoder_Opak_python.cc python_bindings.cc)

gr_pybind_make_oot(KodKal ../../.. gr::KodKal "${KodKal_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET KodKal_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:KodKal_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/KodKal/)

install(
    TARGETS KodKal_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/KodKal
    COMPONENT pythonapi)

/* -*- c++ -*- */
/*
 * Copyright 2025 gr-ErTools author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_PRINTCHAR_IMPL_H
#define INCLUDED_ERTOOLS_PRINTCHAR_IMPL_H

#include <gnuradio/ErTools/PrintChar.h>

namespace gr {
namespace ErTools {

class PrintChar_impl : public PrintChar
{
private:
    // Nothing to declare in this block.

public:
    PrintChar_impl();
    ~PrintChar_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_PRINTCHAR_IMPL_H */

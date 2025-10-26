/* -*- c++ -*- */
/*
 * Copyright 2025 gr-ErTools author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_PRINTFLOAT_IMPL_H
#define INCLUDED_ERTOOLS_PRINTFLOAT_IMPL_H

#include <gnuradio/ErTools/PrintFloat.h>

namespace gr {
namespace ErTools {

class PrintFloat_impl : public PrintFloat
{
private:
    // Nothing to declare in this block.

public:
    PrintFloat_impl();
    ~PrintFloat_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_PRINTFLOAT_IMPL_H */

/* -*- c++ -*- */
/*
 * Copyright 2025 gr-ErTools author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_PRINTINT_IMPL_H
#define INCLUDED_ERTOOLS_PRINTINT_IMPL_H

#include <gnuradio/ErTools/PrintInt.h>

namespace gr {
namespace ErTools {

class PrintInt_impl : public PrintInt
{
private:
    // Nothing to declare in this block.

public:
    PrintInt_impl();
    ~PrintInt_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_PRINTINT_IMPL_H */

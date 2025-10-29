/* -*- c++ -*- */
/*
 * Copyright 2025 gr-tempPY author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TEMPPY_CTEST_IMPL_H
#define INCLUDED_TEMPPY_CTEST_IMPL_H

#include <gnuradio/tempPY/ctest.h>

namespace gr {
namespace tempPY {

class ctest_impl : public ctest
{
private:
    // Nothing to declare in this block.

public:
    ctest_impl(int N, int A, int B);
    ~ctest_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace tempPY
} // namespace gr

#endif /* INCLUDED_TEMPPY_CTEST_IMPL_H */

/* -*- c++ -*- */
/*
 * Copyright 2025 gr-testing author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TESTING_TEST_IMPL_H
#define INCLUDED_TESTING_TEST_IMPL_H

#include <gnuradio/testing/test.h>

namespace gr {
namespace testing {

class test_impl : public test
{
private:
    int _N;

public:
    test_impl(int N);
    ~test_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;
};

} // namespace testing
} // namespace gr

#endif /* INCLUDED_TESTING_TEST_IMPL_H */

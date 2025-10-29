/* -*- c++ -*- */
/*
 * Copyright 2025 gr-testing author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "test_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/thread/thread.h>
#include <type_traits>
#include <cmath>
#include <complex>
#include <iomanip>
#include <memory>
#include <sstream>

namespace gr {
namespace testing {

//using input_type = float;
using output_type = float;
test::sptr test::make(int N) { return gnuradio::make_block_sptr<test_impl>(N); }

static int ios[] = { sizeof(float), sizeof(char) };
static std::vector<int> iosig(ios, ios + sizeof(ios) / sizeof(int));

test_impl::test_impl(int N)
    : gr::sync_block("test",
                     gr::io_signature::makev(1, 2, iosig),
                     gr::io_signature::make(1, 1, sizeof(output_type)))
{
  _N = N;
}

/*
 * Our virtual destructor.
 */
test_impl::~test_impl() {}

int test_impl::work(int noutput_items,
                    gr_vector_const_void_star& input_items,
                    gr_vector_void_star& output_items)
{
    const float *in0 = (const float *) input_items[0];
    const char *in1 = (const char *) input_items[1];
    auto out0 = static_cast<output_type*>(output_items[0]);

    // Do <+signal processing+>
    out0[0] = in0[0];

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace testing */
} /* namespace gr */

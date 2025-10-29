/* -*- c++ -*- */
/*
 * Copyright 2025 gr-tempPY author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "ctest_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace tempPY {

#pragma message("set the following appropriately and remove this warning")
using input_type = float;
#pragma message("set the following appropriately and remove this warning")
using output_type = float;
ctest::sptr ctest::make(int N, int A, int B)
{
    return gnuradio::make_block_sptr<ctest_impl>(N, A, B);
}


/*
 * The private constructor
 */
ctest_impl::ctest_impl(int N, int A, int B)
    : gr::sync_block("ctest",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
}

/*
 * Our virtual destructor.
 */
ctest_impl::~ctest_impl() {}

int ctest_impl::work(int noutput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);

#pragma message("Implement the signal processing in your block and remove this warning")
    // Do <+signal processing+>

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace tempPY */
} /* namespace gr */

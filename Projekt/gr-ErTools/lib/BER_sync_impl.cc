/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BER_sync_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ErTools {

using input_type = float;
using output_type = float;
BER_sync::sptr BER_sync::make(int N)
{
    return gnuradio::make_block_sptr<BER_sync_impl>(N);
}


/*
 * The private constructor
 */
BER_sync_impl::BER_sync_impl(int N)
    : gr::sync_block("BER_sync",
                     gr::io_signature::make(
                         3, 3, sizeof(input_type)),
                     gr::io_signature::make(
                         1, 1, sizeof(output_type)))
{
}

/*
 * Our virtual destructor.
 */
BER_sync_impl::~BER_sync_impl() {}

int BER_sync_impl::work(int noutput_items,
                        gr_vector_const_void_star& input_items,
                        gr_vector_void_star& output_items)
{
    auto in0 = static_cast<const input_type*>(input_items[0]);
    auto in1 = static_cast<const input_type*>(input_items[1]);
    auto in2 = static_cast<const input_type*>(input_items[2]);
    auto out0 = static_cast<output_type*>(output_items[0]);

    // Do <+signal processing+>
    int L = sizeof(in0) / sizeof(in0[0]);

    /*for(int i = 0; i < L; i++) {
    
    }*/

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

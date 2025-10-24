/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BER_moje_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ErTools {

using input_type = char;
using output_type = float;

BER_moje::sptr BER_moje::make(int N) {
    return gnuradio::make_block_sptr<BER_moje_impl>(N);
}


//The private constructor
BER_moje_impl::BER_moje_impl(int N)
    : gr::sync_block("BER_moje",
                     gr::io_signature::make(2, 2, sizeof(input_type)),
                     gr::io_signature::make(1, 1, sizeof(output_type)))
{
  _N = N;
}


//Our virtual destructor.
BER_moje_impl::~BER_moje_impl() {}

int BER_moje_impl::work(int noutput_items,
                        gr_vector_const_void_star& input_items,
                        gr_vector_void_star& output_items)
{
    auto inOg = static_cast<const input_type*>(input_items[0]);
    auto inNo = static_cast<const input_type*>(input_items[1]);
    auto out = static_cast<output_type*>(output_items[0]);
    
    printf("inOg: %ld\n", (sizeof(inOg)/sizeof(inOg[0])));
    //out[0] = inOg[0] + inNo[0];

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

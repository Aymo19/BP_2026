/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BitErrorRate_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ErTools {

using input_type = float;
using output_type = float;

BitErrorRate::sptr BitErrorRate::make(int N, int Rb, int EbN0min, int EbN0max, int fvz)
{
    return gnuradio::make_block_sptr<BitErrorRate_impl>(N, Rb, EbN0min, EbN0max, fvz);
}


//The private constructor
BitErrorRate_impl::BitErrorRate_impl(int N, int Rb, int EbN0min, int EbN0max, int fvz)
    : gr::block("BitErrorRate",
                gr::io_signature::make(
                    1, 2, sizeof(input_type)+sizeof(gr_complex)),
                gr::io_signature::make(
                    0, 1, sizeof(output_type)))
{
}

//Our virtual destructor.
BitErrorRate_impl::~BitErrorRate_impl() {}

void BitErrorRate_impl::forecast(int noutput_items, gr_vector_int& ninput_items_required)
{
    /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
}

int BitErrorRate_impl::general_work(int noutput_items,
                                    gr_vector_int& ninput_items,
                                    gr_vector_const_void_star& input_items,
                                    gr_vector_void_star& output_items)
{
    //auto in = static_cast<const input_type*>(input_items[0]);
    //auto out = static_cast<output_type*>(output_items[0]);



    // Do <+signal processing+>
    // Tell runtime system how many input items we consumed on
    // each input stream.
    consume_each(noutput_items);

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

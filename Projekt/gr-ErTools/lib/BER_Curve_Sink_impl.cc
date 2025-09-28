/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BER_Curve_Sink_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ErTools {

#pragma message("set the following appropriately and remove this warning")
using input_type = float;
BER_Curve_Sink::sptr BER_Curve_Sink::make()
{
    return gnuradio::make_block_sptr<BER_Curve_Sink_impl>();
}


/*
 * The private constructor
 */
BER_Curve_Sink_impl::BER_Curve_Sink_impl()
    : gr::sync_block("BER_Curve_Sink",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(0, 0, 0))
{
}

/*
 * Our virtual destructor.
 */
BER_Curve_Sink_impl::~BER_Curve_Sink_impl() {}

int BER_Curve_Sink_impl::work(int noutput_items,
                              gr_vector_const_void_star& input_items,
                              gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);

#pragma message("Implement the signal processing in your block and remove this warning")
    // Do <+signal processing+>

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

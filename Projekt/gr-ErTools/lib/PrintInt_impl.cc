/* -*- c++ -*- */
/*
 * Copyright 2025 gr-ErTools author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "PrintInt_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ErTools {

using input_type = int;
PrintInt::sptr PrintInt::make() { return gnuradio::make_block_sptr<PrintInt_impl>(); }


/*
 * The private constructor
 */
PrintInt_impl::PrintInt_impl()
    : gr::sync_block("PrintInt",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(0, 0, 0))
{
}

/*
 * Our virtual destructor.
 */
PrintInt_impl::~PrintInt_impl() {}

int PrintInt_impl::work(int noutput_items,
                        gr_vector_const_void_star& input_items,
                        gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);

    // Do <+signal processing+>
    printf("Zaciatok INT:\n");
    for(int i = 0; i < noutput_items; i++)
      printf("\t%d\n", in[i]);

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

/* -*- c++ -*- */
/*
 * Copyright 2025 gr-ErTools author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "PrintChar_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ErTools {

using input_type = char;
PrintChar::sptr PrintChar::make() { return gnuradio::make_block_sptr<PrintChar_impl>(); }


/*
 * The private constructor
 */
PrintChar_impl::PrintChar_impl()
    : gr::sync_block("PrintChar",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(0, 0, 0))
{
}

/*
 * Our virtual destructor.
 */
PrintChar_impl::~PrintChar_impl() {}

int PrintChar_impl::work(int noutput_items,
                         gr_vector_const_void_star& input_items,
                         gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);

    // Do <+signal processing+>
    printf("Zaciatok CHAR:\n");
    for(int i = 0; i < noutput_items; i++)
      printf("\t%c\n", in[i] + 48);

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "Koder_Opak_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace KodKal {

using input_type = unsigned char;
using output_type = unsigned char;

Koder_Opak::sptr Koder_Opak::make(int k) {
    return gnuradio::make_block_sptr<Koder_Opak_impl>(k);
}


// The private constructor
Koder_Opak_impl::Koder_Opak_impl(int k)
    : gr::sync_interpolator(
          "Koder_Opak",
          gr::io_signature::make(1, 1, sizeof(input_type)),
          gr::io_signature::make(1, 1, sizeof(output_type)),
          k)
{
  _k = k;
}

// Our virtual destructor.
Koder_Opak_impl::~Koder_Opak_impl() {}

int Koder_Opak_impl::work(int noutput_items,
                          gr_vector_const_void_star& input_items,
                          gr_vector_void_star& output_items)
{
    auto in0 = static_cast<const input_type*>(input_items[0]);
    auto out0 = static_cast<output_type*>(output_items[0]);

    // Do <+signal processing+>
    
    int ninput_items = noutput_items / _k;

    for(int i = 0; i < ninput_items; i++) {
      for(int j = 0; j < _k; j++) {
        out0[(i * _k) + j] = in0[i];
      }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace KodKal */
} /* namespace gr */

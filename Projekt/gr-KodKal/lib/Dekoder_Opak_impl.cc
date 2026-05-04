/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "Dekoder_Opak_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace KodKal {

using input_type = unsigned char;
using output_type = unsigned char;

Dekoder_Opak::sptr Dekoder_Opak::make(int n) {
    return gnuradio::make_block_sptr<Dekoder_Opak_impl>(n);
}


// The private constructor
Dekoder_Opak_impl::Dekoder_Opak_impl(int n)
    : gr::sync_decimator("Dekoder_Opak",
                         gr::io_signature::make(1, 1, sizeof(input_type)),
                         gr::io_signature::make(1, 1, sizeof(output_type)),
                         n)
{
  _n = n;

  count = 0;
  
  polovica = (_n + 1) / 2; 
}

/*
 * Our virtual destructor.
 */
Dekoder_Opak_impl::~Dekoder_Opak_impl() {}

int Dekoder_Opak_impl::work(int noutput_items,
                            gr_vector_const_void_star& input_items,
                            gr_vector_void_star& output_items)
{
    auto in0 = static_cast<const input_type*>(input_items[0]);
    auto out0 = static_cast<output_type*>(output_items[0]);

    // Do <+signal processing+>
    for(int i = 0; i < noutput_items; i++) { 
      for(int j = 0; j < _n; j++) {
        count += int(in0[(i * _n) + j]);
        //printf("%d\n", in0[(i*_n)+j]);
      }

      if(count >= polovica) {
        out0[i] = 1;
      }else {
        out0[i] = 0;
      }

      count = 0;
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace KodKal */
} /* namespace gr */

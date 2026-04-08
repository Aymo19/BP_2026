/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "MC_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ErTools {

using output_type = float;
MC::sptr MC::make(int N, int EbN0min, int EbN0max) {
    return gnuradio::make_block_sptr<MC_impl>(N, EbN0min, EbN0max);
}


// The private constructor
MC_impl::MC_impl(int N, int EbN0min, int EbN0max)
    : gr::sync_block("MC",
                     gr::io_signature::make(0, 0, 0),
                     gr::io_signature::make(1, 2, sizeof(output_type)))
{
  _N = N;             // Pocet vzoriek EbN0 (kolko bodov na X-osi) Pocet modulacnych stavov
  _EbN0min = EbN0min; // Zaciatok EbN0 [dB]
  _EbN0max = EbN0max;

  index_CLK = 0;
}

// Our virtual destructor.
MC_impl::~MC_impl() {}

// Work
int MC_impl::work(int noutput_items,
                  gr_vector_const_void_star& input_items,
                  gr_vector_void_star& output_items)
{
    //OUTPUT
    auto out0 = static_cast<output_type*>(output_items[0]);
    int *out1 = (int *) output_items[1];


    //LOGIKA
    float EDB[_N];

    // Linearne rozlozenie EbN0db bodov
    Rz = float((_EbN0max - _EbN0min)) / float((_N-1));
    Rz_krok = float(_EbN0min);

    for(int i = 0; i < _N; i++) {
      EDB[i] = Rz_krok;
      Rz_krok += Rz;
    }

    for(int b = 0; b < noutput_items; b++) {
      
      out0[b] = EDB[index_CLK];
      out1[b] = index_CLK;

      if(index_CLK < _N-1) {
        index_CLK += 1;
      }else {
        index_CLK = 0;
      }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

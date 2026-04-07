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
MC::sptr MC::make(int N, int EbN0min, int EbN0max)
{
    return gnuradio::make_block_sptr<MC_impl>(N, EbN0min, EbN0max);
}


/*
 * The private constructor
 */
MC_impl::MC_impl(int N, int EbN0min, int EbN0max)
    : gr::sync_block("MC",
                     gr::io_signature::make(0, 0, 0),
                     gr::io_signature::make(
                         1 /* min outputs */, 2 /*max outputs */, sizeof(output_type)))
{
  _N = N;             // Pocet vzoriek EbN0 (kolko bodov na X-osi) Pocet modulacnych stavov
  _EbN0min = EbN0min; // Zaciatok EbN0 [dB]
  _EbN0max = EbN0max;
}

/*
 * Our virtual destructor.
 */
MC_impl::~MC_impl() {}

float rozpatie2, rozpatiePostup2;
int k2 = 0;

int MC_impl::work(int noutput_items,
                  gr_vector_const_void_star& input_items,
                  gr_vector_void_star& output_items)
{
    auto out0 = static_cast<output_type*>(output_items[0]);
    int *out1 = (int *) output_items[1];
    // Do <+signal processing+>
    float EDB[_N];

    // Linearne rozlozenie EbN0db bodov
    rozpatie2 = float((_EbN0max - _EbN0min)) / float((_N-1));
    rozpatiePostup2 = float(_EbN0min);

    for(int i = 0; i < _N; i++) {
      EDB[i] = rozpatiePostup2;
      rozpatiePostup2 += rozpatie2;
    }

    for(int b = 0; b < noutput_items; b++) {
      
      // Komplexny vystup = AWGN sum
      out0[b] = EDB[k2];
      // Int vystup = N-ta vzorka EbN0, ktoru sme pocitali
      out1[b] = k2;

      // Iterujeme po vsetkych vzorkach EbN0, t.j. od 0 do N-1
      if(k2 < _N-1) {
        k2 += 1;
      }else {
        k2 = 0;
      }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

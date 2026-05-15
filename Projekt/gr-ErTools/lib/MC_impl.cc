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
  _N = N; // Pocet bodov EbN0 v rozostupe
  _EbN0min = EbN0min; // Zaciatok EbN0 [dB]
  _EbN0max = EbN0max; // Koniec EbN0 [dB]

  index_CLK = 0; // Inicializacia indexu pre BER/SER blok

  // VYPOCET ROZOSTUPU Rz
  Rz = double((_EbN0max - _EbN0min)) / double((_N-1));
  // Krok v rozostupe
  Rz_krok = double(_EbN0min);

  // Vektor EbN0 bodov podla rozostupu
  v_EDB = std::vector<double>(_N, 0);

  // Vkladanie EbN0 bodov do vektoru
  for(int i = 0; i < _N; i++) {
    v_EDB.at(i) = Rz_krok; // Vloz EbN0 bod
    Rz_krok += Rz; // Posun sa dalej
  }
}

// Our virtual destructor.
MC_impl::~MC_impl() {}


//----WORK----||
int MC_impl::work(int noutput_items,
                  gr_vector_const_void_star& input_items,
                  gr_vector_void_star& output_items)
{
  // Inicializacia I/O
  // OUTPUT
  auto out0 = static_cast<output_type*>(output_items[0]);
  int *out1 = (int *) output_items[1];

  // LOGIKA
  // Prejdeme vsetkymi OUTPUT items
  for(int b = 0; b < noutput_items; b++) {
      
    out0[b] = v_EDB.at(index_CLK);  // Index pre AWGN bloky
    out1[b] = index_CLK;  // Index pre BER/SER bloky

    // Sekundarna iteracia pre BER/SER bloky
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

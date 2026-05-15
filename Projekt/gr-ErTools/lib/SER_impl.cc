/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "SER_impl.h"
#include <gnuradio/io_signature.h>

// Pridane kniznice
#include <cmath>

namespace gr {
namespace ErTools {

// Datovy Typ vystupu
using output_type = float;

SER::sptr SER::make(int N) { 
  return gnuradio::make_block_sptr<SER_impl>(N); 
}

// Input vector
static int is[] = { sizeof(int), sizeof(unsigned char), sizeof(unsigned char) };
static std::vector<int> isig(is, is + sizeof(is) / sizeof(int));

// The private constructor
SER_impl::SER_impl(int N)
    : gr::sync_block("SER",
                     gr::io_signature::makev(2, 3, isig),
                     gr::io_signature::make(1, 1, sizeof(output_type)))
{
  _N = N; // Pocet bodov EsN0 v rozpati
  
  // Vektory
  _count = std::vector<int>(N, 1); // Celkovy pocet informacnych slov co sme spracovali
  _pocet_chyb = std::vector<int>(N, 0); // Celkovy pocet zistenych chyb
  _pamat_SER = std::vector<double>(N, 1.0); // Vystupne hodnoty SER
}

// Our virtual destructor.
SER_impl::~SER_impl() {}

//----LOGIKA-FUNKCIE----||
// Zisti ci nastala chyba
int SER_calc(unsigned char S1, unsigned char S2) {
  int e_sum = 1;
  
  // Ak ano, tak nie je nulova hodnota e_sum
  if(S1 == S2)
    e_sum = 0;
  
  return e_sum;
}


//----WORK----||
int SER_impl::work(int noutput_items,
                   gr_vector_const_void_star& input_items,
                   gr_vector_void_star& output_items)
{
    // Inicializacia I/O
    // INPUT
    int *in0 = (int *)input_items[0];
    unsigned char *in1 = (unsigned char *)input_items[1];
    unsigned char *in2 = (unsigned char *)input_items[2];
    
    // OUTPUT
    auto out = static_cast<output_type*>(output_items[0]);

    // LOGIKA
    // Prejdeme vsetkymi I/O items
    for(int i = 0; i < noutput_items; i++) {
      k = in0[i];
      
      // Zistime, ci nastala chyba v informacnom slove
      _pocet_chyb.at(k) += SER_calc(in1[i], in2[i]);
      
      // Ak nastala chyba
      if(_pocet_chyb.at(k) != 0) {
        _pamat_SER.at(k) = double(_pocet_chyb.at(k)) / double(_count.at(k));
      }

      // Float vystup = pravdepodobnost chyby na bit v danom Eb/N0
      out[i] = _pamat_SER.at(k);
      
      // Inkrementujeme celkovy pocet bitov
      _count.at(k) += 1;
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

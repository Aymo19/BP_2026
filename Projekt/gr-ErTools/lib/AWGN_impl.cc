/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "AWGN_impl.h"
#include <gnuradio/io_signature.h>

// Pridane kniznice
#include <cmath>
#include <random>
#include <complex>
#include <cstdlib>

namespace gr {
namespace ErTools {

AWGN::sptr AWGN::make(int M, int k, int n) {
    return gnuradio::make_block_sptr<AWGN_impl>(M, k, n);
}

// The private constructor
AWGN_impl::AWGN_impl(int M, int k, int n)
    : gr::sync_block("AWGN",
                     gr::io_signature::make2(2, 2, sizeof(gr_complex) * n, sizeof(float)),
                     gr::io_signature::make(1, 2, sizeof(gr_complex) * n)),
    R(rd()), // Inicializacia random seed
    Gauss(0,1) // Tvorba normalneho rozdelenie N(0,1)
{
  _M = M; // Pocet modulacnych stavov
  _k = k; // informacne slovo
  _n = n; // kodove slovo
  
  // Kodova rychlost
  Rs = double(_k) / double(_n);
}

//----LOGIKA-FUNKCIE----||

// Tvorba komplexneho sumu podla EbN0 a Es
gr_complex AWGN_impl::Sum(float EDB, int stav, float Es, double Rs) {
  double EsN0, REAL, IMAG, odchylka;
  double k = std::log2(stav); // Pocet bitov na modulacny symbol

  // Premena z dB na pomer
  EsN0 = pow(10.0, (EDB + 10.0*std::log10(k) + 10.0*std::log10(Rs)) / 10.0);

  // Variancia sumu
  odchylka = std::sqrt(Es / (EsN0 * 2.0));
  
  //Denormalizacia
  REAL = Gauss(R) * odchylka;
  IMAG = Gauss(R) * odchylka;

  //komplexny sum
  gr_complex n(REAL, IMAG);

  return n;
}

// Our virtual destructor.
AWGN_impl::~AWGN_impl() {}

//----WORK----||
int AWGN_impl::work(int noutput_items,
                    gr_vector_const_void_star& input_items,
                    gr_vector_void_star& output_items)
{
    // Inicializacia I/O
    // INPUT
    gr_complex *in0 = (gr_complex *) input_items[0];
    float *in1 = (float *) input_items[1];
    
    // OUTPUT
    gr_complex *out = (gr_complex *) output_items[0];

    // LOGIKA
    // Prvotne vypocty
    Es = 0; // Energia signalu
    total_Es = 0; // Sucet energii vzoriek

    // Vypocet energie vstupneho signalu Es
    for(int a = 0; a < noutput_items; a++)
      total_Es += std::norm(in0[a]);
    
    Es = total_Es / noutput_items;

    // Prejdeme vsetkymi I/O items
    for(int b = 0; b < noutput_items; b++) { 
      EBQ = in1[b]; // index EbN0 z Master Clock
    
      // Prejdeme cely vektor
      for(int c = 0; c < _n; c++) {
        // Vypocet sumu
        gr_complex sg_n = Sum(EBQ, _M, Es, Rs);

        // Scitanie povodneho signalu so sumom a vyslanie na vystup
        out[(b * _n) + c] = in0[(b * _n) + c] + sg_n;
      } 
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

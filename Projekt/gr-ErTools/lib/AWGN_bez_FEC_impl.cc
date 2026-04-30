/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "AWGN_bez_FEC_impl.h"
#include <gnuradio/io_signature.h>

// Pridane kniznice
#include <cmath>
#include <random>
#include <complex>
#include <cstdlib>

namespace gr {
namespace ErTools {

AWGN_bez_FEC::sptr AWGN_bez_FEC::make(int M) {
    return gnuradio::make_block_sptr<AWGN_bez_FEC_impl>(M);
}

// Output vector
static int os[] = { sizeof(gr_complex) };
static std::vector<int> osig(os, os + sizeof(os) / sizeof(int));

static int is[] = { sizeof(gr_complex), sizeof(float) };
static std::vector<int> isig(is, is + sizeof(is) / sizeof(int));

// The private constructor
AWGN_bez_FEC_impl::AWGN_bez_FEC_impl(int M)
    : gr::sync_block("AWGN_bez_FEC",
                     gr::io_signature::makev(1, 2, isig),
                     gr::io_signature::makev(1, 2, osig)),
    R_B(rd_B()),
    Gauss_B(0,1)
{
  _M = M; // Pocet modulacnych stavov
}

//----------------------------------------------------LOGIKA-FUNKCIE--------------------------------------------------------||

//-------------------Odvodenie-varianci-esumu-z-EbN0-[db]---------------------|
gr_complex AWGN_bez_FEC_impl::Sum_B(double EDB, int stav, double Es) {
  double EbN0, EsN0, REAL, IMAG, odchylka;
  double k = std::log2(stav);

  // Premena z dB na pomer
  
  EsN0 = pow(10.0, (EDB + 10.0*std::log10(k)) / 10.0);
  odchylka = std::sqrt(Es / (EsN0 * 2.0));
  
  //Denormalizacia
  REAL = Gauss_B(R_B) * odchylka;
  IMAG = Gauss_B(R_B) * odchylka;

  gr_complex n(REAL, IMAG);

  return n;
}


// Our virtual destructor.
AWGN_bez_FEC_impl::~AWGN_bez_FEC_impl() {}

int AWGN_bez_FEC_impl::work(int noutput_items,
                            gr_vector_const_void_star& input_items,
                            gr_vector_void_star& output_items)
{
   //-----------------------Inicializacia-I/O--------------------------|
    // INPUT
    gr_complex *in0 = (gr_complex *) input_items[0];
    float *in1 = (float *) input_items[1];
    
    // OUTPUT
    gr_complex *out = (gr_complex *) output_items[0];

    //-----------------------LOGIKA--------------------------|
    //-------------------Prvotne-vypocty---------------------|
   
    Es = 0;
    sumEs = 0;
    // Vypocet vykonu vstupneho signalu Ps = E(x)
    for(int a = 0; a < noutput_items; a++)
      sumEs += std::norm(in0[a]);
    
    Es = sumEs / noutput_items;

    //-----------------------Prejdeme-vsetkymi-I/O-items--------------------------|
    for(int b = 0; b < noutput_items; b++) { 
      EBQ_B = in1[b];
    
      gr_complex sg_n = Sum_B(EBQ_B, _M, Es);
      
      out[b] = sg_n; 
    }


    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

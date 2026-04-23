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

// Output vector
static int os[] = { sizeof(gr_complex) * 7};
static std::vector<int> osig(os, os + sizeof(os) / sizeof(int));

static int is[] = { sizeof(gr_complex) * 7, sizeof(float) };
static std::vector<int> isig(is, is + sizeof(is) / sizeof(int));

// The private constructor
AWGN_impl::AWGN_impl(int M, int k, int n)
    : gr::sync_block("AWGN",
                     gr::io_signature::makev(1, 2, isig),
                     gr::io_signature::makev(1, 2, osig)),
    R(rd()),
    Gauss(0,1)
{
  _M = M; // Pocet modulacnych stavov
  _k = k; // informacne slovo
  _n = n; // kodove slovo
  
  Rs = double(_k) / double(_n);
  printf("%lf\n", Rs);
  
  EBQ = -10000000.0;
}

//----------------------------------------------------LOGIKA-FUNKCIE--------------------------------------------------------||

//-------------------Odvodenie-varianci-esumu-z-EbN0-[db]---------------------|
gr_complex AWGN_impl::Sum(float EDB, int stav, float Es, double Rs) {
  double EbN0, EsN0, REAL, IMAG, odchylka;
  double k = std::log2(stav);

  // Premena z dB na pomer
  
  EsN0 = pow(10.0, (EDB + 10.0*std::log10(k) + 10.0*std::log10(Rs)) / 10.0);
  odchylka = std::sqrt(Es / (EsN0 * 2.0));
  
  //Denormalizacia
  REAL = Gauss(R) * odchylka;
  IMAG = Gauss(R) * odchylka;

  gr_complex n(REAL, IMAG);

  return n;
}

// Our virtual destructor.
AWGN_impl::~AWGN_impl() {}

//-------------------------------------------------------------------------------------------------------------------------||
//---------------------------------------------------------WORK------------------------------------------------------------||
int AWGN_impl::work(int noutput_items,
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
   
    Ps = 0;
    sumPs = 0;
    // Vypocet vykonu vstupneho signalu Ps = E(x)
    for(int a = 0; a < noutput_items; a++)
      sumPs += std::norm(in0[a]);
    
    Ps = sumPs / noutput_items;

    //-----------------------Prejdeme-vsetkymi-I/O-items--------------------------|
    for(int b = 0; b < noutput_items; b++) { 
      EBQ = in1[b];
      sg_n = Sum(EBQ, _M, Ps, Rs);
    
      for(int c = 0; c < 7; c++) {
        out[b * 7 + c] = in0[b * 7 + c] + sg_n;
      } 
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "AWGN_kanal_impl.h"
#include <gnuradio/io_signature.h>

#include <cmath>
#include <random>
#include <complex>
#include <cstdlib>

namespace gr {
namespace ErTools {

//using input_type = float;
//using output_type = float;

AWGN_kanal::sptr AWGN_kanal::make(int N, int EbN0min, int EbN0max, int R, int W)
{
    return gnuradio::make_block_sptr<AWGN_kanal_impl>(N, EbN0min, EbN0max, R, W);
}

static int os[] = { sizeof(gr_complex), sizeof(int) };
static std::vector<int> osig(os, os + sizeof(os) / sizeof(int));
/*
 * The private constructor
 */
AWGN_kanal_impl::AWGN_kanal_impl(int N, int EbN0min, int EbN0max, int R, int W)
    : gr::sync_block("AWGN_kanal",
                     gr::io_signature::make(1, 1, sizeof(gr_complex)),
                     gr::io_signature::makev(1, 2, osig))
{
  _N = N;
  _Rb = R;
  _fvz = W;
  _EbN0min = EbN0min;
  _EbN0max = EbN0max;
  
  //k = 0;
}

//Our virtual destructor.
AWGN_kanal_impl::~AWGN_kanal_impl() {}

gr_complex Sum_vypocet(float odchylka) {
  std::random_device rd;
  std::mt19937 R(rd());
  std::mt19937 I(rd());
  
  std::normal_distribution<double> Gauss{0, odchylka}; //0 lebo AWGN
  
  double GR = Gauss(R);
  double GI = Gauss(I);
  
  gr_complex n(GR, GI);
  
  return n;
}

gr_complex Sum(float EDB, float Ps, int _Rb, int _fvz) {
  float EbN0, SNR, N, VRMS;
  gr_complex n;

  //premena z dB na pomer
  EbN0 = pow(10.0, EDB/10.0);

  //vypocet SNR 
  SNR = EbN0 * float(_Rb) / float(_fvz);

  //vypocet variancie AWGN (vyriancia sumu)
  N = Ps / SNR;
    
  //vypocet smerodajnej odychlky
  VRMS = sqrt(N) / sqrt(2.0);
  srand(time(0));
  //vypocet AWGN
  n = Sum_vypocet(VRMS);

  //gr_complex n(VRMS*randomFloat(), VRMS*randomFloat());

  return n;
}

float Ps, sumPs = 0;
float rozpatie, rozpatiePostup;
//std::vector <float> EDB;
int k = 0;

int AWGN_kanal_impl::work(int noutput_items,
                          gr_vector_const_void_star& input_items,
                          gr_vector_void_star& output_items)
{
    gr_complex *in0 = (gr_complex *) input_items[0];
    
    gr_complex *out0 = (gr_complex *) output_items[0];
    int *out1 = (int *) output_items[1];

    //-----logika------------------------
    float EDB[_N];

    rozpatie = float((_EbN0max - _EbN0min)) / float((_N-1));
    rozpatiePostup = float(_EbN0min);

    for(int i = 0; i < _N; i++) {
      EDB[i] = rozpatiePostup;
      rozpatiePostup += rozpatie;
    }
    
    //vypocet vykonu vstupneho signalu Ps

    for(int a = 0; a < noutput_items; a++)
      sumPs += pow(abs(in0[a]), 2);

    Ps = sumPs / float(noutput_items);
    k = 0;

    for(int b = 0; b < noutput_items; b++) {
      //AWGN kanal
      gr_complex sg_n = Sum(EDB[k], Ps, _Rb, _fvz);
      
      //gr_complex spolu(in0[b].real() + sg_n.real(), in0[b].imag() + sg_n.imag());
      out0[b] = sg_n;
      out1[b] = k;

      //printf("OUT: %d\n", out1[b]);
      if(k < _N-1) {
        k += 1;
      }else {
        k = 0;
      }
    }


    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

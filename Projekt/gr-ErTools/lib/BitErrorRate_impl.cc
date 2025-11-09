/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BitErrorRate_impl.h"
#include <gnuradio/io_signature.h>

#include <cmath>
#include <random>
#include <complex>

namespace gr {
namespace ErTools {

//using input_type = float;
//using output_type = float;

BitErrorRate::sptr BitErrorRate::make(int N, int Rb, int fvz, int EbN0min, int EbN0max)
{
    return gnuradio::make_block_sptr<BitErrorRate_impl>(N, Rb, fvz, EbN0min, EbN0max);
}

static int is[] = { sizeof(gr_complex), sizeof(char), sizeof(char) };
static std::vector<int> isig(is, is + sizeof(is) / sizeof(int));

static int os[] = { sizeof(gr_complex), sizeof(float) };
static std::vector<int> osig(os, os + sizeof(os) / sizeof(int));

//private constructor
BitErrorRate_impl::BitErrorRate_impl(int N, int Rb, int fvz, int EbN0min, int EbN0max)
    : gr::sync_block("BitErrorRate",
                     gr::io_signature::makev(2, 3, isig),
                     gr::io_signature::makev(1, 2, osig))
{
  _N = N;
  _Rb = Rb;
  _fvz = fvz;
  _EbN0min = EbN0min;
  _EbN0max = EbN0max;
  k = 0;
}

//Our virtual destructor.
BitErrorRate_impl::~BitErrorRate_impl() {}

//Moje custom funkcie
//------------------------------------------------------->

//spocita vsetky chybne bity po x(t) XOR x(t)+n(t)
int BitCounter(char slovo, int N) {
  int sum = 0, sign = 0;
  char b_jedna = 1;
  
  if(slovo < 0)
    sign = 1;
  
  for(int i = 0; i < N; i++) {
    if((slovo & b_jedna) > 0)
      sum++;

    if(sign) { //ked plus
      slovo >>= 1;
    }else { //ked minus
      b_jedna <<= 1;
    }
  }

  return sum;
}

float BER(char S1, char S2) {
  char virt_jedna = 1, XORnute;
  int e_sum, N_S1 = sizeof(S1) * 8, N_S2 = sizeof(S2) * 8; //krat 8 lebo 1 kodove slovo ma 8 bitov
  float BER, log_BER;

  XORnute = S1 ^ S2;
  
  e_sum = BitCounter(XORnute, N_S1);
  
  BER = (float)e_sum / (float)N_S1;
  
  log_BER = logf(BER);

  return log_BER;
}

gr_complex AWGN_vypocet(float odchylka) {
  std::default_random_engine R;
  std::default_random_engine I;
  
  std::normal_distribution<double> Gauss{0, odchylka}; //0 lebo AWGN
  
  double GR = Gauss(R);
  double GI = Gauss(I);
  
  gr_complex n = (GR, GI);
  
  return n;
}

gr_complex AWGN_Sum(float EDB, float Ps, int _Rb, int _fvz) {
  float EbN0;

  EbN0 = pow(10.0, EDB/10.0);

  //vypocet SNR --------------------------------------
  float SNR;

  SNR = (EbN0 * float(_Rb)) / float(_fvz);

  //vypocet variancie AWGN (vykon sumu) --------------
  gr_complex N0;
    
  N0 = Ps / SNR;
    
  //vypocet smerodajnej odychlky -----------------------------------
  float VRMS;

  VRMS = float(sqrt(N0.real())) / sqrt(2.0);

  //vypocet AWGN ---------------------------------------
  gr_complex n;

  n = AWGN_vypocet(VRMS);

  return n;
}

//------------------------------------------------------->

int BitErrorRate_impl::work(int noutput_items,
                            gr_vector_const_void_star& input_items,
                            gr_vector_void_star& output_items)
{
    const gr_complex *in0 = (const gr_complex *) input_items[0];
    const char *in1 = (const char *) input_items[1];
    const char *in2 = (const char *) input_items[2];
   
    //nechapem preco nie const
    gr_complex *out0 = (gr_complex *) output_items[0];
    float *out1 = (float *) output_items[1];
    

    //vypocet Eb/N0 [db] -------------------------------
    float rozpatie, rozpatiePostup;

    float EDB[_N];

    rozpatie = float((_EbN0max - _EbN0min)) / float((_N-1));
    rozpatiePostup = float(_EbN0min);

    for(int i = 0; i < _N; i++) {
      EDB[i] = rozpatiePostup;
      rozpatiePostup += rozpatie;
    }
    
    //vypocet vykonu vstupneho signalu Ps
    float Ps, sumPs = 0;

    for(int a = 0; a < noutput_items; a++)
      sumPs += pow(in0[a].real(), 2);

    Ps = sumPs / float(noutput_items);
    
    for(int b = 0; b < noutput_items; b++) {
      //AWGN kanal
      gr_complex sg_n = AWGN_Sum(EDB[k], Ps, _Rb, _fvz);
      gr_complex spolu = (in0[b].real() + sg_n.real(), in0[b].imag() + sg_n.imag());
      
      out0[b] = spolu;

      //BER pravdepodobnost
      out1[b] = BER(in1[b], in2[b]);

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

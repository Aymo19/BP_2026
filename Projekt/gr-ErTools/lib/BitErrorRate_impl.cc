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

static int is[] = { sizeof(int), sizeof(char), sizeof(char) };
static std::vector<int> isig(is, is + sizeof(is) / sizeof(int));

static int os[] = { sizeof(float) };
static std::vector<int> osig(os, os + sizeof(os) / sizeof(int));

//private constructor
BitErrorRate_impl::BitErrorRate_impl(int N, int Rb, int fvz, int EbN0min, int EbN0max)
    : gr::sync_block("BitErrorRate",
                     gr::io_signature::makev(2, 3, isig),
                     gr::io_signature::makev(1, 1, osig))
{
  _N = N;
  
  k = 0;
  int chyby[N];
  int count[N];
  for(int z = 0; z < N; z++) {
    chyby[z] = 0;
    count[z] = 0;
  }
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

float BER(char S1, char S2, int* Chyba) {
  char virt_jedna = 1, XORnute;
  int e_sum, N_S1 = sizeof(S1) * 8, N_S2 = sizeof(S2) * 8; //krat 8 lebo 1 kodove slovo ma 8 bitov
  float BER, log_BER;

  XORnute = S1 ^ S2;
  
  e_sum = BitCounter(XORnute, N_S1);

  if(e_sum != 0)
    *Chyba =+ 1;
  
  BER = (float)e_sum / (float)N_S1;
  
  log_BER = logf(BER);

  return log_BER;
}

//------------------------------------------------------->

int BitErrorRate_impl::work(int noutput_items,
                            gr_vector_const_void_star& input_items,
                            gr_vector_void_star& output_items)
{
    const int *in0 = (const int *) input_items[0];
    const char *in1 = (const char *) input_items[1];
    const char *in2 = (const char *) input_items[2];
    
    

    //nechapem preco nie const
    float *out1 = (float *) output_items[1];

    
    for(int b = 0; b < noutput_items; b++) {
      
      k = in0[b];
      //BER pravdepodobnost
      //out1[b] = BER(in1[b], in2[b], &chyby[k]);

    }
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

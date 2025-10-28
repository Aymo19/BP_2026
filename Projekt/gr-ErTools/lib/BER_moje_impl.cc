/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BER_moje_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ErTools {

using input_type = char;
using output_type = float;

BER_moje::sptr BER_moje::make(int N, int Rb, int EbN0min, int EbN0max) {
    return gnuradio::make_block_sptr<BER_moje_impl>(N, Rb, EbN0min, EbN0max);
}


//The private constructor
BER_moje_impl::BER_moje_impl(int N, int Rb, int EbN0min, int EbN0max)
    : gr::sync_block("BER_moje",
                     gr::io_signature::make(3, 3, sizeof(input_type)+sizeof(gr_complex)),
                     gr::io_signature::make(2, 2, sizeof(output_type)))
{
  _N = N;
  _Rb = Rb;
  _EbN0min = EbN0min;
  _EbN0max = EbN0max;
}

//<------------------------------------------------------------------->
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
//<----------------------------------------------------------------->

void BER(char S1, char S2) {
  char virt_jedna = 1, XORnute; //0000 0001 pre nas
  int e_sum, N_S1 = sizeof(S1) * 8, N_S2 = sizeof(S2) * 8; //krat 8 lebo 1 kodove slovo ma 8 bitov
  float BER, log_BER;

  XORnute = S1 ^ S2;
  
  e_sum = BitCounter(XORnute, N_S1);
  
  BER = (float)e_sum / (float)N_S1;
  
  //log_BER = logf(BER); //doplnit kniznicu na log
}

//Our virtual destructor.
BER_moje_impl::~BER_moje_impl() {}

int BER_moje_impl::work(int noutput_items,
                        gr_vector_const_void_star& input_items,
                        gr_vector_void_star& output_items)
{
    auto in0 = static_cast<const input_type*>(input_items[0]);
    auto in1 = static_cast<const input_type*>(input_items[1]);
    auto in2 = static_cast<const input_type*>(input_items[2]);
    auto out0 = static_cast<output_type*>(output_items[0]);
    auto out1 = static_cast<output_type*>(output_items[1]);    
    

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

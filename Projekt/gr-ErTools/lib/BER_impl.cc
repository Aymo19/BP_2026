/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BER_impl.h"
#include <gnuradio/io_signature.h>

// Pridane kniznice
#include <cmath>
#include <random>
#include <complex>
#include <algorithm>

namespace gr {
namespace ErTools {

using output_type = float;

BER::sptr BER::make(int N, int M) {
  return gnuradio::make_block_sptr<BER_impl>(N, M);
}

// Input vector
static int is[] = { sizeof(int), sizeof(unsigned char), sizeof(unsigned char) };
static std::vector<int> isig(is, is + sizeof(is) / sizeof(int));

// The private constructor
BER_impl::BER_impl(int N, int M)
    : gr::sync_block("BER",
                     gr::io_signature::makev(2, 3, isig),
                     gr::io_signature::make(1, 1, sizeof(output_type)))
{
  _N = N; // Pocet vzoriek EbN0 (kolko bodov na X-osi)
  _M = M;

  k = std::log2(M);

  // Vektory
  _count = std::vector<int>(N, 2);          // Celkovy pocet bitov co sme spracovali
  _pocet_chyb = std::vector<int>(N, 0);     // Celkovy pocet zistenych chyb
  _pamat_BER = std::vector<double>(N, 1.0); // Vystupne hodnoty BER
  
  /* stare pre zoznamy
  std::fill_n(_count, N, 8);
  std::fill_n(_pocet_chyb, N, 0);
  std::fill_n(_pamat_SER, N, 1.0);*/
}

//Our virtual destructor.
BER_impl::~BER_impl() {}

//----------------------------------------------------LOGIKA-FUNKCIE--------------------------------------------------------||

//-------------------Zisti-kolko-chyb-je-v-slove---------------------| prerobim este
int BitCounter(unsigned char slovo, int n) {
  int sum = 0;//, sign = 1;
  unsigned char b_jedna = 1;
  
  // Pracuje sa cisto s kladnými hodnotami, lebo GR dátový typ Byte je totožný s unsigned char v C++  
  for(int i = 0; i < n; i++) {
    if(slovo & b_jedna)
      sum++;

    slovo >>= 1;
  }

  return sum;
}


//-------------------Zisti-ci-nastala-chyba---------------------|
int BER_calc(unsigned char S1, unsigned char S2, int k) {
  unsigned char XORnute;
  int e_sum;
  
  // Logaritmicke premenne
  //float BER, log_BER;

  // XOR-neme slovo zo signalu 1 a slovo zo signalu 2, vieme ze je chyba, ale nevieme kde a kolko chyb
  XORnute = S1 ^ S2;
  
  // Ak hej, tak nie je nulova hodnota e_sum
  e_sum = BitCounter(XORnute, 2);
  
  // Logaritmicky vystup
  //log_BER = logf(e_sum);
  
  //return log_BER;*/
  
  return e_sum;
}

//-------------------------------------------------------------------------------------------------------------------------||
//---------------------------------------------------------WORK------------------------------------------------------------||

int BER_impl::work(int noutput_items,
                   gr_vector_const_void_star& input_items,
                   gr_vector_void_star& output_items)
{
    
    //-----------------------Inicializacia-I/O--------------------------|
    // INPUT
    int *in0 = (int *)input_items[0];
    unsigned char *in1 = (unsigned char *)input_items[1];
    unsigned char *in2 = (unsigned char *)input_items[2];
    
    // OUTPUT
    auto out = static_cast<output_type*>(output_items[0]);

    //-----------------------LOGIKA--------------------------|
    //-------------------Prvotne-vypocty---------------------|
    
    /*long long int pocet_chyb[_N], count[_N];
    float pamat_SER[_N];
    std::fill_n(pocet_chyb, _N, 0);
    std::fill_n(count, _N, 8);
    std::fill_n(pamat_SER, _N, 1.0);*/
    
    //velkost input vektora z AWGN kanala
    int kk;

    //-----------------------Prejdeme-vsetkymi-I/O-items--------------------------|
    for(int i = 0; i < noutput_items; i++) {
      kk = in0[i];
      
      // Zistime, ci nastala chyba v slove
      _pocet_chyb.at(kk) += BER_calc(in1[i], in2[i], k);
      
      // Nastavenia pre logaritmus v pripade ze nenastala chyba
      // GR nedokaze zobrazit v QT GUI nekonecna
      if(_pocet_chyb.at(kk) == 0) {
        _pamat_BER.at(kk) = 0;//0.00000001; // log cisla je -8
      }else {
        _pamat_BER.at(kk) = double(_pocet_chyb.at(kk)) / double(_count.at(kk)); // Tuto nastala chyba, nemenime umelo hodnotu, pocet chyb deleno pocet bitov za celu dobu
      }

     /*if(k%2 == 0)
        GR_LOG_INFO(d_logger,std::to_string(_pocet_chyb.at(kk)) + std::string(" - ") + std::to_string(_count.at(kk)) + std::string("\n"));
      */

      // Float vystup = pravdepodobnost chyby na bit v danom Eb/N0
      out[i] = _pamat_BER.at(kk);
      
      // Inkrementujeme celkovy pocet bitov
      _count.at(kk) += 2;
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

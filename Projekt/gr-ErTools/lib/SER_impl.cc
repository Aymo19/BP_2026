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
#include <random>
#include <complex>
#include <algorithm>

namespace gr {
namespace ErTools {

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
  _N = N; // Pocet vzoriek EsN0 (kolko bodov na X-osi)
  
  // Vektory
  _count = std::vector<int>(N, 1);          // Celkovy pocet symbolov co sme spracovali
  _pocet_chyb = std::vector<int>(N, 0);     // Celkovy pocet zistenych chyb
  _pamat_SER = std::vector<double>(N, 1.0); // Vystupne hodnoty SER
}

// Our virtual destructor.
SER_impl::~SER_impl() {}

//----------------------------------------------------LOGIKA-FUNKCIE--------------------------------------------------------||

//-------------------Zisti-ci-nastala-chyba---------------------|
int SER_calc(unsigned char S1, unsigned char S2) {
  int e_sum = 1;
  
  // Ak hej, tak nie je nulova hodnota e_sum
  if(S1 == S2)
    e_sum = 0;
  
  return e_sum;
}

//-------------------------------------------------------------------------------------------------------------------------||
//---------------------------------------------------------WORK------------------------------------------------------------||


int SER_impl::work(int noutput_items,
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
    
    //velkost input vektora z AWGN kanala
    int k;

    //-----------------------Prejdeme-vsetkymi-I/O-items--------------------------|
    for(int i = 0; i < noutput_items; i++) {
      k = in0[i];
      
      // Zistime, ci nastala chyba v slove
      _pocet_chyb.at(k) += SER_calc(in1[i], in2[i]);
      
      // Nastavenia pre logaritmus v pripade ze nenastala chyba
      // GR nedokaze zobrazit v QT GUI nekonecna
      if(_pocet_chyb.at(k) == 0) {
        _pamat_SER.at(k) = 0;//0.00000001; // log cisla je -8
      }else {
        _pamat_SER.at(k) = double(_pocet_chyb.at(k)) / double(_count.at(k)); // Tuto nastala chyba, nemenime umelo hodnotu, pocet chyb deleno pocet bitov za celu dobu
      }

     /* if(k%10000 == 0)
        GR_LOG_INFO(d_logger, std::string("b: ") + std::to_string(in2[i]) + std::string("\n"));
      */

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

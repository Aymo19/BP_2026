/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "AWGN_kanal_impl.h"
#include <gnuradio/io_signature.h>

// Pridane kniznice
#include <cmath>
#include <random>
#include <complex>
#include <cstdlib>

namespace gr {
namespace ErTools {

AWGN_kanal::sptr AWGN_kanal::make(int N, int EbN0min, int EbN0max, int R, int W) {
    return gnuradio::make_block_sptr<AWGN_kanal_impl>(N, EbN0min, EbN0max, R, W);
}

// Output vector
static int os[] = { sizeof(gr_complex), sizeof(int) };
static std::vector<int> osig(os, os + sizeof(os) / sizeof(int));

//The private constructor
AWGN_kanal_impl::AWGN_kanal_impl(int N, int EbN0min, int EbN0max, int R, int W)
    : gr::sync_block("AWGN_kanal",
                     gr::io_signature::make(1, 1, sizeof(gr_complex)),
                     gr::io_signature::makev(1, 2, osig))
{
  _N = N; // Pocet vzoriek EbN0 (kolko bodov na X-osi)
  _Rb = R; // Bitova rychlost
  _fvz = W; // Sirka pasma
  _EbN0min = EbN0min; // Zaciatok EbN0 [dB]
  _EbN0max = EbN0max; // Koniec EbN0 [dB]

  // Vnutorne premenne
  
}

//Our virtual destructor.
AWGN_kanal_impl::~AWGN_kanal_impl() {}

//----------------------------------------------------LOGIKA-FUNKCIE--------------------------------------------------------||

//-------------------Tvorba-Gaussovky-a-random-bodu---------------------|
double Sum_vypocet() {
  double GR, GI;

  // Generovanie nahodneho cisla podla semena (seed)
  std::random_device rd;
  std::mt19937 R(rd());
  
  // Tvorba Gaussovky podla odchylky
  std::normal_distribution<double> Gauss{0, 1}; //mi = 0 lebo AWGN
  
  // Vyberieme nahodne hodnoty z Gaussovky
  GR = Gauss(R);

  return GR;
}


//-------------------Odvodenie-varianci-esumu-z-EbN0-[db]---------------------|
gr_complex Sum(float EDB, float Ps, int _Rb, int _fvz) {
  double EbN0, SNR, N, VRMS;
  double REAL, IMAG;

  // Premena z dB na pomer
  EbN0 = pow(10.0, EDB/10.0);

  double menovatel = sqrt(2 * EbN0);

  REAL = Sum_vypocet() / menovatel;
  IMAG = Sum_vypocet() / menovatel;

  gr_complex n(REAL, IMAG);

  return n;
}

//-------------------------------------------------------------------------------------------------------------------------||
//-------------------------------------------------------PREMENNE----------------------------------------------------------||

//docasne, musim upravit
float rozpatie, rozpatiePostup;
int k = 0;

//-------------------------------------------------------------------------------------------------------------------------||
//---------------------------------------------------------WORK------------------------------------------------------------||

int AWGN_kanal_impl::work(int noutput_items,
                          gr_vector_const_void_star& input_items,
                          gr_vector_void_star& output_items)
{
    
    //-----------------------Inicializacia-I/O--------------------------|
    // INPUT
    gr_complex *in0 = (gr_complex *) input_items[0];
    
    // OUTPUT
    gr_complex *out0 = (gr_complex *) output_items[0];
    int *out1 = (int *) output_items[1];

    //-----------------------LOGIKA--------------------------|
    //-------------------Prvotne-vypocty---------------------|
    float EDB[_N];

    // Linearne rozlozenie EbN0db bodov
    rozpatie = float((_EbN0max - _EbN0min)) / float((_N-1));
    rozpatiePostup = float(_EbN0min);

    for(int i = 0; i < _N; i++) {
      EDB[i] = rozpatiePostup;
      rozpatiePostup += rozpatie;
    }
    
    // Vypocet vykonu vstupneho signalu Ps = E(x)
    for(int a = 0; a < noutput_items; a++)
      sumPs += pow(abs(in0[a]), 2);

    Ps = sumPs / float(noutput_items);


    //-----------------------Prejdeme-vsetkymi-I/O-items--------------------------|
    for(int b = 0; b < noutput_items; b++) {
      
      // Ziskanie komplexneho sumu
      gr_complex sg_n = Sum(EDB[k], Ps, _Rb, _fvz);
      
      // Tuto by sa malo scitat ale C++ neznasa komplexne cisla, alebo mna...
      //gr_complex spolu(in0[b].real() + sg_n.real(), in0[b].imag() + sg_n.imag());

      // Komplexny vystup = AWGN sum
      out0[b] = sg_n;

      // Int vystup = N-ta vzorka EbN0, ktoru sme pocitali
      out1[b] = k;

      // Iterujeme po vsetkych vzorkach EbN0, t.j. od 0 do N-1
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

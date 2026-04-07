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

AWGN::sptr AWGN::make(int N, int M, int EbN0min, int EbN0max) {
    return gnuradio::make_block_sptr<AWGN_impl>(N, M, EbN0min, EbN0max);
}

// Output vector
static int os[] = { sizeof(gr_complex)};
static std::vector<int> osig(os, os + sizeof(os) / sizeof(int));

static int is[] = { sizeof(gr_complex), sizeof(float) };
static std::vector<int> isig(is, is + sizeof(is) / sizeof(int));

// The private constructor
AWGN_impl::AWGN_impl(int N, int M, int EbN0min, int EbN0max)
    : gr::sync_block("AWGN",
                     gr::io_signature::makev(1, 2, isig),
                     gr::io_signature::makev(1, 2, osig))
{
  _N = N;             // Pocet vzoriek EbN0 (kolko bodov na X-osi)
  _M = M;             // Pocet modulacnych stavov
  _EbN0min = EbN0min; // Zaciatok EbN0 [dB]
  _EbN0max = EbN0max; // Koniec EbN0 [dB]
}

//----------------------------------------------------LOGIKA-FUNKCIE--------------------------------------------------------||

//-------------------Tvorba-Gaussovky-a-random-bodu---------------------|
double Sum_vypocet2() {
  double GR;

  // Generovanie nahodneho cisla podla seed
  std::random_device rd;
  std::mt19937 R(rd());
  
  // Tvorba Gaussovky podla odchylky
  std::normal_distribution<double> Gauss{0, 1}; //mi = 0 lebo AWGN
  
  // Vyberieme nahodne hodnoty z Gaussovky
  GR = Gauss(R);

  return GR;
}


//-------------------Odvodenie-varianci-esumu-z-EbN0-[db]---------------------|
gr_complex Sum2(float EDB, int stav, float Es) {
  double EbN0, N, EsN0;
  double REAL, IMAG;
  double odchylka;
  int k = std::log2(stav);

  // Premena z dB na pomer
  EDB += 10.0*std::log10(4.0/7.0);
  if(stav > 2) {  //pocitame s EsN0, šum na symbol
    //EsN0 = EbN0 + 10*std::log10(k);
    EsN0 = pow(10.0, (EDB + 10.0*std::log10(4)) / 10.0);
    odchylka = std::sqrt(Es / (EsN0 * 2));
  }else {         //pocitame s EbN0, šum na bit
    EsN0 = pow(10.0, EDB/10.0);
    EbN0 = EsN0 * k;
    odchylka = std::sqrt(1 / (EbN0 * 2));
  }
  
  REAL = Sum_vypocet2() * odchylka;
  IMAG = Sum_vypocet2() * odchylka;

  gr_complex n(REAL, IMAG);

  return n;
}

//-------------------------------------------------------------------------------------------------------------------------||
//-------------------------------------------------------PREMENNE----------------------------------------------------------||

//docasne, musim upravit
//float rozpatie2, rozpatiePostup2;
//int k2 = 0;

//-------------------------------------------------------------------------------------------------------------------------||
//---------------------------------------------------------WORK------------------------------------------------------------||

// Our virtual destructor.
AWGN_impl::~AWGN_impl() {}



int AWGN_impl::work(int noutput_items,
                    gr_vector_const_void_star& input_items,
                    gr_vector_void_star& output_items)
{
      //-----------------------Inicializacia-I/O--------------------------|
    // INPUT
    gr_complex *in0 = (gr_complex *) input_items[0];
    float *in1 = (float *) input_items[1];
    
    // OUTPUT
    gr_complex *out0 = (gr_complex *) output_items[0];

    //-----------------------LOGIKA--------------------------|
    //-------------------Prvotne-vypocty---------------------|
    
    float EBQ;

    Ps = 0;
    sumPs = 0;
    // Vypocet vykonu vstupneho signalu Ps = E(x)
    for(int a = 0; a < noutput_items; a++)
      sumPs += std::norm(in0[a]);
    
    Ps = sumPs / noutput_items;
    //-----------------------Prejdeme-vsetkymi-I/O-items--------------------------|
    for(int b = 0; b < noutput_items; b++) {
      
      EBQ = in1[b];
      // Ziskanie komplexneho sumu
      gr_complex sg_n = Sum2(EBQ, _M, Ps);
      
      // Tuto by sa malo scitat ale C++ neznasa komplexne cisla, alebo mna...
      //gr_complex spolu(in0[b].real() + sg_n.real(), in0[b].imag() + sg_n.imag());

      // Komplexny vystup = AWGN sum
      out0[b] = sg_n;

      // Int vystup = N-ta vzorka EbN0, ktoru sme pocitali

      // Iterujeme po vsetkych vzorkach EbN0, t.j. od 0 do N-1
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

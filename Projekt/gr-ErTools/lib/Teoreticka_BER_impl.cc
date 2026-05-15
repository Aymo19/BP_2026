/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#define _USE_MATH_DEFINES

#include "Teoreticka_BER_impl.h"
#include <gnuradio/io_signature.h>

// Pridane kniznice
#include <cmath>
#include <string>

namespace gr {
namespace ErTools {

// Datovy typ vystupu 
using output_type = float;

Teoreticka_BER::sptr Teoreticka_BER::make(int N, int M, std::string Mod, int EbN0min, int EbN0max) {
    return gnuradio::make_block_sptr<Teoreticka_BER_impl>(N, M, Mod, EbN0min, EbN0max);
}

// Our virtual destructor.
Teoreticka_BER_impl::~Teoreticka_BER_impl() {}

//----FUNKCIE----||
// Complementary Error Function (erfc)
double ErrFunkcia(double bod) {
  return std::erfc(bod);
}

// BPSK M = 2
double BPSK(double EbN0) {
  double argument, Pb;

  // Premena z dB na pomer
  EbN0 = pow(10.0, EbN0/10.0);
  
  // VZORCE
  argument = std::sqrt(EbN0);

  Pb = 0.5 * ErrFunkcia(argument);

  return Pb;
}

// QPSK, M = 4
double QPSK(double EbN0) {
  double argument, Pb;

  // Premena z dB na pomer
  EbN0 = pow(10.0, EbN0/10.0);
  
  //VZORCE
  argument = std::sqrt(EbN0);

  Pb = 0.5 * ErrFunkcia(argument);

  return Pb;
}

// M-PSK, M > 4
double MPSK(double EbN0, int M, int k) {
  double argument, Pb;

  // Premena z dB na pomer
  EbN0 = pow(10.0, (EbN0 + 10*std::log10(k))/10.0);
  
  //VZORCE
  argument = std::sin(M_PI / M) * std::sqrt(2*EbN0);
  
  Pb = ErrFunkcia(argument / std::sqrt(2)) / k;
 
  return Pb;
}

// M-QAM
double MQAM(double EbN0, int M, int k) {
  double argument, Pb, faktor;

  // Premena z dB na pomer
  EbN0 = pow(10.0, (EbN0)/10);
  
  //VZORCE
  faktor = (2 / double(k)) * (1 - (1 / std::sqrt(M)));
  argument = std::sqrt((3 * EbN0 * k) / (M - 1));

  Pb = faktor * ErrFunkcia(argument / std::sqrt(2));
  
  return Pb;
};

// The private constructor
Teoreticka_BER_impl::Teoreticka_BER_impl(int N, int M, std::string Mod, int EbN0min, int EbN0max)
    : gr::sync_block("Teoreticka_BER",
                     gr::io_signature::make(0, 0, 0),
                     gr::io_signature::make(1, 1, sizeof(output_type)))
{
  _N = N; // Pocet bodov EbN0 v rozpati
  _M = M; // Pocet modulacnych stavov
  _Mod = Mod; // Vybrany typ modulacie
  _EbN0min = EbN0min; // Zaciatok EbN0
  _EbN0max = EbN0max; // Koniec EbN0

  // Vektory pre BER hodnoty
  _bodyBPSK = std::vector<double>(N, 1.0);
  _bodyQPSK = std::vector<double>(N, 1.0);
  _bodyMPSK = std::vector<double>(N, 1.0);
  _bodyMQAM = std::vector<double>(N, 1.0);
  
  index = 0;
  EDB = std::vector<double>(N, 0);

  // Linearne rozlozenie EbN0db bodov
  rozpatieT = double((_EbN0max - _EbN0min)) / double((_N-1));
  rozpatiePostupT = double(_EbN0min);

  for(int i = 0; i < _N; i++) {
    EDB.at(i) = rozpatiePostupT;
    rozpatiePostupT += rozpatieT;
  }

  // pocet bitov na symbol
  int k = std::log2(_M);

  // Volanie funkcii na vypocet teoretickych BER
  for(int y = 0; y < _N; y++) {
    _bodyBPSK.at(y) = BPSK(EDB[y]); // BPSK
    _bodyQPSK.at(y) = QPSK(EDB[y]); // QPSK
    _bodyMPSK.at(y) = MPSK(EDB[y], _M, k); // MPSK
    _bodyMQAM.at(y) = MQAM(EDB[y], _M, k); // M-QAM
  }
}


//----WORK----||
int Teoreticka_BER_impl::work(int noutput_items,
                              gr_vector_const_void_star& input_items,
                              gr_vector_void_star& output_items)
{
    // Inicializacia I/O
    // OUTPUT
    auto out = static_cast<output_type*>(output_items[0]);
    
    // LOGIKA
    // Prejdeme vsetkymi I/O items
    for(int b = 0; b < noutput_items; b++) {
        // Vypis podla toho aka modulacia(_Mod) a pocet stavov (_M)
        if(_Mod == "PSK") {
          if(_M == 2) {
            out[b] = _bodyBPSK.at(index); // BPSK
          }else if(_M == 4) {
            out[b] = _bodyQPSK.at(index); // QPSK
          }else {
            out[b] = _bodyMPSK.at(index); // MPSK
          }
        }else if(_Mod == "QAM") {
          out[b] = _bodyMQAM.at(index); // M-QAM
        }
        
        // Iteracia cez vsetky EbN0
        if(index < _N-1) {
          index += 1;
        }else {
          index = 0;
        }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

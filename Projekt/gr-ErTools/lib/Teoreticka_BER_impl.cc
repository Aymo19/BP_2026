/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#define _USE_MATH_DEFINES

#include "Teoreticka_BER_impl.h"
#include <gnuradio/io_signature.h>

#include <cmath>

namespace gr {
namespace ErTools {

using output_type = float;

Teoreticka_BER::sptr Teoreticka_BER::make(int N, int M, int EbN0min, int EbN0max) {
    return gnuradio::make_block_sptr<Teoreticka_BER_impl>(N, M, EbN0min, EbN0max);
}

// Our virtual destructor.
Teoreticka_BER_impl::~Teoreticka_BER_impl() {}

double ErrFunkcia(double bod) {
  double BER_lin;

  BER_lin = std::erfc(bod);

  return BER_lin;
}

double BPSK(double EbN0) {
  double argument, Pb;

  EbN0 = pow(10.0, EbN0/10.0);
  
  argument = std::sqrt(EbN0);  
  Pb = 0.5 * ErrFunkcia(argument);

  return Pb;
}

double QPSK(double EbN0) {
  double argument, Pb;

  EbN0 = pow(10.0, EbN0/10.0);
  
  argument = std::sqrt(EbN0);  
  Pb = 0.5 * ErrFunkcia(argument);

  return Pb;
}

double MPSK(double EbN0, int M, int k) {
  double argument, Pb;

  EbN0 = pow(10.0, (EbN0 + 10*std::log10(k))/10.0);
  
  argument = std::sin(M_PI / M) * std::sqrt(2*EbN0);
  
  Pb = ErrFunkcia(argument / std::sqrt(2)) / k;
  //printf("%lf %lf\n", argument, Pb);
  return Pb;
}

double MQAM(double EbN0, int k) {
  double argument, Pb;

  EbN0 = pow(10.0, EbN0/10.0);
  
  argument = std::sqrt(EbN0);  
  Pb = ErrFunkcia(argument);

  return Pb;
}

// The private constructor
Teoreticka_BER_impl::Teoreticka_BER_impl(int N, int M, int EbN0min, int EbN0max)
    : gr::sync_block("Teoreticka_BER",
                     gr::io_signature::make(0, 0, 0),
                     gr::io_signature::make(1, 1, sizeof(output_type)))
{
  _N = N;
  _M = M;
  _EbN0min = EbN0min;
  _EbN0max = EbN0max;

  _bodyBPSK = std::vector<double>(N, 1.0);
  _bodyQPSK = std::vector<double>(N, 1.0);
  _bodyMPSK = std::vector<double>(N, 1.0);
  _bodyMQAM = std::vector<double>(N, 1.0);
  
  koniec = 0;
  j = 0;
  EDB = std::vector<double>(N, 0);

  // Linearne rozlozenie EbN0db bodov
  rozpatieT = double((_EbN0max - _EbN0min)) / double((_N-1));
  rozpatiePostupT = double(_EbN0min);

  for(int i = 0; i < _N; i++) {
    EDB.at(i) = rozpatiePostupT;
    rozpatiePostupT += rozpatieT;
      //GR_LOG_INFO(d_logger, std::string("R: ") + std::to_string(rozpatiePostupT) + std::string("\n"));

  }

  int k = std::log2(_M);

  for(int y = 0; y < _N; y++) {
    _bodyBPSK.at(y) = BPSK(EDB[y]);
    _bodyQPSK.at(y) = QPSK(EDB[y]);
    _bodyMPSK.at(y) = MPSK(EDB[y], _M, k);
    _bodyMQAM.at(y) = MQAM(EDB[y], k);
  }

}

int Teoreticka_BER_impl::work(int noutput_items,
                              gr_vector_const_void_star& input_items,
                              gr_vector_void_star& output_items)
{
    auto out = static_cast<output_type*>(output_items[0]);
    
    for(int b = 0; b < noutput_items; b++) {
        
        if(_M == 2) {
          out[b] = _bodyBPSK.at(j);
        }else if(_M == 4) {
          out[b] = _bodyQPSK.at(j);
        }else {
          out[b] = _bodyMPSK.at(j);
        }

        if(j < _N-1) {
          j += 1;
        }else {
          j = 0;
        }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

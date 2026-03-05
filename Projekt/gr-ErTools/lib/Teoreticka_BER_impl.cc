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

  _bodyBER = std::vector<double>(N, 1.0);
  koniec = 0;
}

// Our virtual destructor.
Teoreticka_BER_impl::~Teoreticka_BER_impl() {}

double QFunkcia(double bod) {
  double BER_lin;

  BER_lin = 0.5 * std::erfc(bod); // / std::sqrt(2));

  return BER_lin;
}

double BPSK(double EbN0) {
  double argument, Pb;

  EbN0 = pow(10.0, EbN0/10.0);
  
  argument = std::sqrt(EbN0 / 2);  
  Pb = QFunkcia(argument);

  return Pb;
}

double rozpatieT, rozpatiePostupT;

int Teoreticka_BER_impl::work(int noutput_items,
                              gr_vector_const_void_star& input_items,
                              gr_vector_void_star& output_items)
{
    auto out = static_cast<output_type*>(output_items[0]);
    
    if(koniec)
      return WORK_DONE;

    //lin rozdelit
    double EDB[_N];

    // Linearne rozlozenie EbN0db bodov
    rozpatieT = double((_EbN0max - _EbN0min)) / double((_N-1));
    rozpatiePostupT = double(_EbN0min);

    for(int i = 0; i < _N; i++) {
      EDB[i] = rozpatiePostupT;
      rozpatiePostupT += rozpatieT;
      //GR_LOG_INFO(d_logger, std::string("R: ") + std::to_string(rozpatiePostupT) + std::string("\n"));

    }
    
    double k = std::log2(_M);
    int j = 0;
    if(k == 1) {
    for(int y = 0; y < noutput_items; y++) {

        out[y] = BPSK(EDB[j]);
        if(j < _N-1) {
          j += 1;
        }else {
          break;
        }
      }
    }

    koniec = 1;

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

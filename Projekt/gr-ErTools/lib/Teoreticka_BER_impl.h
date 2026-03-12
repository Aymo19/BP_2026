/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_TEORETICKA_BER_IMPL_H
#define INCLUDED_ERTOOLS_TEORETICKA_BER_IMPL_H

#include <gnuradio/ErTools/Teoreticka_BER.h>
#include <string>

namespace gr {
namespace ErTools {

class Teoreticka_BER_impl : public Teoreticka_BER
{
private:
  int _N, _M, _EbN0min, _EbN0max;
  std::string _Mod;
  int j;
  double rozpatieT, rozpatiePostupT;

  std::vector<double> _bodyBPSK; // BPSK
  std::vector<double> _bodyQPSK; // QPSK
  std::vector<double> _bodyMPSK; // MPSK

  std::vector<double> _bodyMQAM; // M-QAM

  std::vector<double> EDB;

public:
    Teoreticka_BER_impl(int N, int M, std::string Mod, int EbN0min, int EbN0max);
    ~Teoreticka_BER_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_TEORETICKA_BER_IMPL_H */

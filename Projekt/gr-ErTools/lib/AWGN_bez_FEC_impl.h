/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_AWGN_BEZ_FEC_IMPL_H
#define INCLUDED_ERTOOLS_AWGN_BEZ_FEC_IMPL_H

#include <gnuradio/ErTools/AWGN_bez_FEC.h>

#include <random>

namespace gr {
namespace ErTools {

class AWGN_bez_FEC_impl : public AWGN_bez_FEC
{
private:
  int _M, _k, _n, index, counter;
  double Es, sumEs, EBQ_B;

  std::random_device rd_B;
  std::mt19937 R_B;
  std::normal_distribution<double> Gauss_B;
  
  gr_complex Sum_B(double EDB, int stav, double Es);

public:
    AWGN_bez_FEC_impl(int M);
    ~AWGN_bez_FEC_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_AWGN_BEZ_FEC_IMPL_H */

/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_AWGN_IMPL_H
#define INCLUDED_ERTOOLS_AWGN_IMPL_H

#include <gnuradio/ErTools/AWGN.h>

#include <random>

namespace gr {
namespace ErTools {

class AWGN_impl : public AWGN
{
private:
  int _M, _k, _n, index, counter;
  float Ps, sumPs, EBQ;
  double Rs;
  gr_complex sg_n;

  std::random_device rd;
  std::mt19937 R;
  std::normal_distribution<double> Gauss;
  
  gr_complex Sum(float EDB, int stav, float Es, double Rs);
public:
    AWGN_impl(int M, int k, int n);
    ~AWGN_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_AWGN_IMPL_H */

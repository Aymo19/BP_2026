/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_MC_IMPL_H
#define INCLUDED_ERTOOLS_MC_IMPL_H

#include <gnuradio/ErTools/MC.h>

namespace gr {
namespace ErTools {

class MC_impl : public MC
{
private:
  int _N, _EbN0min, _EbN0max;
  
  int index_CLK, counter;
  double Rz, Rz_krok;

  std::vector<double> v_EDB;

public:
    MC_impl(int N, int EbN0min, int EbN0max);
    ~MC_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_MC_IMPL_H */

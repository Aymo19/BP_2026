/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_AWGN_IMPL_H
#define INCLUDED_ERTOOLS_AWGN_IMPL_H

#include <gnuradio/ErTools/AWGN.h>

namespace gr {
namespace ErTools {

class AWGN_impl : public AWGN
{
private:
  int _N, _M, _EbN0min, _EbN0max;
  float Ps, sumPs;

public:
    AWGN_impl(int N, int M, int EbN0min, int EbN0max);
    ~AWGN_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_AWGN_IMPL_H */

/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_AWGN_KANAL_IMPL_H
#define INCLUDED_ERTOOLS_AWGN_KANAL_IMPL_H

#include <gnuradio/ErTools/AWGN_kanal.h>

namespace gr {
namespace ErTools {

class AWGN_kanal_impl : public AWGN_kanal
{
private:
  int _N, _EbN0min, _EbN0max, _Rb, _fvz, k;
  float Ps, sumPs;

public:
    AWGN_kanal_impl(int N, int EbN0min, int EbN0max, int R, int W);
    ~AWGN_kanal_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_AWGN_KANAL_IMPL_H */

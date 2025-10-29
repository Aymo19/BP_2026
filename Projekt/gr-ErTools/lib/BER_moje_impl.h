/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_BER_MOJE_IMPL_H
#define INCLUDED_ERTOOLS_BER_MOJE_IMPL_H

#include <gnuradio/ErTools/BER_moje.h>

namespace gr {
namespace ErTools {

class BER_moje_impl : public BER_moje
{
private:
  int _N, _Rb, _EbN0min, _EbN0max;

public:
    BER_moje_impl(int N, int Rb, int EbN0min, int  EbN0max);
    ~BER_moje_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_BER_MOJE_IMPL_H */

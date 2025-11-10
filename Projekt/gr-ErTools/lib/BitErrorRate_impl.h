/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_BITERRORRATE_IMPL_H
#define INCLUDED_ERTOOLS_BITERRORRATE_IMPL_H

#include <gnuradio/ErTools/BitErrorRate.h>

namespace gr {
namespace ErTools {

class BitErrorRate_impl : public BitErrorRate
{
private:
  int _N, k;

public:
    BitErrorRate_impl(int N, int Rb, int fvz, int EbN0min, int EbN0max);
    ~BitErrorRate_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_BITERRORRATE_IMPL_H */

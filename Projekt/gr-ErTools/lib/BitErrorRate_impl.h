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
    // Nothing to declare in this block.

public:
    BitErrorRate_impl(int N, int Rb, int EbN0min, int EbN0max, int fvz);
    ~BitErrorRate_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_BITERRORRATE_IMPL_H */

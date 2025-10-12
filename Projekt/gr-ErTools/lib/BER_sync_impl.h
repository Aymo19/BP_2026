/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_BER_SYNC_IMPL_H
#define INCLUDED_ERTOOLS_BER_SYNC_IMPL_H

#include <gnuradio/ErTools/BER_sync.h>

namespace gr {
namespace ErTools {

class BER_sync_impl : public BER_sync
{
private:
  int N;

public:
    BER_sync_impl(int N);
    ~BER_sync_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_BER_SYNC_IMPL_H */

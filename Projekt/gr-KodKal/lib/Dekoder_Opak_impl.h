/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_KODKAL_DEKODER_OPAK_IMPL_H
#define INCLUDED_KODKAL_DEKODER_OPAK_IMPL_H

#include <gnuradio/KodKal/Dekoder_Opak.h>

namespace gr {
namespace KodKal {

class Dekoder_Opak_impl : public Dekoder_Opak
{
private:
  int _n;

  int count, polovica;

public:
    Dekoder_Opak_impl(int n);
    ~Dekoder_Opak_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace KodKal
} // namespace gr

#endif /* INCLUDED_KODKAL_DEKODER_OPAK_IMPL_H */

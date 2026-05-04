/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_KODKAL_KODER_OPAK_IMPL_H
#define INCLUDED_KODKAL_KODER_OPAK_IMPL_H

#include <gnuradio/KodKal/Koder_Opak.h>

namespace gr {
namespace KodKal {

class Koder_Opak_impl : public Koder_Opak
{
private:
  int _k;

public:
    Koder_Opak_impl(int k);
    ~Koder_Opak_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace KodKal
} // namespace gr

#endif /* INCLUDED_KODKAL_KODER_OPAK_IMPL_H */

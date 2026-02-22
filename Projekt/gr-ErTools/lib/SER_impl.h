/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_SER_IMPL_H
#define INCLUDED_ERTOOLS_SER_IMPL_H

#include <gnuradio/ErTools/SER.h>

namespace gr {
namespace ErTools {

class SER_impl : public SER
{
private:
  int _N;

  // Deklarovanie vektorov
  std::vector<int> _count;
  std::vector<double> _pamat_SER;
  std::vector<int> _pocet_chyb;

public:
    SER_impl(int N);
    ~SER_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_SER_IMPL_H */

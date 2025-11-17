/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_BER_IMPL_H
#define INCLUDED_ERTOOLS_BER_IMPL_H

#include <gnuradio/ErTools/BER.h>

namespace gr {
namespace ErTools {

class BER_impl : public BER
{
private:
  int _N;
  std::vector<int> _count;
  std::vector<double> _pamat_SER;
  std::vector<int> _pocet_chyb;
  /*int _count[128], _pocet_chyb[128]; 
  float _pamat_SER[128];
*/
public:
    BER_impl(int N);
    ~BER_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_BER_IMPL_H */

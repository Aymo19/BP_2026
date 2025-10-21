/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BER_sync_impl.h"
#include <gnuradio/io_signature.h>

#include <algorithm>

namespace gr {
namespace ErTools {

using input_type = int;
using output_type = float;
BER_sync::sptr BER_sync::make(int N)
{
    return gnuradio::make_block_sptr<BER_sync_impl>(N);
}


/*
 * The private constructor
 */
BER_sync_impl::BER_sync_impl(int N)
    : gr::sync_block("BER_sync",
                     gr::io_signature::make(
                         3, 3, sizeof(input_type)),
                     gr::io_signature::make(
                         1, 1, sizeof(output_type)))
{
  _N = N;

}

/*
 * Our virtual destructor.
 */
BER_sync_impl::~BER_sync_impl() {}

//PREMENNE
int L, k;

int BER_sync_impl::work(int noutput_items,
                        gr_vector_const_void_star& input_items,
                        gr_vector_void_star& output_items)
{
    //OPRAVIT - zmen input_type na byte namiesto auto
    auto in0 = static_cast<const input_type*>(input_items[0]);
    auto in1 = static_cast<const input_type*>(input_items[1]);
    auto in2 = static_cast<const input_type*>(input_items[2]);
    
    auto out0 = static_cast<output_type*>(output_items[0]);

    int pocet_chyb[_N], count[_N], pamat_SER[_N];
    std::fill_n(pocet_chyb, _N, 1);
    std::fill_n(count, _N, 1);
    std::fill_n(pamat_SER, _N, 1);
    
    //velkost input vektora z AWGN kanala
    L = sizeof(in0) / sizeof(in0[0]);
    
    for(int i = 0; i < L; i++) {
      k = in0[i];

      pocet_chyb[k] += int(in0[i] != in1[i]);

      pamat_SER[k] = pocet_chyb[k] / count[k];

      out0[i] = pamat_SER[k];

      count[k] += 1;
    }

   //TESTOVANIE
    /*int L = sizeof(in0) / sizeof(in0[0]);
    int K = sizeof(in0[0]);
    printf("Cele: %d\t%d %d\n", L, in0[0], in0[1]);
    printf("Jedno: %dB\n", K);
    printf("nout: %d\n\n", noutput_items);*/

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */

/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_TEORETICKA_BER_H
#define INCLUDED_ERTOOLS_TEORETICKA_BER_H

#include <gnuradio/ErTools/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace ErTools {

/*!
 * \brief <+description of block+>
 * \ingroup ErTools
 *
 */
class ERTOOLS_API Teoreticka_BER : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<Teoreticka_BER> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of ErTools::Teoreticka_BER.
     *
     * To avoid accidental use of raw pointers, ErTools::Teoreticka_BER's
     * constructor is in a private implementation
     * class. ErTools::Teoreticka_BER::make is the public interface for
     * creating new instances.
     */
    static sptr make(int N, int M, int EbN0min, int EbN0max);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_TEORETICKA_BER_H */

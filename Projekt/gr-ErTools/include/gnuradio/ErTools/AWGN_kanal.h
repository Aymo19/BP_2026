/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_AWGN_KANAL_H
#define INCLUDED_ERTOOLS_AWGN_KANAL_H

#include <gnuradio/ErTools/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace ErTools {

/*!
 * \brief <+description of block+>
 * \ingroup ErTools
 *
 */
class ERTOOLS_API AWGN_kanal : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<AWGN_kanal> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of ErTools::AWGN_kanal.
     *
     * To avoid accidental use of raw pointers, ErTools::AWGN_kanal's
     * constructor is in a private implementation
     * class. ErTools::AWGN_kanal::make is the public interface for
     * creating new instances.
     */
    static sptr make(int N, int EbN0min, int EbN0max, int R, int W);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_AWGN_KANAL_H */

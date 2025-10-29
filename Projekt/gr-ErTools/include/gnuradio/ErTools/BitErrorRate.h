/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_BITERRORRATE_H
#define INCLUDED_ERTOOLS_BITERRORRATE_H

#include <gnuradio/ErTools/api.h>
#include <gnuradio/block.h>

namespace gr {
namespace ErTools {

/*!
 * \brief <+description of block+>
 * \ingroup ErTools
 *
 */
class ERTOOLS_API BitErrorRate : virtual public gr::block
{
public:
    typedef std::shared_ptr<BitErrorRate> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of ErTools::BitErrorRate.
     *
     * To avoid accidental use of raw pointers, ErTools::BitErrorRate's
     * constructor is in a private implementation
     * class. ErTools::BitErrorRate::make is the public interface for
     * creating new instances.
     */
    static sptr make(int N, int Rb, int EbN0min, int EbN0max, int fvz);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_BITERRORRATE_H */

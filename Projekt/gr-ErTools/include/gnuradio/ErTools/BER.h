/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_BER_H
#define INCLUDED_ERTOOLS_BER_H

#include <gnuradio/ErTools/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace ErTools {

/*!
 * \brief <+description of block+>
 * \ingroup ErTools
 *
 */
class ERTOOLS_API BER : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<BER> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of ErTools::BER.
     *
     * To avoid accidental use of raw pointers, ErTools::BER's
     * constructor is in a private implementation
     * class. ErTools::BER::make is the public interface for
     * creating new instances.
     */
    static sptr make(int N);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_BER_H */

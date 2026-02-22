/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_SER_H
#define INCLUDED_ERTOOLS_SER_H

#include <gnuradio/ErTools/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace ErTools {

/*!
 * \brief <+description of block+>
 * \ingroup ErTools
 *
 */
class ERTOOLS_API SER : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<SER> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of ErTools::SER.
     *
     * To avoid accidental use of raw pointers, ErTools::SER's
     * constructor is in a private implementation
     * class. ErTools::SER::make is the public interface for
     * creating new instances.
     */
    static sptr make(int N);
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_SER_H */

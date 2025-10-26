/* -*- c++ -*- */
/*
 * Copyright 2025 gr-ErTools author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_PRINTINT_H
#define INCLUDED_ERTOOLS_PRINTINT_H

#include <gnuradio/ErTools/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace ErTools {

/*!
 * \brief <+description of block+>
 * \ingroup ErTools
 *
 */
class ERTOOLS_API PrintInt : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<PrintInt> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of ErTools::PrintInt.
     *
     * To avoid accidental use of raw pointers, ErTools::PrintInt's
     * constructor is in a private implementation
     * class. ErTools::PrintInt::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_PRINTINT_H */

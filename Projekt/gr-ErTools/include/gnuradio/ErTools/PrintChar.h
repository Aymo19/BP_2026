/* -*- c++ -*- */
/*
 * Copyright 2025 gr-ErTools author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_PRINTCHAR_H
#define INCLUDED_ERTOOLS_PRINTCHAR_H

#include <gnuradio/ErTools/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace ErTools {

/*!
 * \brief <+description of block+>
 * \ingroup ErTools
 *
 */
class ERTOOLS_API PrintChar : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<PrintChar> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of ErTools::PrintChar.
     *
     * To avoid accidental use of raw pointers, ErTools::PrintChar's
     * constructor is in a private implementation
     * class. ErTools::PrintChar::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_PRINTCHAR_H */

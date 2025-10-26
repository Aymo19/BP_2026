/* -*- c++ -*- */
/*
 * Copyright 2025 gr-ErTools author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ERTOOLS_PRINTFLOAT_H
#define INCLUDED_ERTOOLS_PRINTFLOAT_H

#include <gnuradio/ErTools/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace ErTools {

/*!
 * \brief <+description of block+>
 * \ingroup ErTools
 *
 */
class ERTOOLS_API PrintFloat : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<PrintFloat> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of ErTools::PrintFloat.
     *
     * To avoid accidental use of raw pointers, ErTools::PrintFloat's
     * constructor is in a private implementation
     * class. ErTools::PrintFloat::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace ErTools
} // namespace gr

#endif /* INCLUDED_ERTOOLS_PRINTFLOAT_H */

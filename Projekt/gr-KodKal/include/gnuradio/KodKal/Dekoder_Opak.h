/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_KODKAL_DEKODER_OPAK_H
#define INCLUDED_KODKAL_DEKODER_OPAK_H

#include <gnuradio/KodKal/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
namespace KodKal {

/*!
 * \brief <+description of block+>
 * \ingroup KodKal
 *
 */
class KODKAL_API Dekoder_Opak : virtual public gr::sync_decimator
{
public:
    typedef std::shared_ptr<Dekoder_Opak> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of KodKal::Dekoder_Opak.
     *
     * To avoid accidental use of raw pointers, KodKal::Dekoder_Opak's
     * constructor is in a private implementation
     * class. KodKal::Dekoder_Opak::make is the public interface for
     * creating new instances.
     */
    static sptr make(int n);
};

} // namespace KodKal
} // namespace gr

#endif /* INCLUDED_KODKAL_DEKODER_OPAK_H */

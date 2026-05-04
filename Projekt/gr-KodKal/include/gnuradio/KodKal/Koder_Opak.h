/* -*- c++ -*- */
/*
 * Copyright 2026 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_KODKAL_KODER_OPAK_H
#define INCLUDED_KODKAL_KODER_OPAK_H

#include <gnuradio/KodKal/api.h>
#include <gnuradio/sync_interpolator.h>

namespace gr {
namespace KodKal {

/*!
 * \brief <+description of block+>
 * \ingroup KodKal
 *
 */
class KODKAL_API Koder_Opak : virtual public gr::sync_interpolator
{
public:
    typedef std::shared_ptr<Koder_Opak> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of KodKal::Koder_Opak.
     *
     * To avoid accidental use of raw pointers, KodKal::Koder_Opak's
     * constructor is in a private implementation
     * class. KodKal::Koder_Opak::make is the public interface for
     * creating new instances.
     */
    static sptr make(int k);
};

} // namespace KodKal
} // namespace gr

#endif /* INCLUDED_KODKAL_KODER_OPAK_H */

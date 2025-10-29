/* -*- c++ -*- */
/*
 * Copyright 2025 gr-tempPY author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TEMPPY_CTEST_H
#define INCLUDED_TEMPPY_CTEST_H

#include <gnuradio/sync_block.h>
#include <gnuradio/tempPY/api.h>

namespace gr {
namespace tempPY {

/*!
 * \brief <+description of block+>
 * \ingroup tempPY
 *
 */
class TEMPPY_API ctest : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<ctest> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of tempPY::ctest.
     *
     * To avoid accidental use of raw pointers, tempPY::ctest's
     * constructor is in a private implementation
     * class. tempPY::ctest::make is the public interface for
     * creating new instances.
     */
    static sptr make(int N, int A, int B);
};

} // namespace tempPY
} // namespace gr

#endif /* INCLUDED_TEMPPY_CTEST_H */

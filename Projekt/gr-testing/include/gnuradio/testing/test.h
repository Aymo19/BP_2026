/* -*- c++ -*- */
/*
 * Copyright 2025 gr-testing author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TESTING_TEST_H
#define INCLUDED_TESTING_TEST_H

#include <gnuradio/sync_block.h>
#include <gnuradio/testing/api.h>

namespace gr {
namespace testing {

/*!
 * \brief <+description of block+>
 * \ingroup testing
 *
 */
class TESTING_API test : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<test> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of testing::test.
     *
     * To avoid accidental use of raw pointers, testing::test's
     * constructor is in a private implementation
     * class. testing::test::make is the public interface for
     * creating new instances.
     */
    static sptr make(int N);
};

} // namespace testing
} // namespace gr

#endif /* INCLUDED_TESTING_TEST_H */

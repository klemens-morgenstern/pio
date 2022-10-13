//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "doctest.h"

#include <make_pipe.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>

TEST_CASE("make_pipe")
{
    boost::asio::io_context ctx;
    auto pp = te::make_pipe(ctx.get_executor());

    auto r = std::move(pp.first);
    auto w = std::move(pp.second);


    std::string res;

    boost::asio::async_write(*w, boost::asio::buffer("Test\n", 5), boost::asio::detached);
    boost::asio::async_read_until(*r, boost::asio::dynamic_buffer(res), '\n', boost::asio::detached);
    ctx.run();

    CHECK(res == "Test\n");
}

//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "doctest.h"

#include <pio.hpp>

#include <asio/io_context.hpp>
#include <asio/write.hpp>
#include <asio/detached.hpp>
#include <asio/read.hpp>
#include <asio/read_until.hpp>

TEST_CASE("make_pipe")
{
    asio::io_context ctx;
    pio::readable_pipe r{ctx};
    pio::writable_pipe w{ctx};
    pio::connect_pipe(r, w);


    std::string res;

    pio::async_write(w, asio::buffer("Test\n", 5), asio::detached);
    asio::async_read_until(r, asio::dynamic_buffer(res), '\n', asio::detached);
    ctx.run();

    CHECK(res == "Test\n");
}

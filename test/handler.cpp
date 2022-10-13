//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <handler.hpp>

#include "doctest.h"

#include <boost/asio.hpp>

TEST_CASE("handler_type")
{
    boost::asio::io_context ctx;
    bool called = false;
    te::handler_type<void(boost::system::error_code)> ht{[&](auto e) {called = true;}, ctx.get_executor()};

    boost::asio::steady_timer tim{ctx};
    tim.async_wait(std::move(ht));

    CHECK(!called);

    ctx.run();

    CHECK(called);
}

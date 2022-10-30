//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "pio/handler.hpp"

#include "doctest.h"

#include <asio.hpp>

TEST_CASE("handler_type")
{
    asio::io_context ctx;
    bool called = false;
    pio::handler_type<void(std::error_code)> ht{[&](auto e) {called = true;}, ctx.get_executor()};

    asio::steady_timer tim{ctx};
    tim.async_wait(std::move(ht));

    CHECK(!called);

    ctx.run();

    CHECK(called);
}

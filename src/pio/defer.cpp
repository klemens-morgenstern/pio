//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/defer.hpp>

namespace pio::detail
{

void defer_impl(asio::any_io_executor exec, handler_type<void()> &&h)
{
    asio::defer(exec, std::move(h));
}
void defer_impl(handler_type<void()> &&h)
{
    asio::defer(std::move(h));
}

}

//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/dispatch.hpp>

namespace pio::detail
{

void dispatch_impl(asio::any_io_executor exec, handler_type<void()> &&h)
{
    asio::dispatch(exec, std::move(h));
}
void dispatch_impl(handler_type<void()> &&h)
{
    asio::dispatch(std::move(h));
}

}

//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/post.hpp>

namespace pio::detail
{

void post_impl(asio::any_io_executor exec, handler_type<void()> &&h)
{
    asio::post(exec, std::move(h));
}
void post_impl(handler_type<void()> &&h)
{
    asio::post(std::move(h));
}

}

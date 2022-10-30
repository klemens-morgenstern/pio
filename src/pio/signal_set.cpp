//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/signal_set.hpp>

namespace pio
{
signal_set::signal_set(const executor_type& ex) : impl_(ex)
{
}

signal_set::signal_set(const executor_type& ex, int signal_number_1)
        : impl_(ex, signal_number_1)
{

}

signal_set::signal_set(const executor_type& ex, int signal_number_1, int signal_number_2)
        : impl_(ex, signal_number_1, signal_number_2)
{

}

signal_set::signal_set(const executor_type& ex, int signal_number_1, int signal_number_2, int signal_number_3)
    : impl_(ex, signal_number_1, signal_number_2, signal_number_3)
{

}

signal_set::~signal_set() = default;

auto signal_set::get_executor() noexcept -> executor_type
{
    return impl_.get_executor();
}

void signal_set::add(int signal_number)
{
    return impl_.add(signal_number);
}
ASIO_SYNC_OP_VOID signal_set::add(int signal_number, asio::error_code& ec)
{
    return impl_.add(signal_number, ec);
}
void signal_set::remove(int signal_number)
{
    return impl_.remove(signal_number);
}

ASIO_SYNC_OP_VOID signal_set::remove(int signal_number, asio::error_code& ec)
{
    return impl_.remove(signal_number, ec);
}

void signal_set::clear()
{
    return impl_.clear();
}

ASIO_SYNC_OP_VOID signal_set::clear(asio::error_code& ec)
{
    return impl_.clear(ec);
}

void signal_set::cancel()
{
    return impl_.cancel();
}
ASIO_SYNC_OP_VOID signal_set::cancel(asio::error_code& ec)
{
    return impl_.cancel(ec);
}

void signal_set::async_wait_impl(handler_type<void(std::error_code, int)> && h)
{
    impl_.async_wait(std::move(h));
}

}
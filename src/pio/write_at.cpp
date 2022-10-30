//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <asio/write_at.hpp>
#include <pio/write_at.hpp>

namespace pio
{


std::size_t write_at(concepts::sync_random_access_write_device& d,
                     uint64_t offset, const const_buffer & buffers)
{
    return asio::write_at(d, offset, buffers);
}

std::size_t write_at(concepts::sync_random_access_write_device& d,
                     uint64_t offset, const const_buffer & buffers,
                     asio::error_code& ec)
{
    return asio::write_at(d, offset, buffers, ec);
}

std::size_t write_at(concepts::sync_random_access_write_device& d,
                     uint64_t offset, const const_buffer & buffers,
                     completion_condition_t completion_condition)
{
    return asio::write_at(d, offset, buffers, std::move(completion_condition));
}

std::size_t write_at(concepts::sync_random_access_write_device& d,
                     uint64_t offset, const const_buffer & buffers,
                     completion_condition_t completion_condition, asio::error_code& ec)
{
    return asio::write_at(d, offset, buffers, std::move(completion_condition), ec);
}

std::size_t write_at(concepts::sync_random_access_write_device& d,
                     uint64_t offset, asio::streambuf& b)
{
    return asio::write_at(d, offset, b);
}

std::size_t write_at(concepts::sync_random_access_write_device& d,
                     uint64_t offset, asio::streambuf& b,
                     asio::error_code& ec)
{
    return asio::write_at(d, offset, b, ec);
}

std::size_t write_at(concepts::sync_random_access_write_device& d, uint64_t offset,
                     asio::streambuf& b, completion_condition_t completion_condition)
{
    return asio::write_at(d, offset, b, std::move(completion_condition));
}

std::size_t write_at(concepts::sync_random_access_write_device& d, uint64_t offset,
                     asio::streambuf& b, completion_condition_t completion_condition,
                     asio::error_code& ec)
{
    return asio::write_at(d, offset, b, std::move(completion_condition), ec);
}

namespace detail {

void async_write_at_impl(
        concepts::async_random_access_write_device& d, std::uint64_t offset,
        const const_buffer & buffers, handler_type<void(asio::error_code, std::size_t)> && h)
{
    asio::async_write_at(d, offset, buffers, std::move(h));
}


void async_write_at_impl(
        concepts::async_random_access_write_device& d, std::uint64_t offset,
        asio::streambuf& b, handler_type<void(asio::error_code, std::size_t)> && h)
{
    asio::async_write_at(d, offset, b, std::move(h));
}

void async_write_at_impl(
        concepts::async_random_access_write_device& d, std::uint64_t offset,
        asio::streambuf& b, completion_condition_t completion_condition,
        handler_type<void(asio::error_code, std::size_t)> && h)
{
    asio::async_write_at(d, offset, b, std::move(completion_condition), std::move(h));

}

}

}
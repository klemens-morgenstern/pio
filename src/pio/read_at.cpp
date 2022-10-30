//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <asio/read_at.hpp>
#include <pio/read_at.hpp>

namespace pio
{


std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, const mutable_buffer & buffers)
{
    return asio::read_at(d, offset, buffers);
}

std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, const mutable_buffer & buffers,
                     asio::error_code& ec)
{
    return asio::read_at(d, offset, buffers, ec);
}

std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, const mutable_buffer & buffers,
                     completion_condition_t completion_condition)
{
    return asio::read_at(d, offset, buffers, std::move(completion_condition));
}

std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, const mutable_buffer & buffers,
                     completion_condition_t completion_condition, asio::error_code& ec)
{
    return asio::read_at(d, offset, buffers, std::move(completion_condition), ec);
}

std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, asio::streambuf& b)
{
    return asio::read_at(d, offset, b);
}

std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, asio::streambuf& b,
                     asio::error_code& ec)
{
    return asio::read_at(d, offset, b, ec);
}

std::size_t read_at(concepts::sync_random_access_read_device& d, uint64_t offset,
                     asio::streambuf& b, completion_condition_t completion_condition)
{
    return asio::read_at(d, offset, b, std::move(completion_condition));
}

std::size_t read_at(concepts::sync_random_access_read_device& d, uint64_t offset,
                     asio::streambuf& b, completion_condition_t completion_condition,
                     asio::error_code& ec)
{
    return asio::read_at(d, offset, b, std::move(completion_condition), ec);
}

namespace detail {

void async_read_at_impl(
        concepts::async_random_access_read_device& d, std::uint64_t offset,
        const mutable_buffer & buffers, handler_type<void(asio::error_code, std::size_t)> && h)
{
    asio::async_read_at(d, offset, buffers, std::move(h));
}


void async_read_at_impl(
        concepts::async_random_access_read_device& d, std::uint64_t offset,
        asio::streambuf& b, handler_type<void(asio::error_code, std::size_t)> && h)
{
    asio::async_read_at(d, offset, b, std::move(h));
}

void async_read_at_impl(
        concepts::async_random_access_read_device& d, std::uint64_t offset,
        asio::streambuf& b, completion_condition_t completion_condition,
        handler_type<void(asio::error_code, std::size_t)> && h)
{
    asio::async_read_at(d, offset, b, std::move(completion_condition), std::move(h));

}

}

}
//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_READ_AT_HPP
#define PIO_READ_AT_HPP

#include <pio/concepts.hpp>
#include <pio/buffer.hpp>
#include <asio/streambuf.hpp>
#include <functional>

namespace pio
{

using completion_condition_t = std::function<std::size_t(const asio::error_code &error, std::size_t bytes_transferred)>;


std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, const mutable_buffer & buffers);
std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, const mutable_buffer & buffers,
                     asio::error_code& ec);

std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, const mutable_buffer & buffers,
                     completion_condition_t completion_condition);

std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, const mutable_buffer & buffers,
                     completion_condition_t completion_condition, asio::error_code& ec);
std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, asio::streambuf& b);

std::size_t read_at(concepts::sync_random_access_read_device& d,
                     uint64_t offset, asio::streambuf& b,
                     asio::error_code& ec);

std::size_t read_at(concepts::sync_random_access_read_device& d, uint64_t offset,
                     asio::streambuf& b, completion_condition_t completion_condition);

std::size_t read_at(concepts::sync_random_access_read_device& d, uint64_t offset,
                     asio::streambuf& b, completion_condition_t completion_condition,
                     asio::error_code& ec);

namespace detail {

void async_read_at_impl(
        concepts::async_random_access_read_device& d, uint64_t offset,
        const mutable_buffer & buffers, handler_type<void(asio::error_code, std::size_t)> && h);

void async_read_at_impl(
        concepts::async_random_access_read_device& d, uint64_t offset,
        const mutable_buffer & buffers, completion_condition_t completion_condition,
        handler_type<void(asio::error_code, std::size_t)> && h);


void async_read_at_impl(
        concepts::async_random_access_read_device& d, uint64_t offset,
        asio::streambuf&, handler_type<void(asio::error_code, std::size_t)> && h);


void async_read_at_impl(
        concepts::async_random_access_read_device& d, uint64_t offset,
        asio::streambuf& b, completion_condition_t completion_condition,
        handler_type<void(asio::error_code, std::size_t)> && h);
}

template <ASIO_COMPLETION_TOKEN_FOR(void (asio::error_code,
      std::size_t)) WriteToken
        ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename concepts::async_random_access_read_device::executor_type)>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(WriteToken,
    void (asio::error_code, std::size_t))
async_read_at(concepts::async_random_access_read_device& d, uint64_t offset,
    const mutable_buffer & buffers,
    ASIO_MOVE_ARG(WriteToken) token
      ASIO_DEFAULT_COMPLETION_TOKEN(
        typename concepts::async_random_access_read_device::executor_type))
  ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
    async_initiate<WriteToken,
      void (asio::error_code, std::size_t)>(
        declval<detail::initiate_async_read_at<
          concepts::async_random_access_read_device> >(),
        token, offset, buffers, transfer_all())))
{
    return async_initiate<WriteToken, void (asio::error_code, std::size_t)>(
            [](auto handler,
               concepts::async_random_access_read_device& d, uint64_t offset,
               asio::streambuf& b, const mutable_buffer & buffers)
            {
                detail::async_read_at_impl(d, offset, std::move(buffers), handler_type<void(asio::error_code, std::size_t)>(std::move(handler), d.get_executor()));
            }, token,
            d, offset,  std::move(buffers));
}

template <ASIO_COMPLETION_TOKEN_FOR(void (asio::error_code,
      std::size_t)) WriteToken
        ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename concepts::async_random_access_read_device::executor_type)>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(WriteToken,
    void (asio::error_code, std::size_t))
async_read_at(concepts::async_random_access_read_device& d, uint64_t offset,
    const mutable_buffer & buffers,
    completion_condition_t completion_condition,
    ASIO_MOVE_ARG(WriteToken) token
      ASIO_DEFAULT_COMPLETION_TOKEN(
        typename concepts::async_random_access_read_device::executor_type))
  ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
    async_initiate<WriteToken,
      void (asio::error_code, std::size_t)>(
        declval<detail::initiate_async_read_at<
          concepts::async_random_access_read_device> >(),
        token, offset, buffers, transfer_all())))
{
    return async_initiate<WriteToken, void (asio::error_code, std::size_t)>(
            [](auto handler,
               concepts::async_random_access_read_device& d, uint64_t offset,
               asio::streambuf& b, const mutable_buffer & buffers,
               completion_condition_t completion_condition)
            {
                detail::async_read_at_impl(d, offset, std::move(buffers),
                                            std::move(completion_condition), handler_type<void(asio::error_code, std::size_t)>(std::move(handler), d.get_executor()));
            }, token,
            d, offset,  std::move(buffers), std::move(completion_condition));
}


template <ASIO_COMPLETION_TOKEN_FOR(void (asio::error_code,
      std::size_t)) WriteToken
        ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename concepts::async_random_access_read_device::executor_type)>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(WriteToken,
    void (asio::error_code, std::size_t))
async_read_at(concepts::async_random_access_read_device& d,
    uint64_t offset, asio::streambuf& b,
    ASIO_MOVE_ARG(WriteToken) token
      ASIO_DEFAULT_COMPLETION_TOKEN(
        typename concepts::async_random_access_read_device::executor_type))
  ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
    async_initiate<WriteToken,
      void (asio::error_code, std::size_t)>(
        declval<detail::initiate_async_read_at_streambuf<
          concepts::async_random_access_read_device> >(),
        token, offset, &b, transfer_all())))
{
    return async_initiate<WriteToken, void (asio::error_code, std::size_t)>(
            [](auto handler,
               concepts::async_random_access_read_device& d, uint64_t offset,
               asio::streambuf& b)
            {
                detail::async_read_at_impl(d, offset, b, handler_type<void(asio::error_code, std::size_t)>(std::move(handler), d.get_executor()));
            }, token,
            d, offset,  b);
}


template <ASIO_COMPLETION_TOKEN_FOR(void (asio::error_code,
      std::size_t)) WriteToken
        ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename concepts::async_random_access_read_device::executor_type)>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(WriteToken,
    void (asio::error_code, std::size_t))
async_read_at(concepts::async_random_access_read_device& d, uint64_t offset,
    asio::streambuf& b, completion_condition_t completion_condition,
    ASIO_MOVE_ARG(WriteToken) token
      ASIO_DEFAULT_COMPLETION_TOKEN(
        typename concepts::async_random_access_read_device::executor_type))
  ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
    async_initiate<WriteToken,
      void (asio::error_code, std::size_t)>(
        declval<detail::initiate_async_read_at_streambuf<
          concepts::async_random_access_read_device> >(),
        token, offset, &b,
        ASIO_MOVE_CAST(completion_condition_t)(completion_condition))))
{
    return async_initiate<WriteToken, void (asio::error_code, std::size_t)>(
            [](auto handler,
               concepts::async_random_access_read_device& d, uint64_t offset,
               asio::streambuf& b, completion_condition_t completion_condition)
            {
                detail::async_read_at_impl(d, offset, b, std::move(completion_condition), handler_type<void(asio::error_code, std::size_t)>(std::move(handler), d.get_executor()));
            }, token,
            d, offset,  b, std::move(completion_condition));
}

}

#endif //PIO_READ_AT_HPP

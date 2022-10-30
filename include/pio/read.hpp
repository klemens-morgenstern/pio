//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_READ_HPP
#define PIO_READ_HPP

#include <pio/concepts.hpp>
#include <pio/buffer.hpp>
#include <asio/streambuf.hpp>
#include <functional>

namespace pio
{

using completion_condition_t = std::function<std::size_t(const asio::error_code &error, std::size_t bytes_transferred)>;


std::size_t read(concepts::sync_read_stream& s, const asio::mutable_buffer& buffers);
std::size_t read(concepts::sync_read_stream& s, const asio::mutable_buffer& buffers, asio::error_code& ec);


std::size_t read(concepts::sync_read_stream& s, const asio::mutable_buffer& buffers, completion_condition_t completion_condition);
std::size_t read(concepts::sync_read_stream& s, const asio::mutable_buffer& buffers, completion_condition_t completion_condition, asio::error_code& ec);

std::size_t read(concepts::sync_read_stream& s, dynamic_buffer buffers);
std::size_t read(concepts::sync_read_stream& s, dynamic_buffer buffers, asio::error_code& ec);

std::size_t read(concepts::sync_read_stream& s, dynamic_buffer buffers, completion_condition_t completion_condition);
std::size_t read(concepts::sync_read_stream& s, dynamic_buffer buffers, completion_condition_t completion_condition, asio::error_code& ec);


std::size_t read(concepts::sync_read_stream& s, asio::streambuf & buffers);
std::size_t read(concepts::sync_read_stream& s, asio::streambuf & buffers, asio::error_code& ec);

std::size_t read(concepts::sync_read_stream& s, asio::streambuf & buffers, completion_condition_t completion_condition);
std::size_t read(concepts::sync_read_stream& s, asio::streambuf & buffers, completion_condition_t completion_condition, asio::error_code& ec);

namespace detail
{

    void async_read_impl(concepts::async_read_stream& s, const asio::mutable_buffer& buffers,                                              handler_type<void(asio::error_code, std::size_t)> && h);
    void async_read_impl(concepts::async_read_stream& s, const asio::mutable_buffer& buffers, completion_condition_t completion_condition, handler_type<void(asio::error_code, std::size_t)> && h);
    void async_read_impl(concepts::async_read_stream& s, pio::dynamic_buffer buffers,                                              handler_type<void(asio::error_code, std::size_t)> && h);
    void async_read_impl(concepts::async_read_stream& s, pio::dynamic_buffer buffers, completion_condition_t completion_condition, handler_type<void(asio::error_code, std::size_t)> && h);
    void async_read_impl(concepts::async_read_stream& s, asio::streambuf &buffer,                                              handler_type<void(asio::error_code, std::size_t)> && h);
    void async_read_impl(concepts::async_read_stream& s, asio::streambuf &buffer, completion_condition_t completion_condition, handler_type<void(asio::error_code, std::size_t)> && h);

}


template <
        ASIO_COMPLETION_TOKEN_FOR(void (asio::error_code,
                                          std::size_t)) WriteToken
        ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
                typename concepts::async_read_stream::executor_type)>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(WriteToken,
                                    void (asio::error_code, std::size_t))
async_read(concepts::async_read_stream& s, const asio::mutable_buffer& buffers,
            ASIO_MOVE_ARG(WriteToken) token
            ASIO_DEFAULT_COMPLETION_TOKEN(
                    typename concepts::async_read_stream::executor_type))
ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
                                            async_initiate<WriteToken,
                                                    void (asio::error_code, std::size_t)>(
                                                    declval<detail::initiate_async_read<concepts::async_read_stream> >(),
                                                    token, buffers, transfer_all())))
{
    return async_initiate<WriteToken, void (asio::error_code, std::size_t)>(
            [](auto handler, concepts::async_read_stream& d, const asio::mutable_buffer& buffers)
            {
                detail::async_read_impl(d, buffers, handler_type<void(asio::error_code, std::size_t)>(std::move(handler), d.get_executor()));
            }, token, s, buffers);
}

template <
        ASIO_COMPLETION_TOKEN_FOR(void (asio::error_code,
                                          std::size_t)) WriteToken>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(WriteToken,
                                    void (asio::error_code, std::size_t))
async_read(concepts::async_read_stream& s, const asio::mutable_buffer& buffers,
            completion_condition_t completion_condition,
            ASIO_MOVE_ARG(WriteToken) token)
ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
                                            async_initiate<WriteToken,
                                                    void (asio::error_code, std::size_t)>(
                                                    declval<detail::initiate_async_read<concepts::async_read_stream> >(),
                                                    token, buffers,
                                                    ASIO_MOVE_CAST(completion_condition_t)(completion_condition))))
{
    return async_initiate<WriteToken, void (asio::error_code, std::size_t)>(
            [](auto handler,
               concepts::async_read_stream& d,
               const asio::mutable_buffer& buffers, completion_condition_t completion_condition)
            {
                detail::async_read_impl(d, buffers, std::move(completion_condition), handler_type<void(asio::error_code, std::size_t)>(std::move(handler), d.get_executor()));
            }, token, s, buffers, std::move(completion_condition));
}

template <
        ASIO_COMPLETION_TOKEN_FOR(void (asio::error_code,
                                          std::size_t)) WriteToken
        ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
                typename concepts::async_read_stream::executor_type)>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(WriteToken,
                                    void (asio::error_code, std::size_t))
async_read(concepts::async_read_stream& s,
            dynamic_buffer buffers,
            ASIO_MOVE_ARG(WriteToken) token
            ASIO_DEFAULT_COMPLETION_TOKEN(
                    typename concepts::async_read_stream::executor_type))
ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
                                            async_initiate<WriteToken,
                                                    void (asio::error_code, std::size_t)>(
                                                    declval<detail::initiate_async_read_dynbuf_v1<concepts::async_read_stream> >(),
                                                    token, std::declval<dynamic_buffer>(),
                                                    transfer_all())))
{
    return async_initiate<WriteToken, void (asio::error_code, std::size_t)>(
            [](auto handler,
               concepts::async_read_stream& d, dynamic_buffer buffers)
            {
                detail::async_read_impl(d, std::move(buffers), handler_type<void(asio::error_code, std::size_t)>(std::move(handler), d.get_executor()));
            }, token, s, std::move(buffers));
}

template <
        ASIO_COMPLETION_TOKEN_FOR(void (asio::error_code,
                                          std::size_t)) WriteToken>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(WriteToken,
                                    void (asio::error_code, std::size_t))
async_read(concepts::async_read_stream& s,
            dynamic_buffer buffers,
            completion_condition_t completion_condition,
            ASIO_MOVE_ARG(WriteToken) token)
ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
                                            async_initiate<WriteToken,
                                                    void (asio::error_code, std::size_t)>(
                                                    declval<detail::initiate_async_read_dynbuf_v1<concepts::async_read_stream> >(),
                                                    token, std::declval<dynamic_buffer>(),
                                                    ASIO_MOVE_CAST(completion_condition_t)(completion_condition))))
{
    return async_initiate<WriteToken, void (asio::error_code, std::size_t)>(
            [](auto handler,
               concepts::async_read_stream& d,
               dynamic_buffer buffers, completion_condition_t completion_condition)
            {
                detail::async_read_impl(d, std::move(buffers), std::move(completion_condition), handler_type<void(asio::error_code, std::size_t)>(std::move(handler), d.get_executor()));
            }, token, s, std::move(buffers), std::move(completion_condition));
}

template <
        ASIO_COMPLETION_TOKEN_FOR(void (asio::error_code,
                                          std::size_t)) WriteToken
        ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
                typename concepts::async_read_stream::executor_type)>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(WriteToken,
                                    void (asio::error_code, std::size_t))
async_read(concepts::async_read_stream& s, asio::streambuf& b,
            ASIO_MOVE_ARG(WriteToken) token
            ASIO_DEFAULT_COMPLETION_TOKEN(
                    typename concepts::async_read_stream::executor_type))
ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
                                            async_read(s, basic_streambuf_ref<Allocator>(b),
                                                        ASIO_MOVE_CAST(WriteToken)(token))))
{
    return async_initiate<WriteToken, void (asio::error_code, std::size_t)>(
            [](auto handler,
               concepts::async_read_stream& d, asio::streambuf& b)
            {
                detail::async_read_impl(d, b, handler_type<void(asio::error_code, std::size_t)>(std::move(handler), d.get_executor()));
            }, token, s, b);
}

template <
        typename Allocator, typename completion_condition_t,
        ASIO_COMPLETION_TOKEN_FOR(void (asio::error_code,
                                          std::size_t)) WriteToken>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(WriteToken,
                                    void (asio::error_code, std::size_t))
async_read(concepts::async_read_stream& s, asio::streambuf& b,
            completion_condition_t completion_condition,
            ASIO_MOVE_ARG(WriteToken) token)
ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
                                            async_read(s, basic_streambuf_ref<Allocator>(b),
                                                        ASIO_MOVE_CAST(completion_condition_t)(completion_condition),
                                                        ASIO_MOVE_CAST(WriteToken)(token))))
{
    return async_initiate<WriteToken, void (asio::error_code, std::size_t)>(
            [](auto handler,
               concepts::async_read_stream& d,
               asio::streambuf& b, completion_condition_t completion_condition)
            {
                detail::async_read_impl(d, b, std::move(completion_condition), handler_type<void(asio::error_code, std::size_t)>(std::move(handler), d.get_executor()));
            }, token, s, b, std::move(completion_condition));
}

}

#endif //PIO_READ_HPP

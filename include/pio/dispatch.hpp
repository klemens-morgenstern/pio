//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_DISPATCH_HPP
#define PIO_DISPATCH_HPP

#include <asio/dispatch.hpp>
#include "handler.hpp"

namespace pio
{

namespace detail
{
void dispatch_impl(asio::any_io_executor, handler_type<void()> &&h);
void dispatch_impl(handler_type<void()> &&h);
}

template <ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(NullaryToken, void()) dispatch(
    ASIO_MOVE_ARG(NullaryToken) token)
  ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
    async_initiate<NullaryToken, void()>(
        declval<detail::initiate_dispatch>(), token)))
{
    return asio::async_initiate<NullaryToken, void()>(
            [](auto handler)
            {
                asio::dispatch(std::move(handler));
            }, token);
}


template <typename Executor,
    ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken
      ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(NullaryToken, void()) dispatch(
    const Executor& ex,
    ASIO_MOVE_ARG(NullaryToken) token
      ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename asio::constraint<
      asio::execution::is_executor<Executor>::value || asio::is_executor<Executor>::value
    >::type = 0)
  ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
    async_initiate<NullaryToken, void()>(
        declval<detail::initiate_dispatch_with_executor<Executor> >(), token)))
{
    return asio::async_initiate<NullaryToken, void()>(
            [](auto handler, auto exec)
            {
                asio::dispatch(exec, std::move(handler));
            }, token, ex);
}


template <typename ExecutionContext,
    ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken
      ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
        typename ExecutionContext::executor_type)>
ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(NullaryToken, void()) dispatch(
    ExecutionContext& ctx,
    ASIO_MOVE_ARG(NullaryToken) token
      ASIO_DEFAULT_COMPLETION_TOKEN(
        typename ExecutionContext::executor_type),
    typename asio::constraint<asio::is_convertible<
      ExecutionContext&, asio::execution_context&>::value>::type = 0)
  ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
    async_initiate<NullaryToken, void()>(
        declval<detail::initiate_dispatch_with_executor<
          typename ExecutionContext::executor_type> >(), token)))
{
    return asio::async_initiate<NullaryToken, void()>(
            [](auto handler, auto exec)
            {
                asio::dispatch(exec, std::move(handler));
            }, token, ctx.get_executor());
}
}

#endif //PIO_DISPATCH_HPP

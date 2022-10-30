//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_READABLE_PIPE_HPP
#define PIO_READABLE_PIPE_HPP

#include <asio/readable_pipe.hpp>
#include <pio/buffer.hpp>
#include <pio/concepts.hpp>

namespace pio
{

struct readable_pipe final :
        concepts::implements<
                concepts::sync_read_stream,
                concepts::async_read_stream,
                concepts::cancellable,
                concepts::closable>
{
  typedef asio::any_io_executor executor_type;
  typedef typename asio::readable_pipe::native_handle_type native_handle_type;
  explicit readable_pipe(const executor_type& ex);

  template <typename ExecutionContext>
  explicit readable_pipe(ExecutionContext& context,
      typename asio::constraint<
        asio::is_convertible<ExecutionContext&, asio::execution_context&>::value,
        asio::defaulted_constraint
      >::type = asio::defaulted_constraint())
    : readable_pipe(context.get_executor())
  {
  }


  readable_pipe(const executor_type& ex, const native_handle_type& native_file);

  template <typename ExecutionContext>
  readable_pipe(ExecutionContext& context,
      const native_handle_type& native_file,
      typename asio::constraint<
        asio::is_convertible<ExecutionContext&, execution_context&>::value,
        asio::defaulted_constraint
      >::type = asio::defaulted_constraint())
    : readable_pipe(context, native_file) {}

  readable_pipe(readable_pipe&& other) noexcept;
  readable_pipe& operator=(readable_pipe&& other) noexcept;
  ~readable_pipe();

  std::size_t read_some(const mutable_buffer & buffers) override;
  std::size_t read_some(const mutable_buffer & buffers, asio::error_code& ec) override;
  executor_type get_executor();

  bool is_open() const override;
  void close() override;
  ASIO_SYNC_OP_VOID close(asio::error_code& ec) override;

  void cancel() override;
  ASIO_SYNC_OP_VOID cancel(asio::error_code& ec) override;

   using lowest_layer_type = asio::readable_pipe;
  lowest_layer_type& lowest_layer() { return impl_; }
  const lowest_layer_type& lowest_layer() const { return impl_; }

               void assign(const native_handle_type& native_pipe);
  ASIO_SYNC_OP_VOID assign(const native_handle_type& native_pipe, asio::error_code &);

  native_handle_type native_handle();

  native_handle_type release();
  native_handle_type release(asio::error_code & ec);
private:
  void async_read_some_impl(const asio::mutable_buffer &buffer, handler_type<void(std::error_code, std::size_t)> && h) override;
  asio::readable_pipe impl_;
};

}

#endif //PIO_READABLE_PIPE_HPP

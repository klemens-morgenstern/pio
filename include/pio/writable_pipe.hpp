//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_WRITABLE_PIPE_HPP
#define PIO_WRITABLE_PIPE_HPP


#include <asio/writable_pipe.hpp>
#include <pio/buffer.hpp>
#include <pio/concepts.hpp>

namespace pio
{
struct writable_pipe final :
        concepts::implements<
                concepts::sync_write_stream,
                concepts::async_write_stream,
                concepts::cancellable,
                concepts::closable>
{
  typedef asio::any_io_executor executor_type;
  typedef typename asio::writable_pipe::native_handle_type native_handle_type;
  explicit writable_pipe(const executor_type& ex);

  template <typename ExecutionContext>
  explicit writable_pipe(ExecutionContext& context,
      typename asio::constraint<
        asio::is_convertible<ExecutionContext&, asio::execution_context&>::value,
        asio::defaulted_constraint
      >::type = asio::defaulted_constraint())
    : writable_pipe(context.get_executor())
  {
  }

  writable_pipe(const executor_type& ex, const native_handle_type& native_file);

  template <typename ExecutionContext>
  writable_pipe(ExecutionContext& context,
      const native_handle_type& native_file,
      typename asio::constraint<
        asio::is_convertible<ExecutionContext&, execution_context&>::value,
        asio::defaulted_constraint
      >::type = asio::defaulted_constraint())
    : writable_pipe(context, native_file) {}

  writable_pipe(writable_pipe&& other) noexcept;
  writable_pipe& operator=(writable_pipe&& other) noexcept;
  ~writable_pipe();

  std::size_t write_some(const const_buffer & buffers) override;
  std::size_t write_some(const const_buffer & buffers, asio::error_code& ec) override;

  executor_type get_executor();

  using lowest_layer_type = asio::writable_pipe;
  lowest_layer_type& lowest_layer() { return impl_; }
  const lowest_layer_type& lowest_layer() const { return impl_; }

  void assign(const native_handle_type& native_pipe);
  ASIO_SYNC_OP_VOID assign(const native_handle_type& native_pipe, asio::error_code &);
  bool is_open() const override;
  void close() override;
  ASIO_SYNC_OP_VOID close(asio::error_code& ec) override;

  void cancel() override;
  ASIO_SYNC_OP_VOID cancel(asio::error_code& ec) override;


  native_handle_type release();
  native_handle_type release(asio::error_code& ec);
  native_handle_type native_handle();

private:
  void async_write_some_impl(asio::const_buffer buffer, handler_type<void(std::error_code, std::size_t)> && h) override;
  asio::writable_pipe impl_;
};

}

#endif //PIO_WRITABLE_PIPE_HPP

//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_STREAM_FILE_HPP
#define PIO_STREAM_FILE_HPP

#include <asio/stream_file.hpp>
#include <pio/buffer.hpp>
#include <pio/concepts.hpp>

namespace pio
{

struct stream_file final :
        concepts::implements<
                concepts::sync_read_stream,
                concepts::sync_write_stream,
                concepts::async_read_stream,
                concepts::async_write_stream,
                concepts::cancellable,
                concepts::closable>,
        asio::file_base
{
  typedef asio::any_io_executor executor_type;
  typedef typename asio::stream_file::native_handle_type native_handle_type;
  explicit stream_file(const executor_type& ex);

  template <typename ExecutionContext>
  explicit stream_file(ExecutionContext& context,
      typename asio::constraint<
        asio::is_convertible<ExecutionContext&, asio::execution_context&>::value,
        asio::defaulted_constraint
      >::type = asio::defaulted_constraint())
    : stream_file(context.get_executor())
  {
  }

  stream_file(const executor_type& ex, const char* path, file_base::flags open_flags);
  template <typename ExecutionContext>
  stream_file(ExecutionContext& context,
      const char* path, file_base::flags open_flags,
      typename asio::constraint<
        asio::is_convertible<ExecutionContext&, asio::execution_context&>::value,
        asio::defaulted_constraint
      >::type = asio::defaulted_constraint())
    : stream_file(context, open_flags)
  {}

  stream_file(const executor_type& ex, const std::string& path, file_base::flags open_flags);
    template <typename ExecutionContext>
  stream_file(ExecutionContext& context,
      const std::string& path, file_base::flags open_flags,
      typename asio::constraint<
        asio::is_convertible<ExecutionContext&, execution_context&>::value,
        asio::defaulted_constraint
      >::type = asio::defaulted_constraint())
    : stream_file(context.get_executor(), path, open_flags)
    {}

  stream_file(const executor_type& ex, const native_handle_type& native_file);

  template <typename ExecutionContext>
  stream_file(ExecutionContext& context,
      const native_handle_type& native_file,
      typename asio::constraint<
        asio::is_convertible<ExecutionContext&, execution_context&>::value,
        asio::defaulted_constraint
      >::type = asio::defaulted_constraint())
    : stream_file(context, native_file) {}

  stream_file(stream_file&& other) noexcept;
  stream_file& operator=(stream_file&& other) noexcept;
  ~stream_file();

  uint64_t seek(int64_t offset, file_base::seek_basis whence);
  uint64_t seek(int64_t offset, file_base::seek_basis whence, asio::error_code& ec);

  std::size_t write_some(const const_buffer & buffers) override;
  std::size_t write_some(const const_buffer & buffers, asio::error_code& ec) override;

  std::size_t read_some(const mutable_buffer & buffers) override;
  std::size_t read_some(const mutable_buffer & buffers, asio::error_code& ec) override;
  executor_type get_executor();

  bool is_open() const override;
  void close() override;
  ASIO_SYNC_OP_VOID close(asio::error_code& ec) override;

  void cancel() override;
  ASIO_SYNC_OP_VOID cancel(asio::error_code& ec) override;

               void assign(const native_handle_type& native_pipe);
  ASIO_SYNC_OP_VOID assign(const native_handle_type& native_pipe, asio::error_code &);

  native_handle_type native_handle();

  native_handle_type release();
  native_handle_type release(asio::error_code & ec);
private:
  void async_read_some_impl(const asio::mutable_buffer &buffer, handler_type<void(std::error_code, std::size_t)> && h) override;
  void async_write_some_impl(asio::const_buffer buffer, handler_type<void(std::error_code, std::size_t)> && h) override;
  asio::stream_file impl_;
};

}

#endif //PIO_STREAM_FILE_HPP

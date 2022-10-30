//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/readable_pipe.hpp>

namespace pio
{

readable_pipe::readable_pipe(const executor_type& ex)                                        : impl_(ex) {}
readable_pipe::readable_pipe(const executor_type& ex, const native_handle_type& native_file) : impl_(ex, native_file) {}

readable_pipe::readable_pipe(readable_pipe&& other) noexcept = default;
readable_pipe& readable_pipe::operator=(readable_pipe&& other) noexcept = default;
readable_pipe::~readable_pipe() = default;


std::size_t readable_pipe::read_some(const mutable_buffer & buffers) {return impl_.read_some(buffers);}
std::size_t readable_pipe::read_some(const mutable_buffer & buffers, asio::error_code& ec) {return impl_.read_some(buffers, ec);}
void readable_pipe::async_read_some_impl(const asio::mutable_buffer &buffer, handler_type<void(std::error_code, std::size_t)> && h) {return impl_.async_read_some(buffer, std::move(h));}

auto readable_pipe::get_executor() -> executor_type {return impl_.get_executor();}

bool readable_pipe::is_open() const {return impl_.is_open();}
void              readable_pipe::close()                     {return impl_.close();}
ASIO_SYNC_OP_VOID readable_pipe::close(asio::error_code& ec) {return impl_.close(ec);}

void              readable_pipe::cancel()                     {return impl_.cancel();}
ASIO_SYNC_OP_VOID readable_pipe::cancel(asio::error_code& ec) {return impl_.cancel(ec);}

void readable_pipe::assign(const native_handle_type& native_handle)                        {return impl_.assign(native_handle);}
ASIO_SYNC_OP_VOID readable_pipe::assign(const native_handle_type& native_handle, asio::error_code & ec) {return impl_.assign(native_handle, ec);}

auto readable_pipe::native_handle() -> native_handle_type { return impl_.native_handle();};

auto readable_pipe::release()                      -> native_handle_type {return impl_.release();}
auto readable_pipe::release(asio::error_code & ec) -> native_handle_type {return impl_.release(ec);}

}

//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/writable_pipe.hpp>

namespace pio
{

writable_pipe::writable_pipe(const executor_type& ex)                                        : impl_(ex) {}
writable_pipe::writable_pipe(const executor_type& ex, const native_handle_type& native_file) : impl_(ex, native_file) {}

writable_pipe::writable_pipe(writable_pipe&& other) noexcept = default;
writable_pipe& writable_pipe::operator=(writable_pipe&& other) noexcept = default;
writable_pipe::~writable_pipe()= default;

std::size_t writable_pipe::write_some(const const_buffer & buffers) {return impl_.write_some(buffers);}
std::size_t writable_pipe::write_some(const const_buffer & buffers, asio::error_code& ec) {return impl_.write_some(buffers, ec);}
void writable_pipe::async_write_some_impl(asio::const_buffer buffer, handler_type<void(std::error_code, std::size_t)> && h) {return impl_.async_write_some(buffer, std::move(h));}

auto writable_pipe::get_executor() -> executor_type {return impl_.get_executor();}

bool writable_pipe::is_open() const {return impl_.is_open();}
void              writable_pipe::close()                     {return impl_.close();}
ASIO_SYNC_OP_VOID writable_pipe::close(asio::error_code& ec) {return impl_.close(ec);}

void              writable_pipe::cancel()                     {return impl_.cancel();}
ASIO_SYNC_OP_VOID writable_pipe::cancel(asio::error_code& ec) {return impl_.cancel(ec);}

void writable_pipe::assign(const native_handle_type& native_handle)                        {return impl_.assign(native_handle);}
ASIO_SYNC_OP_VOID writable_pipe::assign(const native_handle_type& native_handle, asio::error_code & ec) {return impl_.assign(native_handle, ec);}

auto writable_pipe::native_handle() -> native_handle_type {return impl_.native_handle();}

auto writable_pipe::release()                      -> native_handle_type {return impl_.release();}
auto writable_pipe::release(asio::error_code & ec) -> native_handle_type {return impl_.release(ec);}

}
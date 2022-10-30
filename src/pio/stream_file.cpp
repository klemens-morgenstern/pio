//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/stream_file.hpp>

namespace pio
{

stream_file::stream_file(const executor_type& ex)
    : impl_(ex) {}
stream_file::stream_file(const executor_type& ex, const char* path, file_base::flags open_flags)
    : impl_(ex, path, open_flags) {}
stream_file::stream_file(const executor_type& ex, const std::string& path, file_base::flags open_flags)
    : impl_(ex, path, open_flags) {}
stream_file::stream_file(const executor_type& ex, const native_handle_type& native_file)
    : impl_(ex, native_file) {}

stream_file::stream_file(stream_file&& other) noexcept = default;
stream_file& stream_file::operator=(stream_file&& other) noexcept = default;
stream_file::~stream_file()= default;

uint64_t stream_file::seek(int64_t offset, file_base::seek_basis whence)
{
    return impl_.seek(offset, whence);
}
uint64_t stream_file::seek(int64_t offset, file_base::seek_basis whence, asio::error_code& ec)
{
    return impl_.seek(offset, whence);
}

std::size_t stream_file::write_some(const const_buffer & buffers) {return impl_.write_some(buffers);}
std::size_t stream_file::write_some(const const_buffer & buffers, asio::error_code& ec) {return impl_.write_some(buffers, ec);}
std::size_t stream_file::read_some(const mutable_buffer & buffers) {return impl_.read_some(buffers);}
std::size_t stream_file::read_some(const mutable_buffer & buffers, asio::error_code& ec) {return impl_.read_some(buffers, ec);}
void stream_file::async_read_some_impl(const asio::mutable_buffer &buffer, handler_type<void(std::error_code, std::size_t)> && h) {return impl_.async_read_some(buffer, std::move(h));}
void stream_file::async_write_some_impl(asio::const_buffer buffer, handler_type<void(std::error_code, std::size_t)> && h) {return impl_.async_write_some(buffer, std::move(h));}

auto stream_file::get_executor() -> executor_type {return impl_.get_executor();}

bool stream_file::is_open() const {return impl_.is_open();}
void              stream_file::close()                     {return impl_.close();}
ASIO_SYNC_OP_VOID stream_file::close(asio::error_code& ec) {return impl_.close(ec);}

void              stream_file::cancel()                     {return impl_.cancel();}
ASIO_SYNC_OP_VOID stream_file::cancel(asio::error_code& ec) {return impl_.cancel(ec);}

             void stream_file::assign(const native_handle_type& native_handle)                        {return impl_.assign(native_handle);}
ASIO_SYNC_OP_VOID stream_file::assign(const native_handle_type& native_handle, asio::error_code & ec) {return impl_.assign(native_handle, ec);}

auto stream_file::native_handle() -> native_handle_type {return impl_.native_handle();};

auto stream_file::release()                      -> native_handle_type {return impl_.release();}
auto stream_file::release(asio::error_code & ec) -> native_handle_type {return impl_.release(ec);}

}

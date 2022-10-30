//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/random_access_file.hpp>

namespace pio
{

random_access_file::random_access_file(const executor_type& ex) : impl_(ex) {}
random_access_file::random_access_file(const executor_type& ex, const char* path, file_base::flags open_flags) : impl_(ex, path, open_flags) {}
random_access_file::random_access_file(const executor_type& ex, const std::string& path, file_base::flags open_flags) : impl_(ex, path, open_flags) {}
random_access_file::random_access_file(const executor_type& ex, const native_handle_type& native_file) : impl_(ex, native_file) {}
random_access_file::random_access_file(random_access_file&& other) noexcept  = default;
random_access_file& random_access_file::operator=(random_access_file&& other) noexcept  = default;
random_access_file::~random_access_file() = default;

std::size_t random_access_file::write_some_at(std::uint64_t offset, const const_buffer & buffers) {return impl_.write_some_at(offset, buffers);};
std::size_t random_access_file::write_some_at(std::uint64_t offset, const const_buffer & buffers, asio::error_code& ec) {return impl_.write_some_at(offset, buffers, ec);};
std::size_t random_access_file::read_some_at(std::uint64_t offset, const mutable_buffer & buffers) {return impl_.read_some_at(offset, buffers);};
std::size_t random_access_file::read_some_at(std::uint64_t offset, const mutable_buffer & buffers, asio::error_code& ec) {return impl_.read_some_at(offset, buffers, ec);};
void random_access_file::async_read_some_at_impl (std::uint64_t offset, mutable_buffer buffer, handler_type<void(std::error_code, std::size_t)> && h) { return impl_.async_read_some_at(offset, buffer, std::move(h)); }
void random_access_file::async_write_some_at_impl(std::uint64_t offset,   const_buffer buffer, handler_type<void(std::error_code, std::size_t)> && h) { return impl_.async_write_some_at(offset, buffer, std::move(h)); }

auto random_access_file::get_executor() -> executor_type {return impl_.get_executor();}

bool random_access_file::is_open() const {return impl_.is_open();}
void              random_access_file::close()                     {return impl_.close();}
ASIO_SYNC_OP_VOID random_access_file::close(asio::error_code& ec) {return impl_.close(ec);}

void              random_access_file::cancel()                     {return impl_.cancel();}
ASIO_SYNC_OP_VOID random_access_file::cancel(asio::error_code& ec) {return impl_.cancel(ec);}

             void random_access_file::assign(const native_handle_type& native_handle)                        {return impl_.assign(native_handle);}
ASIO_SYNC_OP_VOID random_access_file::assign(const native_handle_type& native_handle, asio::error_code & ec) {return impl_.assign(native_handle, ec);}

auto random_access_file::native_handle() -> native_handle_type {return impl_.native_handle();};

auto random_access_file::release()                      -> native_handle_type {return impl_.release();}   
auto random_access_file::release(asio::error_code & ec) -> native_handle_type {return impl_.release(ec);}                           

}

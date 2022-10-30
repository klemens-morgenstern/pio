//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/serial_port.hpp>

namespace pio
{
serial_port::serial_port(const executor_type& ex, const char* device) : impl_(ex, device) {}
serial_port::serial_port(const executor_type& ex, const std::string& device) : impl_(ex, device) {}
serial_port::serial_port(const executor_type& ex, const native_handle_type& native_serial_port) : impl_(ex, native_serial_port) {}

serial_port::serial_port(serial_port&& other) = default;
serial_port& serial_port::operator=(serial_port&& other) = default;
serial_port::~serial_port() = default;

auto serial_port::get_executor() noexcept -> executor_type  { return impl_.get_executor();}

void serial_port::open(const std::string& device) { return impl_.open(device); }
ASIO_SYNC_OP_VOID serial_port::open(const std::string& device, asio::error_code& ec) {return impl_.open(device, ec);}
void serial_port::assign(const native_handle_type& native_serial_port) {return impl_.assign(native_serial_port);}
ASIO_SYNC_OP_VOID serial_port::assign(const native_handle_type& native_serial_port, asio::error_code& ec) {return impl_.assign(native_serial_port, ec);}

bool serial_port::is_open() const { return impl_.is_open(); }
void              serial_port::close()                     { return impl_.close(); }
ASIO_SYNC_OP_VOID serial_port::close(asio::error_code& ec) { return impl_.close(ec); }
auto serial_port::native_handle() -> native_handle_type { return impl_.native_handle(); }
void              serial_port::cancel()                     { return impl_.cancel(); }
ASIO_SYNC_OP_VOID serial_port::cancel(asio::error_code& ec) { return impl_.cancel(ec); }
void              serial_port::send_break()                     { return impl_.send_break(); }
ASIO_SYNC_OP_VOID serial_port::send_break(asio::error_code& ec) { return impl_.send_break(ec); }

void serial_port::set_option(const baud_rate& option     ) { impl_.set_option(option);}
void serial_port::set_option(const flow_control& option  ) { impl_.set_option(option);}
void serial_port::set_option(const parity& option        ) { impl_.set_option(option);}
void serial_port::set_option(const stop_bits& option     ) { impl_.set_option(option);}
void serial_port::set_option(const character_size& option) { impl_.set_option(option);}

ASIO_SYNC_OP_VOID serial_port::set_option(const baud_rate& option,      asio::error_code& ec) {return impl_.set_option(option, ec);}
ASIO_SYNC_OP_VOID serial_port::set_option(const flow_control& option,   asio::error_code& ec) {return impl_.set_option(option, ec);}
ASIO_SYNC_OP_VOID serial_port::set_option(const parity& option,         asio::error_code& ec) {return impl_.set_option(option, ec);}
ASIO_SYNC_OP_VOID serial_port::set_option(const stop_bits& option,      asio::error_code& ec) {return impl_.set_option(option, ec);}
ASIO_SYNC_OP_VOID serial_port::set_option(const character_size& option, asio::error_code& ec) {return impl_.set_option(option, ec);}


void serial_port::get_option(baud_rate& option     ) const {return impl_.get_option(option);}
void serial_port::get_option(flow_control& option  ) const {return impl_.get_option(option);}
void serial_port::get_option(parity& option        ) const {return impl_.get_option(option);}
void serial_port::get_option(stop_bits& option     ) const {return impl_.get_option(option);}
void serial_port::get_option(character_size& option) const {return impl_.get_option(option);}

ASIO_SYNC_OP_VOID serial_port::get_option(baud_rate& option,      asio::error_code& ec) const {return impl_.get_option(option, ec);}
ASIO_SYNC_OP_VOID serial_port::get_option(flow_control& option,   asio::error_code& ec) const {return impl_.get_option(option, ec);}
ASIO_SYNC_OP_VOID serial_port::get_option(parity& option,         asio::error_code& ec) const {return impl_.get_option(option, ec);}
ASIO_SYNC_OP_VOID serial_port::get_option(stop_bits& option,      asio::error_code& ec) const {return impl_.get_option(option, ec);}
ASIO_SYNC_OP_VOID serial_port::get_option(character_size& option, asio::error_code& ec) const {return impl_.get_option(option, ec);}

std::size_t serial_port::write_some(const const_buffer& buffers) {return impl_.write_some(buffers);}
std::size_t serial_port::write_some(const const_buffer& buffers, asio::error_code& ec) {return impl_.write_some(buffers, ec);}
std::size_t serial_port::read_some(const mutable_buffer& buffers) {return impl_.read_some(buffers);}
std::size_t serial_port::read_some(const mutable_buffer& buffers, asio::error_code& ec) {return impl_.read_some(buffers, ec);}

void serial_port::async_read_some_impl(const asio::mutable_buffer &buffer, handler_type<void(std::error_code, std::size_t)> && h)
{
    return impl_.async_read_some(buffer, std::move(h));
}
void serial_port::async_write_some_impl(asio::const_buffer buffer, handler_type<void(std::error_code, std::size_t)> && h)
{
    return impl_.async_write_some(buffer, std::move(h));
}

}
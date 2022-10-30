//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <asio/write.hpp>
#include <pio/write.hpp>

namespace pio
{

std::size_t write(concepts::sync_write_stream& s, const asio::const_buffer& buffers)                                                                     {return asio::write(s, buffers);}
std::size_t write(concepts::sync_write_stream& s, const asio::const_buffer& buffers, asio::error_code& ec)                                               {return asio::write(s, buffers, ec);}
std::size_t write(concepts::sync_write_stream& s, const asio::const_buffer& buffers, completion_condition_t completion_condition)                        {return asio::write(s, buffers, std::move(completion_condition));}
std::size_t write(concepts::sync_write_stream& s, const asio::const_buffer& buffers, completion_condition_t completion_condition, asio::error_code& ec)  {return asio::write(s, buffers, std::move(completion_condition), ec);}
std::size_t write(concepts::sync_write_stream& s, dynamic_buffer buffers)                                                                                {return asio::write(s, std::move(buffers));}
std::size_t write(concepts::sync_write_stream& s, dynamic_buffer buffers, asio::error_code& ec)                                                          {return asio::write(s, std::move(buffers), ec);}
std::size_t write(concepts::sync_write_stream& s, dynamic_buffer buffers, completion_condition_t completion_condition)                                   {return asio::write(s, std::move(buffers), std::move(completion_condition));}
std::size_t write(concepts::sync_write_stream& s, dynamic_buffer buffers, completion_condition_t completion_condition, asio::error_code& ec)             {return asio::write(s, std::move(buffers), std::move(completion_condition), ec);}
std::size_t write(concepts::sync_write_stream& s, asio::streambuf & buffers)                                                                             {return asio::write(s, buffers);}
std::size_t write(concepts::sync_write_stream& s, asio::streambuf & buffers, asio::error_code& ec)                                                       {return asio::write(s, buffers, ec);}
std::size_t write(concepts::sync_write_stream& s, asio::streambuf & buffers, completion_condition_t completion_condition)                                {return asio::write(s, buffers, std::move(completion_condition));}
std::size_t write(concepts::sync_write_stream& s, asio::streambuf & buffers, completion_condition_t completion_condition, asio::error_code& ec)          {return asio::write(s, buffers, std::move(completion_condition), ec);}

namespace detail
{
void async_write_impl(concepts::async_write_stream& s, const asio::const_buffer& buffers,                                              handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_write(s, buffers,                                  std::move(h));}
void async_write_impl(concepts::async_write_stream& s, const asio::const_buffer& buffers, completion_condition_t completion_condition, handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_write(s, buffers, std::move(completion_condition), std::move(h));}
void async_write_impl(concepts::async_write_stream& s, pio::dynamic_buffer buffers,                                                    handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_write(s, std::move(buffers),                                  std::move(h));}
void async_write_impl(concepts::async_write_stream& s, pio::dynamic_buffer buffers,       completion_condition_t completion_condition, handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_write(s, std::move(buffers), std::move(completion_condition), std::move(h));}
void async_write_impl(concepts::async_write_stream& s, asio::streambuf &buffers,                                                       handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_write(s, buffers,                                  std::move(h));}
void async_write_impl(concepts::async_write_stream& s, asio::streambuf &buffers,          completion_condition_t completion_condition, handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_write(s, buffers, std::move(completion_condition), std::move(h));}

}

}
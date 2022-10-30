//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <asio/read.hpp>
#include <pio/read.hpp>

namespace pio
{

    std::size_t read(concepts::sync_read_stream& s, const asio::mutable_buffer& buffers)                                                                     {return asio::read(s, buffers);}
    std::size_t read(concepts::sync_read_stream& s, const asio::mutable_buffer& buffers, asio::error_code& ec)                                               {return asio::read(s, buffers, ec);}
    std::size_t read(concepts::sync_read_stream& s, const asio::mutable_buffer& buffers, completion_condition_t completion_condition)                        {return asio::read(s, buffers, std::move(completion_condition));}
    std::size_t read(concepts::sync_read_stream& s, const asio::mutable_buffer& buffers, completion_condition_t completion_condition, asio::error_code& ec)  {return asio::read(s, buffers, std::move(completion_condition), ec);}
    std::size_t read(concepts::sync_read_stream& s, dynamic_buffer buffers)                                                                                {return asio::read(s, std::move(buffers));}
    std::size_t read(concepts::sync_read_stream& s, dynamic_buffer buffers, asio::error_code& ec)                                                          {return asio::read(s, std::move(buffers), ec);}
    std::size_t read(concepts::sync_read_stream& s, dynamic_buffer buffers, completion_condition_t completion_condition)                                   {return asio::read(s, std::move(buffers), std::move(completion_condition));}
    std::size_t read(concepts::sync_read_stream& s, dynamic_buffer buffers, completion_condition_t completion_condition, asio::error_code& ec)             {return asio::read(s, std::move(buffers), std::move(completion_condition), ec);}
    std::size_t read(concepts::sync_read_stream& s, asio::streambuf & buffers)                                                                             {return asio::read(s, buffers);}
    std::size_t read(concepts::sync_read_stream& s, asio::streambuf & buffers, asio::error_code& ec)                                                       {return asio::read(s, buffers, ec);}
    std::size_t read(concepts::sync_read_stream& s, asio::streambuf & buffers, completion_condition_t completion_condition)                                {return asio::read(s, buffers, std::move(completion_condition));}
    std::size_t read(concepts::sync_read_stream& s, asio::streambuf & buffers, completion_condition_t completion_condition, asio::error_code& ec)          {return asio::read(s, buffers, std::move(completion_condition), ec);}

    namespace detail
    {
        void async_read_impl(concepts::async_read_stream& s, const asio::mutable_buffer& buffers,                                              handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_read(s, buffers,                                  std::move(h));}
        void async_read_impl(concepts::async_read_stream& s, const asio::mutable_buffer& buffers, completion_condition_t completion_condition, handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_read(s, buffers, std::move(completion_condition), std::move(h));}
        void async_read_impl(concepts::async_read_stream& s, pio::dynamic_buffer buffers,                                                    handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_read(s, std::move(buffers),                                  std::move(h));}
        void async_read_impl(concepts::async_read_stream& s, pio::dynamic_buffer buffers,       completion_condition_t completion_condition, handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_read(s, std::move(buffers), std::move(completion_condition), std::move(h));}
        void async_read_impl(concepts::async_read_stream& s, asio::streambuf &buffers,                                                       handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_read(s, buffers,                                  std::move(h));}
        void async_read_impl(concepts::async_read_stream& s, asio::streambuf &buffers,          completion_condition_t completion_condition, handler_type<void(asio::error_code, std::size_t)> && h) {asio::async_read(s, buffers, std::move(completion_condition), std::move(h));}

    }

}
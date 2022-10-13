//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TE_ASIO_CONCEPTS_HPP
#define TE_ASIO_CONCEPTS_HPP

#include <boost/asio/any_io_executor.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/buffer.hpp>

#include <handler.hpp>

namespace te
{

struct closable
{
    virtual void close() = 0;
    virtual void close(boost::system::error_code & ec) = 0;
};

struct executor_base
{
    using executor_type = boost::asio::any_io_executor;
    virtual executor_type get_executor() = 0;
};

struct async_read_stream : virtual executor_base
{

    template<typename CompletionHandler>
    BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionHandler, void(boost::system::error_code, std::size_t))
    async_read_some(boost::asio::mutable_buffer buffer, CompletionHandler && token)
    {
        return boost::asio::async_initiate<CompletionHandler, void(boost::system::error_code, std::size_t)>(
                [this](auto handler, boost::asio::mutable_buffer buffer)
                {
                    this->async_read_some_impl(buffer,
                                               handler_type<void(boost::system::error_code, std::size_t)>(std::move(handler), this->get_executor()));
                },
                token, buffer);
    }

    virtual void async_read_some_impl(boost::asio::mutable_buffer buffer, handler_type<void(boost::system::error_code, std::size_t)> && h) = 0;
};

struct async_write_stream : virtual executor_base
{
    template<typename CompletionHandler>
    BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionHandler, void(boost::system::error_code, std::size_t))
    async_write_some(boost::asio::const_buffer buffer, CompletionHandler && token)
    {
        return boost::asio::async_initiate<CompletionHandler, void(boost::system::error_code, std::size_t)>(
                [this](auto handler, boost::asio::const_buffer buffer)
                {
                    this->async_write_some_impl(buffer,
                                                handler_type<void(boost::system::error_code, std::size_t)>(std::move(handler), this->get_executor()));
                },
                token, buffer);
    }

    virtual void async_write_some_impl(boost::asio::const_buffer buffer,
                                       handler_type<void(boost::system::error_code, std::size_t)> && h) = 0;
};

struct sync_read_stream : virtual executor_base
{
    virtual std::size_t read_some(boost::asio::mutable_buffer buffer) = 0;
    virtual std::size_t read_some(boost::asio::mutable_buffer buffer, boost::system::error_code & ec) = 0;
};



struct sync_write_stream : virtual executor_base
{
    virtual std::size_t write_some(boost::asio::const_buffer buffer) = 0;
    virtual std::size_t write_some(boost::asio::const_buffer buffer, boost::system::error_code & ec) = 0;
};

struct write_stream : async_write_stream, sync_write_stream {};
struct read_stream : async_read_stream, sync_read_stream {};

struct closable_write_stream : write_stream, closable{};
struct closable_read_stream : read_stream, closable {};

struct duplex_stream : write_stream, read_stream {};
struct closable_duplex_stream : closable, duplex_stream {};

}

#endif //TE_ASIO_CONCEPTS_HPP

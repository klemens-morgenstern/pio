//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TE_ASIO_MAKE_PIPE_HPP
#define TE_ASIO_MAKE_PIPE_HPP

#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/connect_pipe.hpp>
#include <boost/asio/readable_pipe.hpp>
#include <boost/asio/writable_pipe.hpp>

#include <concepts.hpp>


namespace te
{

std::pair<std::unique_ptr<closable_read_stream>,
          std::unique_ptr<closable_write_stream>> make_pipe(boost::asio::any_io_executor exec)
{
    struct rt final : closable_read_stream
    {
        boost::asio::readable_pipe rp;

        executor_type get_executor()
        {
            return rp.get_executor();
        }

        rt(boost::asio::any_io_executor exec) : rp(exec) {}

        void close()                               override {rp.close();}
        void close(boost::system::error_code & ec) override {rp.close(ec);}

        std::size_t read_some(boost::asio::mutable_buffer buffer) override
        {
            return rp.read_some(buffer);
        }
        std::size_t read_some(boost::asio::mutable_buffer buffer, boost::system::error_code & ec) override
        {
            return rp.read_some(buffer, ec);
        }

        void async_read_some_impl(boost::asio::mutable_buffer buffer, handler_type<void(boost::system::error_code, std::size_t)> && h)
        {
            return rp.async_read_some(buffer, std::move(h));
        }


    };

    struct wt final : closable_write_stream
    {
        boost::asio::writable_pipe wp;

        executor_type get_executor()
        {
            return wp.get_executor();
        }

        wt(boost::asio::any_io_executor exec) : wp(exec) {}

        void close()                               override {wp.close();}
        void close(boost::system::error_code & ec) override {wp.close(ec);}


        std::size_t write_some(boost::asio::const_buffer buffer) override
        {
            return wp.write_some(buffer);
        }
        std::size_t write_some(boost::asio::const_buffer buffer, boost::system::error_code & ec) override
        {
            return wp.write_some(buffer, ec);
        }

        void async_write_some_impl(boost::asio::const_buffer buffer, handler_type<void(boost::system::error_code, std::size_t)> && h) override
        {
            return wp.async_write_some(buffer, std::move(h));
        }
    };
    auto r = std::make_unique<rt>(exec);
    auto w = std::make_unique<wt>(exec);

    boost::asio::connect_pipe(r->rp, w->wp);

    return std::pair<std::unique_ptr<closable_read_stream>,
              std::unique_ptr<closable_write_stream>>{std::move(r), std::move(w)};


}


}


#endif //TE_ASIO_MAKE_PIPE_HPP

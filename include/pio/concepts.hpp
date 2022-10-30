//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_CONCEPTS_HPP
#define PIO_CONCEPTS_HPP

#include "asio/any_io_executor.hpp"
#include "asio/buffer.hpp"

#include "pio/handler.hpp"

namespace pio::concepts
{

struct closable
{
    virtual void close() = 0;
    virtual ASIO_SYNC_OP_VOID close(std::error_code & ec) = 0;
    virtual bool is_open() const = 0;
    virtual ~closable() = default;
};

struct cancellable
{
    virtual void cancel() = 0;
    virtual ASIO_SYNC_OP_VOID cancel(std::error_code & ec) = 0;
    virtual ~cancellable() = default;
};

struct execution_context
{
    using executor_type = asio::any_io_executor;
    virtual executor_type get_executor() = 0;
    virtual ~execution_context() = default;
};

struct async_read_stream : virtual execution_context
{
    template<typename CompletionHandler>
    ASIO_INITFN_AUTO_RESULT_TYPE(CompletionHandler, void(std::error_code, std::size_t))
    async_read_some(const asio::mutable_buffer &buffer, CompletionHandler && token)
    {
        return asio::async_initiate<CompletionHandler, void(std::error_code, std::size_t)>(
                [this](auto handler, const asio::mutable_buffer &buffer)
                {
                    this->async_read_some_impl(buffer,
                                               handler_type<void(std::error_code, std::size_t)>(std::move(handler), this->get_executor()));
                },
                token, buffer);
    }

    virtual void async_read_some_impl(const asio::mutable_buffer &buffer, handler_type<void(std::error_code, std::size_t)> && h) = 0;
};

struct async_write_stream : virtual execution_context
{
    template<typename CompletionHandler>
    ASIO_INITFN_AUTO_RESULT_TYPE(CompletionHandler, void(std::error_code, std::size_t))
    async_write_some(asio::const_buffer buffer, CompletionHandler && token)
    {
        return asio::async_initiate<CompletionHandler, void(std::error_code, std::size_t)>(
                [this](auto handler, asio::const_buffer buffer)
                {
                    this->async_write_some_impl(buffer,
                                                handler_type<void(std::error_code, std::size_t)>(std::move(handler), this->get_executor()));
                },
                token, buffer);
    }

    virtual void async_write_some_impl(asio::const_buffer buffer,
                                       handler_type<void(std::error_code, std::size_t)> && h) = 0;
};

struct sync_read_stream
{
    virtual std::size_t read_some(const asio::mutable_buffer &buffer) = 0;
    virtual std::size_t read_some(const asio::mutable_buffer &buffer, std::error_code & ec) = 0;
    virtual ~sync_read_stream() = default;

};



struct sync_write_stream
{
    virtual std::size_t write_some(const asio::const_buffer & buffer) = 0;
    virtual std::size_t write_some(const asio::const_buffer & buffer, std::error_code & ec) = 0;
    virtual ~sync_write_stream() = default;
};

struct timer
{
    virtual void wait() = 0;
    virtual void wait(std::error_code & ec) = 0;
    virtual ~timer() = default;
};


struct async_timer : virtual execution_context
{
    template<typename CompletionHandler>
    ASIO_INITFN_AUTO_RESULT_TYPE(CompletionHandler, void(std::error_code))
    async_wait(CompletionHandler && token)
    {
        return asio::async_initiate<CompletionHandler, void(std::error_code)>(
                [this](auto handler)
                {
                    this->async_wait_impl(handler_type<void(std::error_code)>(std::move(handler), this->get_executor()));
                },
                token);
    }

    virtual void async_wait_impl(handler_type<void(std::error_code)> && h) = 0;
};


struct async_random_access_read_device : virtual execution_context
{
    template<typename CompletionHandler>
    ASIO_INITFN_AUTO_RESULT_TYPE(CompletionHandler, void(std::error_code, std::size_t))
    async_read_some_at(std::uint64_t offset,const asio::mutable_buffer &buffer, CompletionHandler && token)
    {
        return asio::async_initiate<CompletionHandler, void(std::error_code, std::size_t)>(
                [this](auto handler, std::uint64_t offset, const asio::mutable_buffer &buffer)
                {
                    this->async_read_some_at_impl(offset, buffer,
                                                  handler_type<void(std::error_code, std::size_t)>(std::move(handler), this->get_executor()));
                },
                token, offset, buffer);
    }

    virtual void async_read_some_at_impl(std::uint64_t offset, asio::mutable_buffer buffer,
                                         handler_type<void(std::error_code, std::size_t)> && h) = 0;
};

struct async_random_access_write_device : virtual execution_context
{
    template<typename CompletionHandler>
    ASIO_INITFN_AUTO_RESULT_TYPE(CompletionHandler, void(std::error_code, std::size_t))
    async_write_some_at(std::uint64_t offset,const asio::const_buffer & buffer, CompletionHandler && token)
    {
        return asio::async_initiate<CompletionHandler, void(std::error_code, std::size_t)>(
                [this](auto handler, std::uint64_t offset, asio::const_buffer buffer)
                {
                    this->async_write_some_at_impl(offset, buffer,
                                                   handler_type<void(std::error_code, std::size_t)>(std::move(handler), this->get_executor()));
                },
                token, offset, buffer);
    }

    virtual void async_write_some_at_impl(std::uint64_t offset, asio::const_buffer buffer,
                                          handler_type<void(std::error_code, std::size_t)> && h) = 0;
};

struct sync_random_access_read_device
{
    virtual std::size_t read_some_at(std::uint64_t offset, const asio::mutable_buffer & buffer) = 0;
    virtual std::size_t read_some_at(std::uint64_t offset, const asio::mutable_buffer & buffer, std::error_code & ec) = 0;
    virtual ~sync_random_access_read_device() = default;
};



struct sync_random_access_write_device
{
    virtual std::size_t write_some_at(std::uint64_t offset, const asio::const_buffer &buffer) = 0;
    virtual std::size_t write_some_at(std::uint64_t offset, const asio::const_buffer &buffer, std::error_code & ec) = 0;
    virtual ~sync_random_access_write_device() = default;
};

struct device_base
{
    virtual ~device_base() = default;
    /// Wait types.
    /**
     * For use with descriptor::wait() and descriptor::async_wait().
     */
    enum wait_type
    {
        /// Wait for a descriptor to become ready to read.
        wait_read,

        /// Wait for a descriptor to become ready to write.
        wait_write,

        /// Wait for a descriptor to have error conditions pending.
        wait_error
    };
};


struct waitable_device : virtual device_base
{
    virtual std::size_t wait(wait_type w, asio::const_buffer buffer) = 0;
    virtual std::size_t wait(wait_type w, asio::const_buffer buffer, std::error_code & ec) = 0;
};


struct async_waitable_device : virtual device_base, virtual execution_context
{
    template<typename CompletionHandler>
    ASIO_INITFN_AUTO_RESULT_TYPE(CompletionHandler, void(std::error_code))
    async_wait(wait_type w, CompletionHandler && token)
    {
        return asio::async_initiate<CompletionHandler, void(std::error_code)>(
                [this](auto handler, wait_type w)
                {
                    this->async_wait_impl(w, handler_type<void(std::error_code)>( std::move(handler), this->get_executor()));
                },
                token, w);
    }

    virtual void async_wait_impl(wait_type w, handler_type<void(std::error_code)> && h) = 0;
};

template<typename ... Args>
struct implements : Args ...
{

};

}

#endif //PIO_CONCEPTS_HPP

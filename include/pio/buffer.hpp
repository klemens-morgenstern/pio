//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_BUFFER_HPP
#define PIO_BUFFER_HPP

#include <asio/buffer.hpp>
#include <cassert>


namespace pio
{

using asio::mutable_buffer;
using asio::buffer;
using asio::const_buffer;
using asio::buffer_sequence_begin;
using asio::buffer_sequence_end;

std::size_t buffer_copy(const mutable_buffer & target, const const_buffer & source) noexcept;

namespace detail
{
struct dynamic_buffer
{
    typedef const_buffer const_buffers_type;
    typedef mutable_buffer mutable_buffers_type;

    virtual std::size_t size() const noexcept = 0;
    virtual std::size_t max_size() const noexcept = 0;
    virtual std::size_t capacity() const noexcept = 0;

#if !defined(ASIO_NO_DYNAMIC_BUFFER_V1)
    virtual const_buffers_type data() const noexcept = 0;
#endif

    virtual mutable_buffers_type data(std::size_t pos, std::size_t n) noexcept = 0;
    virtual   const_buffers_type data(std::size_t pos, std::size_t n) const noexcept = 0;

#if !defined(ASIO_NO_DYNAMIC_BUFFER_V1)
    virtual mutable_buffers_type prepare(std::size_t n) = 0;
    virtual void commit(std::size_t n) = 0;
#endif
    virtual void grow(std::size_t n) = 0;
    virtual void shrink(std::size_t n) = 0;
    virtual void consume(std::size_t n) = 0;
};

template<typename Impl>
struct dynamic_buffer_impl final : dynamic_buffer
{
    typedef const_buffer const_buffers_type;
    typedef mutable_buffer mutable_buffers_type;
    std::size_t     size() const noexcept override {return impl_.size();}
    std::size_t max_size() const noexcept override {return impl_.max_size();}
    std::size_t capacity() const noexcept override {return impl_.capacity();}

#if !defined(ASIO_NO_DYNAMIC_BUFFER_V1)
    const_buffers_type data() const noexcept override  {return impl_.data();};
#endif
    mutable_buffers_type data(std::size_t pos, std::size_t n)     noexcept override {return impl_.data(pos, n);}
    const_buffers_type data(std::size_t pos, std::size_t n) const noexcept override {return impl_.data(pos, n);}

#if !defined(ASIO_NO_DYNAMIC_BUFFER_V1)
    mutable_buffers_type prepare(std::size_t n) override { return impl_.prepare(n);}
    void commit(std::size_t n) override { impl_.commit(n);}
#endif
    void grow(std::size_t n)    override { impl_.grow(n); }
    void shrink(std::size_t n)  override { impl_.shrink(n); }
    void consume(std::size_t n) override { impl_.consume(n); }

    Impl impl_;
    dynamic_buffer_impl(Impl impl) : impl_(std::move(impl)) {}
};

}


struct dynamic_buffer
{
    template<typename ... Args>
    dynamic_buffer(Args && ... args)
        : impl_(std::make_shared<
                detail::dynamic_buffer_impl<
                    decltype(asio::dynamic_buffer(std::forward<Args>(args)...))
                    >>(
                asio::dynamic_buffer(std::forward<Args>(args)...)))
    {
    }

    typedef const_buffer const_buffers_type;
    typedef mutable_buffer mutable_buffers_type;

    std::size_t     size() const noexcept {assert(impl_); return impl_->size();}
    std::size_t max_size() const noexcept {assert(impl_); return impl_->max_size();}
    std::size_t capacity() const noexcept {assert(impl_); return impl_->capacity();}

#if !defined(ASIO_NO_DYNAMIC_BUFFER_V1)
    const_buffers_type data() const noexcept {assert(impl_); return impl_->data();};
#endif
    mutable_buffers_type data(std::size_t pos, std::size_t n)       noexcept {assert(impl_); return impl_->data(pos, n);}
      const_buffers_type data(std::size_t pos, std::size_t n) const noexcept {assert(impl_); return impl_->data(pos, n);}

#if !defined(ASIO_NO_DYNAMIC_BUFFER_V1)
    mutable_buffers_type prepare(std::size_t n) { assert(impl_); return impl_->prepare(n);}
    void commit(std::size_t n) { assert(impl_); impl_->commit(n);}
#endif
    void grow(std::size_t n)    { assert(impl_); impl_->grow(n); }
    void shrink(std::size_t n)  { assert(impl_); impl_->shrink(n); }
    void consume(std::size_t n) { assert(impl_); impl_->consume(n); }
private:
    // can be optimized, it's trivial and just a string and 2 size_t
    std::shared_ptr<detail::dynamic_buffer> impl_;
};

extern template dynamic_buffer::dynamic_buffer(std::string &);
extern template dynamic_buffer::dynamic_buffer(std::vector<unsigned char>&);
extern template dynamic_buffer::dynamic_buffer(std::string &,               std::size_t &&);
extern template dynamic_buffer::dynamic_buffer(std::vector<unsigned char>&, std::size_t &&);


}

#endif //PIO_BUFFER_HPP

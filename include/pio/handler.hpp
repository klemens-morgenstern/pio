//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_HANDLER_HPP
#define PIO_HANDLER_HPP

#include <asio/any_io_executor.hpp>
#include <asio/associated_allocator.hpp>
#include <asio/associated_cancellation_slot.hpp>
#include <asio/associated_executor.hpp>
#include <memory_resource>

namespace pio
{

template<typename Allocator>
struct allocator_adaptor final : std::pmr::memory_resource
{
    allocator_adaptor(Allocator allocator) : allocator(allocator) {}

    using allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<char>;
    using traits = std::allocator_traits<allocator_type>;
    allocator_type allocator;

    void*
    do_allocate(size_t bytes, size_t alignment) override
    {
        return traits::allocate(allocator, bytes);
    }

    void
    do_deallocate(void* p, size_t bytes, size_t alignment)
    {
        return traits::deallocate(allocator, static_cast<char*>(p), bytes);
    };

    bool
    do_is_equal(const memory_resource& __other) const noexcept
    {
        auto p = reinterpret_cast<const allocator_adaptor*>(&__other);
        return p && p->allocator == allocator;
    };

    allocator_type get_allocator() const
    {
        return allocator;
    }
};

template<typename Signature>
struct handler_type;

template<typename ... Args>
struct handler_type<void(Args...)>
{
    struct base
    {
        virtual void invoke(Args...) = 0;

        using allocator_type = std::pmr::polymorphic_allocator<void>;
        virtual allocator_type get_allocator() const = 0;

        using executor_type = asio::any_io_executor;
        virtual executor_type get_executor() const = 0;

        using cancellation_slot_type = asio::cancellation_slot;
        virtual cancellation_slot_type get_cancellation_slot() const = 0;

        virtual void destroy() = 0;
        ~base() = default;
    };

    template<class Handler>
    struct impl : base
    {
        using allocator_type_actual = asio::associated_allocator_t<Handler>;

        using allocator_type = std::pmr::polymorphic_allocator<void>;
        allocator_type get_allocator() const override
        {
            if (std::is_same<allocator_type_actual, std::allocator<void>>::value)
                return allocator_type {};
            else
                return allocator_type(&alloc);
        }

        using executor_type = asio::any_io_executor;
        executor_type get_executor() const override
        {
            return asio::get_associated_executor(handler, default_executor);
        }

        using cancellation_slot_type = asio::cancellation_slot;
        cancellation_slot_type get_cancellation_slot() const override
        {
            return asio::get_associated_cancellation_slot(handler);
        }

        Handler handler;
        asio::any_io_executor default_executor;
        mutable allocator_adaptor<allocator_type_actual> alloc{asio::get_associated_allocator(handler)};

        template<typename Handler_>
        impl(Handler_ && h, asio::any_io_executor exec)
                    : handler(std::forward<Handler_>(h)),
                      default_executor(std::move(exec))
        {
        }

        template<typename Handler_>
        impl(Handler_ && h)
                : handler(std::forward<Handler_>(h)),
                  default_executor(asio::get_associated_executor(handler))
        {
        }


        virtual void invoke(Args... args)
        {
            auto h = std::move(handler);
            destroy();
            std::move(h)(std::move(args)...);
        }

        void destroy()
        {
            auto alloc  = typename std::allocator_traits< allocator_type_actual >
                                    ::template rebind_alloc< impl>(this->alloc.get_allocator());
            using traits = std::allocator_traits< decltype(alloc) >;
            this->~impl();
            traits::deallocate(alloc, this, 1);
        }
    };

    using allocator_type = std::pmr::polymorphic_allocator<void>;
    allocator_type get_allocator() const
    {
        assert(impl_);
        return impl_->get_allocator();
    }

    using executor_type = asio::any_io_executor;
    executor_type get_executor() const
    {
        assert(impl_);
        return impl_->get_executor();
    }


    using cancellation_slot_type = asio::cancellation_slot;
    cancellation_slot_type get_cancellation_slot() const
    {
        assert(impl_);
        return impl_->get_cancellation_slot();
    }

    void operator()(Args ... args)
    {
        assert(impl_);
        impl_.release()->invoke(std::move(args)...);
    }

    struct deleter_t
    {
        virtual void operator()(base * b)
        {
            if (b)
                b->destroy();
        }
    };

    std::unique_ptr<base, deleter_t> impl_;


    template<typename Handler>
    static std::unique_ptr<base, deleter_t> make(Handler && handler,
                                                 asio::any_io_executor exec)
    {
        auto halloc = asio::get_associated_allocator(handler);
        using impl_t = impl<std::decay_t<Handler>>;
        auto alloc  = typename std::allocator_traits< decltype(halloc) >:: template rebind_alloc< impl_t >(halloc);
        using traits = std::allocator_traits< decltype(alloc) >;
        auto pmem   = traits::allocate(alloc, 1);
        struct dealloc
        {
            ~dealloc()
            {
#if defined(__cpp_lib_uncaught_exceptions)
                if (std::uncaught_exceptions() > 0)
#else
                    if (std::uncaught_exception())
#endif
                    traits::deallocate(alloc_, pmem_, 1);
            }
            decltype(alloc) alloc_;
            decltype(pmem) pmem_;
        };

        dealloc dc{halloc, pmem};
        return std::unique_ptr<base, deleter_t>(new (pmem) impl_t(std::move(handler), std::move(exec)), deleter_t{});
    }

    template<typename Handler>
    handler_type(Handler && handler, asio::any_io_executor exec)
            : impl_(make(std::forward<Handler>(handler), std::move(exec)))
    {}
};

using wait_handler = handler_type<void(std::error_code)>;
using read_handler = handler_type<void(std::error_code, std::size_t)>;
using write_handler = handler_type<void(std::error_code, std::size_t)>;

}

#endif //TE_ASIO_HANDLER_HPP

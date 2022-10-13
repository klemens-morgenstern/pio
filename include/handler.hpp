//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TE_ASIO_HANDLER_HPP
#define TE_ASIO_HANDLER_HPP

#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/smart_ptr/allocate_unique.hpp>
#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>
#include <boost/container/pmr/resource_adaptor.hpp>

namespace te
{

template<typename Signature>
struct handler_type;

template<typename ... Args>
struct handler_type<void(Args...)>
{
    struct base
    {
        virtual void invoke(Args...) = 0;

        using allocator_type = boost::container::pmr::polymorphic_allocator<void>;
        virtual allocator_type get_allocator() const = 0;

        using executor_type = boost::asio::any_io_executor;
        virtual executor_type get_executor() const = 0;

        using cancellation_slot_type = boost::asio::cancellation_slot;
        virtual cancellation_slot_type get_cancellation_slot() const = 0;

        virtual void destroy() = 0;
        ~base() = default;
    };

    template<class Handler>
    struct impl : base
    {
        using allocator_type_actual = boost::asio::associated_allocator_t<Handler>;

        using allocator_type = boost::container::pmr::polymorphic_allocator<void>;
        allocator_type get_allocator() const override
        {
            if (std::is_same<allocator_type_actual, std::allocator<void>>::value)
                return allocator_type {};
            else
                return allocator_type(&alloc);
        }

        using executor_type = boost::asio::any_io_executor;
        executor_type get_executor() const override
        {
            return boost::asio::get_associated_executor(handler, default_executor);
        }

        using cancellation_slot_type = boost::asio::cancellation_slot;
        cancellation_slot_type get_cancellation_slot() const override
        {
            return boost::asio::get_associated_cancellation_slot(handler);
        }

        Handler handler;
        boost::asio::any_io_executor default_executor;
        mutable boost::container::pmr::resource_adaptor<allocator_type_actual> alloc{boost::asio::get_associated_allocator(handler)};

        template<typename Handler_>
        impl(Handler_ && h, boost::asio::any_io_executor exec)
                    : handler(std::forward<Handler_>(h)),
                      default_executor(std::move(exec))
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

    using allocator_type = boost::container::pmr::polymorphic_allocator<void>;
    allocator_type get_allocator() const
    {
        assert(impl_);
        return impl_->get_allocator();
    }

    using executor_type = boost::asio::any_io_executor;
    executor_type get_executor() const
    {
        assert(impl_);
        return impl_->get_executor();
    }


    using cancellation_slot_type = boost::asio::cancellation_slot;
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
                                                 boost::asio::any_io_executor exec)
    {
        auto halloc = boost::asio::get_associated_allocator(handler);
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
    handler_type(Handler && handler, boost::asio::any_io_executor exec)
            : impl_(make(std::forward<Handler>(handler), std::move(exec)))
    {}
};


}

#endif //TE_ASIO_HANDLER_HPP

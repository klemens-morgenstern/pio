//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_BASIC_WAITABLE_TIMER_HPP
#define PIO_BASIC_WAITABLE_TIMER_HPP

#include <pio/concepts.hpp>

#include <asio/basic_waitable_timer.hpp>

namespace pio
{

template<typename Clock, typename WaitTraits = asio::wait_traits<Clock>>
struct basic_waitable_timer
        : concepts::implements<concepts::timer, concepts::async_timer>
{
    /// The clock type.
    typedef Clock clock_type;

    /// The duration type of the clock.
    typedef typename clock_type::duration duration;

    /// The time point type of the clock.
    typedef typename clock_type::time_point time_point;

    /// The wait traits type.
    typedef WaitTraits traits_type;

    explicit basic_waitable_timer(asio::any_io_executor ex) : timer_(ex) {}
    template <typename ExecutionContext>
    explicit basic_waitable_timer(ExecutionContext& context,
                                  typename asio::constraint<
                                          asio::is_convertible<ExecutionContext&, asio::execution_context&>::value
                                  >::type = 0)
            : basic_waitable_timer(context.get_executor())
    {
    }

    basic_waitable_timer(const executor_type& ex, const time_point& expiry_time) : timer_(ex, expiry_time) {}

    template <typename ExecutionContext>
    explicit basic_waitable_timer(ExecutionContext& context,
                                  const time_point& expiry_time,
                                  typename asio::constraint<
                                          asio::is_convertible<ExecutionContext&, asio::execution_context&>::value
                                  >::type = 0)
            : basic_waitable_timer(context.get_executor(), expiry_time)
    {
    }

    basic_waitable_timer(const executor_type& ex, const duration& expiry_time) : timer_(ex, expiry_time) {}

    template <typename ExecutionContext>
    explicit basic_waitable_timer(ExecutionContext& context,
                                  const duration& expiry_time,
                                  typename asio::constraint<
                                          asio::is_convertible<ExecutionContext&, asio::execution_context&>::value
                                  >::type = 0)
            : basic_waitable_timer(context.get_executor(), expiry_time)
    {
    }

    basic_waitable_timer(basic_waitable_timer&& other) = default;
    basic_waitable_timer& operator=(basic_waitable_timer&& other) = default;
    ~basic_waitable_timer() = default;


    std::size_t cancel() {return timer_.cancel();}
    std::size_t cancel(std::error_code & ec) {return timer_.cancel(ec);}

    std::size_t cancel_one() {return timer_.cancel_one();}
    std::size_t cancel_one(std::error_code & ec) {return timer_.cancel_one(ec);}

    executor_type get_executor() noexcept override{ return timer_.get_executor(); }

    time_point expires_at() const {return timer_.expires_at();}
    time_point expiry()     const {return timer_.expiry();}
    std::size_t expires_at(const time_point& expiry_time)
    {
        return timer_.expires_at(expiry_time);
    }
    std::size_t expires_at(const time_point& expiry_time,
                           asio::error_code& ec)
    {
        return timer_.expires_at(expiry_time, ec);

    }
    std::size_t expires_after(const duration& expiry_time)
    {
        return timer_.expires_after(expiry_time);
    }
    duration expires_from_now() const
    {
        return timer_.expires_from_now();
    }
    std::size_t expires_from_now(const duration& expiry_time)
    {
        return timer_.expires_after(expiry_time);

    }
    std::size_t expires_from_now(const duration& expiry_time,
                                 asio::error_code& ec)
    {
        return timer_.expires_from_now(expiry_time, ec);

    }
    void wait() override
    {
        timer_.wait();
    }
    void wait(asio::error_code& ec) override
    {
        timer_.wait(ec);
    }

    virtual void async_wait_impl(handler_type<void(std::error_code)> && h)
    {
        return timer_.template async_wait(std::move(h));
    }
private:
    asio::basic_waitable_timer<Clock, WaitTraits> timer_;
};

}

#endif //PIO_BASIC_WAITABLE_TIMER_HPP

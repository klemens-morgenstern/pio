//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_SIGNAL_SET_HPP
#define PIO_SIGNAL_SET_HPP

#include <asio/signal_set.hpp>
#include <pio/concepts.hpp>

namespace pio
{

struct signal_set : concepts::implements<
                            concepts::cancellable,
                            concepts::execution_context>
{
    /// The type of the executor associated with the object.
    typedef asio::any_io_executor executor_type;

    /// Construct a signal set without adding any signals.
    /**
     * This constructor creates a signal set without registering for any signals.
     *
     * @param ex The I/O executor that the signal set will use, by default, to
     * dispatch handlers for any asynchronous operations performed on the
     * signal set.
     */
    explicit signal_set(const executor_type& ex);

    /// Construct a signal set without adding any signals.
    /**
     * This constructor creates a signal set without registering for any signals.
     *
     * @param context An execution context which provides the I/O executor that
     * the signal set will use, by default, to dispatch handlers for any
     * asynchronous operations performed on the signal set.
     */
    template <typename ExecutionContext>
    explicit signal_set(ExecutionContext& context,
                              typename asio::constraint<
                                      asio::is_convertible<ExecutionContext&, execution_context&>::value,
                                      asio::defaulted_constraint
                              >::type = asio::defaulted_constraint()) : impl_(context.get_executor())
    {
    }

    /// Construct a signal set and add one signal.
    /**
     * This constructor creates a signal set and registers for one signal.
     *
     * @param ex The I/O executor that the signal set will use, by default, to
     * dispatch handlers for any asynchronous operations performed on the
     * signal set.
     *
     * @param signal_number_1 The signal number to be added.
     *
     * @note This constructor is equivalent to performing:
     * @code asio::signal_set signals(ex);
     * signals.add(signal_number_1); @endcode
     */
    signal_set(const executor_type& ex, int signal_number_1);

    /// Construct a signal set and add one signal.
    /**
     * This constructor creates a signal set and registers for one signal.
     *
     * @param context An execution context which provides the I/O executor that
     * the signal set will use, by default, to dispatch handlers for any
     * asynchronous operations performed on the signal set.
     *
     * @param signal_number_1 The signal number to be added.
     *
     * @note This constructor is equivalent to performing:
     * @code asio::signal_set signals(context);
     * signals.add(signal_number_1); @endcode
     */
    template <typename ExecutionContext>
    signal_set(ExecutionContext& context, int signal_number_1,
                     typename asio::constraint<
                             asio::is_convertible<ExecutionContext&, execution_context&>::value,
                             asio::defaulted_constraint
                     >::type = asio::defaulted_constraint())
            : signal_set(context.get_executor(), signal_number_1)
    {
    }

    /// Construct a signal set and add two signals.
    /**
     * This constructor creates a signal set and registers for two signals.
     *
     * @param ex The I/O executor that the signal set will use, by default, to
     * dispatch handlers for any asynchronous operations performed on the
     * signal set.
     *
     * @param signal_number_1 The first signal number to be added.
     *
     * @param signal_number_2 The second signal number to be added.
     *
     * @note This constructor is equivalent to performing:
     * @code asio::signal_set signals(ex);
     * signals.add(signal_number_1);
     * signals.add(signal_number_2); @endcode
     */
    signal_set(const executor_type& ex, int signal_number_1, int signal_number_2);

    /// Construct a signal set and add two signals.
    /**
     * This constructor creates a signal set and registers for two signals.
     *
     * @param context An execution context which provides the I/O executor that
     * the signal set will use, by default, to dispatch handlers for any
     * asynchronous operations performed on the signal set.
     *
     * @param signal_number_1 The first signal number to be added.
     *
     * @param signal_number_2 The second signal number to be added.
     *
     * @note This constructor is equivalent to performing:
     * @code asio::signal_set signals(context);
     * signals.add(signal_number_1);
     * signals.add(signal_number_2); @endcode
     */
    template <typename ExecutionContext>
    signal_set(ExecutionContext& context, int signal_number_1,
                     int signal_number_2,
                     typename asio::constraint<
                             asio::is_convertible<ExecutionContext&, execution_context&>::value,
                             asio::defaulted_constraint
                     >::type = asio::defaulted_constraint())
            : signal_set(context.get_executor(), signal_number_1, signal_number_2)
    {
    }

    /// Construct a signal set and add three signals.
    /**
     * This constructor creates a signal set and registers for three signals.
     *
     * @param ex The I/O executor that the signal set will use, by default, to
     * dispatch handlers for any asynchronous operations performed on the
     * signal set.
     *
     * @param signal_number_1 The first signal number to be added.
     *
     * @param signal_number_2 The second signal number to be added.
     *
     * @param signal_number_3 The third signal number to be added.
     *
     * @note This constructor is equivalent to performing:
     * @code asio::signal_set signals(ex);
     * signals.add(signal_number_1);
     * signals.add(signal_number_2);
     * signals.add(signal_number_3); @endcode
     */
    signal_set(const executor_type& ex, int signal_number_1,
               int signal_number_2, int signal_number_3);
    /// Construct a signal set and add three signals.
    /**
     * This constructor creates a signal set and registers for three signals.
     *
     * @param context An execution context which provides the I/O executor that
     * the signal set will use, by default, to dispatch handlers for any
     * asynchronous operations performed on the signal set.
     *
     * @param signal_number_1 The first signal number to be added.
     *
     * @param signal_number_2 The second signal number to be added.
     *
     * @param signal_number_3 The third signal number to be added.
     *
     * @note This constructor is equivalent to performing:
     * @code asio::signal_set signals(context);
     * signals.add(signal_number_1);
     * signals.add(signal_number_2);
     * signals.add(signal_number_3); @endcode
     */
    template <typename ExecutionContext>
    signal_set(ExecutionContext& context, int signal_number_1,
                     int signal_number_2, int signal_number_3,
                     typename asio::constraint<
                             asio::is_convertible<ExecutionContext&, execution_context&>::value,
                             asio::defaulted_constraint
                     >::type = asio::defaulted_constraint())
            : signal_set(context.get_executor(), signal_number_1, signal_number_2, signal_number_3)
    {
    }

    /// Destroys the signal set.
    /**
     * This function destroys the signal set, cancelling any outstanding
     * asynchronous wait operations associated with the signal set as if by
     * calling @c cancel.
     */
    ~signal_set();

    /// Get the executor associated with the object.
    executor_type get_executor() noexcept ;

    /// Add a signal to a signal_set.
    /**
     * This function adds the specified signal to the set. It has no effect if the
     * signal is already in the set.
     *
     * @param signal_number The signal to be added to the set.
     *
     * @throws asio::system_error Thrown on failure.
     */
    void add(int signal_number);

    /// Add a signal to a signal_set.
    /**
     * This function adds the specified signal to the set. It has no effect if the
     * signal is already in the set.
     *
     * @param signal_number The signal to be added to the set.
     *
     * @param ec Set to indicate what error occurred, if any.
     */
    ASIO_SYNC_OP_VOID add(int signal_number, asio::error_code& ec);

    /// Remove a signal from a signal_set.
    /**
     * This function removes the specified signal from the set. It has no effect
     * if the signal is not in the set.
     *
     * @param signal_number The signal to be removed from the set.
     *
     * @throws asio::system_error Thrown on failure.
     *
     * @note Removes any notifications that have been queued for the specified
     * signal number.
     */
    void remove(int signal_number);

    /// Remove a signal from a signal_set.
    /**
     * This function removes the specified signal from the set. It has no effect
     * if the signal is not in the set.
     *
     * @param signal_number The signal to be removed from the set.
     *
     * @param ec Set to indicate what error occurred, if any.
     *
     * @note Removes any notifications that have been queued for the specified
     * signal number.
     */
    ASIO_SYNC_OP_VOID remove(int signal_number, asio::error_code& ec);

    /// Remove all signals from a signal_set.
    /**
     * This function removes all signals from the set. It has no effect if the set
     * is already empty.
     *
     * @throws asio::system_error Thrown on failure.
     *
     * @note Removes all queued notifications.
     */
    void clear();

    /// Remove all signals from a signal_set.
    /**
     * This function removes all signals from the set. It has no effect if the set
     * is already empty.
     *
     * @param ec Set to indicate what error occurred, if any.
     *
     * @note Removes all queued notifications.
     */
    ASIO_SYNC_OP_VOID clear(asio::error_code& ec);

    /// Cancel all operations associated with the signal set.
    /**
     * This function forces the completion of any pending asynchronous wait
     * operations against the signal set. The handler for each cancelled
     * operation will be invoked with the asio::error::operation_aborted
     * error code.
     *
     * Cancellation does not alter the set of registered signals.
     *
     * @throws asio::system_error Thrown on failure.
     *
     * @note If a registered signal occurred before cancel() is called, then the
     * handlers for asynchronous wait operations will:
     *
     * @li have already been invoked; or
     *
     * @li have been queued for invocation in the near future.
     *
     * These handlers can no longer be cancelled, and therefore are passed an
     * error code that indicates the successful completion of the wait operation.
     */
    void cancel() override;

    /// Cancel all operations associated with the signal set.
    /**
     * This function forces the completion of any pending asynchronous wait
     * operations against the signal set. The handler for each cancelled
     * operation will be invoked with the asio::error::operation_aborted
     * error code.
     *
     * Cancellation does not alter the set of registered signals.
     *
     * @param ec Set to indicate what error occurred, if any.
     *
     * @note If a registered signal occurred before cancel() is called, then the
     * handlers for asynchronous wait operations will:
     *
     * @li have already been invoked; or
     *
     * @li have been queued for invocation in the near future.
     *
     * These handlers can no longer be cancelled, and therefore are passed an
     * error code that indicates the successful completion of the wait operation.
     */
    ASIO_SYNC_OP_VOID cancel(asio::error_code& ec) override;

    /// Start an asynchronous operation to wait for a signal to be delivered.
    /**
     * This function may be used to initiate an asynchronous wait against the
     * signal set. It is an initiating function for an @ref
     * asynchronous_operation, and always returns immediately.
     *
     * For each call to async_wait(), the completion handler will be called
     * exactly once. The completion handler will be called when:
     *
     * @li One of the registered signals in the signal set occurs; or
     *
     * @li The signal set was cancelled, in which case the handler is passed the
     * error code asio::error::operation_aborted.
     *
     * @param token The @ref completion_token that will be used to produce a
     * completion handler, which will be called when the wait completes.
     * Potential completion tokens include @ref use_future, @ref use_awaitable,
     * @ref yield_context, or a function object with the correct completion
     * signature. The function signature of the completion handler must be:
     * @code void handler(
     *   const asio::error_code& error, // Result of operation.
     *   int signal_number // Indicates which signal occurred.
     * ); @endcode
     * Regardless of whether the asynchronous operation completes immediately or
     * not, the completion handler will not be invoked from within this function.
     * On immediate completion, invocation of the handler will be performed in a
     * manner equivalent to using asio::post().
     *
     * @par Completion Signature
     * @code void(asio::error_code, int) @endcode
     *
     * @par Per-Operation Cancellation
     * This asynchronous operation supports cancellation for the following
     * asio::cancellation_type values:
     *
     * @li @c cancellation_type::terminal
     *
     * @li @c cancellation_type::partial
     *
     * @li @c cancellation_type::total
     */
  template <
    ASIO_COMPLETION_TOKEN_FOR(void (asio::error_code, int))
      SignalToken ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  ASIO_INITFN_AUTO_RESULT_TYPE_PREFIX(SignalToken,
      void (asio::error_code, int))
  async_wait(
      ASIO_MOVE_ARG(SignalToken) token
        ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
    ASIO_INITFN_AUTO_RESULT_TYPE_SUFFIX((
      async_initiate<SignalToken, void (asio::error_code, int)>(
          declval<initiate_async_wait>(), token)))
  {
    return async_initiate<SignalToken, void (asio::error_code, int)>(
            [this](auto handler){this->async_wait_impl(handler_type<void(asio::error_code , int)>(std::move(handler), get_executor()));}, token);
  }

private:

    void async_wait_impl(handler_type<void(std::error_code, int)> && h);
    asio::signal_set impl_;
};

    
}

#endif //PIO_SIGNAL_SET_HPP

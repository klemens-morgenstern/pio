//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_SERIAL_PORT_HPP
#define PIO_SERIAL_PORT_HPP

#include <asio/serial_port.hpp>
#include <pio/buffer.hpp>
#include <pio/concepts.hpp>

namespace pio
{

struct serial_port final :
        concepts::implements<
                concepts::sync_read_stream,
                concepts::sync_write_stream,
                concepts::async_read_stream,
                concepts::async_write_stream,
                concepts::cancellable,
                concepts::closable>,
        asio::serial_port_base
{
    /// The type of the executor associated with the object.
    typedef asio::any_io_executor executor_type;
    /// The native representation of a serial port.
    typedef typename asio::serial_port::native_handle_type native_handle_type;

    typedef serial_port lowest_layer_type;

    /// Construct a basic_serial_port without opening it.
    /**
     * This constructor creates a serial port without opening it.
     *
     * @param ex The I/O executor that the serial port will use, by default, to
     * dispatch handlers for any asynchronous operations performed on the
     * serial port.
     */
    explicit serial_port(const executor_type& ex);
    /// Construct a basic_serial_port without opening it.
    /**
     * This constructor creates a serial port without opening it.
     *
     * @param context An execution context which provides the I/O executor that
     * the serial port will use, by default, to dispatch handlers for any
     * asynchronous operations performed on the serial port.
     */
    template <typename ExecutionContext>
    explicit serial_port(ExecutionContext& context,
    typename asio::constraint<
            asio::is_convertible<ExecutionContext&, execution_context&>::value,
            asio::defaulted_constraint
    >::type = asio::defaulted_constraint()) : serial_port(context.get_executor())
    {
    }


  /// Construct and open a basic_serial_port.
  /**
   * This constructor creates and opens a serial port for the specified device
   * name.
   *
   * @param ex The I/O executor that the serial port will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * serial port.
   *
   * @param device The platform-specific device name for this serial
   * port.
   */
  serial_port(const executor_type& ex, const char* device);

  /// Construct and open a basic_serial_port.
  /**
   * This constructor creates and opens a serial port for the specified device
   * name.
   *
   * @param context An execution context which provides the I/O executor that
   * the serial port will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the serial port.
   *
   * @param device The platform-specific device name for this serial
   * port.
   */
  template <typename ExecutionContext>
  serial_port(ExecutionContext& context, const char* device,
      typename asio::constraint<
              asio::is_convertible<ExecutionContext&, asio::execution_context&>::value
      >::type = 0)
    : serial_port(context.get_executor(), device)
  {
  }

  /// Construct and open a basic_serial_port.
  /**
   * This constructor creates and opens a serial port for the specified device
   * name.
   *
   * @param ex The I/O executor that the serial port will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * serial port.
   *
   * @param device The platform-specific device name for this serial
   * port.
   */
  serial_port(const executor_type& ex, const std::string& device);

  /// Construct and open a basic_serial_port.
  /**
   * This constructor creates and opens a serial port for the specified device
   * name.
   *
   * @param context An execution context which provides the I/O executor that
   * the serial port will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the serial port.
   *
   * @param device The platform-specific device name for this serial
   * port.
   */
  template <typename ExecutionContext>
  serial_port(ExecutionContext& context, const std::string& device,
      typename asio::constraint<
              asio::is_convertible<ExecutionContext&, asio::execution_context&>::value
      >::type = 0)
    : impl_(context.get_executor(), device)
  {
  }

  /// Construct a basic_serial_port on an existing native serial port.
  /**
   * This constructor creates a serial port object to hold an existing native
   * serial port.
   *
   * @param ex The I/O executor that the serial port will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * serial port.
   *
   * @param native_serial_port A native serial port.
   *
   * @throws asio::system_error Thrown on failure.
   */
  serial_port(const executor_type& ex, const native_handle_type& native_serial_port);

  /// Construct a basic_serial_port on an existing native serial port.
  /**
   * This constructor creates a serial port object to hold an existing native
   * serial port.
   *
   * @param context An execution context which provides the I/O executor that
   * the serial port will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the serial port.
   *
   * @param native_serial_port A native serial port.
   *
   * @throws asio::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  serial_port(ExecutionContext& context,
      const native_handle_type& native_serial_port,
      typename asio::constraint<
              asio::is_convertible<ExecutionContext&, asio::execution_context&>::value
      >::type = 0)
    : serial_port(context.get_executor(), native_serial_port)
  {
  }

  /// Move-construct a basic_serial_port from another.
  /**
   * This constructor moves a serial port from one object to another.
   *
   * @param other The other basic_serial_port object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_serial_port(const executor_type&)
   * constructor.
   */
  serial_port(serial_port&& other);

  /// Move-assign a basic_serial_port from another.
  /**
   * This assignment operator moves a serial port from one object to another.
   *
   * @param other The other basic_serial_port object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_serial_port(const executor_type&)
   * constructor.
   */
  serial_port& operator=(serial_port&& other);
  ~serial_port();

  /// Get the executor associated with the obect.
  executor_type get_executor() ASIO_NOEXCEPT;

  /// Get a reference to the lowest layer.
  /**
   * This function returns a reference to the lowest layer in a stack of
   * layers. Since a basic_serial_port cannot contain any further layers, it
   * simply returns a reference to itself.
   *
   * @return A reference to the lowest layer in the stack of layers. Ownership
   * is not transferred to the caller.
   */
  lowest_layer_type& lowest_layer()
  {
    return *this;
  }

  /// Get a const reference to the lowest layer.
  /**
   * This function returns a const reference to the lowest layer in a stack of
   * layers. Since a basic_serial_port cannot contain any further layers, it
   * simply returns a reference to itself.
   *
   * @return A const reference to the lowest layer in the stack of layers.
   * Ownership is not transferred to the caller.
   */
  const lowest_layer_type& lowest_layer() const
  {
    return *this;
  }

  void open(const std::string& device);
  ASIO_SYNC_OP_VOID open(const std::string& device, asio::error_code& ec);
  void assign(const native_handle_type& native_serial_port);
  ASIO_SYNC_OP_VOID assign(const native_handle_type& native_serial_port, asio::error_code& ec);
  /// Determine whether the serial port is open.
  bool is_open() const;
  void close() override;
  ASIO_SYNC_OP_VOID close(asio::error_code& ec) override;
  native_handle_type native_handle();
  void cancel() override ;
  ASIO_SYNC_OP_VOID cancel(asio::error_code& ec) override;
  void send_break();
  ASIO_SYNC_OP_VOID send_break(asio::error_code& ec);

  void set_option(const baud_rate& option     );
  void set_option(const flow_control& option  );
  void set_option(const parity& option        );
  void set_option(const stop_bits& option     );
  void set_option(const character_size& option);

  ASIO_SYNC_OP_VOID set_option(const baud_rate& option,      asio::error_code& ec);
  ASIO_SYNC_OP_VOID set_option(const flow_control& option,   asio::error_code& ec);
  ASIO_SYNC_OP_VOID set_option(const parity& option,         asio::error_code& ec);
  ASIO_SYNC_OP_VOID set_option(const stop_bits& option,      asio::error_code& ec);
  ASIO_SYNC_OP_VOID set_option(const character_size& option, asio::error_code& ec);


  void get_option(baud_rate& option     ) const;
  void get_option(flow_control& option  ) const;
  void get_option(parity& option        ) const;
  void get_option(stop_bits& option     ) const;
  void get_option(character_size& option) const;

  ASIO_SYNC_OP_VOID get_option(baud_rate& option,      asio::error_code& ec) const;
  ASIO_SYNC_OP_VOID get_option(flow_control& option,   asio::error_code& ec) const;
  ASIO_SYNC_OP_VOID get_option(parity& option,         asio::error_code& ec) const;
  ASIO_SYNC_OP_VOID get_option(stop_bits& option,      asio::error_code& ec) const;
  ASIO_SYNC_OP_VOID get_option(character_size& option, asio::error_code& ec) const;

  std::size_t write_some(const const_buffer& buffers);
  std::size_t write_some(const const_buffer& buffers, asio::error_code& ec);
  std::size_t read_some(const mutable_buffer& buffers);
  std::size_t read_some(const mutable_buffer& buffers, asio::error_code& ec);
private:
    void async_read_some_impl(const asio::mutable_buffer &buffer, handler_type<void(std::error_code, std::size_t)> && h) override;
    void async_write_some_impl(asio::const_buffer buffer, handler_type<void(std::error_code, std::size_t)> && h) override;
    asio::serial_port impl_;
};

}

#endif //PIO_SERIAL_PORT_HPP

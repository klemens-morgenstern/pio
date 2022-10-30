//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_CONNECT_PIPE_HPP
#define PIO_CONNECT_PIPE_HPP

#include <asio/error.hpp>

namespace pio
{

struct readable_pipe;
struct writable_pipe;

void connect_pipe(readable_pipe& read_end,
                  writable_pipe& write_end);

ASIO_SYNC_OP_VOID connect_pipe(readable_pipe& read_end,
                               writable_pipe& write_end, asio::error_code& ec);

}

#endif //PIO_CONNECT_PIPE_HPP

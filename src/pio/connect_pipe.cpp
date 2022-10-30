//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/connect_pipe.hpp>
#include <pio/readable_pipe.hpp>
#include <pio/writable_pipe.hpp>
#include <asio/connect_pipe.hpp>

namespace pio
{

void connect_pipe(readable_pipe& read_end,
                  writable_pipe& write_end)
{
    asio::connect_pipe(read_end.lowest_layer(), write_end.lowest_layer());
}

ASIO_SYNC_OP_VOID connect_pipe(readable_pipe& read_end,
                               writable_pipe& write_end, asio::error_code& ec)
{
    return asio::connect_pipe(read_end.lowest_layer(), write_end.lowest_layer(), ec);
}

}
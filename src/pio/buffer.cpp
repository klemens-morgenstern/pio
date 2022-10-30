//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/buffer.hpp>


namespace pio
{

std::size_t buffer_copy(const mutable_buffer & target, const const_buffer & source) noexcept
{
    return asio::buffer_copy(target, source);
}


template dynamic_buffer::dynamic_buffer(std::string &);
template dynamic_buffer::dynamic_buffer(std::vector<unsigned char>&);

template dynamic_buffer::dynamic_buffer(std::string &,               std::size_t &&);
template dynamic_buffer::dynamic_buffer(std::vector<unsigned char>&, std::size_t &&);
}
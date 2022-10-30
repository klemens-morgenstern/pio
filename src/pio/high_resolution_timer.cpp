//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <pio/high_resolution_timer.hpp>

namespace pio
{
template struct basic_waitable_timer<std::chrono::high_resolution_clock>;
}
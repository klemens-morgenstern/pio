//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PIO_HIGH_RESOLUTION_TIMER_HPP
#define PIO_HIGH_RESOLUTION_TIMER_HPP

#include <pio/basic_waitable_timer.hpp>


namespace pio
{

typedef basic_waitable_timer<std::chrono::high_resolution_clock> system_timer;
extern template struct basic_waitable_timer<std::chrono::high_resolution_clock>;

}

#endif //PIO_HIGH_RESOLUTION_TIMER_HPP

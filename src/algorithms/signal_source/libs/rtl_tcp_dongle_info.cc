/*!
 * \file rtl_tcp_dongle_info.cc
 * \brief Defines methods for retrieving and validating rtl_tcp donle
 *  info.
 * \author Anthony Arnold, 2015. anthony.arnold(at)uqconnect.edu.au
 *
 * This file contains information taken from librtlsdr:
 *  http://git.osmocom.org/rtl-sdr/
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2015  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */
#include "rtl_tcp_dongle_info.h"
#include <string.h>

using boost::asio::ip::tcp;

rtl_tcp_dongle_info::rtl_tcp_dongle_info ()
    : tuner_type_ (0), tuner_gain_count_ (0)
{
    ::memset (magic_, 0, sizeof (magic_));
}

boost::system::error_code rtl_tcp_dongle_info::read (tcp::socket &socket) {
    boost::system::error_code ec;

    unsigned char data[sizeof (char) * 4 + sizeof (uint32_t) * 2];
    socket.receive (boost::asio::buffer (data), 0, ec);
    if (!ec) {
        ::memcpy (magic_, data, 4);

        uint32_t type;
        ::memcpy (&type, &data[4], 4);

        tuner_type_ =
           boost::asio::detail::socket_ops::network_to_host_long (type);


        uint32_t count;
        ::memcpy (&count, &data[8], 4);

        tuner_gain_count_ =
           boost::asio::detail::socket_ops::network_to_host_long (count);
    }
    return ec;
}


const char *rtl_tcp_dongle_info::get_type_name () const {
    switch (get_tuner_type()) {
    default:
        return "UNKNOWN";
    case TUNER_E4000:
        return "E4000";
    case TUNER_FC0012:
        return "FC0012";
    case TUNER_FC0013:
        return "FC0013";
    case TUNER_FC2580:
        return "FC2580";
    case TUNER_R820T:
        return "R820T";
    case TUNER_R828D:
        return "R828D";
    }
}

bool rtl_tcp_dongle_info::is_valid () const {
    return ::memcmp (magic_, "RTL0", 4) == 0;
}

/*!
 * \file code_generation_test.cc
 * \note Code added as part of GSoC 2017 program
 * \author Damian Miralles, 2017. dmiralles2009(at)gmail.com
 * \see <a href="http://russianspacesystems.ru/wp-content/uploads/2016/08/ICD_GLONASS_eng_v5.1.pdf">GLONASS ICD</a>
 *
 *
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


#include <complex>
#include <ctime>
#include <iostream>
#include "gnss_signal_processing.h"
#include "glonass_gnav_ephemeris.h"


TEST(GlonassGnavEphemerisTest, ComputeGlonassTime)
{
    Glonass_Gnav_Ephemeris gnav_eph;
    gnav_eph.d_yr = 2016;
    gnav_eph.d_N_T = 367;
    boost::posix_time::time_duration t(0, 0, 7560);
    boost::gregorian::date d(gnav_eph.d_yr, 1, 1);
    boost::gregorian::days d2(gnav_eph.d_N_T);
    d = d + d2;

    boost::gregorian::date expected_gdate;
	boost::posix_time::time_duration expected_gtime;

	boost::posix_time::ptime gtime = gnav_eph.compute_GLONASS_time(7560);
	expected_gdate = gtime.date();
	expected_gtime = gtime.time_of_day();

    // Perform assertions of decoded fields
	ASSERT_TRUE(expected_gdate.year() - d.year() < FLT_EPSILON );
	ASSERT_TRUE(expected_gdate.month() - d.month() < FLT_EPSILON );
	ASSERT_TRUE(expected_gdate.day() - d.day() < FLT_EPSILON );
	ASSERT_TRUE(expected_gtime.hours() -  t.hours() < FLT_EPSILON );
	ASSERT_TRUE(expected_gtime.minutes() -  t.minutes() < FLT_EPSILON );
	ASSERT_TRUE(expected_gtime.seconds() -  t.seconds() < FLT_EPSILON );
}
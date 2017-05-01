/*
 * EasyProfiler
 * Copyright (c) 2017 Alik Aslanyan <cplusplus256@gmail.com>
 *
 *
 *
 *    This program is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 3 of the License, or (at
 *    your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

#ifndef TEST_PROFILERFRAME_H
#define TEST_PROFILERFRAME_H

#include <unistd.h>
#include <cxxtest/TestSuite.h>
#include "../src/profilerframe.h"

class TestProfilerFrame : public CxxTest::TestSuite
{
public:
	void testFrameTime()
	{
		ProfilerFrame frame;
		TS_ASSERT_LESS_THAN_EQUALS(frame.getTimeFromStart(), 0.0001);
		TS_ASSERT_LESS_THAN_EQUALS(-0.01, frame.getTimeFromStart());
		usleep(1000 * 1000);
		TS_ASSERT_LESS_THAN_EQUALS(1.000, frame.getTimeFromStart());
		TS_ASSERT_LESS_THAN_EQUALS(frame.getTimeFromStart(), 1.0001);
	}
};

#endif // TEST_PROFILERFRAME_H

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

#ifndef TEST_EASYPROFILER_H
#define TEST_EASYPROFILER_H

#include <unistd.h>
#include <cxxtest/TestSuite.h>
#include "../src/easyprofiler.h"
class TestEasyProfiler : public CxxTest::TestSuite
{
public:
	void testEasyProfiler()
	{
		std::size_t executed_count = 0;
		EasyProfiler profiler([&executed_count](const char *fmt, double time)
		{
			if(strcmp(fmt, "Test string") == 0)
				++executed_count;
		});
		profiler.pushFrame();
		{
			auto time = profiler.popFrame(1, 0.0, "Test string");
			TS_ASSERT_LESS_THAN_EQUALS(time, 0.0001);
		}

		profiler.pushFrame();
		for(auto i = 0; i < 2; ++i)
		{
			profiler.pushFrame();
			usleep(1000 * 1000);
			auto time = profiler.popFrame(1, 0.0, "Test string");
			TS_ASSERT_LESS_THAN_EQUALS(time, 1.01);
			TS_ASSERT_LESS_THAN_EQUALS(0.990, time);
		}
		auto time = profiler.popFrame(1, 0.0, "Test string");
		TS_ASSERT_LESS_THAN_EQUALS(time, 2.01);
		TS_ASSERT_LESS_THAN_EQUALS(1.990, time);

		TS_ASSERT_EQUALS(executed_count, 4);
	}
};

#endif // TEST_EASYPROFILER_H

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


#include "main.h"
#include "helper/config.h"

#include <cmath>

#include <unistd.h>
#include <sys/select.h>

cell AMX_NATIVE_CALL ep_start(AMX*, cell*)
{
	profiler->pushFrame();
	return 1;
}

cell AMX_NATIVE_CALL ep_end(AMX *amx, cell *params)
{
	int dummy_length;
	auto count = static_cast<std::size_t>(params[1]);
	const char *fmt = MF_GetAmxString(amx, params[2], 0, &dummy_length);

	auto time = profiler->popFrame(count, g_correction, fmt);
	return amx_ftoc(time);
}

cell AMX_NATIVE_CALL ep_sleep(AMX*, cell *params)
{
	float time = amx_ctof(params[1]);
	float integer_part;
	float fraction_part = std::modf(time, &integer_part);

	struct timeval tv;
	tv.tv_usec = std::min(__suseconds_t(fraction_part * 1000000),
								 __suseconds_t(1000000 - 1)
								 );
	tv.tv_sec = __time_t(integer_part);

	return select(0, nullptr, nullptr, nullptr, &tv);
}

cell AMX_NATIVE_CALL ep_set_correction(AMX*, cell *params)
{
	g_correction = static_cast<double>(amx_ctof(params[1]));
	return 1;
}

cell AMX_NATIVE_CALL ep_end_and_set_correction(AMX *amx, cell *params)
{
	auto count = static_cast<std::size_t>(params[1]);
	auto time = profiler->popFrame(count, 0.0, nullptr);
	if(time > 0.0)
	{
		g_correction = -time * 2;

		int dummy_length;
		const char *fmt = MF_GetAmxString(amx, params[2], 0, &dummy_length);
		profiler->getPrintHandler()(fmt, -g_correction);
	}
	return amx_ftoc(g_correction);
}


cell AMX_NATIVE_CALL ep_dummy_call(AMX*, cell*)
{
	return 1;
}

void OnAmxxAttach()
{
	g_correction = 0.0;
	profiler = new EasyProfiler([](const char *fmt, double time)
	{
		MF_Log(fmt, time);
	});
	MF_AddNatives(ep_exports);
}

void OnAmxxDetach()
{
	delete profiler;
	profiler = nullptr;
}

void StartFrame()
{

}

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

#include "easyprofiler.h"

EasyProfiler::EasyProfiler(const PrintHandler &printHandler)
	: printHandler_(printHandler)
{
}

void EasyProfiler::setPrintHandler(const PrintHandler &newHandler)
{
	printHandler_ = newHandler;
}

const EasyProfiler::PrintHandler &EasyProfiler::getPrintHandler() const
{
	return printHandler_;
}

void EasyProfiler::pushFrame()
{
	stack_.push({});
}

double EasyProfiler::popFrame(std::size_t count/*= 0L*/,
										double correction/* = 0.0*/,
										const char *fmt/* = nullptr*/)
{
	auto time =
			stack_.top().getTimeFromStart() / std::max(count, std::size_t(1)) + correction;
	stack_.pop();
	if(fmt && fmt[0] && printHandler_)
		printHandler_(fmt, time);
	return time;
}

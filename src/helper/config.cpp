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

#include <string>
#include <stdexcept>

#include "config.h"
#include "stringutils.h"

#include <fstream>

Config::Config(const std::string &path)
	:
		path_(path)
{
	if(!load())
		throw std::runtime_error("Unable to load config file: " + path_);
}

bool Config::load()
{
	std::ifstream file;
	file.open(path_);

	if(!file)
		file.open(path_, std::ios::out | std::ios::in | std::ios::trunc);

	if(!file)
		return false;

	minimumTimeBetweenFrames_ = 0.0;

	for(std::string line; std::getline(file, line);)
	{
		line = StringUtils::trim(StringUtils::removeComments(line));
		if(line.empty())
			continue;

		std::size_t pos = line.find_first_not_of('=');
		if(pos != std::string::npos && pos > 1 && pos < line.size())
		{
			auto key = StringUtils::trim(line.substr(0, pos - 1));
			auto value = line.substr(pos + 1, std::string::npos);

			if(key == "minimum_time_between_frames")
			{
				minimumTimeBetweenFrames_ = std::stod(value);
				return true;
			}
		}
	}

	return false;
}

const std::string &Config::getPath() const
{
	return path_;
}

void Config::setPath(const std::string &path)
{
	path_ = path;
}

double Config::getMinimumTimeBetweenFrames() const
{
	return minimumTimeBetweenFrames_;
}

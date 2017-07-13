#include <string>
#include <stdexcept>
#include "config.h"

Config::Config(const std::string &path)
	:
		path_(path)
{
	if(!load())
		throw std::runtime_error("Unable to load config file: " + path_);
}

bool Config::load()
{

}

const std::string &Config::getPath() const
{
	return path_;
}

void Config::setPath(const std::string &path)
{
	path_ = path;
}

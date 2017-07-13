#ifndef EASYPROFILER_CONFIG_H
#define EASYPROFILER_CONFIG_H

#include <string>

class Config
{
public:
	Config(const std::string &path);
	bool load();

	const std::string &getPath() const;
	void setPath(const std::string &path);
private:
	std::string path;
};


#endif //EASYPROFILER_CONFIG_H

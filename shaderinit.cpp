#include "geng.hpp"

bool	ShaderScr::checkfile(const std::string& filepath)
{
	bool	success;

	success = true;
	file.open(filepath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filepath << std::endl;
		return success = false;
	}
	while (std::getline(file, line))
		std::cout << line << std::endl;
	file.close();
	std::cout << "File is OK" << std::endl;
	return success;
}

unsigned	int	ShaderScr::make_module(const std::string& filepath, unsigned int module_type)
{
	file.open(filepath);
	while (std::getline(file, line))
	{
		bufferedLines << line << "\n";
	}
}

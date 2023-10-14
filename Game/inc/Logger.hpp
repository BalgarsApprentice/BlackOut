#pragma once

#include <fstream>

class Logger
{
public:
	Logger();
	~Logger();

	void write(const std::string& a_Message);

private:
	std::ofstream m_Stream;
};
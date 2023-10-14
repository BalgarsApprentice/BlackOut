#include <Logger.hpp>

Logger::Logger()
	: m_Stream("BlackOut_log.txt")
{
}

Logger::~Logger()
{
}

void Logger::write(const std::string &a_Message)
{
	m_Stream << a_Message << std::endl;
}
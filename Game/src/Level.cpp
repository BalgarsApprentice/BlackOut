#include <Level.hpp>


Level::Level() = default;

const int* Level::getMap() const
{
	return map;
}
#pragma once

template <typename TYPE>
class Singleton
{
public:
	static TYPE& GetInstance()
	{
		static TYPE instance;
		return instance;
	}

private:
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
	~Singleton() = default;
};
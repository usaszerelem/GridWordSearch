#pragma once
class CHelper
{
public:
	inline CHelper() {}
	inline ~CHelper() {}

	static void TrimWhiteSpace(std::string& x);
	static string ToLower(std::string src);
	static string ToUpper(std::string src);
};


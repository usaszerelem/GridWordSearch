#include "stdafx.h"
using namespace std;

// ---------------------------------------------------------------------------

void CHelper::TrimWhiteSpace(std::string & str)
{
	unsigned int uStartIndex = 0;
	unsigned int uEndIndex = str.length();

	// Leading
	while (isspace(str[uStartIndex]))
	{
		uStartIndex++;
	}

	// Trailing
	while (uEndIndex > uStartIndex && isspace(str[uEndIndex - 1]))
	{
		uEndIndex--;
	}

	if (uStartIndex != uEndIndex)
	{
		str = str.substr(uStartIndex, uEndIndex);
	}
}

// ---------------------------------------------------------------------------

string CHelper::ToLower(std::string src)
{
	string dst;

	// Allocate the destination space
	dst.resize(src.size());

	// Convert the source string to lower case storing the result in
	// destination string
	std::transform(src.begin(), src.end(), dst.begin(), ::tolower);

	return(dst);
}

// ---------------------------------------------------------------------------

string CHelper::ToUpper(std::string src)
{
	string dst;

	// Allocate the destination space
	dst.resize(src.size());

	// Convert the source string to lower case storing the result in
	// destination string
	std::transform(src.begin(), src.end(), dst.begin(), ::toupper);

	return(dst);
}

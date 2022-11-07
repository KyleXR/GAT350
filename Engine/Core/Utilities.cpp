#include "Utilities.h" 
#include <algorithm> 

namespace neu
{
	std::string ToLower(const std::string& str)
	{
		std::string lower{};
		// convert string characters to lower case 
		//std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {return std::tolower(c); });
		for (int i = 0; i < str.size(); i++)
		{
			lower += tolower(str[i]);
		}

		return lower;
	}

	std::string ToUpper(const std::string& str)
	{
		std::string upper{};
		// convert string characters to upper case 
		//std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) {return std::toupper(c); });
		for (int i = 0; i < str.size(); i++)
		{
			upper += toupper(str[i]);
		}

		return upper;
	}

	bool CompareIgnoreCase(const std::string& str1, const std::string& str2)
	{
		// if string lengths don't match return false 
		if (str1.size() != str2.size())
		{
			return false;
		}

		if (ToLower(str1) != ToLower(str2)) return false;
		// returns false if string characters aren't equal 
		return true;
	}
}
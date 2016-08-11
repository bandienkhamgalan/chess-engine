#include "Helpers.h"
#include <cctype>

namespace Chess
{
	namespace Helpers
	{
		using namespace std;

		string trimmed(const string& toTrim, const string& whitespace)
		{
			const auto firstNonWhitespace = toTrim.find_first_not_of(whitespace);
			if (firstNonWhitespace == std::string::npos)
				return "";
			const auto lastNonWhitespace = toTrim.find_last_not_of(whitespace);
			return toTrim.substr(firstNonWhitespace, lastNonWhitespace - firstNonWhitespace + 1);
		}

		string lower(const string& toConvert)
		{
			string toReturn { toConvert };
			for (auto cur = toReturn.begin(); cur != toReturn.end(); cur++)
				*cur = tolower(*cur);
			return toReturn;
		}
	}
}
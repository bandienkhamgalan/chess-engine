#include "Helpers.hpp"
#include <cctype>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace Chess
{
	namespace Helpers
	{
		using namespace std;

		string trimmed(const string& toTrim)
		{
			auto itr = toTrim.cbegin();
			while (true)
			{
				if(itr == toTrim.cend())
					return "";

				if(!isspace(*itr))
					break;

				++itr;
			}
			
			auto ritr = toTrim.crbegin();
			while (true)
			{
				if(!isspace(*ritr))
					break;
				++ritr;
			}

			return string(itr, ritr.base());
		}

		string lower(const string& toConvert)
		{
			string toReturn { toConvert };
			for (auto cur = toReturn.begin(); cur != toReturn.end(); cur++)
				*cur = tolower(*cur);
			return toReturn;
		}

		vector<string> split(const string& toSplit)
		{
			istringstream stream(toSplit);
			vector<string> toReturn;
			copy(istream_iterator<string>(stream), istream_iterator<string>(), back_inserter(toReturn));
			return toReturn;
		}
	}
}
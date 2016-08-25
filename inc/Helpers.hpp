#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace Chess
{
	namespace Helpers
	{
		std::string trimmed(const std::string& toTrim);
		std::string lower(const std::string& toConvert);

		template<typename T>
		void sprintinternal(std::stringstream& ss, const T& toPrint) {
			ss << toPrint;
		}

		template<typename T, typename... Args>
		void sprintinternal(std::stringstream& ss, const T& toPrint, const Args&... rest) {
			ss << toPrint;
			sprintinternal(ss, rest...);
		} 

		template<typename... Args>
		std::string sprint(const Args&... rest) {
			std::stringstream ss;
			sprintinternal(ss, rest...);
			return ss.str();
		}

		std::vector<std::string> split(const std::string& toSplit);
	}
}
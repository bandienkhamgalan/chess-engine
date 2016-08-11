#pragma once

#include <string>

namespace Chess
{
   namespace Helpers
   {
	  std::string trimmed(const std::string& toTrim, const std::string& whitespace = " \t\n\r");
	  std::string lower(const std::string& toConvert);
   }
}
#pragma once
#include <memory>
#include <string>

namespace Chess
{
namespace IO
{
	class IFENParserDelegate;
	class IFENParser
	{
	public:
		virtual ~IFENParser() {};
		virtual void BeginParsing() = 0;
		virtual void SetDelegate(std::shared_ptr<IFENParserDelegate> delegate) = 0;
		virtual bool operator==(const IFENParser& toCompare)
		{
			return this == &toCompare;
		}
		virtual bool operator!=(const IFENParser& toCompare)
		{
			return this != &toCompare;
		}
	};
}
}
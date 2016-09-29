#pragma once
#include <iostream>
#include <string>
#include <memory>

namespace Chess
{
	class Location
	{
	public:
		enum AlgebraicLocation : int8_t;
		enum File : int8_t;

		Location() = delete;
		Location(const AlgebraicLocation& location);
		Location(const File& file, const int8_t rank);
		Location(const int8_t file, const int8_t rank);
		Location(const std::string& location);

		enum File : int8_t
		{
			a = 1,
			b,
			c,
			d,
			e,
			f,
			g,
			h
		};

		enum AlgebraicLocation : int8_t
		{
			UNDEFINED,
			a8, b8, c8, d8, e8, f8, g8, h8,
			a7, b7, c7, d7, e7, f7, g7, h7,
			a6, b6, c6, d6, e6, f6, g6, h6,
			a5, b5, c5, d5, e5, f5, g5, h5,
			a4, b4, c4, d4, e4, f4, g4, h4,
			a3, b3, c3, d3, e3, f3, g3, h3,
			a2, b2, c2, d2, e2, f2, g2, h2,
			a1, b1, c1, d1, e1, f1, g1, h1, MAX
		};

		template <typename Func>
		static inline void for_each(Func callback)
		{
			for(int current = static_cast<int>(AlgebraicLocation::a8) ; current <= static_cast<int>(AlgebraicLocation::h1) ; current++ )
			{
				callback(Location(static_cast<AlgebraicLocation>(current)));
			}
		}

		File GetFile() const;
		int8_t GetRank() const;

		bool operator <(const Location& toCompare) const;
		bool operator ==(const Location& toCompare) const;
		bool operator ==(const AlgebraicLocation& toCompare) const;
		bool operator !=(const Location& toCompare) const;
		bool operator !=(const AlgebraicLocation& toCompare) const;
		operator int() const;
		operator std::string() const;
	private:
		AlgebraicLocation location;
		static AlgebraicLocation fromString(const std::string& toConvert);
		static AlgebraicLocation fromFileAndRank(const int8_t file, const int8_t rank);
	};

	std::ostream& operator<<(std::ostream& output, const Location& location);
}
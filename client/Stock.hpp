//
// stock.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SERIALIZATION_STOCK_HPP
#define SERIALIZATION_STOCK_HPP

#include <string>

namespace s11n_example {

	/// Structure to hold information about a single stock.
	struct stock
	{
		std::string name;
		double number;
	

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & name;
			ar & nummber;
		}
	};

} // namespace s11n_example

#endif // SERIALIZATION_STOCK_HPP
#pragma once
// ProgramTools Functions only!

// C++ Standard Libraries
#include<algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include<chrono>
#include<cmath>
#include <cstdarg>
#include<cstdlib>
#include <format>
#include <forward_list>
#include<fstream>
#include<iomanip>
#include<iostream>
#include <iterator>
#include <limits>
#include<list>
#include <numeric>
#include<random>
#include <regex>
#include <span>
#include<sstream>
#include<stdexcept>
#include<string>
#include<string_view>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include<unordered_map>
#include <utility>
#include<vector>



// User Defined HeaderFiles
#include "/HeaderFiles/programTools.h"
#include "/HeaderFiles/universalEnglish.h"
#include "/HeaderFiles/universalGaming.h"
#include "/HeaderFiles/universalMathPatterns.h"
#include "/HeaderFiles/universalScience.h"
#include "/HeaderFiles/universalTesting.h"

namespace programTools
{
	/****************************************************************************************/
	/* This is a grouped function: characterToNumber() can not be called seperately requires*/
	/* characterPrinter() calls characterToNumber()                                         */
	/****************************************************************************************/

	inline void characterToNumber(double x)
	{
		std::cout << x << '\n';

	}
	inline void characterPrinter()
	{
		char input{ };
		std::cout << "This simple program will convert your symbol or character into a ASCII letter code. ";
		std::cout << "Please enter a number, character or symbol: " << '\n';
		std::cin >> input;

		characterToNumber(input);

	}
	/*** End of grouped function! */
	/******************************************************************************************/

	// Overloaded function to get a users input: either int or double allowed.
	inline int getValueFromUserReturn(int input)
	{ // this function will run as long as the user does not enter a non-number
		std::cout << "To terminate: (type in -1) " << '\n';
		while (true)
		{
			std::cout << "\nEnter an integer: " << '\n';
			std::cin >> input;

			if (input == -1)
			{
				std::cout << "That is a terminating character! " << '\n';
				return false;
			}

			else
			{
				std::cout << "\nInput = " << input;

			}
		}
		return input;
	}

	inline double getValueFromUserReturn(double input)
	{
		// this function will run as long as the user does not enter a non-number

		// this function will run as long as the user does not enter a non-number
		std::cout << "To terminate: (type in -1) " << '\n';
		while (true)
		{
			std::cout << "\nEnter an integer: " << '\n';
			std::cin >> input;

			if (input == -1)
			{
				std::cout << "That is a terminating character! " << '\n';
				return false;
			}

		}
		return input;
	}

	// ignoreLine() This function will ignore the rest of an input stream
	inline void ignoreLine()
	{ // ie: 7*9+3, only the 7 would be preserved with this function.
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	// pauseConsole() a function to pause the console and wait for a return input
	inline void pauseConsole()
	{
		// Reset any error flags
		std::cin.clear();

		// Ignore any characters in the input buffer until we find a newline
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cout << "Please Press any Key to continue . . . (Preferably Enter)\n";
		// Get one more character from the user 
		// (Waits for the user to press enter)
		// std::cin.get();
		
	}
}
// includes, using, etc
#pragma once
#include <chrono>

// TIME, CLOCK, AND DURATION ALIASING.
using ullong = unsigned long long;
using nanoseconds = std::chrono::nanoseconds;

// Expected use: seconds = nanoseconds * NANO_TO_SECONDS
static const double NANO_TO_SECONDS = 0.000000001;

// Expected use: nanoseconds = seconds * NANO_IN_SECONDS
static const ullong NANO_IN_SECONDS = 1000000000ULL;

// namespace age for use with time
namespace age
{
	using clock = std::chrono::high_resolution_clock;
	using time = std::chrono::time_point<clock>;
}
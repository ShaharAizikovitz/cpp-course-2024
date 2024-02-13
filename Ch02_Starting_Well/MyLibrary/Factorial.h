#pragma once

/// <summary>
/// Factorials the specified number.
/// </summary>
/// <param name="number">The number.</param>
/// <returns></returns>
unsigned int Factorial(unsigned int number) {
	return number <= 1 ? number : Factorial(number - 1)*number;
}

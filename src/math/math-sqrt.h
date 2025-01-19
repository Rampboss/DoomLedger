#pragma once

/**
 * @brief Fast Inverse Square Root using bit-level hacking and Newton's method
 * 
 * @param x The input number for which the inverse square root is to be calculated.
 * @return The fast inverse square root of the input number.
 */
float fast_inv_sqrt(float x);

/**
 * @brief Optimized square root function.
 * 
 * @param number The input value for which the square root is to be computed.
 * @return The square root of the input number, or 0 if the input is less than or equal to 0.
 */
float sqrt_optimized(float number);


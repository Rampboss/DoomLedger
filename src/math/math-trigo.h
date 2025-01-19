#pragma once
#include <stdint.h>

#define TERMS 10
#define PI 3.14159265358979323846

/**
 * @brief Computes the floating-point remainder of dividing x by y.
 *
 *
 * @param x The dividend (numerator).
 * @param y The divisor (denominator). If y is 0, the function returns x as-is.
 * @return The remainder of x divided by y, or x if y is 0.
 */
double custom_fmod(double v, double d);

/**
 * @brief Precomputes odd powers of a given base and stores them in an array.
 *
 *
 * @param x The base value for which odd powers are computed.
 * @param powers Pointer to an array of doubles, with at least TERMS elements,
 * where each element `powers[i]` will store `x^(2*i + 1)`.
 */
void precompute_powers(double x, double *powers);

/**
 * @brief Precomputes factorial values for odd factorials and stores them in an array.
 *
 *
 * @param factorials Pointer to an array of doubles, with at least TERMS elements,
 * where each element `factorials[i]` will store the factorial of (2*i + 1), i.e., (2*i + 1)!.
 */
void precompute_factorials(double *factorials);


/**
 * @brief Approximates the sine of an angle in radians using a Taylor series expansion.
 *
 * @param x The angle in radians for which to compute the sine.
 * @return The approximate sine of the angle `x`.
 */
double sine(double x);

/**
 * @brief Computes the cosine of an angle in radians by using the sine function.
 *
 * @param x The angle in radians for which to compute the cosine.
 * @return The cosine of the angle `x`.
 */
double cosine(double x);

/**
 * @brief Polynomial approximation of the arctangent (atan) function.
 * 
 * 
 * @param z The value for which the arctangent is to be computed.
 * @return The approximate arctangent of z.
 */
double atan_approx(double z);

/**
 * @brief Custom implementation of the atan2 function.
 * 
 * 
 * @param y The y-coordinate (numerator).
 * @param x The x-coordinate (denominator).
 * @return The angle θ in radians, where θ = atan2(y, x), taking into account the quadrant.
 */
double atan2_custom(double y, double x);
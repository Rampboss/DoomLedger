#include "math/math-trigo.h"

double custom_fmod(double x, double y) {
    if (y == 0.0) {
        return x;  // Handle division by zero case
    }
    int quotient = (int) (x / y);
    return x - (quotient * y);
}

void precompute_powers(double x, double *powers) {
    powers[0] = x;  // First power is just x
    for (int i = 1; i < TERMS; i++) {
        powers[i] = powers[i - 1] * x * x;  // x^3, x^5, etc.
    }
}

void precompute_factorials(double *factorials) {
    factorials[0] = 1;  // 1 for 3!
    double fact = 1;
    for (int i = 1; i < TERMS; i++) {
        fact *= (2 * i) * (2 * i + 1);  // Factorial for (2n+1)!
        factorials[i] = fact;
    }
}

double sine(double x) {
    // Normalize x to the range [-pi, pi] using custom fmod
    x = custom_fmod(x, 2 * PI);
    if (x > PI) {
        x -= 2 * PI;
    }

    double powers[TERMS];      // Array to store precomputed powers of x
    double factorials[TERMS];  // Array to store precomputed factorials

    // Precompute values
    precompute_powers(x, powers);
    precompute_factorials(factorials);

    // Compute sine using precomputed values
    double sin_x = 0;
    int sign = 1;  // Alternating sign

    for (int n = 0; n < TERMS; n++) {
        sin_x += sign * powers[n] / factorials[n];  // Add each term to the result
        sign = -sign;                               // Flip sign for the next term
    }

    return sin_x;
}

double cosine(double x) {
    return sine(PI / 2 - x);
}

double atan_approx(double z) {
    if (z == 0.0) return 0.0;

    double z2 = z * z;
    double result = z;
    double term = z;
    int sign = -1;
    
    // Use the first few terms of the Taylor series
    for (int i = 3; i <= 11; i += 2) {
        term *= z2;
        result += sign * term / i;
        sign = -sign;
    }
    
    return result;
}

double atan2_custom(double y, double x) {
    if (x > 0.0) {
        return atan_approx(y / x);  // If x > 0, use the approximation
    } else if (x < 0.0) {
        if (y >= 0.0) {
            return atan_approx(y / x) + PI;  // Add pi for the second and third quadrants
        } else {
            return atan_approx(y / x) - PI;  // Subtract pi for the third and fourth quadrants
        }
    } else {
        if (y > 0.0) {
            return PI / 2;  // If x == 0 and y > 0, the result is pi/2
        } else if (y < 0.0) {
            return -PI / 2; // If x == 0 and y < 0, the result is -pi/2
        } else {
            return 0.0;  // If both x and y are 0, return 0
        }
    }
}
// Basic math utilities

#ifndef BMU_H
#define BMU_H

#include <complex.h>

typedef struct {
    float m[2][2];
} Matrix2x2;

// Algebra

float complex* polynomial_equation(int degree, ...);
float complex* exponential_equation(float base, float result);

// Matrix
Matrix2x2 matrix_create(float m00, float m01, float m10, float m11);
Matrix2x2 matrix_add(Matrix2x2 a, Matrix2x2 b);
Matrix2x2 matrix_subtract(Matrix2x2 a, Matrix2x2 b);
Matrix2x2 matrix_multiply_scalar(Matrix2x2 a, float scalar);
Matrix2x2 matrix_multiply(Matrix2x2 a, Matrix2x2 b);
float matrix_determinant(Matrix2x2 a);
Matrix2x2 matrix_inverse(Matrix2x2 a);
int matrix_equals(Matrix2x2 a, Matrix2x2 b, float tolerance);

#endif

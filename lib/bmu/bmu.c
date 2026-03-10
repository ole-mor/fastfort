// Basic math utilities

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "bmu.h"

// Geometry
float pytogorasL(float x, float y){
    float l = (x > y) ? x : y;
    float s = (x > y) ? y : x;
    return sqrtf(powf(l, 2) - powf(s, 2));
}

float pytogorasH(float x, float y){
    return sqrtf(powf(x, 2) + powf(y, 2));
}

// Algebra
float complex* polynomial_equation(int degree, ...) {
    va_list args;
    va_start(args, degree);
    
    float* coeffs = malloc((degree + 1) * sizeof(float));
    for (int i = 0; i <= degree; i++) {
        coeffs[i] = va_arg(args, double);
    }
    va_end(args);
    
    float complex* roots = malloc((degree + 1) * sizeof(float complex));
    
    if (degree == 1) {
        roots[0] = -coeffs[0] / coeffs[1];
    } else if (degree == 2) {
        float disc = coeffs[1] * coeffs[1] - 4 * coeffs[2] * coeffs[0];
        float complex sqrt_disc = csqrtf(disc + 0.0f * I);
        roots[0] = (-coeffs[1] + sqrt_disc) / (2 * coeffs[2]);
        roots[1] = (-coeffs[1] - sqrt_disc) / (2 * coeffs[2]);
    } else if (degree == 3) {
        float b_norm = coeffs[2] / coeffs[3];
        float c_norm = coeffs[1] / coeffs[3];
        float d_norm = coeffs[0] / coeffs[3];
        
        float p = c_norm - (b_norm * b_norm) / 3;
        float q = 2 * (b_norm * b_norm * b_norm) / 27 - (b_norm * c_norm) / 3 + d_norm;
        
        float complex discriminant = (q * q / 4) + (p * p * p / 27);
        float complex sqrt_disc = csqrtf(discriminant);
        
        float complex C = cpowf((-q / 2) + sqrt_disc, 1.0f / 3.0f);
        
        if (cabsf(C) < 1e-10) {
            C = cpowf((-q / 2) - sqrt_disc, 1.0f / 3.0f);
        }
        
        float complex omega = -0.5f + 0.86602540378f * I;
        float b_shift = b_norm / 3;
        
        roots[0] = C + p / (3 * C) - b_shift;
        roots[1] = omega * C + p / (3 * omega * C) - b_shift;
        roots[2] = omega * omega * C + p / (3 * omega * omega * C) - b_shift;
    } else if (degree == 4) {
        float b_norm = coeffs[3] / coeffs[4];
        float c_norm = coeffs[2] / coeffs[4];
        float d_norm = coeffs[1] / coeffs[4];
        float e_norm = coeffs[0] / coeffs[4];
        
        float p = c_norm - 3 * (b_norm * b_norm) / 8;
        float q = (b_norm * b_norm * b_norm) / 8 - (b_norm * c_norm) / 2 + d_norm;
        float r = -3 * (b_norm * b_norm * b_norm * b_norm) / 256 + (b_norm * b_norm * c_norm) / 16 - (b_norm * d_norm) / 4 + e_norm;
        
        float b_norm_2p = 2 * p;
        float c_norm_pp = p * p - 4 * r;
        float d_norm_qq = -q * q;
        
        float b_cubic = b_norm_2p;
        float c_cubic = c_norm_pp;
        float d_cubic = d_norm_qq;
        
        float complex* cubic_helper = malloc(3 * sizeof(float complex));
        va_list dummy;
        va_start(dummy, degree);
        
        float disc_c = c_cubic * c_cubic - 4 * b_cubic * d_cubic;
        float complex sqrt_disc_c = csqrtf(disc_c + 0.0f * I);
        float complex C = cpowf((-c_cubic / 2) + sqrt_disc_c, 1.0f / 3.0f);
        
        if (cabsf(C) < 1e-10) {
            C = cpowf((-c_cubic / 2) - sqrt_disc_c, 1.0f / 3.0f);
        }
        
        float complex sqrt_y = csqrtf(C);
        float complex sqrt_term1 = csqrtf(p + 2 * C + q / sqrt_y);
        float complex sqrt_term2 = csqrtf(p + 2 * C - q / sqrt_y);
        
        roots[0] = sqrt_term1 - b_norm / 4;
        roots[1] = -sqrt_term1 - b_norm / 4;
        roots[2] = sqrt_term2 - b_norm / 4;
        roots[3] = -sqrt_term2 - b_norm / 4;
    } else { // Durand-Kerner if above quartic
        for (int i = 0; i <= degree; i++) {
            roots[i] = cosf(2 * 3.14159265f * i / degree) + sinf(2 * 3.14159265f * i / degree) * I;
        }
        
        for (int iter = 0; iter < 100; iter++) {
            int converged = 1;
            
            for (int i = 0; i <= degree; i++) {
                float complex p = 0;
                
                for (int j = degree; j >= 0; j--) {
                    p = p * roots[i] + coeffs[j];
                }
                
                float complex divisor = coeffs[degree];
                for (int j = 0; j <= degree; j++) {
                    if (i != j) {
                        divisor *= (roots[i] - roots[j]);
                    }
                }
                
                if (cabsf(divisor) < 1e-15) continue;
                
                float complex correction = p / divisor;
                float complex new_root = roots[i] - correction;
                
                if (cabsf(new_root - roots[i]) > 1e-10) {
                    converged = 0;
                }
                
                roots[i] = new_root;
            }
            
            if (converged) break;
        }
    }
    
    free(coeffs);
    return roots;
}

float complex* exponential_equation(float base, float result) {
    float complex* res = malloc(sizeof(float complex));
    res[0] = clogf(result + 0.0f * I) / clogf(base + 0.0f * I);
    return res;
}

// Matrix
Matrix2x2 matrix_create(float m00, float m01, float m10, float m11) {
    Matrix2x2 mat = {{{m00, m01}, {m10, m11}}};
    return mat;
}

Matrix2x2 matrix_add(Matrix2x2 a, Matrix2x2 b) {
    Matrix2x2 result;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result.m[i][j] = a.m[i][j] + b.m[i][j];
        }
    }
    return result;
}

Matrix2x2 matrix_subtract(Matrix2x2 a, Matrix2x2 b) {
    Matrix2x2 result;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result.m[i][j] = a.m[i][j] - b.m[i][j];
        }
    }
    return result;
}

Matrix2x2 matrix_multiply_scalar(Matrix2x2 a, float scalar) {
    Matrix2x2 result;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result.m[i][j] = a.m[i][j] * scalar;
        }
    }
    return result;
}

Matrix2x2 matrix_multiply(Matrix2x2 a, Matrix2x2 b) {
    Matrix2x2 result = matrix_create(0, 0, 0, 0);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return result;
}

float matrix_determinant(Matrix2x2 a) {
    return a.m[0][0] * a.m[1][1] - a.m[0][1] * a.m[1][0];
}

Matrix2x2 matrix_inverse(Matrix2x2 a) {
    float det = matrix_determinant(a);
    
    if (fabs(det) < 1e-10) {
        return matrix_create(0, 0, 0, 0);
    }
    
    float inv_det = 1.0f / det;
    return matrix_create(
        a.m[1][1] * inv_det,
        -a.m[0][1] * inv_det,
        -a.m[1][0] * inv_det,
        a.m[0][0] * inv_det
    );
}

int matrix_equals(Matrix2x2 a, Matrix2x2 b, float tolerance) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (fabs(a.m[i][j] - b.m[i][j]) > tolerance) {
                return 0;
            }
        }
    }
    return 1;
}

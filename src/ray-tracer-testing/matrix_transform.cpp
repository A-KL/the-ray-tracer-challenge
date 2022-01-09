#include "CppUnitTest.h"

#include <iostream>
#include <list>
#include <cassert>

#include "../ray-tracer-core/Vector3D.h"
#include "../ray-tracer-core/Point3D.h"

#include "../ray-tracer-core/Matrix.h"
#include "../ray-tracer-core/MatrixOps.hpp"
#include "../ray-tracer-core/MatrixTransform.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ray_tracer_testing
{
	TEST_CLASS(matrix_transform_test)
	{
	public:	
		TEST_METHOD(matrix_scaling)
		{	
			// Set up
			Matrix<int, 4, 4> m0;

			int point[4] = { -4, 6, 8, 1 };
			int result[4];

			// Act
			matrix_scale(2, 3, 4, m0);
			matrix_mul(m0, point, result);

			// Assert
			assert(-8 == result[0]);
			assert(18 == result[1]);
			assert(32 == result[2]);
		}

		TEST_METHOD(matrix_rotation)
		{
			// Set up
			Matrix<double, 4, 4> half_quarter, full_quarter;

			double point[4] = { 0, 1, 0, 1 };
			double result[4];

			// Act
			matrix_rotate_x(PI / 4, half_quarter);
			matrix_rotate_x(PI / 2, full_quarter);

			matrix_mul(full_quarter, point, result);

			// Assert
			assert(0 == result[0]);
			assert(0 == result[1]);
			assert(1 == result[2]);
		}

		TEST_METHOD(matrix_translation_with_point)
		{
			// Set up
			Matrix<int, 4, 4> m0;
			int point[4] = { -3, 4, 5, 1 };
			int result[4];

			matrix_translate(5, -3, 2, m0);

			// Act
			matrix_mul(m0, point, result);

			// Assert
			assert(2 == result[0]);
			assert(1 == result[1]);
			assert(7 == result[2]);
		}

		TEST_METHOD(matrix_translation_with_inverse)
		{
			// Set up
			Matrix<int, 4, 4> m0, inverted_m0;
			int point[4] = { -3, 4, 5, 1 };
			int result[4];

			matrix_translate(5, -3, 2, m0);

			// Act
			matrix_inverse(m0, inverted_m0);
			matrix_mul(inverted_m0, point, result);

			// Assert
			assert(-8 == result[0]);
			assert(7 == result[1]);
			assert(3 == result[2]);
		}

		TEST_METHOD(matrix_translation_with_vector)
		{
			// Set up
			Matrix<int, 4, 4> m0;

			int vector[4] = { -3, 4, 5, 0 };
			int result[4];

			matrix_translate(5, -3, 2, m0);

			// Act
			matrix_mul(m0, vector, result);

			// Assert
			assert(vector[0] == result[0]);
			assert(vector[1] == result[1]);
			assert(vector[2] == result[2]);
		}
	};
}

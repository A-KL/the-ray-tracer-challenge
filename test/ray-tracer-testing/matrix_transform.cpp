#include "CppUnitTest.h"

#include <iostream>
#include <list>
#include <cassert>

#include "../../lib/ray-tracer-core/Primitive3D.h"
#include "../../lib/ray-tracer-core/Vector3D.h"
#include "../../lib/ray-tracer-core/Point3D.h"

#include "../../lib/ray-tracer-core/Matrix.hpp"
#include "../../lib/ray-tracer-core/MatrixOps.hpp"
#include "../../lib/ray-tracer-core/MatrixTransform.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ray_tracer_testing
{
	TEST_CLASS(matrix_transform_test)
	{
	public:	
		TEST_METHOD(matrix_scaling)
		{	
			// Set up
			Matrix4 m0;

			int point[4] = { -4, 6, 8, 1 };
			int result[4];

			// Act
			matrix_scale(2, 3, 4, m0);
			matrix_mul(m0, point, result);

			// Assert
			Assert::AreEqual(-8, result[0]);
			Assert::AreEqual(18, result[1]);
			Assert::AreEqual(32, result[2]);
		}

		TEST_METHOD(matrix_rotation)
		{
			// Set up
			Matrix<int, 4, 4> half_quarter, full_quarter;

			int point[4] = { 0, 1, 0, 1 };
			int result[4];

			// Act
			matrix_rotate_x(M_PI / 4, half_quarter);
			matrix_rotate_x(M_PI / 2, full_quarter);

			matrix_mul(full_quarter, point, result);

			// Assert
			Assert::AreEqual(0, result[0]);
			Assert::AreEqual(0, result[1]);
			Assert::AreEqual(1, result[2]);
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
			Assert::AreEqual(2, result[0]);
			Assert::AreEqual(1, result[1]);
			Assert::AreEqual(7, result[2]);
		}

		TEST_METHOD(matrix_translation_with_inverse)
		{
			// Set up
			Matrix4 m0;
			int point[4] = { -3, 4, 5, 1 };
			int result[4];

			matrix_translate(5, -3, 2, m0);

			// Act
			matrix_mul(m0.Inverse(), point, result);

			// Assert
			Assert::AreEqual(-8, result[0]);
			Assert::AreEqual(7, result[1]);
			Assert::AreEqual(3, result[2]);
		}

		TEST_METHOD(matrix_translation_with_vector)
		{
			// Set up
			Matrix4 m0;

			int vector[4] = { -3, 4, 5, 0 };
			int result[4];

			matrix_translate(5, -3, 2, m0);

			// Act
			matrix_mul(m0, vector, result);

			// Assert
			Assert::AreEqual(vector[0], result[0]);
			Assert::AreEqual(vector[1], result[1]);
			Assert::AreEqual(vector[2], result[2]);
		}
	};
}

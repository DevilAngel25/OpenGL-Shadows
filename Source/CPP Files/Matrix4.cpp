#include "StdAfx.h"
#include "Matrix4.h"

// Constructors

Matrix4::Matrix4(void)
{
	Init(1.0f, 0.0f, 0.0f, 0.0f, 
		 0.0f, 1.0f, 0.0f, 0.0f, 
		 0.0f, 0.0f, 1.0f, 0.0f, 
		 0.0f, 0.0f, 0.0f, 1.0f);		//default matrix.
}

Matrix4::Matrix4(GLfloat r1c1, GLfloat r1c2, GLfloat r1c3, GLfloat r1c4, 
				 GLfloat r2c1, GLfloat r2c2, GLfloat r2c3, GLfloat r2c4,
				 GLfloat r3c1, GLfloat r3c2, GLfloat r3c3, GLfloat r3c4, 
				 GLfloat r4c1, GLfloat r4c2, GLfloat r4c3, GLfloat r4c4)
{
	Init(r1c1, r1c2, r1c3, r1c4, 
		 r2c1, r2c2, r2c3, r2c4, 
		 r3c1, r3c2, r3c3, r3c4,
		 r4c1, r4c2, r4c3, r4c4);
}

Matrix4::Matrix4(const Matrix4& m)
{
	Copy(m);
}

Matrix4::~Matrix4(void)
{
}

// Accessors and mutators

GLfloat Matrix4::GetM(int i, int j) const			//get the value at matrix position
{
	return _mat4Val[i][j];
}

void Matrix4::SetM(int i, int j, float k)		//set the matrix value at position
{
	_mat4Val[i][j] = k;
}


// Methods

void Matrix4::ResetMatrix()					//reset the matrix if needed (to default)
{
	Init(1.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f);
}

void Matrix4::GLfloatToMatrix(GLfloat glf[16])
{
	_mat4Val[0][0] = glf[0], _mat4Val[0][1] = glf[4], _mat4Val[0][2] = glf[8], _mat4Val[0][3] = glf[12];
	_mat4Val[1][0] = glf[1], _mat4Val[1][1] = glf[5], _mat4Val[1][2] = glf[9], _mat4Val[1][3] = glf[13];
	_mat4Val[2][0] = glf[2], _mat4Val[2][1] = glf[6], _mat4Val[2][2] = glf[10], _mat4Val[2][3] = glf[14];
	_mat4Val[3][0] = glf[3], _mat4Val[3][1] = glf[7], _mat4Val[3][2] = glf[11], _mat4Val[3][3] = glf[15];
}
// Operator overloads

Matrix4& Matrix4::operator=(const Matrix4 &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

//Matrix-Matrix multiplication
const Matrix4 Matrix4::operator*(const Matrix4 &other) const
{

	Matrix4 result;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			GLfloat value = 0;
			for(int k = 0; k < 4; k++)
			{
				value += _mat4Val[i][k] * other.GetM(k, j);
			}
			result.SetM(i, j, value);
		}
	}

	return result;
}

// Private methods

void Matrix4::Init(GLfloat r1c1, GLfloat r1c2, GLfloat r1c3, GLfloat r1c4, 
				   GLfloat r2c1, GLfloat r2c2, GLfloat r2c3, GLfloat r2c4,
				   GLfloat r3c1, GLfloat r3c2, GLfloat r3c3, GLfloat r3c4, 
				   GLfloat r4c1, GLfloat r4c2, GLfloat r4c3, GLfloat r4c4)
{
	_mat4Val[0][0] = r1c1, _mat4Val[0][1] = r1c2, _mat4Val[0][2] = r1c3, _mat4Val[0][3] = r1c4;
	_mat4Val[1][0] = r2c1, _mat4Val[1][1] = r2c2, _mat4Val[1][2] = r2c3, _mat4Val[1][3] = r2c4;
	_mat4Val[2][0] = r3c1, _mat4Val[2][1] = r3c2, _mat4Val[2][2] = r3c3, _mat4Val[2][3] = r3c4;
	_mat4Val[3][0] = r4c1, _mat4Val[3][1] = r4c2, _mat4Val[3][2] = r4c3, _mat4Val[3][3] = r4c4;
}

void Matrix4::Copy(const Matrix4& m)
{
	_mat4Val[0][0] = m.GetM(0, 0), _mat4Val[0][1] = m.GetM(0, 1), _mat4Val[0][2] = m.GetM(0, 2), _mat4Val[0][3] = m.GetM(0, 3);
	_mat4Val[1][0] = m.GetM(1, 0), _mat4Val[1][1] = m.GetM(1, 1), _mat4Val[1][2] = m.GetM(1, 2), _mat4Val[1][3] = m.GetM(1, 3);
	_mat4Val[2][0] = m.GetM(2, 0), _mat4Val[2][1] = m.GetM(2, 1), _mat4Val[2][2] = m.GetM(2, 2), _mat4Val[2][3] = m.GetM(2, 3);
	_mat4Val[3][0] = m.GetM(3, 0), _mat4Val[3][1] = m.GetM(3, 1), _mat4Val[3][2] = m.GetM(3, 2), _mat4Val[3][3] = m.GetM(3, 3);
}
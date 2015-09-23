#pragma once
#include <string>
#include "GL\include\glew.h"

//create a class to handle matrices
class Matrix4
{
	public:
		Matrix4(void);
		Matrix4(GLfloat r1c1, GLfloat r1c2, GLfloat r1c3, GLfloat r1c4, 
				GLfloat r2c1, GLfloat r2c2, GLfloat r2c3, GLfloat r2c4,
				GLfloat r3c1, GLfloat r3c2, GLfloat r3c3, GLfloat r3c4, 
				GLfloat r4c1, GLfloat r4c2, GLfloat r4c3, GLfloat r4c4);
		Matrix4(const Matrix4& m);
		~Matrix4(void);

		GLfloat GetM(int, int) const;
		void SetM(int, int, float);

		void ResetMatrix();											//reset matrix values to default	
		void GLfloatToMatrix(GLfloat glf[16]);	

		Matrix4& operator= (const Matrix4 &rhs);

		const Matrix4 operator*(const Matrix4 &other) const;		//matrix multiplied by a matrix
		
	private:
		float _mat4Val[4][4];

		void Init(GLfloat r1c1, GLfloat r1c2, GLfloat r1c3, GLfloat r1c4, 
				  GLfloat r2c1, GLfloat r2c2, GLfloat r2c3, GLfloat r2c4,
				  GLfloat r3c1, GLfloat r3c2, GLfloat r3c3, GLfloat r3c4, 
				  GLfloat r4c1, GLfloat r4c2, GLfloat r4c3, GLfloat r4c4);
		void Copy(const Matrix4& m);
		
};
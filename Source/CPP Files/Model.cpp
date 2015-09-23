#include "StdAfx.h"
#include "Model.h"

// Constructors

Model::Model(void)
{
	Init();
}

Model::Model(const Model& m)
{
	Copy(m);
}

Model::~Model(void)
{
}

// Accessors and mutators

int Model::GetVCount(void) const
{
	return _mVCount;
}
int Model::GetTCount(void) const
{
	return _mTCount;
}
int Model::GetNCount(void) const
{
	return _mNCount;
}
int Model::GetVPCount(void) const
{
	return _mVPCount;
}

//Get Models Vertices
float Model::GetModelVerticeX(int i) const
{
	return _list_mVertices[i]._vX;
}
float Model::GetModelVerticeY(int i) const
{
	return _list_mVertices[i]._vY;
}
float Model::GetModelVerticeZ(int i) const
{
	return _list_mVertices[i]._vZ;
}

float Model::GetModelNormalX(int i) const
{
	return _list_mNormals[i]._nX;
}
float Model::GetModelNormalY(int i) const
{
	return _list_mNormals[i]._nY;
}
float Model::GetModelNormalZ(int i) const
{
	return _list_mNormals[i]._nZ;
}

float Model::GetModelTexCoOrdU(int i) const
{
	return _list_mTexCoOrds[i]._tU;
}
float Model::GetModelTexCoOrdV(int i) const
{
	return _list_mTexCoOrds[i]._tV;
}
float Model::GetModelTexCoOrdW(int i) const
{
	return _list_mTexCoOrds[i]._tW;
}

float Model::GetModelVerticeSpaceU(int i) const
{
	return _list_mVertSpaces[i]._vpU;
}
float Model::GetModelVerticeSpaceV(int i) const
{
	return _list_mVertSpaces[i]._vpV;
}
float Model::GetModelVerticeSpaceW(int i) const
{
	return _list_mVertSpaces[i]._vpW;
}

//set the values
void Model::SetVCount(int i)
{
	_mVCount = i;
}
void Model::SetTCount(int i)
{
	_mTCount = i;
}
void Model::SetNCount(int i)
{
	_mNCount = i;
}
void Model::SetVPCount(int i)
{
	_mVPCount = i;
}

void Model::SetModelVertice(int i, float vx, float vy, float vz)
{
	_list_mVertices.resize(i+1);
	_list_mVertices[i]._vX = vx;
	_list_mVertices[i]._vY = vy;
	_list_mVertices[i]._vZ = vz;
	++_mVCount;
}
void Model::SetModelNormal(int i, float nx, float ny, float nz)
{
	_list_mNormals.resize(i+1);
	_list_mNormals[i]._nX = nx;
	_list_mNormals[i]._nY = ny;
	_list_mNormals[i]._nZ = nz;
	++_mNCount;
}
void Model::SetModelTexCoOrd(int i, float tu, float tv, float tw)
{
	_list_mTexCoOrds.resize(i+1);
	_list_mTexCoOrds[i]._tU = tu;
	_list_mTexCoOrds[i]._tV = tv;
	_list_mTexCoOrds[i]._tW = tw;
	++_mTCount;
}
void Model::SetModelVerticeSpace(int i, float vpu, float vpv, float vpw)
{
	_list_mVertSpaces.resize(i+1);
	_list_mVertSpaces[i]._vpU = vpu;
	_list_mVertSpaces[i]._vpV = vpv;
	_list_mVertSpaces[i]._vpW = vpw;
	++_mVPCount;
}

// Operator overloads
Model& Model::operator=(const Model &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

// Private methods

void Model::Init()
{
	_mVCount = 0, _mTCount = 0, _mNCount = 0, _mVPCount = 0;
}

void Model::Copy(const Model& m)
{

	_mVCount = m.GetVCount(), _mTCount = m.GetTCount(), 
	_mNCount = m.GetNCount(), _mVPCount = m.GetVPCount();

	for(int i = 0; i < m.GetVCount(); i++)
	{
		_list_mVertices[i]._vX = m.GetModelVerticeX(i);
		_list_mVertices[i]._vY = m.GetModelVerticeY(i);
		_list_mVertices[i]._vZ = m.GetModelVerticeZ(i);
	}

	for(int i = 0; i < m.GetNCount(); i++)
	{
		_list_mNormals[i]._nX = m.GetModelNormalX(i);
		_list_mNormals[i]._nY = m.GetModelNormalY(i);
		_list_mNormals[i]._nZ = m.GetModelNormalZ(i);
	}

	for(int i = 0; i < m.GetTCount(); i++)
	{
		_list_mTexCoOrds[i]._tU = m.GetModelTexCoOrdU(i);
		_list_mTexCoOrds[i]._tV = m.GetModelTexCoOrdV(i);
		_list_mTexCoOrds[i]._tW = m.GetModelTexCoOrdW(i);
	}

	for(int i = 0; i < m.GetVPCount(); i++)
	{
		_list_mVertSpaces[i]._vpU = m.GetModelVerticeSpaceU(i);
		_list_mVertSpaces[i]._vpV = m.GetModelVerticeSpaceV(i);
		_list_mVertSpaces[i]._vpW = m.GetModelVerticeSpaceW(i);
	}
}
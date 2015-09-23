#pragma once
#include <string>
#include <vector>
using namespace std;

class Model
{
	public:
		Model(void);
		Model(const Model& m);
		~Model(void);

		int GetVCount(void) const;
		int GetTCount(void) const;
		int GetNCount(void) const;
		int GetVPCount(void) const;

		float GetModelVerticeX(int i) const;
		float GetModelVerticeY(int i) const;
		float GetModelVerticeZ(int i) const;

		float GetModelNormalX(int i) const;
		float GetModelNormalY(int i) const;
		float GetModelNormalZ(int i) const;

		float GetModelTexCoOrdU(int i) const;
		float GetModelTexCoOrdV(int i) const;
		float GetModelTexCoOrdW(int i) const;

		float GetModelVerticeSpaceU(int i) const;
		float GetModelVerticeSpaceV(int i) const;
		float GetModelVerticeSpaceW(int i) const;

		void SetVCount(int i);
		void SetTCount(int i);
		void SetNCount(int i);
		void SetVPCount(int i);

		void SetModelVertice(int i, float vx, float vy, float vz);
		void SetModelNormal(int i, float nx, float ny, float nz);
		void SetModelTexCoOrd(int i, float tu, float tv, float tw);
		void SetModelVerticeSpace(int i, float vu, float vv, float vw);

		Model& operator= (const Model &rhs);

	private:
		int _mVCount, _mTCount, _mNCount, _mVPCount;

		typedef struct { float _vX; float _vY; float _vZ; } _mVertices;
		vector<_mVertices> _list_mVertices;

		typedef struct { float _tV; float _tU; float _tW; } _mTexCoOrds;
		vector<_mTexCoOrds> _list_mTexCoOrds;

		typedef struct { float _nX; float _nY; float _nZ; } _mNormals;
		vector<_mNormals> _list_mNormals;

		typedef struct { float _vpU; float _vpV; float _vpW; } _mVertSpaces;
		vector<_mVertSpaces> _list_mVertSpaces;

		void Init();
		void Copy(const Model& m);
		
};
#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

#include "Model.h"

//create a class to Load an Object file
class LoadObj
{
	public:
		LoadObj(void);
		LoadObj(LPSTR fileName, Model& m);
		LoadObj(const LoadObj& e);
		~LoadObj(void);

		LPSTR GetFN(void) const;

		int GetCVer(void) const;
		int GetCVerTex(void) const;
		int GetCVerTexNor(void) const;
		int GetCVerNor(void) const;

		int GetFaceC(void) const;
		int GetVerC(void) const;
		int GetNorC(void) const;
		int GetTexC(void) const;
		int GetVPC(void) const;

		LoadObj& operator= (const LoadObj &rhs);

	private:
		LPSTR	_fn;
		int		_fCount, _verCount, _texCount, _norCount, _vpCount,
				_countVer, _countVerTex, _countVerTexNor, _countVerNor,
				_modelVer, _modelNor;
		char	_op1, _op2, _char1, _char2, _char3; 
		float	_vx,  _vy,  _vz,
				_nx,  _ny,  _nz,
				_tu,  _tv,  _tw,
				_vpu, _vpv, _vpw;
		int		_ver,  _nor, _tex, _int1, _int2, _int3;
		bool	_bVer, _bVerTex, _bVerTexNor, _bVerNor;

		char _buffer[100];
		int _sizeBuffer;

		//Vert, Tex, Nor, VerSpace Data v
		typedef struct { float _vX; float _vY; float _vZ; } _Vertices;
		vector<_Vertices> _list_Vertices;

		typedef struct { float _tV; float _tU; float _tW; } _TexCoOrds;
		vector<_TexCoOrds> _list_TexCoOrds;

		typedef struct { float _nX; float _nY; float _nZ; } _Normals;
		vector<_Normals> _list_Normals;

		typedef struct { float _vpU; float _vpV; float _vpW; } _VertSpaces;
		vector<_VertSpaces> _list_VertSpaces;

		//Faces v

		typedef struct { int _Ver[3]; } _Ver;		
		vector<_Ver> _list_Ver;

		typedef struct { int _Ver[3]; int _Tex[3]; } _VerTex;		
		vector<_VerTex> _list_VerTex;

		typedef struct { int _Ver[3]; int _Tex[3]; int _Nor[3]; } _VerTexNor;		
		vector<_VerTexNor> _list_VerTexNor;

		typedef struct { int _Ver[3]; int _Nor[3]; } _VerNor;		
		vector<_VerNor> _list_VerNor;

		void Init(LPSTR fn);
		void Copy(const LoadObj& l);
		void OrderFaces(Model& m);	
};

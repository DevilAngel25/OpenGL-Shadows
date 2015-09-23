#include "stdAfx.h"
#include "LoadObj.h"

//CONSTRUCTORS v
LoadObj::LoadObj(void)
{
	Init(_fn);
}

LoadObj::LoadObj(LPSTR fn, Model& m)
{
	Init(fn);
	
	if(fn == "Scene")
	{
		fn = "Objects\\Scene.obj";
	}

	if(fn == "Monkey")
	{
		fn = "Objects\\Monkey.obj";
	}

	if(fn == "Torus")
	{
		fn = "Objects\\Torus.obj";
	}

	if(fn == "Teapot")
	{
		fn = "Objects\\Teapot.obj";
	}

	if(fn == "DetailedSphere")
	{
		fn = "Objects\\DetailedSphere.obj";
	}

	if(fn == "Teddy")
	{
		fn = "Objects\\Teddy.obj";
	}

	if(fn == "Humanoid")
	{
		fn = "Objects\\Humanoid.obj";
	}

	if(fn == "IcoSphere")
	{
		fn = "Objects\\IcoSphere.obj";
	}

	if(fn == "TieFighter")
	{
		fn = "Objects\\TieFighter.obj";
	}

	if(fn == "TieIntercepter")
	{
		fn = "Objects\\TieIntercepter.obj";
	}


	std::ifstream infile(fn, std::ifstream::in);

	while(infile.getline(_buffer, _sizeBuffer))
	{
		std::istringstream iss(_buffer, std::istringstream::in);
		iss>>_op1>>_op2;
		if(_op1 == '#')			
		{
			_vx = 0.0f,	_vy = 0.0f,	_vz = 0.0f,
			_nx = 0.0f,	_ny = 0.0f,	_nz = 0.0f,
			_tu = 0.0f, _tv = 0.0f, _tw = 0.0f,
			_vpu = 0.0f, _vpv = 0.0f, _vpw = 0.0f;
			_ver = 0,  _nor = 0, _tex = 0;
			_int1 = -1, _int2 = -1, _int3 = -1;
			_char1 = '.', _char2 = '.', _char3 = '.';
			_bVer = false, _bVerNor = false, _bVerTex = false, _bVerTexNor = false;
		}
		else if(_op1 == 'v' && _op2 == 't')	//Texture CoOrds
		{
			std::istringstream iss(_buffer, std::istringstream::in);
			iss>>_op1>>_op2>>_tu>>_tv>>_tw;
			_list_TexCoOrds.resize(_texCount+1);
			_list_TexCoOrds[_texCount]._tU = _tu;
			_list_TexCoOrds[_texCount]._tV = _tv;
			_list_TexCoOrds[_texCount]._tW = _tw;
			++_texCount;
		}
		else if(_op1 == 'v' && _op2 == 'n')	//Normals
		{
			std::istringstream iss(_buffer, std::istringstream::in);
			iss>>_op1>>_op2>>_nx>>_ny>>_nz;
			_list_Normals.resize(_norCount+1);
			_list_Normals[_norCount]._nX = _nx;
			_list_Normals[_norCount]._nY = _ny;
			_list_Normals[_norCount]._nZ = _nz;
			++_norCount;
		}
		else if(_op1 == 'v' && _op2 == 'p')	//Vertice Spaces
		{
			std::istringstream iss(_buffer, std::istringstream::in);
			iss>>_op1>>_op2>>_vpu>>_vpv>>_vpw;
			_list_VertSpaces.resize(_vpCount+1);
			_list_VertSpaces[_vpCount]._vpU = _vpu;
			_list_VertSpaces[_vpCount]._vpV = _vpv;
			_list_VertSpaces[_vpCount]._vpW = _vpw;
			++_vpCount;
		}
		else if(_op1 == 'v')	//Vertices
		{
			std::istringstream iss(_buffer, std::istringstream::in);
			iss>>_op1>>_vx>>_vy>>_vz;
			_list_Vertices.resize(_verCount+1);
			_list_Vertices[_verCount]._vX = _vx;
			_list_Vertices[_verCount]._vY = _vy;
			_list_Vertices[_verCount]._vZ = _vz;
			++_verCount;
		}
		else if(_op1 == 'f')		//Faces
		{	
			std::istringstream iss(_buffer, std::istringstream::in);
			iss>>_op1>>_int1>>_int2>>_int3;
			if(_int1 == -1 || _int2 == -1 || _int3 == -1)
			{
				_bVer = false;

				std::istringstream iss(_buffer, std::istringstream::in);
				iss>>_op1>>_int1>>_char1>>_char2>>_int2;
				if(_char1 == '.' || _char2 == '.')
				{
					_bVerNor = false;

					std::istringstream iss(_buffer, std::istringstream::in);
					iss>>_op1>>_int1>>_char1>>_int2>>_char2>>_int3;
					if(_char2 != '.' || _int3 != -1)
					{
						_bVerTex = false;

						std::istringstream iss(_buffer, std::istringstream::in);
						iss>>_op1>>_int1>>_char1>>_int2>>_char2>>_int3;
						if(_char1 == '.' || _char2 == '.') { _bVerTexNor = false; }
						else { _bVerTexNor = true, _bVerNor = false, _bVer = false, _bVerTex = false; }
					}
					else{ _bVerTex = true, _bVerTexNor = false, _bVerNor = false, _bVer = false; }
				}
				else { _bVerNor = true; _bVerTex = false, _bVerTexNor = false, _bVer = false;}
			}
			else { _bVer = true, _bVerNor = false, _bVerTex = false, _bVerTexNor = false;}

			if(_bVerNor)
			{
				std::istringstream iss(_buffer, std::istringstream::in);
				iss>>_op1;
				_fCount = 0;
				while(_fCount < 3)
				{
					iss>>_ver>>_char1>>_char2>>_nor;
					_list_VerNor.resize(_countVerNor+1);
					_list_VerNor[_countVerNor]._Ver[_fCount] = _ver - 1;
					_list_VerNor[_countVerNor]._Nor[_fCount] = _nor - 1;
					++_fCount;
				}
				++_countVerNor;
			}
			else if(_bVerTex)
			{
				std::istringstream iss(_buffer, std::istringstream::in);
				iss>>_op1;
				_fCount = 0;
				while(_fCount < 3)
				{
					iss>>_ver>>_char1>>_tex;
					_list_VerTex.resize(_countVerTex+1);
					_list_VerTex[_countVerTex]._Ver[_fCount] = _ver - 1;
					_list_VerTex[_countVerTex]._Tex[_fCount] = _tex - 1;
					++_fCount;
				}
				++_countVerTex;
			}
			else if(_bVerTexNor)
			{
				std::istringstream iss(_buffer, std::istringstream::in);
				iss>>_op1;
				_fCount = 0;
				while(_fCount < 3)
				{
					iss>>_ver>>_char1>>_tex>>_char2>>_nor;
					_list_VerTexNor.resize(_countVerTexNor+1);
					_list_VerTexNor[_countVerTexNor]._Ver[_fCount] = _ver - 1;
					_list_VerTexNor[_countVerTexNor]._Tex[_fCount] = _tex - 1;
					_list_VerTexNor[_countVerTexNor]._Nor[_fCount] = _nor - 1;
					++_fCount;
				}
				++_countVerTexNor;
			}
			else
			{
				std::istringstream iss(_buffer, std::istringstream::in);
				iss>>_op1;
				_fCount = 0;
				while(_fCount < 3)
				{
					iss>>_ver;
					_list_Ver.resize(_countVer+1);
					_list_Ver[_countVer]._Ver[_fCount] = _ver - 1;
					++_fCount;
				}
				++_countVer;
			}
		}
		else
		{
			_vx = 0.0f,	_vy = 0.0f,	_vz = 0.0f,
			_nx = 0.0f,	_ny = 0.0f,	_nz = 0.0f,
			_tu = 0.0f, _tv = 0.0f, _tw = 0.0f,
			_vpu = 0.0f, _vpv = 0.0f, _vpw = 0.0f;
			_ver = 0,  _nor = 0, _tex = 0;
			_int1 = -1, _int2 = -1, _int3 = -1;
			_char1 = '.', _char2 = '.', _char3 = '.';
			_bVer = false, _bVerNor = false, _bVerTex = false, _bVerTexNor = false;
		}
	}

	infile.close();

	OrderFaces(m);
}

LoadObj::LoadObj(const LoadObj& l)
{
	Copy(l);
}

LoadObj::~LoadObj()
{
}

// Accessors and mutators

LPSTR LoadObj::GetFN() const
{
	return _fn;
}

int LoadObj::GetCVer() const
{
	return _countVer;
}
int LoadObj::GetCVerTex() const
{
	return _countVerTex;
}
int LoadObj::GetCVerTexNor() const
{
	return _countVerTexNor;
}
int LoadObj::GetCVerNor() const
{
	return _countVerNor;
}

int LoadObj::GetFaceC() const
{
	return _fCount;
}
int LoadObj::GetVerC() const
{
	return _verCount;
}
int LoadObj::GetNorC() const
{
	return _norCount;
}
int LoadObj::GetTexC() const
{
	return _texCount;
}
int LoadObj::GetVPC() const
{
	return _vpCount;
}

// Operator overloads
LoadObj& LoadObj::operator=(const LoadObj &rhs)
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
void LoadObj::Init(LPSTR fileName)
{
	_fn = fileName;
	_fCount = 0, _verCount = 0, _norCount = 0, _texCount = 0, _vpCount = 0,
	_countVer = 0, _countVerTex = 0, _countVerTexNor = 0, _countVerNor = 0;
	_sizeBuffer = 1000;
	_vx = 0.0f,	_vy = 0.0f,	_vz = 0.0f,
	_nx = 0.0f,	_ny = 0.0f,	_nz = 0.0f,
	_tu = 0.0f, _tv = 0.0f, _tw = 0.0f,
	_vpu = 0.0f, _vpv = 0.0f, _vpw = 0.0f;
	_ver = 0,  _nor = 0, _tex = 0;
	_int1 = -1, _int2 = -1, _int3 = -1;
	_char1 = '.', _char2 = '.', _char3 = '.';
	_bVer = false, _bVerNor = false, _bVerTex = false, _bVerTexNor = false;
}

void LoadObj::Copy(const LoadObj& l)
{
	_fn = l.GetFN();
	_fCount = l.GetFaceC(), _verCount = l.GetVerC(), _norCount = l.GetNorC(), 
	_texCount = l.GetTexC(), _vpCount = l.GetVPC();
	_countVer = l.GetCVer(), _countVerTex = l.GetCVerTex(), 
	_countVerTexNor = l.GetCVerTexNor(), _countVerNor = l.GetCVerNor();
}

void LoadObj::OrderFaces(Model& m)
{
	_modelVer = 0;
	if(_bVer)
	{
		for(int i = 0; i < _countVer; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				m.SetModelVertice(_modelVer,	_list_Vertices[_list_Ver[i]._Ver[j]]._vX, 
												_list_Vertices[_list_Ver[i]._Ver[j]]._vY, 
												_list_Vertices[_list_Ver[i]._Ver[j]]._vZ);
				++_modelVer;
			}
		}
	}
	else if(_bVerTex)
	{
		for(int i = 0; i < _countVerTex; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				m.SetModelVertice(_modelVer,	_list_Vertices[_list_VerTex[i]._Ver[j]]._vX, 
												_list_Vertices[_list_VerTex[i]._Ver[j]]._vY, 
												_list_Vertices[_list_VerTex[i]._Ver[j]]._vZ);

				m.SetModelTexCoOrd(_modelVer,	_list_TexCoOrds[_list_VerTex[i]._Tex[j]]._tU, 
												_list_TexCoOrds[_list_VerTex[i]._Tex[j]]._tV, 
												_list_TexCoOrds[_list_VerTex[i]._Tex[j]]._tW);
				++_modelVer;
			}
		}
	}
	else if(_bVerTexNor)
	{
		for(int i = 0; i < _countVerTexNor; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				m.SetModelVertice(_modelVer,	_list_Vertices[_list_VerTexNor[i]._Ver[j]]._vX, 
												_list_Vertices[_list_VerTexNor[i]._Ver[j]]._vY, 
												_list_Vertices[_list_VerTexNor[i]._Ver[j]]._vZ);

				m.SetModelTexCoOrd(_modelVer,	_list_TexCoOrds[_list_VerTexNor[i]._Tex[j]]._tU, 
												_list_TexCoOrds[_list_VerTexNor[i]._Tex[j]]._tV, 
												_list_TexCoOrds[_list_VerTexNor[i]._Tex[j]]._tW);

				m.SetModelNormal(_modelVer,		_list_Normals[_list_VerTexNor[i]._Nor[j]]._nX, 
												_list_Normals[_list_VerTexNor[i]._Nor[j]]._nY, 
												_list_Normals[_list_VerTexNor[i]._Nor[j]]._nZ);
				++_modelVer;
			}
		}
	}
	else if(_bVerNor)
	{
		for(int i = 0; i < _countVerNor; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				m.SetModelVertice(_modelVer,	_list_Vertices[_list_VerNor[i]._Ver[j]]._vX, 
												_list_Vertices[_list_VerNor[i]._Ver[j]]._vY, 
												_list_Vertices[_list_VerNor[i]._Ver[j]]._vZ);
				
				m.SetModelNormal(_modelVer,		_list_Normals[_list_VerNor[i]._Nor[j]]._nX, 
												_list_Normals[_list_VerNor[i]._Nor[j]]._nY, 
												_list_Normals[_list_VerNor[i]._Nor[j]]._nZ);
				++_modelVer; 
			}
		}
	}
}
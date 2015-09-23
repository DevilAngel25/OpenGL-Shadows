// OGLWin32.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "OGLWin32.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HGLRC hGLRC = NULL;
HDC g_hdc = NULL;
HWND g_hwnd = NULL;
BOOL terminate2 = FALSE;

//Rotation
bool rotatingX = false;
bool rotDirectionX = false;

bool rotatingY = false;
bool rotDirectionY = false;

bool rotatingZ = false;
bool rotDirectionZ = false;

bool Light0rotDirectionY = false;
bool IdleRotation = false;

bool local = false;
bool world = true;

//World Rotation
float worldRotateX = 0.0f;
float worldRotateY = 0.0f;
float worldRotateZ = 0.0f;

//World Translation
float worldTranslateX = 0.0f;
float worldTranslateY = 5.0f;
float worldTranslateZ = 20.0f;

//Local Rotation
float localRotateX = 0.0f;
float localRotateY = 0.0f;
float localRotateZ = 0.0f;

//Local Translation
float localTranslateX = 0.0f;
float localTranslateY = 2.0f;
float localTranslateZ = 0.0f;

//RotateY Light0
float Light0RotateY = 0.0f;

//Translate Light
float TranslateLight0X = -4.5f;
float TranslateLight0Y = 4.5f;
float TranslateLight0Z = 2.0f;

float TranslateLight1X = -3.5f;
float TranslateLight1Y = 3.5f;
float TranslateLight1Z = 0.0f;

//field of vision
float fov = 45.0f;
float Width = 0.0f;
float Height = 0.0f;

bool ChangeLight = false;
bool LightEnabled = false;

//render type
bool wireFrameModel = false;
bool fillModel = false;
bool pointModel = false;

bool DrawTorus = true;
bool DrawMonkey = false;
bool DrawTeapot = false;
bool DrawDetailedSphere = false;
bool DrawHumanoid = false;
bool DrawIcoSphere = false;
bool DrawTeddy = false;
bool DrawTieFighter = false;
bool DrawTieIntercepter = false;

bool LoadModels = false;
bool SettingsSet = false;

//Material Properties
GLfloat ambient_material[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat diffuse_material[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat specular_material[] = {0.2f, 0.2f, 0.2f, 0.5f};
GLfloat emission_material[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat mat_shininess[] = {64.0f};

GLfloat amb_light_model[] = {0.3f, 0.3f, 0.3f, 1.0f};

//Lighting Properties
GLfloat light0_Pos[] = {TranslateLight0X, TranslateLight0Y, TranslateLight0Z, 1.0f};
GLfloat light1_Pos[] = {TranslateLight1X, TranslateLight1Y, TranslateLight1Z, 1.0f};
		
GLfloat ambient_light0[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat diffuse_light0[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat specular_light0[] = {1.0f, 1.0f, 1.0f, 1.0f};

GLfloat ambient_light1[] = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat diffuse_light1[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat specular_light1[] = {1.0f, 1.0f, 1.0f, 1.0f};

Model Torus; 
Model Monkey; 
Model Teapot; 
Model DetailedSphere; 
Model Humanoid; 
Model IcoSphere; 
Model Teddy; 
Model TieFighter; 
Model TieIntercepter; 
Model Scene;

//SHADOWMAP
const int ShadowMapSize = 1024;

GLuint Light0ShadowMapTex;
GLuint Light1ShadowMapTex;

GLfloat shadow_ambient_light0[] =	{0.0f, 0.0f, 0.0f, 1.0f};
GLfloat shadow_diffuse_light0[] =	{1.0f, 1.0f, 1.0f, 1.0f};
GLfloat shadow_specular_light0[] =	{0.0f, 0.0f, 0.0f, 1.0f};

GLfloat shadow_ambient_light1[] =	{0.0f, 0.0f, 0.0f, 1.0f};
GLfloat shadow_diffuse_light1[] =	{1.0f, 1.0f, 1.0f, 1.0f};
GLfloat shadow_specular_light1[] =	{0.0f, 0.0f, 0.0f, 1.0f};

//Camera Projection
Matrix4 CamProjMatrix4(			0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f);

GLfloat CamProjGLfloat[] =	{	0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f};
//Camera View
Matrix4 CamViewMatrix4(			0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f);

GLfloat CamViewGLfloat[] =	{	0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f};

//Light Projection
//Light0
Matrix4 Light0ProjMatrix4(		0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f);

GLfloat Light0ProjGLfloat[] = {	0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f};
//Light1
Matrix4 Light1ProjMatrix4(		0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f);

GLfloat Light1ProjGLfloat[] = {	0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f};
//Light View
//Light0
Matrix4 Light0ViewMatrix4(		0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f);

GLfloat Light0ViewGLfloat[] = {	0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f};
//Light1
Matrix4 Light1ViewMatrix4(		0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f);

GLfloat Light1ViewGLfloat[] = {	0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f};

//Convert Texture Coords -1,1 Too 0,1

Matrix4 biasMatrix4(			0.5f,0.0f,0.0f,0.5f,
								0.0f,0.5f,0.0f,0.5f,
								0.0f,0.0f,0.5f,0.5f,
								0.0f,0.0f,0.0f,1.0f);
//Light0 Texture Coords
Matrix4 Light0TextureMatrix4(	0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f);

GLfloat Light0TextureGLfloat[] = {	0.0f,0.0f,0.0f,0.0f,
								    0.0f,0.0f,0.0f,0.0f,
								    0.0f,0.0f,0.0f,0.0f,
								    0.0f,0.0f,0.0f,0.0f};

//Light1 Texture Coords
Matrix4 Light1TextureMatrix4(	0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f,
								0.0f,0.0f,0.0f,0.0f);

GLfloat Light1TextureGLfloat[] = {	0.0f,0.0f,0.0f,0.0f,
								    0.0f,0.0f,0.0f,0.0f,
								    0.0f,0.0f,0.0f,0.0f,
								    0.0f,0.0f,0.0f,0.0f};

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void Resize( int width, int height );
BOOL CreateGLContext(HWND hwnd);
BOOL DestroyGLContext(HWND hwnd);
BOOL InitialiseGLState();
BOOL DrawScene(); 

void CheckRotation();
void Light0RotationY();

void DrawObject();
void Settings();

void DrawModel(Model& m, GLfloat color[4]);
void Models();

void DrawShadowMaps();

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_OGLWIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OGLWIN32));

	// Main message loop:

	while (!terminate2 )
	{
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE) )
		{
			if ( msg.message == WM_QUIT )
			{
				terminate2 = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			DrawScene();
			SwapBuffers(g_hdc);
		}
	}
	
	DestroyGLContext(msg.hwnd);

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OGLWIN32));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDC_OGLWIN32);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
      0, 0, 1024, 1024, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hwnd = hWnd;
   g_hdc = GetDC(hWnd);

   CreateGLContext(hWnd);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//Create an Opengl context
BOOL CreateGLContext( HWND hwnd )
{
	unsigned int pixelformat;

	HDC hdc = GetDC(hwnd);

	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Support Window
		PFD_SUPPORT_OPENGL |						// Format Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request RGBA Format
		32,											// Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits mask
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		32,											// Z-Buffer depth
		8,											// Stencil Buffer
		0,											// Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(pixelformat=ChoosePixelFormat(hdc,&pfd)))
	{
		return FALSE;
	}

	if(!SetPixelFormat(hdc,pixelformat,&pfd))
	{
		return FALSE;
	}

	if (!(hGLRC=wglCreateContext(hdc)))
	{
		return FALSE;
	}

	if(!wglMakeCurrent(hdc,hGLRC))
	{
		return FALSE;
	}

	return TRUE;
}

//Resize the Projection and View Matrices
void Resize(int width,int height)
{
	glPushMatrix();
		glLoadIdentity();
		gluPerspective(fov,(GLfloat)width/(GLfloat)height,0.01f,1000.0f); //Projection of camera

		glGetFloatv(GL_MODELVIEW_MATRIX, CamProjGLfloat); //Create the camera projection matrix (GLfloat)
		CamProjMatrix4.GLfloatToMatrix(CamProjGLfloat); //Convert GLfloat proj, Too Matrix4 proj. (my own martix)

		glLoadIdentity();
		gluLookAt(	worldTranslateX, worldTranslateY, worldTranslateZ,		//View of camera
					0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f);

		//Rotate the camera
		glRotatef(worldRotateX,1.0f,0.0f,0.0f);
		glRotatef(worldRotateY,0.0f,1.0f,0.0f);
		glRotatef(worldRotateZ,0.0f,0.0f,1.0f);

		glGetFloatv(GL_MODELVIEW_MATRIX, CamViewGLfloat);					//Create the camera view matrix (GLfloat)
		CamViewMatrix4.GLfloatToMatrix(CamViewGLfloat);						//Convert GLfloat proj, Too Matrix4 proj.

		//Light0
		glLoadIdentity();
		gluPerspective(90.0f, 1.0f, 0.01f, 1000.0f);						//projection of the light source
		glGetFloatv(GL_MODELVIEW_MATRIX, Light0ProjGLfloat);				//Create the light0 matrix (GLfloat)
		Light0ProjMatrix4.GLfloatToMatrix(Light0ProjGLfloat);				//Convert GLfloat proj, Too Matrix4 proj.
		
		glLoadIdentity();
		gluLookAt(	TranslateLight0X, TranslateLight0Y, TranslateLight0Z,	//View of the light source, position of light0
					0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f);

		glRotatef(Light0RotateY,0.0f,1.0f,0.0f);

		glGetFloatv(GL_MODELVIEW_MATRIX, Light0ViewGLfloat);
		Light0ViewMatrix4.GLfloatToMatrix(Light0ViewGLfloat);				//Convert GLfloat proj, Too Matrix4 proj.
		
		//Light1
		glLoadIdentity();													//Create second light projection and view
		gluPerspective(90.0f, 1.0f, 0.01f, 1000.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX, Light1ProjGLfloat);
		Light1ProjMatrix4.GLfloatToMatrix(Light1ProjGLfloat);

		glLoadIdentity();
		gluLookAt(	TranslateLight1X, TranslateLight1Y, TranslateLight1Z,	//position of light1
					0.0f, 0.0, 0.0f,
					0.0f, 1.0f, 0.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX, Light1ViewGLfloat);
		Light1ViewMatrix4.GLfloatToMatrix(Light1ViewGLfloat);
    glPopMatrix();
}

//Cleanup GL context
BOOL DestroyGLContext(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);

	if (hGLRC)
	{
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(hGLRC);
		hGLRC=NULL;
	}

	ReleaseDC(hwnd,hdc);
	
	DestroyWindow(hwnd);
		
	return TRUE;
}

//Draw something
BOOL DrawScene()
{
	//glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Resize((int)Width,(int)Height);			//Resize the view Matrices

	if(!SettingsSet)
	{
		Settings();							//Create the default settings, and shadowmap textures
		SettingsSet = true;
	}

	if(!LoadModels)							//Load all models
	{
		LoadObj("Scene", Scene);

		LoadObj("Torus", Torus);
		LoadObj("Monkey", Monkey);
		LoadObj("Teapot", Teapot);
		LoadObj("DetailedSphere", DetailedSphere);
		LoadObj("Humanoid", Humanoid);
		LoadObj("IcoSphere", IcoSphere);
		LoadObj("Teddy", Teddy);
		LoadObj("TieFighter", TieFighter);
		LoadObj("TieIntercepter", TieIntercepter);

		LoadModels = true;
	}

	CheckRotation();	//Rotate World or Model
	Light0RotationY();	//Rotate light in Y
	DrawObject();		//Draw render type, Point, Line, Fill

	DrawShadowMaps();   //Draw Shadows

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYUP:
		//Set rotating direction Bools
		if(wParam == 0x57)
		{
			if(rotatingX && rotDirectionX) {rotatingX = false;} else {rotatingX = true;}
			rotDirectionX = true;
		}
		else if(wParam == 0x53)
		{
			if(rotatingX && !rotDirectionX) {rotatingX = false;} else {rotatingX = true;}
			rotDirectionX = false;
		}

		if(wParam == 0x41)
		{
			if(rotatingY && rotDirectionY) {rotatingY = false;} else {rotatingY = true;}
			rotDirectionY = true;
		}
		else if(wParam == 0x44)
		{
			if(rotatingY && !rotDirectionY) {rotatingY = false;} else {rotatingY = true;}
			rotDirectionY = false;
		}

		if(wParam == 0x51)
		{
			if(rotatingZ && rotDirectionZ) {rotatingZ = false;} else {rotatingZ = true;}
			rotDirectionZ = true;
		}
		else if(wParam == 0x45)
		{
			if(rotatingZ && !rotDirectionZ) {rotatingZ = false;} else {rotatingZ = true;}
			rotDirectionZ = false;
		}

		//Switch light (light0, light1)
		if(wParam == 0x70)
		{
			ChangeLight = false;
		}
		else if(wParam == 0x71)
		{
			ChangeLight = true;
		}

		//Rotate Light0 in Y if true
		if(wParam == 0x72)
		{
			IdleRotation = true;
		}
		else if(wParam == 0x73)
		{
			IdleRotation = false;
		}

		//Set render type
		if(wParam == 0x74)
		{
			if(pointModel) {pointModel = false;} else {pointModel = true; wireFrameModel = false; fillModel = false;}
		}
		else if(wParam == 0x75)
		{
			if(wireFrameModel) {wireFrameModel = false;} else {wireFrameModel = true; fillModel = false; pointModel = false;}
		}
		else if(wParam == 0x76)
		{
			if(fillModel) {fillModel = false;} else {fillModel = true; wireFrameModel = false; pointModel = false;}
		}

		//Load Different Model
		if(wParam == 0x31)
		{
			if(!DrawTorus) 
			{ 
				DrawTorus = true; DrawMonkey = false; DrawTeapot = false;
				DrawDetailedSphere = false; DrawHumanoid = false; DrawIcoSphere = false;
				DrawTeddy = false; DrawTieFighter = false; DrawTieIntercepter = false;
			} 
		}

		if(wParam == 0x32)
		{
			if(!DrawMonkey) 
			{ 
				DrawTorus = false; DrawMonkey = true; DrawTeapot = false;
				DrawDetailedSphere = false; DrawHumanoid = false; DrawIcoSphere = false;
				DrawTeddy = false; DrawTieFighter = false; DrawTieIntercepter = false;
			}
		}
		if(wParam == 0x33)
		{
			if(!DrawTeapot) 
			{ 
				DrawTorus = false; DrawMonkey = false; DrawTeapot = true;
				DrawDetailedSphere = false; DrawHumanoid = false; DrawIcoSphere = false;
				DrawTeddy = false; DrawTieFighter = false; DrawTieIntercepter = false;
			}
		}
		if(wParam == 0x34)
		{
			if(!DrawDetailedSphere) 
			{ 
				DrawTorus = false; DrawMonkey = false; DrawTeapot = false;
				DrawDetailedSphere = true; DrawHumanoid = false; DrawIcoSphere = false;
				DrawTeddy = false; DrawTieFighter = false; DrawTieIntercepter = false;
			}
		}
		if(wParam == 0x35)
		{
			if(!DrawHumanoid) 
			{ 
				DrawTorus = false; DrawMonkey = false; DrawTeapot = false;
				DrawDetailedSphere = false; DrawHumanoid = true; DrawIcoSphere = false;
				DrawTeddy = false; DrawTieFighter = false; DrawTieIntercepter = false;
			}
		}
		if(wParam == 0x36)
		{
			if(!DrawIcoSphere) 
			{ 
				DrawTorus = false; DrawMonkey = false; DrawTeapot = false;
				DrawDetailedSphere = false; DrawHumanoid = false; DrawIcoSphere = true;
				DrawTeddy = false; DrawTieFighter = false; DrawTieIntercepter = false;
			}
		}
		if(wParam == 0x37)
		{
			if(!DrawTeddy) 
			{ 
				DrawTorus = false; DrawMonkey = false; DrawTeapot = false;
				DrawDetailedSphere = false; DrawHumanoid = false; DrawIcoSphere = false;
				DrawTeddy = true; DrawTieFighter = false; DrawTieIntercepter = false;
			} 
		}
		if(wParam == 0x38)
		{
			if(!DrawTieFighter) 
			{ 
				DrawTorus = false; DrawMonkey = false; DrawTeapot = false;
				DrawDetailedSphere = false; DrawHumanoid = false; DrawIcoSphere = false;
				DrawTeddy = false; DrawTieFighter = true; DrawTieIntercepter = false;
			}
		}
		if(wParam == 0x39)
		{
			if(!DrawTieIntercepter) 
			{ 
				DrawTorus = false; DrawMonkey = false; DrawTeapot = false; 
				DrawDetailedSphere = false; DrawHumanoid = false; DrawIcoSphere = false;
				DrawTeddy = false; DrawTieFighter = false; DrawTieIntercepter = true;
			} 
		}
		//Rotate in local (Model) or world (view)
		if(wParam == 0x21)
		{
			local = true; world = false;
		}
		else if(wParam == 0x22)
		{
			local = false; world = true;
		}
		break;
	case WM_KEYDOWN:
		//Translate All Models v
		if(wParam == 0x68)
		{
			if(local) { localTranslateY += 0.5f; } else if(world) { worldTranslateY += 0.5f; }
		}
		else if(wParam == 0x62)
		{
			if(local) { localTranslateY -= 0.5f; } else if(world) { worldTranslateY -= 0.5f; }
		}

		if(wParam == 0x64)
		{
			if(local) { localTranslateX += 0.5f; } else if(world) { worldTranslateX += 0.5f; }
		}
		else if(wParam == 0x66)
		{
			if(local) { localTranslateX -= 0.5f; } else if(world) { worldTranslateX -= 0.5f; }
		}

		if(wParam == 0x6D)
		{
			if(local) { localTranslateZ += 0.5f; } else if(world) { worldTranslateZ += 0.5f; }
		}
		else if(wParam == 0x6B)
		{
			if(local) { localTranslateZ -= 0.5f; } else if(world) { worldTranslateZ -= 0.5f; }
		}

		if(!ChangeLight)
		{
			//Translate Light0 v
			if(wParam == 0x49) { TranslateLight0Y += 0.5f; } else if(wParam == 0x4B) { TranslateLight0Y -= 0.5f; }

			if(wParam == 0x4A) { TranslateLight0X += 0.5f; } else if(wParam == 0x4C) { TranslateLight0X -= 0.5f; }

			if(wParam == 0x55) { TranslateLight0Z += 0.5f; } else if(wParam == 0x4F) { TranslateLight0Z -= 0.5f; }
		}
		else if(ChangeLight)
		{
			//Translate Light1 v
			if(wParam == 0x49) { TranslateLight1Y += 0.5f; } else if(wParam == 0x4B) { TranslateLight1Y -= 0.5f; }

			if(wParam == 0x4A) { TranslateLight1X += 0.5f; } else if(wParam == 0x4C) { TranslateLight1X -= 0.5f; }

			if(wParam == 0x55) { TranslateLight1Z += 0.5f; } else if(wParam == 0x4F) { TranslateLight1Z -= 0.5f; }
		}

		//Change field of view
		if(wParam == 0x26)
		{
			fov = fov + 1.0f;
			Resize((int)Width, (int)Height);
		}
		else if(wParam == 0x28)
		{
			fov = fov - 1.0f;
			Resize((int)Width, (int)Height);
		}
		break;
	case WM_SIZE:
		Resize(LOWORD(lParam), HIWORD(lParam));	//Resize matrices and store width, height info
		Width = LOWORD(lParam);
		Height = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//Rotate Model or world by amount
void CheckRotation()
{
	//Check X
	if(rotatingX) 
	{
		if(rotDirectionX)
		{
			if(local) { localRotateX += 1.0f; } else if(world) { worldRotateX += 1.0f; }
			if(worldRotateX > 360.0) worldRotateX = 0.0f;
			if(localRotateX > 360.0) localRotateX = 0.0f;
		}
		else
		{
			if(local) { localRotateX -= 1.0f; } else if(world) { worldRotateX -= 1.0f; }
			if(worldRotateX < 0.0) worldRotateX = 360.0f;
			if(localRotateX < 0.0) localRotateX = 360.0f;
		}
	} 
	else 
	{ 
		worldRotateX = worldRotateX;
		localRotateX = localRotateX;
	}

	//Check Y
	if(rotatingY) 
	{
		if(rotDirectionY)
		{
			if(local) { localRotateY += 1.0f; } else if(world) { worldRotateY += 1.0f; }
			if(worldRotateY > 360.0) worldRotateY = 0.0f;
			if(localRotateY > 360.0) localRotateY = 0.0f;
		}
		else
		{
			if(local) { localRotateY -= 1.0f; } else if(world) { worldRotateY -= 1.0f; }
			if(worldRotateY < 0.0) worldRotateY = 360.0f;
			if(localRotateY < 0.0) localRotateY = 360.0f;
		}
	} 
	else 
	{
		worldRotateY = worldRotateY;
		localRotateY = localRotateY;
	}

	//Check Z
	if(rotatingZ) 
	{ 
		if(rotDirectionZ)
		{
			if(local) { localRotateZ += 1.0f; } else if(world) { worldRotateZ += 1.0f; }
			if(worldRotateZ > 360.0) worldRotateZ = 0.0f;
			if(localRotateZ > 360.0) localRotateZ = 0.0f;
		}
		else
		{
			if(local) { localRotateZ -= 1.0f; } else if(world) { worldRotateZ -= 1.0f; }
			if(worldRotateZ < 0.0) worldRotateZ = 360.0f;
			if(localRotateZ < 0.0) localRotateZ = 360.0f;
		}
	} 
	else 
	{ 
		worldRotateZ = worldRotateZ;
		localRotateZ = localRotateZ;
	}
}

//Rotate light0 by amount
void Light0RotationY()
{
	//Check Y
	if(IdleRotation) 
	{
		if(Light0rotDirectionY)
		{
			Light0RotateY += 1.0f;
			if(Light0RotateY > 45.0) { Light0rotDirectionY = false; }
		}
		else
		{
			Light0RotateY -= 1.0f;
			if(Light0RotateY < 0.0) { Light0rotDirectionY = true; }
		}
	} 
	else 
	{
		Light0RotateY = Light0RotateY;
	}
}

//Render type
void DrawObject()
{
	if(wireFrameModel)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if(fillModel)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if(pointModel)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
}

//Default Settings
void Settings()
{
    glShadeModel(GL_SMOOTH);								//Smooth shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					//clearcolor (background/void color)
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);								//Enable DepthTest

    glEnable(GL_CULL_FACE);									//Enable Culling

	//Create First ShadowMap
    glGenTextures(1, &Light0ShadowMapTex);
    glBindTexture(GL_TEXTURE_2D, Light0ShadowMapTex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, ShadowMapSize, ShadowMapSize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	//Create Second ShadowMap
	glGenTextures(1, &Light1ShadowMapTex);
    glBindTexture(GL_TEXTURE_2D, Light1ShadowMapTex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, ShadowMapSize, ShadowMapSize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	//Set and enable MaterialColor
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

	//Set Material prop
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light_model);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_material); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_material); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_material); 
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material); 
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glBlendFunc(GL_ONE, GL_ONE ); //Set blending function (to be enabled later)
}

//Set Models
void Models()
{
	//Draw Scene
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		GLfloat SceneColor[] = {0.0f, 0.3f, 0.0f, 1.0f};
	    DrawModel(Scene, SceneColor);
	glPopMatrix();

	//Draw Models
	GLfloat Grey[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glPushMatrix();
		glTranslatef(localTranslateX, localTranslateY, localTranslateZ);
		glRotatef(localRotateX,1.0f,0.0f,0.0f);
		glRotatef(localRotateY,0.0f,1.0f,0.0f);
		glRotatef(localRotateZ,0.0f,0.0f,1.0f);
		if(DrawTorus){ DrawModel(Torus, Grey); }
		else if(DrawMonkey){ DrawModel(Monkey, Grey); }
		else if(DrawTeapot){ DrawModel(Teapot, Grey); }
		else if(DrawDetailedSphere){ DrawModel(DetailedSphere, Grey); }
		else if(DrawHumanoid){ DrawModel(Humanoid, Grey); }
		else if(DrawIcoSphere){ DrawModel(IcoSphere, Grey); }
		else if(DrawTeddy){ DrawModel(Teddy, Grey); }
		else if(DrawTieFighter){ DrawModel(TieFighter, Grey); }
		else if(DrawTieIntercepter){ DrawModel(TieIntercepter, Grey); }
	glPopMatrix();

	//Draw model to demenstrate shadows on other models
	glPushMatrix();
		glTranslatef(4.0f, 2.0f, 0.0f);
		DrawModel(DetailedSphere, Grey);
	glPopMatrix();

	//Draw Light Models
	glPushMatrix();
		glDisable(GL_DEPTH_TEST);	//Disable depth test so light models are not included in shadowmap

		light0_Pos[0] = TranslateLight0X; light0_Pos[1] = TranslateLight0Y; light0_Pos[2] = TranslateLight0Z;
		GLfloat Light0Color[] = {0.0f, 0.0f, 1.0f, 1.0f};
		glTranslatef(TranslateLight0X, TranslateLight0Y, TranslateLight0Z);
			
		if(LightEnabled)
		{
			glDisable(GL_LIGHTING);					//light will not affect light models
			DrawModel(IcoSphere, Light0Color);
			glEnable(GL_LIGHTING);
		}
		else { DrawModel(IcoSphere, Light0Color); }

		glEnable(GL_DEPTH_TEST);	//reenable depth test
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_DEPTH_TEST);

		light1_Pos[0] = TranslateLight1X; light1_Pos[1] = TranslateLight1Y; light1_Pos[2] = TranslateLight1Z;
		GLfloat Light1Color[] = {0.0f, 0.0f, 1.0f, 1.0f};
		glTranslatef(TranslateLight1X, TranslateLight1Y, TranslateLight1Z);
			
		if(LightEnabled)
		{
			glDisable(GL_LIGHTING);
			DrawModel(IcoSphere, Light1Color);
			glEnable(GL_LIGHTING);
		}
		else { DrawModel(IcoSphere, Light0Color); }

		glEnable(GL_DEPTH_TEST);
	glPopMatrix();
}

//Draw models from verts, normals ect
void DrawModel(Model& m, GLfloat color[4])
{
		if(m.GetNCount() > 0)
		{
			glBegin(GL_TRIANGLES);

				for(int i = 0; i < m.GetVCount(); i++)
				{
					glColor4fv(color);
					glNormal3f(m.GetModelNormalX(i), m.GetModelNormalY(i), m.GetModelNormalZ(i));
					glVertex3f(m.GetModelVerticeX(i), m.GetModelVerticeY(i), m.GetModelVerticeZ(i));		
				}
			glEnd();
			glFlush();
		}
		else if(m.GetVCount() > 0 && m.GetNCount() == 0)
		{
			glBegin(GL_TRIANGLES);

				for(int i = 0; i < m.GetVCount(); i++)
				{
					glColor3f(1.0f, 0.0f, 0.0f);
					glVertex3f(m.GetModelVerticeX(i), m.GetModelVerticeY(i), m.GetModelVerticeZ(i));
				}
			glEnd();
			glFlush();
		}
}

//References which helped me with shadow mapping.

//REF:http://ogldev.atspace.co.uk/www/tutorial23/tutorial23.html
//REF:http://www.paulsprojects.net/tutorials/smt/smt.html

void DrawShadowMaps()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Light0
    glMatrixMode(GL_PROJECTION);						//set projection and view for light 0
    glLoadMatrixf(Light0ProjGLfloat);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(Light0ViewGLfloat);

    glViewport(0, 0, ShadowMapSize, ShadowMapSize);		//set viewport as the shadowmap size

    glCullFace(GL_FRONT);								//cull front faces
    glShadeModel(GL_FLAT);								//flat shading (no need for smooth shading)
    glColorMask(0, 0, 0, 0);							//ignore color

	Models();											//Draw models (Depthmap) form light point of view

	//apply depthmap to texture
    glBindTexture(GL_TEXTURE_2D, Light0ShadowMapTex); //texture map 0
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0,  ShadowMapSize,  ShadowMapSize);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear buffers

	//Light1
	glMatrixMode(GL_PROJECTION);						//repeat for second light
    glLoadMatrixf(Light1ProjGLfloat);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(Light1ViewGLfloat);

	Models();

    glBindTexture(GL_TEXTURE_2D, Light1ShadowMapTex); //texture map 1
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0,  ShadowMapSize,  ShadowMapSize);

	//Restore Default Settings
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);
    glColorMask(1, 1, 1, 1);

	//Clear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(CamProjGLfloat);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(CamViewGLfloat);

    glViewport(0, 0, (int)Width, (int)Height);	//reset the viewport as the screen width/height
	
	//Lights which will be the shadow
    glLightfv(GL_LIGHT0, GL_POSITION, light0_Pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, shadow_ambient_light0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, shadow_diffuse_light0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, shadow_specular_light0);

	glLightfv(GL_LIGHT1, GL_POSITION, light1_Pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, shadow_ambient_light1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, shadow_diffuse_light1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, shadow_specular_light1);

	//Enable Lighting
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	LightEnabled = true;  //controls drawing light models

	//Draw models
	Models();

	//THIRD PASS - draw normal light 
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light1);

	//--Light0--
	//Calculate the TextureMatrix for light 0
	Light0TextureMatrix4 = biasMatrix4 * Light0ProjMatrix4 * Light0ViewMatrix4;

	//Convert Matrix4 Coords into GLfloat Coords.
	Light0TextureGLfloat[0] = Light0TextureMatrix4.GetM(0,0); Light0TextureGLfloat[1] = Light0TextureMatrix4.GetM(0,1); 
	Light0TextureGLfloat[2] = Light0TextureMatrix4.GetM(0,2); Light0TextureGLfloat[3] = Light0TextureMatrix4.GetM(0,3);

	Light0TextureGLfloat[4] = Light0TextureMatrix4.GetM(1,0); Light0TextureGLfloat[5] = Light0TextureMatrix4.GetM(1,1); 
	Light0TextureGLfloat[6] = Light0TextureMatrix4.GetM(1,2); Light0TextureGLfloat[7] = Light0TextureMatrix4.GetM(1,3);

	Light0TextureGLfloat[8] = Light0TextureMatrix4.GetM(2,0); Light0TextureGLfloat[9] = Light0TextureMatrix4.GetM(2,1); 
	Light0TextureGLfloat[10] = Light0TextureMatrix4.GetM(2,2); Light0TextureGLfloat[11] = Light0TextureMatrix4.GetM(2,3);

	Light0TextureGLfloat[12] = Light0TextureMatrix4.GetM(3,0); Light0TextureGLfloat[13] = Light0TextureMatrix4.GetM(3,1); 
	Light0TextureGLfloat[14] = Light0TextureMatrix4.GetM(3,2); Light0TextureGLfloat[15] = Light0TextureMatrix4.GetM(3,3);

	//add texture coords to rows
	GLfloat Light0Row1[] = {Light0TextureGLfloat[0], Light0TextureGLfloat[1], Light0TextureGLfloat[2], Light0TextureGLfloat[3]};
	GLfloat Light0Row2[] = {Light0TextureGLfloat[4], Light0TextureGLfloat[5], Light0TextureGLfloat[6], Light0TextureGLfloat[7]};
	GLfloat Light0Row3[] = {Light0TextureGLfloat[8], Light0TextureGLfloat[9], Light0TextureGLfloat[10], Light0TextureGLfloat[11]};
	GLfloat Light0Row4[] = {Light0TextureGLfloat[12], Light0TextureGLfloat[13], Light0TextureGLfloat[14], Light0TextureGLfloat[15]};
	
	//Set up texture coordinate generation.
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_S, GL_EYE_PLANE, Light0Row1);
    glEnable(GL_TEXTURE_GEN_S);

    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_T, GL_EYE_PLANE, Light0Row2);
    glEnable(GL_TEXTURE_GEN_T);

    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_R, GL_EYE_PLANE, Light0Row3);
    glEnable(GL_TEXTURE_GEN_R);

    glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_Q, GL_EYE_PLANE, Light0Row4);
    glEnable(GL_TEXTURE_GEN_Q);

    glBindTexture(GL_TEXTURE_2D, Light0ShadowMapTex); //texture map 0
    glEnable(GL_TEXTURE_2D); //Enable shadow map texture

	//Enable shadow comparison
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

	//Set alpha test to discard false comparisons
    glAlphaFunc(GL_GEQUAL, 0.99f);
    glEnable(GL_ALPHA_TEST);

	glEnable(GL_BLEND); //enable blending for shadowmap

	Models();

	glDisable(GL_BLEND);//disable blending for shadowmap

	//Disable Textures and Texture Generation
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);
    glDisable(GL_TEXTURE_GEN_Q);
    glDisable(GL_ALPHA_TEST);

	//--Light1--
	//Calculate the TextureMatrix
	Light1TextureMatrix4 = biasMatrix4 * Light1ProjMatrix4 * Light1ViewMatrix4;

	//Convert Matrix4 Coords into GLfloat Coords.
	Light1TextureGLfloat[0] = Light1TextureMatrix4.GetM(0,0); Light1TextureGLfloat[1] = Light1TextureMatrix4.GetM(0,1); 
	Light1TextureGLfloat[2] = Light1TextureMatrix4.GetM(0,2); Light1TextureGLfloat[3] = Light1TextureMatrix4.GetM(0,3);

	Light1TextureGLfloat[4] = Light1TextureMatrix4.GetM(1,0); Light1TextureGLfloat[5] = Light1TextureMatrix4.GetM(1,1); 
	Light1TextureGLfloat[6] = Light1TextureMatrix4.GetM(1,2); Light1TextureGLfloat[7] = Light1TextureMatrix4.GetM(1,3);

	Light1TextureGLfloat[8] = Light1TextureMatrix4.GetM(2,0); Light1TextureGLfloat[9] = Light1TextureMatrix4.GetM(2,1); 
	Light1TextureGLfloat[10] = Light1TextureMatrix4.GetM(2,2); Light1TextureGLfloat[11] = Light1TextureMatrix4.GetM(2,3);

	Light1TextureGLfloat[12] = Light1TextureMatrix4.GetM(3,0); Light1TextureGLfloat[13] = Light1TextureMatrix4.GetM(3,1); 
	Light1TextureGLfloat[14] = Light1TextureMatrix4.GetM(3,2); Light1TextureGLfloat[15] = Light1TextureMatrix4.GetM(3,3);

	//create CoOrd rows
	GLfloat Light1Row1[] = {Light1TextureGLfloat[0], Light1TextureGLfloat[1], Light1TextureGLfloat[2], Light1TextureGLfloat[3]};
	GLfloat Light1Row2[] = {Light1TextureGLfloat[4], Light1TextureGLfloat[5], Light1TextureGLfloat[6], Light1TextureGLfloat[7]};
	GLfloat Light1Row3[] = {Light1TextureGLfloat[8], Light1TextureGLfloat[9], Light1TextureGLfloat[10], Light1TextureGLfloat[11]};
	GLfloat Light1Row4[] = {Light1TextureGLfloat[12], Light1TextureGLfloat[13], Light1TextureGLfloat[14], Light1TextureGLfloat[15]};
	
	//Set up texture coordinate generation.
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_S, GL_EYE_PLANE, Light1Row1);
    glEnable(GL_TEXTURE_GEN_S);

    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_T, GL_EYE_PLANE, Light1Row2);
    glEnable(GL_TEXTURE_GEN_T);

    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_R, GL_EYE_PLANE, Light1Row3);
    glEnable(GL_TEXTURE_GEN_R);

    glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_Q, GL_EYE_PLANE, Light1Row4);
    glEnable(GL_TEXTURE_GEN_Q);

    glBindTexture(GL_TEXTURE_2D, Light1ShadowMapTex); //texture map 1
    glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

	glAlphaFunc(GL_GEQUAL, 0.99f);
    glEnable(GL_ALPHA_TEST);

	//Draw second shadowmap with blending
	glEnable(GL_BLEND);

	Models();

	glDisable(GL_BLEND);

	//Disable textures and texgen
    glDisable(GL_TEXTURE_2D);

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);
    glDisable(GL_TEXTURE_GEN_Q);

    //Restore other states
	glDisable(GL_LIGHTING);
	LightEnabled = false; //controls drawing light models
    glDisable(GL_ALPHA_TEST);
}
//Mariana Arguelles Macosay
//Diana Anayanssi Martínez Santana

#define _USE_MATH_DEFINES
#include <cmath>
//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

// contains new std::shuffle definition
#include <algorithm>
#include <random>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"
#include "Headers/ThirdPersonCamera.h"


//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/Texture.h"

// Include loader Model class
#include "Headers/Model.h"

// Include Terrain
#include "Headers/Terrain.h"

#include "Headers/AnimationUtils.h"

// Include Colision headers functions
#include "Headers/Colisiones.h"

// ShadowBox include
#include "Headers/ShadowBox.h"

// OpenAL include
#include <AL/alut.h>

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight; 

//selector de vista - camara 
bool selec_vista = true;
bool camaraActivada = false;

const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;

GLFWwindow *window;

Shader shader;
//Shader con skybox
Shader shaderSkybox;
//Shader con multiples luces
Shader shaderMulLighting;
//Shader para el terreno
Shader shaderTerrain;
//Shader para las particulas de fountain
Shader shaderParticlesFountain;
//Shader para las particulas de fuego
Shader shaderParticlesFire;
//Shader para visualizar el buffer de profundidad
Shader shaderViewDepth;
//Shader para dibujar el buffer de profunidad
Shader shaderDepth;


std::shared_ptr<Camera> camera(new ThirdPersonCamera());
float distanceFromTarget = 25.0;

std::shared_ptr<FirstPersonCamera>cameraPP(new FirstPersonCamera());

Sphere skyboxSphere(20, 20);
Box boxCollider;
Sphere sphereCollider(10, 10);
Box boxViewDepth;
Box boxLightViewBox;

ShadowBox * shadowBox;

// Models complex instances
Model panditaRojo;
Model panditaAmarillo;
Model panditaAzul;
Model panditaNaranja;
Model panditaVerde;
Model CaramAmarillo;
Model CaramAzul;
Model CaramRosa;
Model CaramVerde;
Model DonaChocolate;
Model DonaFresa;
Model HeladoChocolate;
Model HeladoFresa;
Model HeladoMenta;
Model HeladoMoraAzul;
Model HeladoMoraAzulFresa;
Model PiruletaAmarillo;
Model PiruletaRojo;
Model PiruletaVerde;
Model BallKirby;
Model Cake;
Model Chocolate;
Model ChocoPaleta;
Model Cookie;
Model CuteHome1;
Model CuteHome2;
Model CuteShop;
Model IceCreamSign;
Model Nube;
Model Paleta;
Model Strawberry;
Model SweetCarrito;
Model CuteGun;
// Lamps
Model BastonLampara;
// Model animate instance
// Mayow
Model MayowCuteAnimate;
// Terrain model instance
Terrain terrain(-1, -1, 800, 60, "../Textures/heightmap.png"); //Valores practica 14: -1, -1, 200, 16

GLuint textureCespedID, textureWallID, textureWindowID, textureHighwayID, textureLandingPadID;
GLuint textureTerrainBackgroundID, textureTerrainRID, textureTerrainGID, textureTerrainBID, textureTerrainBlendMapID;
GLuint textureParticleFountainID, textureParticleFireID, texId;
GLuint skyboxTextureID;

bool dia = true;

	GLenum types[6] = {
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

	std::string fileNames[6] = { "../Textures/mp_Cute/Cute_ft.tga",
					"../Textures/mp_Cute/Cute_bk.tga",
					"../Textures/mp_Cute/Cute_up.tga",
					"../Textures/mp_Cute/Cute_dn.tga",
					"../Textures/mp_Cute/Cute_lf.tga",
					"../Textures/mp_Cute/Cute_rt.tga" };


	std::string fileNames2[6] = { "../Textures/mp_Cute/Cute_ft_n.tga",
		"../Textures/mp_Cute/Cute_bk_n.tga",
		"../Textures/mp_Cute/Cute_up_n.tga",
		"../Textures/mp_Cute/Cute_dn_n.tga",
		"../Textures/mp_Cute/Cute_lf_n.tga",
		"../Textures/mp_Cute/Cute_rt_n.tga" };

		

bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;
bool ColisionMP = false; //Colisión entre May y Pelotas

// Model matrix definitions
glm::mat4 matrixModelPanditaRojo = glm::mat4(1.0);
glm::mat4 matrixModelPanditaAzul = glm::mat4(1.0);
glm::mat4 matrixModelPanditaNaranja = glm::mat4(1.0);
glm::mat4 matrixModelPanditaAmarillo = glm::mat4(1.0);
glm::mat4 matrixModelPanditaVerde = glm::mat4(1.0);
glm::mat4 matrixModelCaramAmarillo = glm::mat4(1.0);
glm::mat4 matrixModelCaramAzul = glm::mat4(1.0);
glm::mat4 matrixModelCaramRosa = glm::mat4(1.0);
glm::mat4 matrixModelCaramVerde = glm::mat4(1.0);
glm::mat4 matrixModelHeladoChocolate = glm::mat4(1.0);
glm::mat4 matrixModelHeladoFresa = glm::mat4(1.0);
glm::mat4 matrixModelHeladoMenta = glm::mat4(1.0);
glm::mat4 matrixModelHeladoMoraAzul = glm::mat4(1.0);
glm::mat4 matrixModelHeladoMoraAzulFresa = glm::mat4(1.0);
glm::mat4 matrixModelPiruletaAmarillo = glm::mat4(1.0);
glm::mat4 matrixModelPiruletaRojo = glm::mat4(1.0);
glm::mat4 matrixModelPiruletaVerde = glm::mat4(1.0);
glm::mat4 matrixModelDonaChocolate = glm::mat4(1.0);
glm::mat4 matrixModelDonaFresa = glm::mat4(1.0);
glm::mat4 matrixModelBallKirby = glm::mat4(1.0);
glm::mat4 matrixModelCake = glm::mat4(1.0);
glm::mat4 matrixModelChocolate = glm::mat4(1.0);
glm::mat4 matrixModelChocoPaleta = glm::mat4(1.0);
glm::mat4 matrixModelCookie = glm::mat4(1.0);
glm::mat4 matrixModelCuteHome1 = glm::mat4(1.0);
glm::mat4 matrixModelCuteHome2 = glm::mat4(1.0);
glm::mat4 matrixModelCuteShop = glm::mat4(1.0);
glm::mat4 matrixModelIceCreamSign = glm::mat4(1.0);
glm::mat4 matrixModelNube = glm::mat4(1.0);
glm::mat4 matrixModelPaleta = glm::mat4(1.0);
glm::mat4 matrixModelStrawberry = glm::mat4(1.0);
glm::mat4 matrixModelSweetCarrito = glm::mat4(1.0);
glm::mat4 matrixModelCuteGun = glm::mat4(1.0);
//Model matrix definitions Animate
glm::mat4 matrixModelMayow = glm::mat4(1.0);

int animationIndex = 7;
int modelSelected = 1;
bool enableCountSelected = true;

//Posicion pelotas
std::vector<glm::vec3> pelotasPosition = {};

// Lamps positions
std::vector<glm::vec3> lamp1Position = {
	glm::vec3(73.4375, 0, -426.5625),
	glm::vec3(21.09375, 0, -372.65625),
	glm::vec3(-25, 0, -392.96875),
	glm::vec3(-85.9375, 0, -388.28125),
	glm::vec3(-136.71875, 0, -347.65625),
	glm::vec3(-206.25, 0, -365.625),
	glm::vec3(-250, 0, -321.875),
	glm::vec3(-308.59375, 0, -364.0625),
	glm::vec3(-359.375, 0, -416.40625),
	glm::vec3(-322.65625, 0, -498.4375),
	glm::vec3(-288.28125, 0, -569.53125),
	glm::vec3(-229.6875, 0, -584.375),
	glm::vec3(-162.5, 0, -632.03125) };
std::vector<float> lamp1Orientation = { 16.36, - 258.69, - 349.7,
	- 161.94, 14.53, - 162.72, - 330.26, - 231.71, 19.29, - 326.89,
	- 141.07, - 326.31,- 145.71};

//CuteHome1 positions
std::vector<glm::vec3> CutH1Position = {
	glm::vec3(32.8125	, 0, -15.625),
	glm::vec3(-589.0625 , 0,-328.125),
	glm::vec3(-367.96875, 0, -614.0625) };
std::vector<float> CutH1Orientation = { -235.89, - 58.57, - 68.5};

//CuteHome2 positions
std::vector<glm::vec3> CutH2Position = {
	glm::vec3(-227.34375, 0,-71.09375),
	glm::vec3(-11.71875 , 0,-494.53125),};
std::vector<float> CutH2Orientation = { -2688.16, - 146.59};

//CuteShop positions
std::vector<glm::vec3> CutShPosition = {
	glm::vec3(-667.1875, 0,64.0625),
	glm::vec3(20.3125, 0,-653.90625), }; 
std::vector<float> CutShOrientation = { 44.12, - 233 };

// Cake positions
std::vector<glm::vec3> CakePosition = {
	glm::vec3(64.0625,0 ,-44.53125),
	glm::vec3(62.5,0 ,-306.25),
	glm::vec3(-164.0625,0 ,-94.53125),
	glm::vec3(-363.28125,0 ,-191.40625),
	glm::vec3(-527.34375,0 ,82.03125),
	glm::vec3(-561.71875,0 ,-110.9375),
	glm::vec3(57.03125,0 ,-604.6875),
	glm::vec3(-125,0 ,-526.5625),
	glm::vec3(-325.78125,0 ,-669.53125),
	glm::vec3(-554.6875,0 ,-488.28125),};
std::vector<float> CakeOrientation = { -137.64, - 211.72, - 141.04,
	- 243.92, 15.57, - 57.38, - 239.93, - 158.96, - 240, - 159.65};

// CarameloAmarillo positions
std::vector<glm::vec3> CarAmPosition = {
	glm::vec3(25.78125,0,-196.875),
	glm::vec3(-381.25,0,-46.875),
	glm::vec3(23.4375,0,-507.8125),
	glm::vec3(-387.5,0,-560.9375) };
std::vector<float> CarAmOrientation = { 180, - 137.64, - 180, - 57.65};

// CarameloAzul positions
std::vector<glm::vec3> CarAzPosition = {
	glm::vec3(-42.96875, 0, -253.90625),
	glm::vec3(-449.21875, 0,83.59375),
	glm::vec3(-84.375, 0,	-583.59375),
	glm::vec3(-521.875, 0,	-547.65625) };
std::vector<float> CarAzOrientation = { -334.54, 33.34, - 318.81, - 228.95};

// CarameloRosa positions
std::vector<glm::vec3> CarRoPosition = {
	glm::vec3(-167.96875, 0,42.96875),
	glm::vec3(-667.96875, 0,-204.6875),
	glm::vec3(-450.5, 0 ,- 160) };
std::vector<float> CarRoOrientation = { -316.4, - 53.75,- 318.81};

// CarameloVerde positions
std::vector<glm::vec3> CarVerPosition = {
	glm::vec3(-210.15625,0,-221.09375),
	glm::vec3(80.46875,0,-628.90625),
	glm::vec3(-415.625,0,-352.34375)};
std::vector<float> CarVerOrientation = { 0, - 232.21,- 59.98};

// Chocolate positions
std::vector<glm::vec3> ChocoPosition = {
	glm::vec3(-21.09375, 0 ,12.5),
	glm::vec3(-153.125, 0 ,5.46875),
	glm::vec3(-283.59375, 0 ,-221.875),
	glm::vec3(-584.375, 0 ,-91.40625),
	glm::vec3(2.34375, 0 ,-585.15625),
	glm::vec3(-45.3125, 0 ,-348.4375),
	glm::vec3(-95.3125, 0 ,-487.5),
	glm::vec3(-489.84375, 0 ,-300),
	glm::vec3(-611.71875, 0 ,-458.59375),
	glm::vec3(-533.59375, 0 ,-664.0625)};
std::vector<float> ChocoOrientation = { -341.32, - 224.4, - 346.29, 
	- 237.88, - 236.31, - 251.3, - 252.43, - 328.06, - 74.9, 35.97};

// ChocoPaleta positions
std::vector<glm::vec3> ChocoPPosition = {
	glm::vec3(-60.9375,0 , -57.03125),
	glm::vec3(-196.09375,0 , -133.59375),
	glm::vec3(-153.90625,0 , -292.1875),
	glm::vec3(-307.03125,0 , 70.3125),
	glm::vec3(-434.375,0 , -255.46875),
	glm::vec3(-544.53125,0 , -170.3125),
	glm::vec3(-589.0625,0 , 48.4375),
	glm::vec3(37.5,0 , -346.09375),
	glm::vec3(69.53125,0 , -454.6875),
	glm::vec3(65.625,0 , -548.4375) };
std::vector<float> ChocoPOrientation = { 38.45, - 349.02, - 335.16, 0,
	40.6, 42.2, 0, - 335.73, - 143.88, - 270 };

// Galletas positions
std::vector<glm::vec3> CookPosition = {
	glm::vec3(-238.28125,0 ,15.625),
	glm::vec3(-266.40625,0 ,-152.34375),
	glm::vec3(-510.15625,0 ,-15.625),
	glm::vec3(-514.84375,0 ,-250.78125),
	glm::vec3(-42.96875,0 ,-550),
	glm::vec3(-282.03125,0 ,-637.5),
	glm::vec3(-503.125,0 ,-456.25)};
std::vector<float> CookOrientation = { 0, 0, 0, 0, 0, 0, 0};

// DonaChocolate positions
std::vector<glm::vec3> DonChoPosition = {
	glm::vec3(-11.71875,0, -188.28125),
	glm::vec3(-342.96875,0, -157.03125),
	glm::vec3(-661.71875,0, -154.6875),
	glm::vec3(-260.9375,0, -422.65625),
	glm::vec3(-446.875,0, -507.03125),
	glm::vec3(-675.78125,0, -510.15625)};
std::vector<float> DonChoOrientation = { 0,0,0,0,0,0};

// DonaChocolate positions
std::vector<glm::vec3> DonFrePosition = {
	glm::vec3(-105.46875,0 ,-31.25),
	glm::vec3(-411.71875,0 ,-47.65625),
	glm::vec3(-103.90625,0 ,-440.625),
	glm::vec3(-385.15625,0 ,-666.40625),
	glm::vec3(-657.8125,0 ,-678.125)};
std::vector<float> DonFreOrientation = { 0,0,0,0,0 };

// PanditaAmarillo positions
std::vector<glm::vec3> PAmPosition = {
	glm::vec3(-99.21875, 0, -109.375),
	glm::vec3(-673.4375, 0, -35.9375)};
std::vector<float> PAmOrientation = { 26.83, - 62.24};

// PanditaAzul positions
std::vector<glm::vec3> PAzPosition = {
	glm::vec3(-106.25, 0, -220.3125),
	glm::vec3(-203.90625, 0, -475.78125) };
std::vector<float> PAzOrientation = { -239.68, - 252.23};

// PanditaNaranja positions
std::vector<glm::vec3> PNaPosition = {
	glm::vec3(-349.21875, 0, -214.84375),
	glm::vec3(-226.5625, 0, -678.90625) };
std::vector<float> PNaOrientation = { -340.2, - 162.35};

// PanditaRojo positions
std::vector<glm::vec3> PRoPosition = {
	glm::vec3(78.125, 0, -151.5625),
	glm::vec3(-416.40625, 0, 25.78125),
	glm::vec3(-655.46875, 0, -613.28125) };
std::vector<float> PRoOrientation = { -270, - 228.26, - 118.1};

// PanditaVerde positions
std::vector<glm::vec3> PVePosition = {
	glm::vec3(-550.78125, 0, -14.84375),
	glm::vec3(-416.40625, 0, -503.90625) };
std::vector<float> PVeOrientation = { 17.65, - 65.73};


// Blending model unsorted
std::map<std::string, glm::vec3> blendingUnsorted = {
		{"aircraft", glm::vec3(10.0, 0.0, -17.5)},
		{"lambo", glm::vec3(23.0, 0.0, 0.0)},
		{"heli", glm::vec3(5.0, 10.0, -5.0)},
		{"fountain", glm::vec3(0.0, 0.0, 0.0)},
		{"fire", glm::vec3(0.0, 0.0, 7.0)}
};

double deltaTime;
double currTime, lastTime;

// Definition for the particle system
GLuint initVel, startTime;
GLuint VAOParticles;
GLuint nParticles = 8000;
double currTimeParticlesAnimation, lastTimeParticlesAnimation;

// Definition for the particle system fire
GLuint initVelFire, startTimeFire;
GLuint VAOParticlesFire;
GLuint nParticlesFire = 2000;
GLuint posBuf[2], velBuf[2], age[2];
GLuint particleArray[2];
GLuint feedback[2];
GLuint drawBuf = 1;
float particleSize = 0.5, particleLifetime = 3.0;
double currTimeParticlesAnimationFire, lastTimeParticlesAnimationFire;


// Colliders
std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> > collidersOBB;
std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> > collidersSBB;

// Framesbuffers
GLuint depthMap, depthMapFBO;

/**********************
 * OpenAL config
 */

 // OpenAL Defines
#define NUM_BUFFERS 3
#define NUM_SOURCES 3
#define NUM_ENVIRONMENTS 1
// Listener
ALfloat listenerPos[] = { 0.0, 0.0, 4.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
// Source 0
ALfloat source0Pos[] = { -2.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
// Source 1
ALfloat source1Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
// Source 2
ALfloat source2Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source2Vel[] = { 0.0, 0.0, 0.0 };
// Buffers
ALuint buffer[NUM_BUFFERS];
ALuint source[NUM_SOURCES];
ALuint environment[NUM_ENVIRONMENTS];
// Configs
ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
ALboolean loop;
std::vector<bool> sourcesPlay = { true, true, true };

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
	int mode);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
//void initParticleBuffers();
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);
void prepareScene();
void prepareDepthScene();
void renderScene(bool renderParticles = true);


void initParticleBuffers() {
	// Generate the buffers
	glGenBuffers(1, &initVel);   // Initial velocity buffer
	glGenBuffers(1, &startTime); // Start time buffer

	// Allocate space for all buffers
	int size = nParticles * 3 * sizeof(float);
	glBindBuffer(GL_ARRAY_BUFFER, initVel);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, startTime);
	glBufferData(GL_ARRAY_BUFFER, nParticles * sizeof(float), NULL, GL_STATIC_DRAW);

	// Fill the first velocity buffer with random velocities
	glm::vec3 v(0.0f);
	float velocity, theta, phi;
	GLfloat *data = new GLfloat[nParticles * 3];
	for (unsigned int i = 0; i < nParticles; i++) {

		theta = glm::mix(0.0f, glm::pi<float>() / 6.0f, ((float)rand() / RAND_MAX));
		phi = glm::mix(0.0f, glm::two_pi<float>(), ((float)rand() / RAND_MAX));

		v.x = sinf(theta) * cosf(phi);
		v.y = cosf(theta);
		v.z = sinf(theta) * sinf(phi);

		velocity = glm::mix(0.6f, 0.8f, ((float)rand() / RAND_MAX));
		v = glm::normalize(v) * velocity;

		data[3 * i] = v.x;
		data[3 * i + 1] = v.y;
		data[3 * i + 2] = v.z;
	}
	glBindBuffer(GL_ARRAY_BUFFER, initVel);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

	// Fill the start time buffer
	delete[] data;
	data = new GLfloat[nParticles];
	float time = 0.0f;
	float rate = 0.00075f;
	for (unsigned int i = 0; i < nParticles; i++) {
		data[i] = time;
		time += rate;
	}
	glBindBuffer(GL_ARRAY_BUFFER, startTime);
	glBufferSubData(GL_ARRAY_BUFFER, 0, nParticles * sizeof(float), data);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] data;

	glGenVertexArrays(1, &VAOParticles);
	glBindVertexArray(VAOParticles);
	glBindBuffer(GL_ARRAY_BUFFER, initVel);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, startTime);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}


void initParticleBuffersFire() {
	// Generate the buffers
	glGenBuffers(2, posBuf);    // position buffers
	glGenBuffers(2, velBuf);    // velocity buffers
	glGenBuffers(2, age);       // age buffers

	// Allocate space for all buffers
	int size = nParticlesFire * sizeof(GLfloat);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, velBuf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, velBuf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, age[0]);
	glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, age[1]);
	glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_COPY);

	// Fill the first age buffer
	std::vector<GLfloat> initialAge(nParticlesFire);
	float rate = particleLifetime / nParticlesFire;
	for (unsigned int i = 0; i < nParticlesFire; i++) {
		int index = i - nParticlesFire;
		float result = rate * index;
		initialAge[i] = result;
	}
	// Shuffle them for better looking results
	//Random::shuffle(initialAge);
	auto rng = std::default_random_engine{};
	std::shuffle(initialAge.begin(), initialAge.end(), rng);
	glBindBuffer(GL_ARRAY_BUFFER, age[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, initialAge.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create vertex arrays for each set of buffers
	glGenVertexArrays(2, particleArray);

	// Set up particle array 0
	glBindVertexArray(particleArray[0]);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, velBuf[0]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, age[0]);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// Set up particle array 1
	glBindVertexArray(particleArray[1]);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, velBuf[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, age[1]);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	// Setup the feedback objects
	glGenTransformFeedbacks(2, feedback);

	// Transform feedback 0
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[0]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, posBuf[0]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, velBuf[0]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, age[0]);

	// Transform feedback 1
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[1]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, posBuf[1]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, velBuf[1]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, age[1]);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}

float cont_dia = 0.0f;
// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
			glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
			nullptr);

	if (window == nullptr) {
		std::cerr
			<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
			<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// InicializaciÃ³n de los shaders
	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox_fog.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_textura_animation_shadow.vs", "../Shaders/multipleLights_shadow.fs");
	shaderTerrain.initialize("../Shaders/terrain_shadow.vs", "../Shaders/terrain_shadow.fs");
	shaderParticlesFountain.initialize("../Shaders/particlesFountain.vs", "../Shaders/particlesFountain.fs");
	shaderParticlesFire.initialize("../Shaders/particlesFire.vs", "../Shaders/particlesFire.fs", { "Position", "Velocity", "Age" });
	shaderViewDepth.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado_depth_view.fs");
	shaderDepth.initialize("../Shaders/shadow_mapping_depth.vs", "../Shaders/shadow_mapping_depth.fs");

	// Inicializacion de los objetos.
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(100.0f, 100.0f, 100.0f));  //Valores practica 14: 100.0f, 100.0f, 100.0f

	boxCollider.init();
	boxCollider.setShader(&shader);
	boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphereCollider.init();
	sphereCollider.setShader(&shader);
	sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	boxViewDepth.init();
	boxViewDepth.setShader(&shaderViewDepth);

	boxLightViewBox.init();
	boxLightViewBox.setShader(&shaderViewDepth);


	terrain.init();
	terrain.setShader(&shaderTerrain);
	terrain.setPosition(glm::vec3(100, 0, 100));

	// Panditas models
	panditaRojo.loadModel("../models/Panditas/PanditaRojo.obj");
	panditaRojo.setShader(&shaderMulLighting);
	panditaAzul.loadModel("../models/Panditas/PanditaAzul.obj");
	panditaAzul.setShader(&shaderMulLighting);
	panditaNaranja.loadModel("../models/Panditas/PanditaNaranja.obj");
	panditaNaranja.setShader(&shaderMulLighting);
	panditaVerde.loadModel("../models/Panditas/PanditaVerde.obj");
	panditaVerde.setShader(&shaderMulLighting);
	panditaAmarillo.loadModel("../models/Panditas/PanditaAmarillo.obj");
	panditaAmarillo.setShader(&shaderMulLighting);

	//Caramelos models
	CaramAmarillo.loadModel("../models/Caramelos/CarameloAmarillo.obj");
	CaramAmarillo.setShader(&shaderMulLighting);
	CaramAzul.loadModel("../models/Caramelos/CarameloAzul.obj");
	CaramAzul.setShader(&shaderMulLighting);
	CaramRosa.loadModel("../models/Caramelos/CarameloRosa.obj");
	CaramRosa.setShader(&shaderMulLighting);
	CaramVerde.loadModel("../models/Caramelos/CarameloVerde.obj");
	CaramVerde.setShader(&shaderMulLighting);

	//Donas models
	DonaChocolate.loadModel("../models/Dona/DonaChocolate.obj");
	DonaChocolate.setShader(&shaderMulLighting);
	DonaFresa.loadModel("../models/Dona/DonaFresa.obj");
	DonaFresa.setShader(&shaderMulLighting);

	//Helados models
	HeladoChocolate.loadModel("../models/Helado/HeladoChocolate.obj");
	HeladoChocolate.setShader(&shaderMulLighting);
	HeladoFresa.loadModel("../models/Helado/HeladoFresa.obj");
	HeladoFresa.setShader(&shaderMulLighting);
	HeladoMenta.loadModel("../models/Helado/HeladoMenta.obj");
	HeladoMenta.setShader(&shaderMulLighting);
	HeladoMoraAzul.loadModel("../models/Helado/HeladoMoraAzul.obj");
	HeladoMoraAzul.setShader(&shaderMulLighting);
	HeladoMoraAzulFresa.loadModel("../models/Helado/HeladoMoraAzulConFresa.obj");
	HeladoMoraAzulFresa.setShader(&shaderMulLighting);

	//Piruletas models
	PiruletaAmarillo.loadModel("../models/PaletaPirueta/PaletaPiruetaAmarillo.obj");
	PiruletaAmarillo.setShader(&shaderMulLighting);
	PiruletaRojo.loadModel("../models/PaletaPirueta/PaletaPiruetaRojo.obj");
	PiruletaRojo.setShader(&shaderMulLighting);
	PiruletaVerde.loadModel("../models/PaletaPirueta/PaletaPiruetaVerde.obj");
	PiruletaVerde.setShader(&shaderMulLighting);

	//BalKirby model
	BallKirby.loadModel("../models/BallKirby/ballkirby.obj");
	BallKirby.setShader(&shaderMulLighting);

	//Lamp model
	BastonLampara.loadModel("../models/BastonLampara/BastonLampara.obj");
	BastonLampara.setShader(&shaderMulLighting);

	//Cake model
	Cake.loadModel("../models/Cake/Cake.obj");
	Cake.setShader(&shaderMulLighting);

	//Chocolate model
	Chocolate.loadModel("../models/Chocolate/Chocolate.obj");
	Chocolate.setShader(&shaderMulLighting);

	//ChocoPaleta model
	ChocoPaleta.loadModel("../models/ChocoPaleta/ChocoPaleta.obj");
	ChocoPaleta.setShader(&shaderMulLighting);

	//Cookie model
	Cookie.loadModel("../models/Cookie/Cookie.obj");
	Cookie.setShader(&shaderMulLighting);

	//Cute Home 1 model
	CuteHome1.loadModel("../models/CuteHome1/Cute Home M1.obj");
	CuteHome1.setShader(&shaderMulLighting);

	//Cute Home 2 model
	CuteHome2.loadModel("../models/CuteHouse2/Cute House 2.obj");
	CuteHome2.setShader(&shaderMulLighting);

	//Cute Home Shop model
	CuteShop.loadModel("../models/CuteHouseShop/Regular Flower Shop.obj");
	CuteShop.setShader(&shaderMulLighting);

	//Ice Cream Sign model
	IceCreamSign.loadModel("../models/IceCreamSign/icecreamsign.obj");
	IceCreamSign.setShader(&shaderMulLighting);

	//Nube model
	Nube.loadModel("../models/Nube/nube.obj");
	Nube.setShader(&shaderMulLighting);

	//Paleta model
	Paleta.loadModel("../models/Paleta/paleta.obj");
	Paleta.setShader(&shaderMulLighting);

	//Strawberry model
	Strawberry.loadModel("../models/Strawberry/Strawberry.obj");
	Strawberry.setShader(&shaderMulLighting);

	//SweerCarrito model
	SweetCarrito.loadModel("../models/SweetCarrito/1.obj");
	SweetCarrito.setShader(&shaderMulLighting);

	//Cute Gun model
	CuteGun.loadModel("../models/Water Gun (DR)/Water Gun (DR).obj");
	CuteGun.setShader(&shaderMulLighting);


	//Mayow Animate Model
	MayowCuteAnimate.loadModel("../models/ChicaMay/MayAnimacionesPistola.fbx");
	MayowCuteAnimate.setShader(&shaderMulLighting);

	//Posicion de la camara
	glm::vec3 posicion_camara = glm::vec3(0.0, 0.0, 0.0);
	camera->setPosition(posicion_camara);
	camera->setDistanceFromTarget(distanceFromTarget);
	camera->setSensitivity(1.0f); // velocidad de la camara
	//Para camara en Primera persona inicial
	posicion_camara = glm::vec3(5.0, 20.0, 5.0);
	cameraPP->setPosition(posicion_camara);
	//followcamera->setPosition(posicion_camara);

	// Definimos el tamanio de la imagen
	int imageWidth, imageHeight;
	FIBITMAP *bitmap;
	unsigned char *data;

	// Carga de texturas para el skybox
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	// Tipo de textura CUBE MAP
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		for (int cont_dia = 0; cont_dia < 10000; cont_dia++) {
			dia = true;
			if (cont_dia >= 10000) {
				dia = false;
			}
		}
		

		if (dia == true) {
			skyboxTexture = Texture(fileNames[i]);
		}
		else {
			skyboxTexture = Texture(fileNames2[i]);
		}
		FIBITMAP *bitmap = skyboxTexture.loadImage(true);
		unsigned char *data = skyboxTexture.convertToData(bitmap, imageWidth,
			imageHeight);
		if (data) {
			glTexImage2D(types[i], 0, GL_RGBA, imageWidth, imageHeight, 0,
				GL_BGRA, GL_UNSIGNED_BYTE, data);
		}
		else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage(bitmap);
	}

	// Definiendo la textura a utilizar
	Texture textureTerrainBackground("../Textures/Floor/nubeRosa.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainBackground.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainBackground.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBackgroundID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBackgroundID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainBackground.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainR("../Textures/Floor/nubeVerde.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainR.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainR.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainRID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainR.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainG("../Textures/Floor/nubeAzul.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainG.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainG.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainGID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainG.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainB("../Textures/Floor/nubeAmarilla.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainB.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainB.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el encargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainB.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainBlendMap("../Textures/blendMap.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainBlendMap.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainBlendMap.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBlendMapID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainBlendMap.freeImage(bitmap);


	Texture textureParticlesFountain("../Textures/Particulas/Estrellas.png");
	bitmap = textureParticlesFountain.loadImage();
	data = textureParticlesFountain.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureParticleFountainID);
	glBindTexture(GL_TEXTURE_2D, textureParticleFountainID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	textureParticlesFountain.freeImage(bitmap);
	/*
	Texture textureParticleFire("../Textures/fire.png");
	bitmap = textureParticleFire.loadImage();
	data = textureParticleFire.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureParticleFireID);
	glBindTexture(GL_TEXTURE_2D, textureParticleFireID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	textureParticleFire.freeImage(bitmap);

	std::uniform_real_distribution<float> distr01 = std::uniform_real_distribution<float>(0.0f, 1.0f);
	std::mt19937 generator;
	std::random_device rd;
	generator.seed(rd());
	int size = nParticlesFire * 2;
	std::vector<GLfloat> randData(size);
	for (int i = 0; i < randData.size(); i++) {
		randData[i] = distr01(generator);
	}

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_1D, texId);
	glTexStorage1D(GL_TEXTURE_1D, 1, GL_R32F, size);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, size, GL_RED, GL_FLOAT, randData.data());
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	shaderParticlesFire.setInt("Pass", 1);
	shaderParticlesFire.setInt("ParticleTex", 0);
	shaderParticlesFire.setInt("RandomTex", 1);
	shaderParticlesFire.setFloat("ParticleLifetime", particleLifetime);
	shaderParticlesFire.setFloat("ParticleSize", particleSize);
	shaderParticlesFire.setVectorFloat3("Accel", glm::value_ptr(glm::vec3(0.0f, 0.1f, 0.0f)));
	shaderParticlesFire.setVectorFloat3("Emitter", glm::value_ptr(glm::vec3(0.0f)));

	glm::mat3 basis;
	glm::vec3 u, v, n;
	v = glm::vec3(0, 1, 0);
	n = glm::cross(glm::vec3(1, 0, 0), v);
	if (glm::length(n) < 0.00001f) {
		n = glm::cross(glm::vec3(0, 1, 0), v);
	}
	u = glm::cross(v, n);
	basis[0] = glm::normalize(u);
	basis[1] = glm::normalize(v);
	basis[2] = glm::normalize(n);
	shaderParticlesFire.setMatrix3("EmitterBasis", 1, false, glm::value_ptr(basis));
	*/
	/*******************************************
	 * Inicializacion de los buffers de la fuente
	 *******************************************/
	initParticleBuffers();

	/*******************************************
	 * Inicializacion de los buffers del fuego
	 *******************************************/
	//initParticleBuffersFire();

	/*******************************************
	 * Inicializacion del framebuffer para
	 * almacenar el buffer de profunidadad
	 *******************************************/
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	/*******************************************
	 * OpenAL init
	 *******************************************/
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError(); // clear any error messages
	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating buffers !!\n");
		exit(1);
	}
	else {
		printf("init() - No errors yet.");
	}
	// Config source 0
	// Generate buffers, or else no sound will happen!
	alGenBuffers(NUM_BUFFERS, buffer);
	buffer[0] = alutCreateBufferFromFile("../sounds/cuteMusicFondo.wav");
	buffer[1] = alutCreateBufferFromFile("../sounds/Saltito.wav");
//	buffer[2] = alutCreateBufferFromFile("../sounds/darth_vader.wav");
	int errorAlut = alutGetError();
	if (errorAlut != ALUT_ERROR_NO_ERROR) {
		printf("- Error open files with alut %d !!\n", errorAlut);
		exit(2);
	}


	alGetError(); /* clear error */
	alGenSources(NUM_SOURCES, source);

	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating sources !!\n");
		exit(2);
	}
	else {
		printf("init - no errors after alGenSources\n");
	}
	//Musica de fondo
	alSourcef(source[0], AL_PITCH, 1.0f);
	alSourcef(source[0], AL_GAIN, 3.0f);
	alSourcefv(source[0], AL_POSITION, source0Pos);
	alSourcefv(source[0], AL_VELOCITY, source0Vel);
	alSourcei(source[0], AL_BUFFER, buffer[0]);
	alSourcei(source[0], AL_LOOPING, AL_TRUE);
	alSourcef(source[0], AL_MAX_DISTANCE, 2000);

	//Sonido Pelotas
	alSourcef(source[1], AL_PITCH, 1.0f);
	alSourcef(source[1], AL_GAIN, 3.0f);
	alSourcefv(source[1], AL_POSITION, source1Pos);
	alSourcefv(source[1], AL_VELOCITY, source1Vel);
	alSourcei(source[1], AL_BUFFER, buffer[1]);
	alSourcei(source[1], AL_LOOPING, AL_TRUE);
	alSourcef(source[1], AL_MAX_DISTANCE, 40);
}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Shaders Delete
	shader.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderTerrain.destroy();
	shaderParticlesFountain.destroy();
	shaderParticlesFire.destroy();

	// Basic objects Delete
	skyboxSphere.destroy();
	boxCollider.destroy();
	sphereCollider.destroy();
	boxViewDepth.destroy();
	boxLightViewBox.destroy();

	// Terrains objects Delete
	terrain.destroy();

	// Custom objects Delete
	panditaAmarillo.destroy();
	panditaAzul.destroy();
	panditaNaranja.destroy();
	panditaRojo.destroy();
	panditaVerde.destroy();
	CaramAmarillo.destroy();
	CaramAzul.destroy();
	CaramRosa.destroy();
	CaramVerde.destroy();
	DonaChocolate.destroy();
	DonaFresa.destroy();
	HeladoChocolate.destroy();
	HeladoFresa.destroy();
	HeladoMenta.destroy();
	HeladoMoraAzul.destroy();
	HeladoMoraAzulFresa.destroy();
	PiruletaAmarillo.destroy();
	PiruletaRojo.destroy();
	PiruletaVerde.destroy();
	BallKirby.destroy();
	BastonLampara.destroy();
	Cake.destroy();
	Chocolate.destroy();
	ChocoPaleta.destroy();
	Cookie.destroy();
	CuteHome1.destroy();
	CuteHome2.destroy();
	CuteShop.destroy();
	IceCreamSign.destroy();
	Nube.destroy();
	Paleta.destroy();
	Strawberry.destroy();
	SweetCarrito.destroy();

	// Custom objects animate
	MayowCuteAnimate.destroy();

	// Textures Delete
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureCespedID);
	glDeleteTextures(1, &textureWallID);
	glDeleteTextures(1, &textureWindowID);
	glDeleteTextures(1, &textureHighwayID);
	glDeleteTextures(1, &textureLandingPadID);
	glDeleteTextures(1, &textureTerrainBackgroundID);
	glDeleteTextures(1, &textureTerrainRID);
	glDeleteTextures(1, &textureTerrainGID);
	glDeleteTextures(1, &textureTerrainBID);
	glDeleteTextures(1, &textureTerrainBlendMapID);
	glDeleteTextures(1, &textureParticleFountainID);
	//glDeleteTextures(1, &textureParticleFireID);

	// Cube Maps Delete
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &skyboxTextureID);

	// Remove the buffer of the fountain particles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &initVel);
	glDeleteBuffers(1, &startTime);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAOParticles);
	/*
	// Remove the buffer of the fire particles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, posBuf);
	glDeleteBuffers(2, velBuf);
	glDeleteBuffers(2, age);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	glDeleteTransformFeedbacks(2, feedback);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAOParticlesFire);
*/
}


void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
	int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	distanceFromTarget -= yoffset;
	camera->setDistanceFromTarget(distanceFromTarget);
}

void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}

	if (camaraActivada == 1) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPP->moveFrontCamera(true, deltaTime + 0.3);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPP->moveFrontCamera(false, deltaTime + 0.3);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPP->moveRightCamera(false, deltaTime + 0.3);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPP->moveRightCamera(true, deltaTime + 0.3);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			cameraPP->mouseMoveCamera(offsetX, offsetY, deltaTime);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			cameraPP->mouseMoveCamera(offsetX, offsetY, deltaTime);

	}
	else {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			camera->mouseMoveCamera(offsetX, 0.0, deltaTime);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			camera->mouseMoveCamera(offsetX, offsetY, deltaTime);
	}
	

	// Seleccionar modelo
	if (enableCountSelected && glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
		enableCountSelected = false;
		modelSelected++;
		if (modelSelected > 1)
			modelSelected = 0;
		std::cout << "modelSelected:" << modelSelected << std::endl;
	}
	else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
		enableCountSelected = true;

	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	
	if (present == 1) {
		int count;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
		if (axes[0] < -0.5) {
			matrixModelMayow = glm::rotate(matrixModelMayow, glm::radians(1.0f), glm::vec3(0, 1, 0));
			animationIndex = 1;
		}
		else if (axes[0] > 0.5) {
			matrixModelMayow = glm::rotate(matrixModelMayow, glm::radians(-1.0f), glm::vec3(0, 1, 0));
			animationIndex = 1;
		}
		else if (axes[1] > 0.5) {
			matrixModelMayow = glm::translate(matrixModelMayow, glm::vec3(0, 0, 0.3));
			animationIndex = 1;
		}
		else if(axes[1] < -0.5) {
			matrixModelMayow = glm::translate(matrixModelMayow, glm::vec3(0, 0, -0.3));
			animationIndex = 1;
		}
		else if (axes[2] < -0.5) {
			camera->mouseMoveCamera(offsetX, 0.0, deltaTime);
		}
		else if (axes[2] > 0.5) {
			camera->mouseMoveCamera(offsetX, offsetY, deltaTime);
		}
		else if (axes[4] > 0.5) {
			animationIndex = 0;
		}
		else if (axes[5] > 0.5) {
			animationIndex = 2;
		}
		else {
			animationIndex = 7;
		}
		const char *Control_name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		
	}
	offsetX = 0;
	offsetY = 0;
//Desplazamiento y movimiento

	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT  ) == GLFW_PRESS){
		matrixModelMayow = glm::rotate(matrixModelMayow, glm::radians(1.0f), glm::vec3(0, 1, 0));
		animationIndex = 1;
	}else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		matrixModelMayow = glm::rotate(matrixModelMayow, glm::radians(-1.0f), glm::vec3(0, 1, 0));
		animationIndex = 1;
	}if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		matrixModelMayow = glm::translate(matrixModelMayow, glm::vec3(0, 0, 0.3));
		animationIndex = 1;
	}else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		matrixModelMayow = glm::translate(matrixModelMayow, glm::vec3(0, 0, -0.3));
		animationIndex = 1;
	}
	else if (present == 0) {
		animationIndex = 7;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && selec_vista) {
		selec_vista = false;
		if (camaraActivada == 1) {
			camaraActivada = 0;
		}
		else if (camaraActivada == 0) {
			camaraActivada = 1;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_K) == GLFW_RELEASE) {
		selec_vista = true;
	}
	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;

	glm::mat4 view;
	glm::vec3 axis;
	glm::vec3 target;
	float angleTarget;
	//Matrix Models
	matrixModelHeladoChocolate = glm::translate(matrixModelHeladoChocolate, glm::vec3(-200.4375, 0, -200.5));
	matrixModelHeladoFresa = glm::translate(matrixModelHeladoFresa, glm::vec3(-576.5625, 0, -354.6875));
	matrixModelHeladoMenta = glm::translate(matrixModelHeladoMenta, glm::vec3(-169.53125, 0, -478.125));
	matrixModelHeladoMoraAzul = glm::translate(matrixModelHeladoMoraAzul, glm::vec3(-400.78125, 0, -623.4375));
	matrixModelHeladoMoraAzulFresa = glm::translate(matrixModelHeladoMoraAzulFresa, glm::vec3(-10.0, 0.0, 50.0));
	matrixModelPiruletaAmarillo = glm::translate(matrixModelPiruletaAmarillo, glm::vec3(-100.0, 0.0, 10.0));
	matrixModelPiruletaRojo = glm::translate(matrixModelPiruletaRojo, glm::vec3(-222.65625, 0, 61.71875));
	matrixModelPiruletaVerde = glm::translate(matrixModelPiruletaVerde, glm::vec3(-7.8125, 0, -278.125));
	matrixModelBallKirby = glm::translate(matrixModelBallKirby, glm::vec3(-14.0, 0.0, 2.0));
	matrixModelIceCreamSign = glm::translate(matrixModelIceCreamSign, glm::vec3(-25.0, 0.0, -85.0));
	matrixModelNube = glm::translate(matrixModelIceCreamSign, glm::vec3(0.0, 20.0, 2.0));
	matrixModelPaleta = glm::translate(matrixModelPaleta, glm::vec3(-78.90625, 0, -670.3125));
	matrixModelStrawberry = glm::translate(matrixModelStrawberry, glm::vec3(-200.0, 0.0, -300.0));
	matrixModelSweetCarrito = glm::translate(matrixModelSweetCarrito, glm::vec3(15.0, 0.0, -70.0));
	matrixModelCuteGun = glm::translate(matrixModelCuteGun, glm::vec3(-523.4375 - 400.78125));




	//Matrix Models Animate
	matrixModelMayow = glm::translate(matrixModelMayow, glm::vec3(0.0, 0.0, 0.0));

	lastTime = TimeManager::Instance().GetTime();

	// Time for the particles animation
	currTimeParticlesAnimation = lastTime;
	lastTimeParticlesAnimation = lastTime;

	//currTimeParticlesAnimationFire = lastTime;
	//lastTimeParticlesAnimationFire = lastTime;

	glm::vec3 lightPos = glm::vec3(20.0, 50.0, 0.0);
	shadowBox = new ShadowBox(-lightPos, camera.get(), 60.0f, 20.0f, 60.0f);

	while (psi) {
		currTime = TimeManager::Instance().GetTime();
		if (currTime - lastTime < 0.016666667) {
			glfwPollEvents();
			continue;
		}
		lastTime = currTime;
		TimeManager::Instance().CalculateFrameRate(true);
		deltaTime = TimeManager::Instance().DeltaTime;
		psi = processInput(true);

		std::map<std::string, bool> collisionDetection;

		// Variables donde se guardan las matrices de cada articulacion por 1 frame
		std::vector<float> matrixDartJoints;
		std::vector<glm::mat4> matrixDart;

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)screenWidth / (float)screenHeight, 0.1f, 400.0f); //Antes 0.01f, 400.0f

		if (modelSelected == 1) {
			axis = glm::axis(glm::quat_cast(matrixModelMayow));
			angleTarget = glm::angle(glm::quat_cast(matrixModelMayow));
			target = matrixModelMayow[3];
		}
		else {
			axis = glm::axis(glm::quat_cast(matrixModelMayow));
			angleTarget = glm::angle(glm::quat_cast(matrixModelMayow));
			target = matrixModelMayow[3];
		}

		glm::mat4 view;

		if (std::isnan(angleTarget))
			angleTarget = 0.0;
		if (axis.y < 0)
			angleTarget = -angleTarget;
		camera->setCameraTarget(target);
		camera->setAngleTarget(angleTarget);
		camera->updateCamera();
		if (camaraActivada == true) {
			//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), target, glm::vec3(0.0f, 1.0f, 0.0f));
			view = cameraPP->getViewMatrix();
		}
		else
			view = camera->getViewMatrix();

		shadowBox->update(screenWidth, screenHeight);
		glm::vec3 centerBox = shadowBox->getCenter();

		// Projection light shadow mapping
		glm::mat4 lightProjection = glm::mat4(1.0f), lightView = glm::mat4(1.0f);
		glm::mat4 lightSpaceMatrix;

		lightProjection[0][0] = 2.0f / shadowBox->getWidth();
		lightProjection[1][1] = 2.0f / shadowBox->getHeight();
		lightProjection[2][2] = -2.0f / shadowBox->getLength();
		lightProjection[3][3] = 1.0f;

		lightView = glm::lookAt(centerBox, centerBox + glm::normalize(-lightPos), glm::vec3(0.0, 1.0, 0.0));

		lightSpaceMatrix = lightProjection * lightView;
		shaderDepth.setMatrix4("lightSpaceMatrix", 1, false, glm::value_ptr(lightSpaceMatrix));

		// Settea la matriz de vista y projection al shader con solo color
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con skybox
		shaderSkybox.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
			glm::value_ptr(glm::mat4(glm::mat3(view))));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderMulLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false,
			glm::value_ptr(view));
		shaderMulLighting.setMatrix4("lightSpaceMatrix", 1, false,
			glm::value_ptr(lightSpaceMatrix));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderTerrain.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderTerrain.setMatrix4("view", 1, false,
			glm::value_ptr(view));
		shaderTerrain.setMatrix4("lightSpaceMatrix", 1, false,
			glm::value_ptr(lightSpaceMatrix));
		// Settea la matriz de vista y projection al shader para el fountain
		shaderParticlesFountain.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderParticlesFountain.setMatrix4("view", 1, false,
			glm::value_ptr(view));
		// Settea la matriz de vista y projection al shader para el fuego
		shaderParticlesFire.setInt("Pass", 2);
		shaderParticlesFire.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shaderParticlesFire.setMatrix4("view", 1, false, glm::value_ptr(view));

		/*******************************************
		 * Propiedades de neblina
		 *******************************************/
		shaderMulLighting.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(1.0, 0.69412, 0.73334)));
		shaderTerrain.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(1.0, 0.69412, 0.73334)));
		shaderSkybox.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(1.0, 0.69412, 0.73334)));

		/*******************************************
		 * Propiedades Luz direccional
		 *******************************************/
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-0.707106781, -0.707106781, 0.0)));

		/*******************************************
		 * Propiedades Luz direccional Terrain
		 *******************************************/
		shaderTerrain.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderTerrain.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderTerrain.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderTerrain.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderTerrain.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-0.707106781, -0.707106781, 0.0)));

		/*******************************************
		 * Propiedades SpotLights
		 *******************************************/

		/*glm::vec3 spotPosition = glm::vec3(modelMatrixHeli * glm::vec4(0.32437, 0.226053, 1.79149, 1.0));
		shaderMulLighting.setInt("spotLightCount", 1);
		shaderTerrain.setInt("spotLightCount", 1);
		shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.2, 0.3, 0.2)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
		shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, -1, 0)));
		shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[0].linear", 0.074);
		shaderMulLighting.setFloat("spotLights[0].quadratic", 0.03);
		shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5f)));
		shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.2, 0.3, 0.2)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTerrain.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
		shaderTerrain.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, -1, 0)));
		shaderTerrain.setFloat("spotLights[0].constant", 1.0);
		shaderTerrain.setFloat("spotLights[0].linear", 0.074);
		shaderTerrain.setFloat("spotLights[0].quadratic", 0.03);
		shaderTerrain.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5f)));
		shaderTerrain.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));
		*/
		/*******************************************
		 * Propiedades PointLights
		 *******************************************/

		shaderMulLighting.setInt("pointLightCount", lamp1Position.size());
		shaderTerrain.setInt("pointLightCount", lamp1Position.size());
		for (int i = 0; i < lamp1Position.size(); i++) {
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0f);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp1Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp1Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(1.0, 1.0, 1.0));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0, 15.3585, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.01);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.01);
		}

		/*******************************************
		 * 1.- We render the depth buffer
		 *******************************************/

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// render scene from light's point of view
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		//glCullFace(GL_FRONT);
		prepareDepthScene();
		renderScene(false);
		//glCullFace(GL_BACK);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		/*******************************************
		 * Debug to view the texture view map
		 *******************************************/

		 // reset viewport
		 /*glViewport(0, 0, screenWidth, screenHeight);
		 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		 // render Depth map to quad for visual debugging
		 shaderViewDepth.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
		 shaderViewDepth.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
		 glActiveTexture(GL_TEXTURE0);
		 glBindTexture(GL_TEXTURE_2D, depthMap);
		 boxViewDepth.setScale(glm::vec3(2.0, 2.0, 1.0));
		 boxViewDepth.render();*/

		 /*******************************************
		  * 2.- We render the normal objects
		  *******************************************/
		glViewport(0, 0, screenWidth, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		prepareScene();
		glActiveTexture(GL_TEXTURE10);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		shaderMulLighting.setInt("shadowMap", 10);
		shaderTerrain.setInt("shadowMap", 10);


		/*******************************************
		 * Skybox
		 *******************************************/
		GLint oldCullFaceMode;
		GLint oldDepthFuncMode;
		// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
		glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
		shaderSkybox.setFloat("skybox", 0);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
		glActiveTexture(GL_TEXTURE0);
		skyboxSphere.render();
		glCullFace(oldCullFaceMode);
		glDepthFunc(oldDepthFuncMode);
		renderScene(true);
		/*******************************************
		 * Debug to box light box
		 *******************************************/
		 /*glm::vec3 front = glm::normalize(-lightPos);
		 glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), front));
		 glm::vec3 up = glm::normalize(glm::cross(front, right));
		 glDisable(GL_CULL_FACE);
		 glm::mat4 boxViewTransform = glm::mat4(1.0f);
		 boxViewTransform = glm::translate(boxViewTransform, centerBox);
		 boxViewTransform[0] = glm::vec4(right, 0.0);
		 boxViewTransform[1] = glm::vec4(up, 0.0);
		 boxViewTransform[2] = glm::vec4(front, 0.0);
		 boxViewTransform = glm::scale(boxViewTransform, glm::vec3(shadowBox->getWidth(), shadowBox->getHeight(), shadowBox->getLength()));
		 boxLightViewBox.enableWireMode();
		 boxLightViewBox.render(boxViewTransform);
		 glEnable(GL_CULL_FACE);*/

		 /*******************************************
		 * Creacion de colliders
		 * IMPORTANT do this before interpolations
		 *******************************************/
		 // Lamps1 colliders
		for (int i = 0; i < lamp1Position.size(); i++) {
			AbstractModel::OBB lampCollider;
			glm::mat4 modelMatrixColliderLamp = glm::mat4(1.0);
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, lamp1Position[i]);
			modelMatrixColliderLamp = glm::rotate(modelMatrixColliderLamp, glm::radians(lamp1Orientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "BastonLampara-" + std::to_string(i), lampCollider, modelMatrixColliderLamp);
			// Set the orientation of collider before doing the scale
			lampCollider.u = glm::quat_cast(modelMatrixColliderLamp);
			modelMatrixColliderLamp = glm::scale(modelMatrixColliderLamp, glm::vec3(2.0, 9.5, 10.0));
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, BastonLampara.getObb().c);
			lampCollider.c = glm::vec3(modelMatrixColliderLamp[3]);
			lampCollider.e = BastonLampara.getObb().e * glm::vec3(2.0, 9.5, 10.0);
			std::get<0>(collidersOBB.find("BastonLampara-" + std::to_string(i))->second) = lampCollider;
		}

		//Cute Home1 Colliders 
		for (int i = 0; i < CutH1Position.size(); i++) {
			AbstractModel::OBB CutH1Collider;
			glm::mat4 modelMatrixColliderCutH1 = glm::mat4(1.0);
			modelMatrixColliderCutH1 = glm::translate(modelMatrixColliderCutH1, CutH1Position[i]);
			modelMatrixColliderCutH1 = glm::rotate(modelMatrixColliderCutH1, glm::radians(CutH1Orientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "CuteHome1-" + std::to_string(i), CutH1Collider, modelMatrixColliderCutH1);
			// Set the orientation of collider before doing the scale
			CutH1Collider.u = glm::quat_cast(modelMatrixColliderCutH1);
			modelMatrixColliderCutH1 = glm::scale(modelMatrixColliderCutH1, glm::vec3(3.5, 3.5, 3.5));
			modelMatrixColliderCutH1 = glm::translate(modelMatrixColliderCutH1, CuteHome1.getObb().c);
			CutH1Collider.c = glm::vec3(modelMatrixColliderCutH1[3]);
			CutH1Collider.e = CuteHome1.getObb().e * glm::vec3(3.5, 3.5, 3.5);
			std::get<0>(collidersOBB.find("CuteHome1-" + std::to_string(i))->second) = CutH1Collider;
		}

		//Cute Home2 Colliders 
		for (int i = 0; i < CutH2Position.size(); i++) {
			AbstractModel::OBB CutH2Collider;
			glm::mat4 modelMatrixColliderCutH2 = glm::mat4(1.0);
			modelMatrixColliderCutH2 = glm::translate(modelMatrixColliderCutH2, CutH2Position[i]);
			modelMatrixColliderCutH2 = glm::rotate(modelMatrixColliderCutH2, glm::radians(CutH2Orientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "CuteHome2-" + std::to_string(i), CutH2Collider, modelMatrixColliderCutH2);
			// Set the orientation of collider before doing the scale
			CutH2Collider.u = glm::quat_cast(modelMatrixColliderCutH2);
			modelMatrixColliderCutH2 = glm::scale(modelMatrixColliderCutH2, glm::vec3(1.9, 1.7, 1.8));
			modelMatrixColliderCutH2 = glm::translate(modelMatrixColliderCutH2, CuteHome2.getObb().c);
			CutH2Collider.c = glm::vec3(modelMatrixColliderCutH2[3]);
			CutH2Collider.e = CuteHome2.getObb().e * glm::vec3(1.9, 1.7, 1.8);
			std::get<0>(collidersOBB.find("CuteHome2-" + std::to_string(i))->second) = CutH2Collider;
		}
		//Cute Shop Colliders 
		for (int i = 0; i < CutShPosition.size(); i++) {
			AbstractModel::OBB CutShCollider;
			glm::mat4 modelMatrixColliderCutSh = glm::mat4(1.0);
			modelMatrixColliderCutSh = glm::translate(modelMatrixColliderCutSh, CutShPosition[i]);
			modelMatrixColliderCutSh = glm::rotate(modelMatrixColliderCutSh, glm::radians(CutShOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "CuteShop-" + std::to_string(i), CutShCollider, modelMatrixColliderCutSh);
			// Set the orientation of collider before doing the scale
			CutShCollider.u = glm::quat_cast(modelMatrixColliderCutSh);
			modelMatrixColliderCutSh = glm::scale(modelMatrixColliderCutSh, glm::vec3(3.5, 3.5, 3.5));
			modelMatrixColliderCutSh = glm::translate(modelMatrixColliderCutSh, CuteShop.getObb().c);
			CutShCollider.c = glm::vec3(modelMatrixColliderCutSh[3]);
			CutShCollider.e = CuteShop.getObb().e * glm::vec3(3.5, 3.5, 3.5);
			std::get<0>(collidersOBB.find("CuteShop-" + std::to_string(i))->second) = CutShCollider;
		}
		//Cake Colliders 
		for (int i = 0; i < CakePosition.size(); i++) {
			AbstractModel::OBB CakeCollider;
			glm::mat4 modelMatrixColliderCake = glm::mat4(1.0);
			modelMatrixColliderCake = glm::translate(modelMatrixColliderCake, CakePosition[i]);
			modelMatrixColliderCake = glm::rotate(modelMatrixColliderCake, glm::radians(CakeOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "Cake-" + std::to_string(i), CakeCollider, modelMatrixColliderCake);
			// Set the orientation of collider before doing the scale
			CakeCollider.u = glm::quat_cast(modelMatrixColliderCake);
			modelMatrixColliderCake = glm::scale(modelMatrixColliderCake, glm::vec3(80.0, 75.0, 80.0));
			modelMatrixColliderCake = glm::translate(modelMatrixColliderCake, Cake.getObb().c);
			CakeCollider.c = glm::vec3(modelMatrixColliderCake[3]);
			CakeCollider.e = Cake.getObb().e * glm::vec3(80.0, 75.0, 80.0);
			std::get<0>(collidersOBB.find("Cake-" + std::to_string(i))->second) = CakeCollider;
		}

		//Caramelos Colliders 
		for (int i = 0; i < CarAmPosition.size(); i++) {
			AbstractModel::SBB CarAmCollider;
			glm::mat4 modelMatrixColliderCarAm = glm::mat4(1.0);
			modelMatrixColliderCarAm = glm::translate(modelMatrixColliderCarAm, CarAmPosition[i]);
			modelMatrixColliderCarAm = glm::rotate(modelMatrixColliderCarAm, glm::radians(CarAmOrientation[i]),
				glm::vec3(0, 1, 0));
			// Set the orientation of collider before doing the scale
			modelMatrixColliderCarAm = glm::scale(modelMatrixColliderCarAm, glm::vec3(10.0, 10.0, 10.0));
			modelMatrixColliderCarAm = glm::translate(modelMatrixColliderCarAm, CaramAmarillo.getSbb().c);
			CarAmCollider.c = glm::vec3(modelMatrixColliderCarAm[3]);
			CarAmCollider.ratio = CaramAmarillo.getSbb().ratio * 6.0;
			std::get<0>(collidersSBB.find("CarameloAmarillo-" + std::to_string(i))->second) = CarAmCollider;
			addOrUpdateColliders(collidersSBB, "CarameloAmarillo-" + std::to_string(i), CarAmCollider, modelMatrixColliderCarAm);
		}
		for (int i = 0; i < CarAzPosition.size(); i++) {
			AbstractModel::SBB CarAzCollider;
			glm::mat4 modelMatrixColliderCarAz = glm::mat4(1.0);
			modelMatrixColliderCarAz = glm::translate(modelMatrixColliderCarAz, CarAzPosition[i]);
			modelMatrixColliderCarAz = glm::rotate(modelMatrixColliderCarAz, glm::radians(CarAzOrientation[i]),
				glm::vec3(0, 1, 0));
			// Set the orientation of collider before doing the scale
			modelMatrixColliderCarAz = glm::scale(modelMatrixColliderCarAz, glm::vec3(15.5, 15.5, 15.5));
			modelMatrixColliderCarAz = glm::translate(modelMatrixColliderCarAz, CaramAzul.getSbb().c);
			CarAzCollider.c = glm::vec3(modelMatrixColliderCarAz[3]);
			CarAzCollider.ratio = CaramAzul.getSbb().ratio * 5.4;
			std::get<0>(collidersSBB.find("CarameloAzul-" + std::to_string(i))->second) = CarAzCollider;
			addOrUpdateColliders(collidersSBB, "CarameloAzul-" + std::to_string(i), CarAzCollider, modelMatrixColliderCarAz);
		}
		for (int i = 0; i < CarRoPosition.size(); i++) {
			AbstractModel::SBB CarRoCollider;
			glm::mat4 modelMatrixColliderCarRo = glm::mat4(1.0);
			modelMatrixColliderCarRo = glm::translate(modelMatrixColliderCarRo, CarRoPosition[i]);
			modelMatrixColliderCarRo = glm::rotate(modelMatrixColliderCarRo, glm::radians(CarRoOrientation[i]),
				glm::vec3(0, 1, 0));
			// Set the orientation of collider before doing the scale
			modelMatrixColliderCarRo = glm::scale(modelMatrixColliderCarRo, glm::vec3(30.5, 20.5, 1.5));
			modelMatrixColliderCarRo = glm::translate(modelMatrixColliderCarRo, CaramRosa.getSbb().c);
			CarRoCollider.c = glm::vec3(modelMatrixColliderCarRo[3]);
			CarRoCollider.ratio = CaramRosa.getSbb().ratio * 7.0;
			std::get<0>(collidersSBB.find("CarameloRosa-" + std::to_string(i))->second) = CarRoCollider;
			addOrUpdateColliders(collidersSBB, "CarameloRosa-" + std::to_string(i), CarRoCollider, modelMatrixColliderCarRo);
		}
		for (int i = 0; i < CarVerPosition.size(); i++) {
			AbstractModel::SBB CarVerCollider;
			glm::mat4 modelMatrixColliderCarVer = glm::mat4(1.0);
			modelMatrixColliderCarVer = glm::translate(modelMatrixColliderCarVer, CarVerPosition[i]);
			modelMatrixColliderCarVer = glm::rotate(modelMatrixColliderCarVer, glm::radians(CarVerOrientation[i]),
				glm::vec3(0, 1, 0));
			// Set the orientation of collider before doing the scale
			modelMatrixColliderCarVer = glm::scale(modelMatrixColliderCarVer, glm::vec3(15.0, 15.0, 15.0));
			modelMatrixColliderCarVer = glm::translate(modelMatrixColliderCarVer, CaramVerde.getSbb().c);
			CarVerCollider.c = glm::vec3(modelMatrixColliderCarVer[3]);
			CarVerCollider.ratio = CaramVerde.getSbb().ratio * 9.0;
			std::get<0>(collidersSBB.find("CarameloVerde-" + std::to_string(i))->second) = CarVerCollider;
			addOrUpdateColliders(collidersSBB, "CarameloVerde-" + std::to_string(i), CarVerCollider, modelMatrixColliderCarVer);
		}

		//Collider del los chocolate
		for (int i = 0; i < ChocoPosition.size(); i++) {
			AbstractModel::OBB ChocoCollider;
			glm::mat4 modelMatrixColliderChoco = glm::mat4(1.0);
			modelMatrixColliderChoco = glm::translate(modelMatrixColliderChoco, ChocoPosition[i]);
			modelMatrixColliderChoco = glm::rotate(modelMatrixColliderChoco, glm::radians(ChocoOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "Chocolate-" + std::to_string(i), ChocoCollider, modelMatrixColliderChoco);
			// Set the orientation of collider before doing the scale
			ChocoCollider.u = glm::quat_cast(modelMatrixColliderChoco);
			modelMatrixColliderChoco = glm::scale(modelMatrixColliderChoco, glm::vec3(70.5, 70.8, 70.0));
			modelMatrixColliderChoco = glm::translate(modelMatrixColliderChoco, Chocolate.getObb().c);
			ChocoCollider.c = glm::vec3(modelMatrixColliderChoco[3]);
			ChocoCollider.e = Chocolate.getObb().e * glm::vec3(70.5, 70.8, 70.0);
			std::get<0>(collidersOBB.find("Chocolate-" + std::to_string(i))->second) = ChocoCollider;
		}

		//Collider de las chocoPaleta
		for (int i = 0; i < ChocoPPosition.size(); i++) {
			AbstractModel::OBB ChocoPCollider;
			glm::mat4 modelMatrixColliderChocoP = glm::mat4(1.0);
			modelMatrixColliderChocoP = glm::translate(modelMatrixColliderChocoP, ChocoPPosition[i]);
			modelMatrixColliderChocoP = glm::rotate(modelMatrixColliderChocoP, glm::radians(ChocoPOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "ChocoPaleta-" + std::to_string(i), ChocoPCollider, modelMatrixColliderChocoP);
			// Set the orientation of collider before doing the scale
			ChocoPCollider.u = glm::quat_cast(modelMatrixColliderChocoP);
			modelMatrixColliderChocoP = glm::scale(modelMatrixColliderChocoP, glm::vec3(2.0, 1.5, 1.5));
			modelMatrixColliderChocoP = glm::translate(modelMatrixColliderChocoP, ChocoPaleta.getObb().c);
			ChocoPCollider.c = glm::vec3(modelMatrixColliderChocoP[3]);
			ChocoPCollider.e = ChocoPaleta.getObb().e * glm::vec3(2.0, 1.5, 1.5);
			std::get<0>(collidersOBB.find("ChocoPaleta-" + std::to_string(i))->second) = ChocoPCollider;
		}
		//Collider de las Cookies
		for (int i = 0; i < CookPosition.size(); i++) {
			AbstractModel::OBB CookCollider;
			glm::mat4 modelMatrixColliderCook = glm::mat4(1.0);
			modelMatrixColliderCook = glm::translate(modelMatrixColliderCook, CookPosition[i]);
			modelMatrixColliderCook = glm::rotate(modelMatrixColliderCook, glm::radians(CookOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "Cookie-" + std::to_string(i), CookCollider, modelMatrixColliderCook);
			// Set the orientation of collider before doing the scale
			CookCollider.u = glm::quat_cast(modelMatrixColliderCook);
			modelMatrixColliderCook = glm::scale(modelMatrixColliderCook, glm::vec3(150.0, 100.5, 150.5));
			modelMatrixColliderCook = glm::translate(modelMatrixColliderCook, Cookie.getObb().c);
			CookCollider.c = glm::vec3(modelMatrixColliderCook[3]);
			CookCollider.e = Cookie.getObb().e * glm::vec3(140.0, 100.5, 140.5);
			std::get<0>(collidersOBB.find("Cookie-" + std::to_string(i))->second) = CookCollider;
		}

		//Collider de las Donas
		for (int i = 0; i < DonChoPosition.size(); i++) {
			AbstractModel::OBB DonChoCollider;
			glm::mat4 modelMatrixColliderDonCho = glm::mat4(1.0);
			modelMatrixColliderDonCho = glm::translate(modelMatrixColliderDonCho, DonChoPosition[i]);
			modelMatrixColliderDonCho = glm::rotate(modelMatrixColliderDonCho, glm::radians(DonChoOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "DonaChocolate-" + std::to_string(i), DonChoCollider, modelMatrixColliderDonCho);
			// Set the orientation of collider before doing the scale
			DonChoCollider.u = glm::quat_cast(modelMatrixColliderDonCho);
			modelMatrixColliderDonCho = glm::scale(modelMatrixColliderDonCho, glm::vec3(8.7, 8.7, 9.0));
			modelMatrixColliderDonCho = glm::translate(modelMatrixColliderDonCho, DonaChocolate.getObb().c);
			DonChoCollider.c = glm::vec3(modelMatrixColliderDonCho[3]);
			DonChoCollider.e = DonaChocolate.getObb().e * glm::vec3(8.7, 8.7, 9.0);
			std::get<0>(collidersOBB.find("DonaChocholate-" + std::to_string(i))->second) = DonChoCollider;
		}
		for (int i = 0; i < DonFrePosition.size(); i++) {
			AbstractModel::OBB DonFreCollider;
			glm::mat4 modelMatrixColliderDonFre = glm::mat4(1.0);
			modelMatrixColliderDonFre = glm::translate(modelMatrixColliderDonFre, DonFrePosition[i]);
			modelMatrixColliderDonFre = glm::rotate(modelMatrixColliderDonFre, glm::radians(DonFreOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "DonaFresa-" + std::to_string(i), DonFreCollider, modelMatrixColliderDonFre);
			// Set the orientation of collider before doing the scale
			DonFreCollider.u = glm::quat_cast(modelMatrixColliderDonFre);
			modelMatrixColliderDonFre = glm::scale(modelMatrixColliderDonFre, glm::vec3(8.7, 8.7, 9.0));
			modelMatrixColliderDonFre = glm::translate(modelMatrixColliderDonFre, DonaFresa.getObb().c);
			DonFreCollider.c = glm::vec3(modelMatrixColliderDonFre[3]);
			DonFreCollider.e = DonaFresa.getObb().e * glm::vec3(8.7, 8.7, 9.0);
			std::get<0>(collidersOBB.find("DonaFresa-" + std::to_string(i))->second) = DonFreCollider;
		}

		//Collider del los panditas
		for (int i = 0; i < PRoPosition.size(); i++) {
			AbstractModel::OBB panditaRojoCollider;
			glm::mat4 modelMatrixColliderPRo = glm::mat4(1.0);
			modelMatrixColliderPRo = glm::translate(modelMatrixColliderPRo, PRoPosition[i]);
			modelMatrixColliderPRo = glm::rotate(modelMatrixColliderPRo, glm::radians(PRoOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "panditaRojo-" + std::to_string(i), panditaRojoCollider, modelMatrixColliderPRo);
			// Set the orientation of collider before doing the scale
			panditaRojoCollider.u = glm::quat_cast(modelMatrixColliderPRo);
			modelMatrixColliderPRo = glm::scale(modelMatrixColliderPRo, glm::vec3(5.5, 5.8, 6.0));
			modelMatrixColliderPRo = glm::translate(modelMatrixColliderPRo, panditaRojo.getObb().c);
			panditaRojoCollider.c = glm::vec3(modelMatrixColliderPRo[3]);
			panditaRojoCollider.e = panditaRojo.getObb().e * glm::vec3(5.5, 5.8, 6.0);
			std::get<0>(collidersOBB.find("panditaRojo-" + std::to_string(i))->second) = panditaRojoCollider;
		}
		for (int i = 0; i < PVePosition.size(); i++) {
			AbstractModel::OBB panditaVerdeCollider;
			glm::mat4 modelMatrixColliderPVe = glm::mat4(1.0);
			modelMatrixColliderPVe = glm::translate(modelMatrixColliderPVe, PVePosition[i]);
			modelMatrixColliderPVe = glm::rotate(modelMatrixColliderPVe, glm::radians(PVeOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "panditaVerde-" + std::to_string(i), panditaVerdeCollider, modelMatrixColliderPVe);
			// Set the orientation of collider before doing the scale
			panditaVerdeCollider.u = glm::quat_cast(modelMatrixColliderPVe);
			modelMatrixColliderPVe = glm::scale(modelMatrixColliderPVe, glm::vec3(5.5, 5.8, 6.0));
			modelMatrixColliderPVe = glm::translate(modelMatrixColliderPVe, panditaVerde.getObb().c);
			panditaVerdeCollider.c = glm::vec3(modelMatrixColliderPVe[3]);
			panditaVerdeCollider.e = panditaVerde.getObb().e * glm::vec3(5.5, 5.8, 6.0);
			std::get<0>(collidersOBB.find("panditaVerde-" + std::to_string(i))->second) = panditaVerdeCollider;
		}
		for (int i = 0; i < PAzPosition.size(); i++) {
			AbstractModel::OBB panditaAzulCollider;
			glm::mat4 modelMatrixColliderPAz = glm::mat4(1.0);
			modelMatrixColliderPAz = glm::translate(modelMatrixColliderPAz, PAzPosition[i]);
			modelMatrixColliderPAz = glm::rotate(modelMatrixColliderPAz, glm::radians(PAzOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "panditaAzul-" + std::to_string(i), panditaAzulCollider, modelMatrixColliderPAz);
			// Set the orientation of collider before doing the scale
			panditaAzulCollider.u = glm::quat_cast(modelMatrixColliderPAz);
			modelMatrixColliderPAz = glm::scale(modelMatrixColliderPAz, glm::vec3(8.5, 8.8, 9.0));
			modelMatrixColliderPAz = glm::translate(modelMatrixColliderPAz, panditaAzul.getObb().c);
			panditaAzulCollider.c = glm::vec3(modelMatrixColliderPAz[3]);
			panditaAzulCollider.e = panditaAzul.getObb().e * glm::vec3(8.5, 8.8, 9.0);
			std::get<0>(collidersOBB.find("panditaAzul-" + std::to_string(i))->second) = panditaAzulCollider;
		}
		for (int i = 0; i < PAmPosition.size(); i++) {
			AbstractModel::OBB panditaAmarilloCollider;
			glm::mat4 modelMatrixColliderPAm = glm::mat4(1.0);
			modelMatrixColliderPAm = glm::translate(modelMatrixColliderPAm, PAmPosition[i]);
			modelMatrixColliderPAm = glm::rotate(modelMatrixColliderPAm, glm::radians(PAmOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "panditaAmarillo-" + std::to_string(i), panditaAmarilloCollider, modelMatrixColliderPAm);
			// Set the orientation of collider before doing the scale
			panditaAmarilloCollider.u = glm::quat_cast(modelMatrixColliderPAm);
			modelMatrixColliderPAm = glm::scale(modelMatrixColliderPAm, glm::vec3(8.5, 8.8, 9.0));
			modelMatrixColliderPAm = glm::translate(modelMatrixColliderPAm, panditaAmarillo.getObb().c);
			panditaAmarilloCollider.c = glm::vec3(modelMatrixColliderPAm[3]);
			panditaAmarilloCollider.e = panditaAmarillo.getObb().e * glm::vec3(8.5, 8.8, 9.0);
			std::get<0>(collidersOBB.find("panditaAmarillo-" + std::to_string(i))->second) = panditaAmarilloCollider;
		}
		for (int i = 0; i < PNaPosition.size(); i++) {
			AbstractModel::OBB panditaNaranjaCollider;
			glm::mat4 modelMatrixColliderPNa = glm::mat4(1.0);
			modelMatrixColliderPNa = glm::translate(modelMatrixColliderPNa, PNaPosition[i]);
			modelMatrixColliderPNa = glm::rotate(modelMatrixColliderPNa, glm::radians(PNaOrientation[i]),
				glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "panditaNaranja-" + std::to_string(i), panditaNaranjaCollider, modelMatrixColliderPNa);
			// Set the orientation of collider before doing the scale
			panditaNaranjaCollider.u = glm::quat_cast(modelMatrixColliderPNa);
			modelMatrixColliderPNa = glm::scale(modelMatrixColliderPNa, glm::vec3(4.5, 4.8, 5.0));
			modelMatrixColliderPNa = glm::translate(modelMatrixColliderPNa, panditaNaranja.getObb().c);
			panditaNaranjaCollider.c = glm::vec3(modelMatrixColliderPNa[3]);
			panditaNaranjaCollider.e = panditaNaranja.getObb().e * glm::vec3(4.5, 4.8, 5.0);
			std::get<0>(collidersOBB.find("panditaNaranja-" + std::to_string(i))->second) = panditaNaranjaCollider;
		}

		//Collider HeladoChocolate
		AbstractModel::OBB HeladoChocolateCollider;
		glm::mat4 modelmatrixColliderHeladoChocolate = glm::mat4(matrixModelHeladoChocolate);
		modelmatrixColliderHeladoChocolate = glm::rotate(modelmatrixColliderHeladoChocolate,
			glm::radians(0.0f), glm::vec3(0, 0, 1));
		// Set the orientation of collider before doing the scale
		HeladoChocolateCollider.u = glm::quat_cast(modelmatrixColliderHeladoChocolate);
		modelmatrixColliderHeladoChocolate = glm::scale(modelmatrixColliderHeladoChocolate, glm::vec3(4.0, 5.0, 4.0));
		modelmatrixColliderHeladoChocolate = glm::translate(modelmatrixColliderHeladoChocolate,
			glm::vec3(HeladoChocolate.getObb().c.x,
				HeladoChocolate.getObb().c.y,
				HeladoChocolate.getObb().c.z));
		HeladoChocolateCollider.e = HeladoChocolate.getObb().e * glm::vec3(4.0, 5.0, 4.0) * glm::vec3(1.0, 1.0, 1.0);
		HeladoChocolateCollider.c = glm::vec3(modelmatrixColliderHeladoChocolate[3]);
		addOrUpdateColliders(collidersOBB, "HeladoChocolate", HeladoChocolateCollider, matrixModelHeladoChocolate);

		//Collider HeladoFresa 
		AbstractModel::OBB HeladoFresaCollider;
		glm::mat4 modelmatrixColliderHeladoFresa = glm::mat4(matrixModelHeladoFresa);
		modelmatrixColliderHeladoFresa = glm::rotate(modelmatrixColliderHeladoFresa,
			glm::radians(0.0f), glm::vec3(0, 0, 1));
		// Set the orientation of collider before doing the scale
		HeladoFresaCollider.u = glm::quat_cast(modelmatrixColliderHeladoFresa);
		modelmatrixColliderHeladoFresa = glm::scale(modelmatrixColliderHeladoFresa, glm::vec3(5.0, 7.0, 5.0));
		modelmatrixColliderHeladoFresa = glm::translate(modelmatrixColliderHeladoFresa,
			glm::vec3(HeladoFresa.getObb().c.x,
				HeladoFresa.getObb().c.y,
				HeladoFresa.getObb().c.z));
		HeladoFresaCollider.e = HeladoFresa.getObb().e * glm::vec3(5.0, 7.0, 5.0) * glm::vec3(1.0, 1.0, 1.0);
		HeladoFresaCollider.c = glm::vec3(modelmatrixColliderHeladoFresa[3]);
		addOrUpdateColliders(collidersOBB, "HeladoFresa", HeladoFresaCollider, matrixModelHeladoFresa);

		//Collider HeladoMenta
		AbstractModel::OBB HeladoMentaCollider;
		glm::mat4 modelmatrixColliderHeladoMenta = glm::mat4(matrixModelHeladoMenta);
		modelmatrixColliderHeladoMenta = glm::rotate(modelmatrixColliderHeladoMenta,
			glm::radians(0.0f), glm::vec3(0, 0, 1));
		// Set the orientation of collider before doing the scale
		HeladoMentaCollider.u = glm::quat_cast(modelmatrixColliderHeladoMenta);
		modelmatrixColliderHeladoMenta = glm::scale(modelmatrixColliderHeladoMenta, glm::vec3(5.0, 8.0, 5.0));
		modelmatrixColliderHeladoMenta = glm::translate(modelmatrixColliderHeladoMenta,
			glm::vec3(HeladoMenta.getObb().c.x,
				HeladoMenta.getObb().c.y,
				HeladoMenta.getObb().c.z));
		HeladoMentaCollider.e = HeladoMenta.getObb().e * glm::vec3(5.0, 8.0, 5.0) * glm::vec3(1.0, 1.0, 1.0);
		HeladoMentaCollider.c = glm::vec3(modelmatrixColliderHeladoMenta[3]);
		addOrUpdateColliders(collidersOBB, "HeladoMenta", HeladoMentaCollider, matrixModelHeladoMenta);

		//Collider HeladoMoraAzul
		AbstractModel::OBB HeladoMoraAzulCollider;
		glm::mat4 modelmatrixColliderHeladoMoraAzul = glm::mat4(matrixModelHeladoMoraAzul);
		modelmatrixColliderHeladoMoraAzul = glm::rotate(modelmatrixColliderHeladoMoraAzul,
			glm::radians(0.0f), glm::vec3(0, 0, 1));
		// Set the orientation of collider before doing the scale
		HeladoMoraAzulCollider.u = glm::quat_cast(modelmatrixColliderHeladoMoraAzul);
		modelmatrixColliderHeladoMoraAzul = glm::scale(modelmatrixColliderHeladoMoraAzul, glm::vec3(4.0, 5.0, 4.0));
		modelmatrixColliderHeladoMoraAzul = glm::translate(modelmatrixColliderHeladoMoraAzul,
			glm::vec3(HeladoMoraAzul.getObb().c.x,
				HeladoMoraAzul.getObb().c.y,
				HeladoMoraAzul.getObb().c.z));
		HeladoMoraAzulCollider.e = HeladoMoraAzul.getObb().e * glm::vec3(4.0, 5.0, 4.0) * glm::vec3(1.0, 1.0, 1.0);
		HeladoMoraAzulCollider.c = glm::vec3(modelmatrixColliderHeladoMoraAzul[3]);
		addOrUpdateColliders(collidersOBB, "HeladoMoraAzul", HeladoMoraAzulCollider, matrixModelHeladoMoraAzul);

		//Collider HeladoMoraAzulFresa
		AbstractModel::OBB HeladoMoraAzulFresaCollider;
		glm::mat4 modelmatrixColliderHeladoMoraAzulFresa = glm::mat4(matrixModelHeladoMoraAzulFresa);
		modelmatrixColliderHeladoMoraAzulFresa = glm::rotate(modelmatrixColliderHeladoMoraAzulFresa,
			glm::radians(0.0f), glm::vec3(0, 0, 1));
		// Set the orientation of collider before doing the scale
		HeladoMoraAzulFresaCollider.u = glm::quat_cast(modelmatrixColliderHeladoMoraAzulFresa);
		modelmatrixColliderHeladoMoraAzulFresa = glm::scale(modelmatrixColliderHeladoMoraAzulFresa, glm::vec3(4.0, 5.0, 4.0));
		modelmatrixColliderHeladoMoraAzulFresa = glm::translate(modelmatrixColliderHeladoMoraAzulFresa,
			glm::vec3(HeladoMoraAzulFresa.getObb().c.x,
				HeladoMoraAzulFresa.getObb().c.y,
				HeladoMoraAzulFresa.getObb().c.z));
		HeladoMoraAzulFresaCollider.e = HeladoMoraAzulFresa.getObb().e * glm::vec3(4.0, 5.0, 4.0) * glm::vec3(1.0, 1.0, 1.0);
		HeladoMoraAzulFresaCollider.c = glm::vec3(modelmatrixColliderHeladoMoraAzulFresa[3]);
		addOrUpdateColliders(collidersOBB, "HeladoMoraAzul", HeladoMoraAzulFresaCollider, matrixModelHeladoMoraAzulFresa);

		// Collider de mayow
		AbstractModel::OBB mayowCollider;
		glm::mat4 modelmatrixColliderMayow = glm::mat4(matrixModelMayow);
		modelmatrixColliderMayow = glm::rotate(modelmatrixColliderMayow,
			glm::radians(0.0f), glm::vec3(0, 0, 1));
		// Set the orientation of collider before doing the scale
		mayowCollider.u = glm::quat_cast(modelmatrixColliderMayow);
		modelmatrixColliderMayow = glm::scale(modelmatrixColliderMayow, glm::vec3(1.0, 2.0, 2.0));
		modelmatrixColliderMayow = glm::translate(modelmatrixColliderMayow,
			glm::vec3(MayowCuteAnimate.getObb().c.x,
				MayowCuteAnimate.getObb().c.y,
				MayowCuteAnimate.getObb().c.z));
		mayowCollider.e = MayowCuteAnimate.getObb().e * glm::vec3(1.0, 2.0, 2.0) * glm::vec3(1.0, 1.0, 1.0);
		mayowCollider.c = glm::vec3(modelmatrixColliderMayow[3]);
		addOrUpdateColliders(collidersOBB, "mayow", mayowCollider, matrixModelMayow);

		//Collider ballKirby pelotasPosition
		for (int i = 0; i < pelotasPosition.size(); i++) {
			AbstractModel::SBB BallKirbyCollider;
			glm::mat4 modelMatrixColliderBallKirby = glm::mat4(1.0);
			modelMatrixColliderBallKirby = glm::translate(modelMatrixColliderBallKirby, pelotasPosition[i]);
			modelMatrixColliderBallKirby = glm::rotate(modelMatrixColliderBallKirby, glm::radians(0.0f),
				glm::vec3(0, 1, 0));
			// Set the orientation of collider before doing the scale
			modelMatrixColliderBallKirby = glm::scale(modelMatrixColliderBallKirby, glm::vec3(5.0, 5.0, 5.0));
			modelMatrixColliderBallKirby = glm::translate(modelMatrixColliderBallKirby, BallKirby.getSbb().c);
			BallKirbyCollider.c = glm::vec3(modelMatrixColliderBallKirby[3]);
			BallKirbyCollider.ratio = BallKirby.getSbb().ratio * 3.5;
			std::get<0>(collidersSBB.find("BallKirby-" + std::to_string(i))->second) = BallKirbyCollider;
			addOrUpdateColliders(collidersSBB, "BallKirby-" + std::to_string(i), BallKirbyCollider, modelMatrixColliderBallKirby);
		}

	
		/*******************************************
		 * Render de ders
		 *******************************************/
		for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
			collidersOBB.begin(); it != collidersOBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = matrixCollider * glm::mat4(std::get<0>(it->second).u);
			matrixCollider = glm::scale(matrixCollider, std::get<0>(it->second).e * 2.0f);
			boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			boxCollider.enableWireMode();
			//boxCollider.render(matrixCollider);
		}

		for (std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
			collidersSBB.begin(); it != collidersSBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = glm::scale(matrixCollider, glm::vec3(std::get<0>(it->second).ratio * 2.0f));
			sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			sphereCollider.enableWireMode();
			//sphereCollider.render(matrixCollider);
		}

		// Esto es para ilustrar la transformacion inversa de los coliders
/*		glm::vec3 cinv = glm::inverse(mayowCollider.u) * glm::vec4(rockCollider.c, 1.0);
		glm::mat4 invColliderS = glm::mat4(1.0);
		invColliderS = glm::translate(invColliderS, cinv);
		invColliderS =  invColliderS * glm::mat4(mayowCollider.u);
		invColliderS = glm::scale(invColliderS, glm::vec3(rockCollider.ratio * 2.0, rockCollider.ratio * 2.0, rockCollider.ratio * 2.0));
		sphereCollider.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereCollider.enableWireMode();
		sphereCollider.render(invColliderS);
		glm::vec3 cinv2 = glm::inverse(mayowCollider.u) * glm::vec4(mayowCollider.c, 1.0);
		glm::mat4 invColliderB = glm::mat4(1.0);
		invColliderB = glm::translate(invColliderB, cinv2);
		invColliderB = glm::scale(invColliderB, mayowCollider.e * 2.0f);
		boxCollider.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		boxCollider.enableWireMode();
		boxCollider.render(invColliderB);
		// Se regresa el color blanco
		sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
		boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));*/

		/*******************************************
		 * Test Colisions
		 *******************************************/
		for (std::map<std::string,
			std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
			collidersOBB.begin(); it != collidersOBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
				std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt =
				collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (it != jt
					&& testOBBOBB(std::get<0>(it->second),
						std::get<0>(jt->second))) {
					std::cout << "Colision " << it->first << " with "
						<< jt->first << std::endl;
					isCollision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		for (std::map<std::string,
			std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
			collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
				std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator jt =
				collidersSBB.begin(); jt != collidersSBB.end(); jt++) {
				if (it != jt
					&& testSphereSphereIntersection(std::get<0>(it->second),
						std::get<0>(jt->second))) {
					std::cout << "Colision " << it->first << " with "
						<< jt->first << std::endl;
					isCollision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		for (std::map<std::string,
			std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
			collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			std::map<std::string,
				std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt =
				collidersOBB.begin();
			for (; jt != collidersOBB.end(); jt++) {
				if (testSphereOBox(std::get<0>(it->second),
					std::get<0>(jt->second))) {
					std::cout << "Colision " << it->first << " with "
						<< jt->first << std::endl;
					isCollision = true;
					addOrUpdateCollisionDetection(collisionDetection, jt->first, isCollision);
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}
		std::string kirby;
		std::map<std::string, bool>::iterator colIt;
		for (colIt = collisionDetection.begin(); colIt != collisionDetection.end();
			colIt++) {
			std::map<std::string,
				std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
				collidersSBB.find(colIt->first);
			std::map<std::string,
				std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt =
				collidersOBB.find(colIt->first);
			if (it != collidersSBB.end()) {
				if (!colIt->second)
					addOrUpdateColliders(collidersSBB, it->first);
			}
			if (jt != collidersOBB.end()) {
				if (!colIt->second)
					addOrUpdateColliders(collidersOBB, jt->first);
				else {
					if (jt->first.compare("mayow") == 0)
						matrixModelMayow= std::get<1>(jt->second);
					if (jt->first.compare("BallKirby-") == 0) {
						kirby = jt->first;
						printf("%s", kirby);
					}
							

				}
			}
		}
		/*******************************************
		 * State machines
		 *******************************************/
	/*
		 // State machine for the lambo car
		switch (stateDoor) {
		case 0:
			dorRotCount += 0.5;
			if (dorRotCount > 75)
				stateDoor = 1;
			break;
		case 1:
			dorRotCount -= 0.5;
			if (dorRotCount < 0) {
				dorRotCount = 0.0;
				stateDoor = 0;
			}
			break;
		}
*/
		glfwSwapBuffers(window);

		/****************************+
		 * Open AL sound data
		 */
		//SonidoMusicaFondo
		source0Pos[0] = matrixModelMayow[3].x;
		source0Pos[1] = matrixModelMayow[3].y;
		source0Pos[2] = matrixModelMayow[3].z;
		alSourcefv(source[0], AL_POSITION, source0Pos);
		//SonidoPelota
		source1Pos[0] = matrixModelBallKirby[3].x;
		source1Pos[1] = matrixModelBallKirby[3].y;
		source1Pos[2] = matrixModelBallKirby[3].z;
		alSourcefv(source[1], AL_POSITION, source1Pos);

		// Listener for the Thris person camera
		listenerPos[0] = matrixModelMayow[3].x;
		listenerPos[1] = matrixModelMayow[3].y;
		listenerPos[2] = matrixModelMayow[3].z;
		alListenerfv(AL_POSITION, listenerPos);

		glm::vec3 upModel = glm::normalize(matrixModelMayow[1]);
		glm::vec3 frontModel = glm::normalize(matrixModelMayow[2]);

		listenerOri[0] = frontModel.x;
		listenerOri[1] = frontModel.y;
		listenerOri[2] = frontModel.z;
		listenerOri[3] = upModel.x;
		listenerOri[4] = upModel.y;
		listenerOri[5] = upModel.z;
		
		// Listener for the First person camera

		/*listenerPos[0] = camera->getPosition().x;

		listenerPos[1] = camera->getPosition().y;
		listenerPos[2] = camera->getPosition().z;
		alListenerfv(AL_POSITION, listenerPos);
		listenerOri[0] = camera->getFront().x;
		listenerOri[1] = camera->getFront().y;
		listenerOri[2] = camera->getFront().z;
		listenerOri[3] = camera->getUp().x;
		listenerOri[4] = camera->getUp().y;
		listenerOri[5] = camera->getUp().z;
		alListenerfv(AL_ORIENTATION, listenerOri);*/
		for (unsigned int i = 0; i < sourcesPlay.size(); i++) {
			if (sourcesPlay[i]) {
				sourcesPlay[i] = false;
				alSourcePlay(source[i]);
			}
		}
	}
}

void prepareScene() {

	skyboxSphere.setShader(&shaderSkybox);

	
	terrain.setShader(&shaderTerrain);
/*
	// Helicopter
	modelHeliChasis.setShader(&shaderMulLighting);
	modelHeliHeli.setShader(&shaderMulLighting);
	// Lamborginhi
	modelLambo.setShader(&shaderMulLighting);
	modelLamboLeftDor.setShader(&shaderMulLighting);
	modelLamboRightDor.setShader(&shaderMulLighting);
	modelLamboFrontLeftWheel.setShader(&shaderMulLighting);
	modelLamboFrontRightWheel.setShader(&shaderMulLighting);
	modelLamboRearLeftWheel.setShader(&shaderMulLighting);
	modelLamboRearRightWheel.setShader(&shaderMulLighting);

	// Dart Lego
	modelDartLegoBody.setShader(&shaderMulLighting);
	modelDartLegoMask.setShader(&shaderMulLighting);
	modelDartLegoHead.setShader(&shaderMulLighting);
	modelDartLegoLeftArm.setShader(&shaderMulLighting);
	modelDartLegoRightArm.setShader(&shaderMulLighting);
	modelDartLegoLeftHand.setShader(&shaderMulLighting);
	modelDartLegoRightHand.setShader(&shaderMulLighting);
	modelDartLegoLeftLeg.setShader(&shaderMulLighting);
	modelDartLegoRightLeg.setShader(&shaderMulLighting);

	//Lamp models
	modelLamp1.setShader(&shaderMulLighting);
	modelLamp2.setShader(&shaderMulLighting);
	modelLampPost2.setShader(&shaderMulLighting);

	//Grass
	modelGrass.setShader(&shaderMulLighting);
	*/
	//Mayow

	MayowCuteAnimate.setShader(&shaderMulLighting);
	panditaRojo.setShader(&shaderMulLighting);
	panditaAzul.setShader(&shaderMulLighting);
	panditaNaranja.setShader(&shaderMulLighting);
	panditaVerde.setShader(&shaderMulLighting);
	panditaAmarillo.setShader(&shaderMulLighting);
	CaramAmarillo.setShader(&shaderMulLighting);
	CaramAzul.setShader(&shaderMulLighting);
	CaramRosa.setShader(&shaderMulLighting);
	CaramVerde.setShader(&shaderMulLighting);
	DonaChocolate.setShader(&shaderMulLighting);
	DonaFresa.setShader(&shaderMulLighting);
	HeladoChocolate.setShader(&shaderMulLighting);
	HeladoFresa.setShader(&shaderMulLighting);
	HeladoMenta.setShader(&shaderMulLighting);
	HeladoMoraAzul.setShader(&shaderMulLighting);
	HeladoMoraAzulFresa.setShader(&shaderMulLighting);
	PiruletaAmarillo.setShader(&shaderMulLighting);
	PiruletaRojo.setShader(&shaderMulLighting);
	PiruletaVerde.setShader(&shaderMulLighting);
	BallKirby.setShader(&shaderMulLighting);
	BastonLampara.setShader(&shaderMulLighting);
	Cake.setShader(&shaderMulLighting);
	Chocolate.setShader(&shaderMulLighting);
	ChocoPaleta.setShader(&shaderMulLighting);
	Cookie.setShader(&shaderMulLighting);
	CuteHome1.setShader(&shaderMulLighting);
	CuteHome2.setShader(&shaderMulLighting);
	CuteShop.setShader(&shaderMulLighting);
	IceCreamSign.setShader(&shaderMulLighting);
	Nube.setShader(&shaderMulLighting);
	Paleta.setShader(&shaderMulLighting);
	Strawberry.setShader(&shaderMulLighting);
	SweetCarrito.setShader(&shaderMulLighting);


}


int ronda = 1;
int cantidad_de_pelotas = 0;
int posx, posz, posy;
float y_max = 4.0f;
float avance = 5.0f, altura = 0.0f;
int pos_chica, pos_grande, decicion;
void prepareDepthScene() {

	skyboxSphere.setShader(&shaderDepth);
	terrain.setShader(&shaderDepth);
	/*
	// Helicopter
	modelHeliChasis.setShader(&shaderDepth);
	modelHeliHeli.setShader(&shaderDepth);
	// Lamborginhi
	modelLambo.setShader(&shaderDepth);
	modelLamboLeftDor.setShader(&shaderDepth);
	modelLamboRightDor.setShader(&shaderDepth);
	modelLamboFrontLeftWheel.setShader(&shaderDepth);
	modelLamboFrontRightWheel.setShader(&shaderDepth);
	modelLamboRearLeftWheel.setShader(&shaderDepth);
	modelLamboRearRightWheel.setShader(&shaderDepth);

	// Dart Lego
	modelDartLegoBody.setShader(&shaderDepth);
	modelDartLegoMask.setShader(&shaderDepth);
	modelDartLegoHead.setShader(&shaderDepth);
	modelDartLegoLeftArm.setShader(&shaderDepth);
	modelDartLegoRightArm.setShader(&shaderDepth);
	modelDartLegoLeftHand.setShader(&shaderDepth);
	modelDartLegoRightHand.setShader(&shaderDepth);
	modelDartLegoLeftLeg.setShader(&shaderDepth);
	modelDartLegoRightLeg.setShader(&shaderDepth);

	//Lamp models
	modelLamp1.setShader(&shaderDepth);
	modelLamp2.setShader(&shaderDepth);
	modelLampPost2.setShader(&shaderDepth);

	//Grass
	modelGrass.setShader(&shaderDepth);
	*/
	//Mayow
	MayowCuteAnimate.setShader(&shaderDepth);
	panditaRojo.setShader(&shaderDepth);
	panditaAzul.setShader(&shaderDepth);
	panditaNaranja.setShader(&shaderDepth);
	panditaVerde.setShader(&shaderDepth);
	panditaAmarillo.setShader(&shaderDepth);
	CaramAmarillo.setShader(&shaderDepth);
	CaramAzul.setShader(&shaderDepth);
	CaramRosa.setShader(&shaderDepth);
	CaramVerde.setShader(&shaderDepth);
	DonaChocolate.setShader(&shaderDepth);
	DonaFresa.setShader(&shaderDepth);
	HeladoChocolate.setShader(&shaderDepth);
	HeladoFresa.setShader(&shaderDepth);
	HeladoMenta.setShader(&shaderDepth);
	HeladoMoraAzul.setShader(&shaderDepth);
	HeladoMoraAzulFresa.setShader(&shaderDepth);
	PiruletaAmarillo.setShader(&shaderDepth);
	PiruletaRojo.setShader(&shaderDepth);
	PiruletaVerde.setShader(&shaderDepth);
	BallKirby.setShader(&shaderDepth);
	BastonLampara.setShader(&shaderDepth);
	Cake.setShader(&shaderDepth);
	Chocolate.setShader(&shaderDepth);
	ChocoPaleta.setShader(&shaderDepth);
	Cookie.setShader(&shaderDepth);
	CuteHome1.setShader(&shaderDepth);
	CuteHome2.setShader(&shaderDepth);
	CuteShop.setShader(&shaderDepth);
	IceCreamSign.setShader(&shaderDepth);
	Nube.setShader(&shaderDepth);
	Paleta.setShader(&shaderDepth);
	Strawberry.setShader(&shaderDepth);
	SweetCarrito.setShader(&shaderDepth);
}

void renderScene(bool renderParticles) {
	/*******************************************
	 * Terrain
	 *******************************************/
	 // Se activa la textura del background
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBackgroundID);
	shaderTerrain.setInt("backgroundTexture", 0);
	// Se activa la textura de ColorNube
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
	shaderTerrain.setInt("rTexture", 1);
	// Se activa la textura de ColorNube
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
	shaderTerrain.setInt("gTexture", 2);
	// Se activa la textura del ColorNube
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
	shaderTerrain.setInt("bTexture", 3);
	// Se activa la textura del blend map
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
	shaderTerrain.setInt("blendMapTexture", 4);
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(1, 1)));
	terrain.render();
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(0, 0)));
	glBindTexture(GL_TEXTURE_2D, 0);

	/*******************************************
	 * Custom objects obj
	 *******************************************/

	 // Forze to enable the unit texture to 0 always ----------------- IMPORTANT
	glActiveTexture(GL_TEXTURE0);

	// Render the lamps
	for (int i = 0; i < lamp1Position.size(); i++) {
		lamp1Position[i].y = terrain.getHeightTerrain(lamp1Position[i].x, lamp1Position[i].z);
		BastonLampara.setPosition(lamp1Position[i]);
		BastonLampara.setScale(glm::vec3(9.0, 9.0, 9.0));
		BastonLampara.setOrientation(glm::vec3(0, lamp1Orientation[i], 0));
		BastonLampara.render();
	}

	// Render the CuteHouse1
	for (int i = 0; i < CutH1Position.size(); i++) {
		CutH1Position[i].y = terrain.getHeightTerrain(CutH1Position[i].x, CutH1Position[i].z);
		CuteHome1.setPosition(CutH1Position[i]);
		CuteHome1.setScale(glm::vec3(4.0, 4.0, 4.0));
		CuteHome1.setOrientation(glm::vec3(0, CutH1Orientation[i], 0));
		CuteHome1.render();
	}

	// Render the CuteHouse2
	for (int i = 0; i < CutH2Position.size(); i++) {
		CutH2Position[i].y = terrain.getHeightTerrain(CutH2Position[i].x, CutH2Position[i].z);
		CuteHome2.setPosition(CutH2Position[i]);
		CuteHome2.setScale(glm::vec3(2.0, 2.0, 2.0));
		CuteHome2.setOrientation(glm::vec3(0, CutH2Orientation[i], 0));
		CuteHome2.render();
	}

	// Render the CuteShop
	for (int i = 0; i < CutShPosition.size(); i++) {
		CutShPosition[i].y = terrain.getHeightTerrain(CutShPosition[i].x, CutShPosition[i].z);
		CuteShop.setPosition(CutShPosition[i]);
		CuteShop.setScale(glm::vec3(4.0, 4.0, 4.0));
		CuteShop.setOrientation(glm::vec3(0, CutShOrientation[i], 0));
		CuteShop.render();
	}

	// Render the Cake
	for (int i = 0; i < CakePosition.size(); i++) {
		CakePosition[i].y = terrain.getHeightTerrain(CakePosition[i].x, CakePosition[i].z);
		Cake.setPosition(CakePosition[i]);
		Cake.setScale(glm::vec3(100.0, 100.0, 100.0));
		Cake.setOrientation(glm::vec3(0, CakeOrientation[i], 0));
		Cake.render();
	}

	// Render the Caramelos
	for (int i = 0; i < CarAmPosition.size(); i++) {
		CarAmPosition[i].y = terrain.getHeightTerrain(CarAmPosition[i].x, CarAmPosition[i].z);
		CaramAmarillo.setPosition(CarAmPosition[i]);
		CaramAmarillo.setScale(glm::vec3(10.0, 10.0, 10.0));
		CaramAmarillo.setOrientation(glm::vec3(0, CarAmOrientation[i], 0));
		CaramAmarillo.render();
	}
	for (int i = 0; i < CarAzPosition.size(); i++) {
		CarAzPosition[i].y = terrain.getHeightTerrain(CarAzPosition[i].x, CarAzPosition[i].z);
		CaramAzul.setPosition(CarAzPosition[i]);
		CaramAzul.setScale(glm::vec3(15.0, 15.0, 15.0));
		CaramAzul.setOrientation(glm::vec3(0, CarAzOrientation[i], 0));
		CaramAzul.render();
	}
	for (int i = 0; i < CarRoPosition.size(); i++) {
		CarRoPosition[i].y = terrain.getHeightTerrain(CarRoPosition[i].x, CarRoPosition[i].z);
		CaramRosa.setPosition(CarRoPosition[i]);
		CaramRosa.setScale(glm::vec3(20.0, 20.0, 20.0));
		CaramRosa.setOrientation(glm::vec3(0, CarRoOrientation[i], 0));
		CaramRosa.render();
	}
	for (int i = 0; i < CarVerPosition.size(); i++) {
		CarVerPosition[i].y = terrain.getHeightTerrain(CarVerPosition[i].x, CarVerPosition[i].z);
		CaramVerde.setPosition(CarVerPosition[i]);
		CaramVerde.setScale(glm::vec3(15.0, 15.0, 15.0));
		CaramVerde.setOrientation(glm::vec3(0, CarVerOrientation[i], 0));
		CaramVerde.render();
	}
	// Render the Chocolate
	for (int i = 0; i < ChocoPosition.size(); i++) {
		ChocoPosition[i].y = terrain.getHeightTerrain(ChocoPosition[i].x, ChocoPosition[i].z);
		Chocolate.setPosition(ChocoPosition[i]);
		Chocolate.setScale(glm::vec3(100.0, 100.0, 100.0));
		Chocolate.setOrientation(glm::vec3(0, ChocoOrientation[i], 0));
		Chocolate.render();
	}
	// Render the ChocoPaleta
	for (int i = 0; i < ChocoPPosition.size(); i++) {
		ChocoPPosition[i].y = terrain.getHeightTerrain(ChocoPPosition[i].x, ChocoPPosition[i].z);
		ChocoPaleta.setPosition(ChocoPPosition[i]);
		ChocoPaleta.setScale(glm::vec3(1.5, 1.5, 1.5));
		ChocoPaleta.setOrientation(glm::vec3(0, ChocoPOrientation[i], 0));
		ChocoPaleta.render();
	}

	// Render the Cookies
	for (int i = 0; i < CookPosition.size(); i++) {
		CookPosition[i].y = terrain.getHeightTerrain(CookPosition[i].x, CookPosition[i].z);
		Cookie.setPosition(CookPosition[i]);
		Cookie.setScale(glm::vec3(150.0, 150.0, 150.0));
		Cookie.setOrientation(glm::vec3(0, CookOrientation[i], 0));
		Cookie.render();
	}

	// Render the DonaChoco
	for (int i = 0; i < DonChoPosition.size(); i++) {
		DonChoPosition[i].y = terrain.getHeightTerrain(DonChoPosition[i].x, DonChoPosition[i].z);
		DonaChocolate.setPosition(DonChoPosition[i]);
		DonaChocolate.setScale(glm::vec3(9.0, 9.0, 9.0));
		DonaChocolate.setOrientation(glm::vec3(0, DonChoOrientation[i], 0));
		DonaChocolate.render();
	}

	// Render the DonaFresa
	for (int i = 0; i < DonFrePosition.size(); i++) {
		DonFrePosition[i].y = terrain.getHeightTerrain(DonFrePosition[i].x, DonFrePosition[i].z);
		DonaFresa.setPosition(DonFrePosition[i]);
		DonaFresa.setScale(glm::vec3(9.0, 9.0, 9.0));
		DonaFresa.setOrientation(glm::vec3(0, DonFreOrientation[i], 0));
		DonaFresa.render();
	}

	// Render the Panditas
	for (int i = 0; i < PAmPosition.size(); i++) {
		PAmPosition[i].y = terrain.getHeightTerrain(PAmPosition[i].x, PAmPosition[i].z);
		panditaAmarillo.setPosition(PAmPosition[i]);
		panditaAmarillo.setScale(glm::vec3(9.0, 9.0, 9.0));
		panditaAmarillo.setOrientation(glm::vec3(0, PAmOrientation[i], 0));
		panditaAmarillo.render();
	}
	for (int i = 0; i < PAzPosition.size(); i++) {
		PAzPosition[i].y = terrain.getHeightTerrain(PAzPosition[i].x, PAzPosition[i].z);
		panditaAzul.setPosition(PAzPosition[i]);
		panditaAzul.setScale(glm::vec3(9.0, 9.0, 9.0));
		panditaAzul.setOrientation(glm::vec3(0, PAzOrientation[i], 0));
		panditaAzul.render();
	}
	for (int i = 0; i < PNaPosition.size(); i++) {
		PNaPosition[i].y = terrain.getHeightTerrain(PNaPosition[i].x, PNaPosition[i].z);
		panditaNaranja.setPosition(PNaPosition[i]);
		panditaNaranja.setScale(glm::vec3(5.0, 5.0, 5.0));
		panditaNaranja.setOrientation(glm::vec3(0, PNaOrientation[i], 0));
		panditaNaranja.render();
	}
	for (int i = 0; i < PRoPosition.size(); i++) {
		PRoPosition[i].y = terrain.getHeightTerrain(PRoPosition[i].x, PRoPosition[i].z);
		panditaRojo.setPosition(PRoPosition[i]);
		panditaRojo.setScale(glm::vec3(6.0, 6.0, 6.0));
		panditaRojo.setOrientation(glm::vec3(0, PRoOrientation[i], 0));
		panditaRojo.render();
	}
	for (int i = 0; i < PVePosition.size(); i++) {
		PVePosition[i].y = terrain.getHeightTerrain(PVePosition[i].x, PVePosition[i].z);
		panditaVerde.setPosition(PVePosition[i]);
		panditaVerde.setScale(glm::vec3(6.0, 6.0, 6.0));
		panditaVerde.setOrientation(glm::vec3(0, PVeOrientation[i], 0));
		panditaVerde.render();
	}


	//Helados render
	matrixModelHeladoChocolate[3][1] = terrain.getHeightTerrain(matrixModelHeladoChocolate[3][0], matrixModelHeladoChocolate[3][2]);
	glm::mat4 matrixModelHeladoChocolateBody = glm::mat4(matrixModelHeladoChocolate);
	matrixModelHeladoChocolateBody = glm::scale(matrixModelHeladoChocolateBody, glm::vec3(5.0, 5.0, 5.0));
	HeladoChocolate.render(matrixModelHeladoChocolateBody);
	glActiveTexture(GL_TEXTURE0);
	matrixModelHeladoFresa[3][1] = terrain.getHeightTerrain(matrixModelHeladoFresa[3][0], matrixModelHeladoFresa[3][2]);
	glm::mat4 matrixModelHeladoFresaBody = glm::mat4(matrixModelHeladoFresa);
	matrixModelHeladoFresaBody = glm::scale(matrixModelHeladoFresaBody, glm::vec3(7.0, 7.0, 7.0));
	HeladoFresa.render(matrixModelHeladoFresaBody);
	glActiveTexture(GL_TEXTURE0);
	matrixModelHeladoMenta[3][1] = terrain.getHeightTerrain(matrixModelHeladoMenta[3][0], matrixModelHeladoMenta[3][2]);
	glm::mat4 matrixModelHeladoMentaBody = glm::mat4(matrixModelHeladoMenta);
	matrixModelHeladoMentaBody = glm::scale(matrixModelHeladoMentaBody, glm::vec3(8.0, 8.0, 8.0));
	HeladoMenta.render(matrixModelHeladoMentaBody);
	glActiveTexture(GL_TEXTURE0);
	matrixModelHeladoMoraAzul[3][1] = terrain.getHeightTerrain(matrixModelHeladoMoraAzul[3][0], matrixModelHeladoMoraAzul[3][2]);
	glm::mat4 matrixModelHeladoMoraAzulBody = glm::mat4(matrixModelHeladoMoraAzul);
	matrixModelHeladoMoraAzulBody = glm::scale(matrixModelHeladoMoraAzulBody, glm::vec3(6.0, 6.0, 6.0));
	HeladoMoraAzul.render(matrixModelHeladoMoraAzulBody);
	glActiveTexture(GL_TEXTURE0);
	matrixModelHeladoMoraAzulFresa[3][1] = terrain.getHeightTerrain(matrixModelHeladoMoraAzulFresa[3][0], matrixModelHeladoMoraAzulFresa[3][2]);
	glm::mat4 matrixModelHeladoMoraAzulFresaBody = glm::mat4(matrixModelHeladoMoraAzulFresa);
	matrixModelHeladoMoraAzulFresaBody = glm::scale(matrixModelHeladoMoraAzulFresaBody, glm::vec3(5.0, 5.0, 5.0));
	HeladoMoraAzulFresa.render(matrixModelHeladoMoraAzulFresaBody);
	glActiveTexture(GL_TEXTURE0);

	//Piruletas render
	matrixModelPiruletaAmarillo[3][1] = terrain.getHeightTerrain(matrixModelPiruletaAmarillo[3][0], matrixModelPiruletaAmarillo[3][2]);
	glm::mat4 matrixModelPiruletaAmarilloBody = glm::mat4(matrixModelPiruletaAmarillo);
	matrixModelPiruletaAmarilloBody = glm::scale(matrixModelPiruletaAmarilloBody, glm::vec3(3.0, 3.0, 3.0));
	PiruletaAmarillo.render(matrixModelPiruletaAmarilloBody);
	glActiveTexture(GL_TEXTURE0);
	matrixModelPiruletaRojo[3][1] = terrain.getHeightTerrain(matrixModelPiruletaRojo[3][0], matrixModelPiruletaRojo[3][2]);
	glm::mat4 matrixModelPiruletaRojoBody = glm::mat4(matrixModelPiruletaRojo);
	matrixModelPiruletaRojoBody = glm::scale(matrixModelPiruletaRojoBody, glm::vec3(3.0, 3.0, 3.0));
	PiruletaRojo.render(matrixModelPiruletaRojoBody);
	glActiveTexture(GL_TEXTURE0);
	matrixModelPiruletaVerde[3][1] = terrain.getHeightTerrain(matrixModelPiruletaVerde[3][0], matrixModelPiruletaVerde[3][2]);
	glm::mat4 matrixModelPiruletaVerdeBody = glm::mat4(matrixModelPiruletaVerde);
	matrixModelPiruletaVerdeBody = glm::scale(matrixModelPiruletaVerdeBody, glm::vec3(4.0, 4.0, 4.0));
	PiruletaVerde.render(matrixModelPiruletaVerdeBody);
	glActiveTexture(GL_TEXTURE0);


	//Ice Cream Sign render
	matrixModelIceCreamSign[3][1] = terrain.getHeightTerrain(matrixModelIceCreamSign[3][0], matrixModelIceCreamSign[3][2]);
	glm::mat4 matrixModelIceCreamSignBody = glm::mat4(matrixModelIceCreamSign);
	matrixModelIceCreamSignBody = glm::scale(matrixModelIceCreamSignBody, glm::vec3(5.0, 5.0, 5.0));
	IceCreamSign.render(matrixModelIceCreamSignBody);
	glActiveTexture(GL_TEXTURE0);

	//Nube Sign render
	//matrixModelNube[3][1] = terrain.getHeightTerrain(matrixModelNube[3][0], matrixModelNube[3][2]);
	glm::mat4 matrixModelNubeBody = glm::mat4(matrixModelNube);
	matrixModelNubeBody = glm::scale(matrixModelNubeBody, glm::vec3(60.0, 30.0, 60.0));
	Nube.render(matrixModelNubeBody);
	glActiveTexture(GL_TEXTURE0);

	//Paleta render
	matrixModelPaleta[3][1] = terrain.getHeightTerrain(matrixModelPaleta[3][0], matrixModelPaleta[3][2]);
	glm::mat4 matrixModelPaletaBody = glm::mat4(matrixModelPaleta);
	matrixModelPaletaBody = glm::scale(matrixModelPaletaBody, glm::vec3(30.0, 30.0, 30.0));
	Paleta.render(matrixModelPaletaBody);
	glActiveTexture(GL_TEXTURE0);

	//Strawberry render
	matrixModelStrawberry[3][1] = terrain.getHeightTerrain(matrixModelStrawberry[3][0], matrixModelStrawberry[3][2]);
	glm::mat4 matrixModelStrawberryBody = glm::mat4(matrixModelStrawberry);
	matrixModelStrawberryBody = glm::scale(matrixModelStrawberryBody, glm::vec3(200.0, 200.0, 200.0));
	Strawberry.render(matrixModelStrawberryBody);
	glActiveTexture(GL_TEXTURE0);

	//SweerCarrito render
	matrixModelSweetCarrito[3][1] = terrain.getHeightTerrain(matrixModelSweetCarrito[3][0], matrixModelSweetCarrito[3][2]);
	glm::mat4 matrixModelSweetCarritoBody = glm::mat4(matrixModelSweetCarrito);
	matrixModelSweetCarritoBody = glm::scale(matrixModelSweetCarritoBody, glm::vec3(80.0, 80.0, 80.0));
	SweetCarrito.render(matrixModelSweetCarritoBody);
	glActiveTexture(GL_TEXTURE0);

	/*******************************************
	 * Custom Anim objects obj
	 *******************************************/

	matrixModelMayow[3][1] = terrain.getHeightTerrain(matrixModelMayow[3][0], matrixModelMayow[3][2]);
	glm::mat4 matrixModelMayowBody = glm::mat4(matrixModelMayow);
	matrixModelMayowBody = glm::scale(matrixModelMayowBody, glm::vec3(0.02, 0.02, 0.02));
	MayowCuteAnimate.setAnimationIndex(animationIndex);
	MayowCuteAnimate.render(matrixModelMayowBody);

	/*********************************************
	*Funcion para el span aleatorio de pelotas
	************************************************/

	//for (int i = 0; i < 10; i++) {
	if (ronda == 1) {
		cantidad_de_pelotas = (rand() % (ronda * 5 + 1))+5;
		printf("cantidad de pelotas :%d \n", cantidad_de_pelotas);
		for (int j = 0; j < cantidad_de_pelotas; j++) {
			pos_chica = rand() % (101);
			pos_grande = rand() % (101);
			pos_grande = -700 + pos_grande;
			decicion = rand() % (4);
			if (decicion == 0) {
				posx = pos_chica;
				posz = pos_grande;
			}
			if (decicion == 1) {
				posx = pos_grande;
				posz = pos_chica;
			}
			if (decicion == 2) {
				posx = pos_grande;
				posz = pos_grande;
			}
			if (decicion == 3) {
				posx = pos_chica;
				posz = pos_chica;
			}
			pelotasPosition.push_back(glm::vec3(posx, 0, posz));
		}
		ronda += 1;
	}
	/*while (ronda == 2) {
		for (int j = 0; j < cantidad_de_pelotas; j++) {
			while (altura < y_max && avance>0.0f) {
				altura += 5.0;
				avance -= 5.0;
				if (posx > matrixModelMayowBody[3][0]) {
					posx = -1;
				}
				if (posz > matrixModelMayowBody[3][2]) {
					posz = -1;
				}
				if (matrixModelMayowBody[3][0] > posx) {
					posx = 1;
				}
				if (matrixModelMayowBody[3][2] > posz) {
					posx = 1;
				}
				matrixModelBallKirby = glm::translate(matrixModelBallKirby, glm::vec3(posx, altura, posz));
				pelotasPosition[j] = glm::vec3(matrixModelBallKirby[3][0], matrixModelBallKirby[3][1], matrixModelBallKirby[3][2]);
			}
		}*/
		/*for (int j = 0; j < cantidad_de_pelotas; j++) {
			while (altura < y_max && avance>0.0f) {
				altura -= 5.0;
				avance -= 5.0;
				if (posx > matrixModelMayowBody[3][0]) {
					posx = -0.2;
				}
				if (posz > matrixModelMayowBody[3][2]) {
					posz = -0.2;
				}
				if (matrixModelMayowBody[3][0] > posx) {
					posx = 0.2;
				}
				if (matrixModelMayowBody[3][2] > posz) {
					posx = 0.2;
				}
				matrixModelBallKirby = glm::translate(matrixModelBallKirby, glm::vec3(posx, altura, posz));
				pelotasPosition[j] = glm::vec3(matrixModelBallKirby[3][0], matrixModelBallKirby[3][1], matrixModelBallKirby[3][2]);
			}*/



	for (int i = 0; i < cantidad_de_pelotas; i++) {
		pelotasPosition[i].y = terrain.getHeightTerrain(pelotasPosition[i].x, pelotasPosition[i].z);
		BallKirby.setPosition(pelotasPosition[i]);
		BallKirby.setScale(glm::vec3(5.0, 5.0, 5.0));
		BallKirby.setOrientation(glm::vec3(0, 1.0, 0));
		//if (ColisionMP == true) {
		BallKirby.render();
		//}
		//else {//Aqui va la renderización en este mismo punto de la particula
			glm::mat4 modelMatrixParticlesFountain = glm::mat4(1.0);
			modelMatrixParticlesFountain = glm::translate(modelMatrixParticlesFountain, pelotasPosition[i]);
			modelMatrixParticlesFountain[3][1] = terrain.getHeightTerrain(modelMatrixParticlesFountain[3][0], modelMatrixParticlesFountain[3][2]) + 0.36 * 10.0;
			modelMatrixParticlesFountain = glm::scale(modelMatrixParticlesFountain, glm::vec3(3.0, 3.0, 3.0));
			currTimeParticlesAnimation = TimeManager::Instance().GetTime();
		//}
	}

		
	

	/**********
	 * Update the position with alpha objects
	 */
	 // Update the aircraft
//	blendingUnsorted.find("aircraft")->second = glm::vec3(modelMatrixAircraft[3]);
	// Update the lambo
//	blendingUnsorted.find("lambo")->second = glm::vec3(modelMatrixLambo[3]);
	// Update the helicopter
//	blendingUnsorted.find("heli")->second = glm::vec3(modelMatrixHeli[3]);

	/**********
	 * Sorter with alpha objects
	 */
	std::map<float, std::pair<std::string, glm::vec3>> blendingSorted;
	std::map<std::string, glm::vec3>::iterator itblend;
	for (itblend = blendingUnsorted.begin(); itblend != blendingUnsorted.end(); itblend++) {
		float distanceFromView = glm::length(camera->getPosition() - itblend->second);
		blendingSorted[distanceFromView] = std::make_pair(itblend->first, itblend->second);
	}

	/**********
	 * Render de las transparencias
	 */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	for (std::map<float, std::pair<std::string, glm::vec3> >::reverse_iterator it = blendingSorted.rbegin(); it != blendingSorted.rend(); it++) {
		/*if (it->second.first.compare("aircraft") == 0) {
			// Render for the aircraft model
			glm::mat4 modelMatrixAircraftBlend = glm::mat4(modelMatrixAircraft);
			modelMatrixAircraftBlend[3][1] = terrain.getHeightTerrain(modelMatrixAircraftBlend[3][0], modelMatrixAircraftBlend[3][2]) + 2.0;
			modelAircraft.render(modelMatrixAircraftBlend);
		}
		else if (it->second.first.compare("lambo") == 0) {
			// Lambo car
			glm::mat4 modelMatrixLamboBlend = glm::mat4(modelMatrixLambo);
			modelMatrixLamboBlend[3][1] = terrain.getHeightTerrain(modelMatrixLamboBlend[3][0], modelMatrixLamboBlend[3][2]);
			modelMatrixLamboBlend = glm::scale(modelMatrixLamboBlend, glm::vec3(1.3, 1.3, 1.3));
			modelLambo.render(modelMatrixLamboBlend);
			glActiveTexture(GL_TEXTURE0);
			glm::mat4 modelMatrixLamboLeftDor = glm::mat4(modelMatrixLamboBlend);
			modelMatrixLamboLeftDor = glm::translate(modelMatrixLamboLeftDor, glm::vec3(1.08676, 0.707316, 0.982601));
			modelMatrixLamboLeftDor = glm::rotate(modelMatrixLamboLeftDor, glm::radians(dorRotCount), glm::vec3(1.0, 0, 0));
			modelMatrixLamboLeftDor = glm::translate(modelMatrixLamboLeftDor, glm::vec3(-1.08676, -0.707316, -0.982601));
			modelLamboLeftDor.render(modelMatrixLamboLeftDor);
			modelLamboRightDor.render(modelMatrixLamboBlend);
			modelLamboFrontLeftWheel.render(modelMatrixLamboBlend);
			modelLamboFrontRightWheel.render(modelMatrixLamboBlend);
			modelLamboRearLeftWheel.render(modelMatrixLamboBlend);
			modelLamboRearRightWheel.render(modelMatrixLamboBlend);
			// Se regresa el cull faces IMPORTANTE para las puertas
		}
		else if (it->second.first.compare("heli") == 0) {
			// Helicopter
			glm::mat4 modelMatrixHeliChasis = glm::mat4(modelMatrixHeli);
			modelHeliChasis.render(modelMatrixHeliChasis);

			glm::mat4 modelMatrixHeliHeli = glm::mat4(modelMatrixHeliChasis);
			modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.0, 0.0, -0.249548));
			modelMatrixHeliHeli = glm::rotate(modelMatrixHeliHeli, rotHelHelY, glm::vec3(0, 1, 0));
			modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.0, 0.0, 0.249548));
			modelHeliHeli.render(modelMatrixHeliHeli);
		}
	*/
		    if (renderParticles && it->second.first.compare("fountain") == 0) {
			/**********
			 * Init Render particles systems
			 */
			glm::mat4 modelMatrixParticlesFountain = glm::mat4(1.0);
			modelMatrixParticlesFountain = glm::translate(modelMatrixParticlesFountain, it->second.second);
			modelMatrixParticlesFountain = glm::translate(modelMatrixParticlesFountain, pelotasPosition[1]);
			modelMatrixParticlesFountain[3][1] = terrain.getHeightTerrain(modelMatrixParticlesFountain[3][0], modelMatrixParticlesFountain[3][2]) + 0.36 * 10.0;
			modelMatrixParticlesFountain = glm::scale(modelMatrixParticlesFountain, glm::vec3(3.0, 3.0, 3.0));
			currTimeParticlesAnimation = TimeManager::Instance().GetTime();
			if (currTimeParticlesAnimation - lastTimeParticlesAnimation > 10.0)
				lastTimeParticlesAnimation = currTimeParticlesAnimation;
			//glDisable(GL_DEPTH_TEST);
			glDepthMask(GL_FALSE);
			// Set the point size
			glPointSize(10.0f);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureParticleFountainID);
			shaderParticlesFountain.turnOn();
			shaderParticlesFountain.setFloat("Time", float(currTimeParticlesAnimation - lastTimeParticlesAnimation));
			shaderParticlesFountain.setFloat("ParticleLifetime", 3.5f);
			shaderParticlesFountain.setInt("ParticleTex", 0);
			shaderParticlesFountain.setVectorFloat3("Gravity", glm::value_ptr(glm::vec3(0.0f, -0.3f, 0.0f)));
			shaderParticlesFountain.setMatrix4("model", 1, false, glm::value_ptr(modelMatrixParticlesFountain));
			glBindVertexArray(VAOParticles);
			glDrawArrays(GL_POINTS, 0, nParticles);
			glDepthMask(GL_TRUE);
			//glEnable(GL_DEPTH_TEST);
			shaderParticlesFountain.turnOff();
			/**********
			 * End Render particles systems
			 */
		}
	//	else if (renderParticles && it->second.first.compare("fire") == 0) {
			/**********
			 * Init Render particles systems
			 */
	/*		lastTimeParticlesAnimationFire = currTimeParticlesAnimationFire;
			currTimeParticlesAnimationFire = TimeManager::Instance().GetTime();

			shaderParticlesFire.setInt("Pass", 1);
			shaderParticlesFire.setFloat("Time", currTimeParticlesAnimationFire);
			shaderParticlesFire.setFloat("DeltaT", currTimeParticlesAnimationFire - lastTimeParticlesAnimationFire);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_1D, texId);
			glEnable(GL_RASTERIZER_DISCARD);
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[drawBuf]);
			glBeginTransformFeedback(GL_POINTS);
			glBindVertexArray(particleArray[1 - drawBuf]);
			glVertexAttribDivisor(0, 0);
			glVertexAttribDivisor(1, 0);
			glVertexAttribDivisor(2, 0);
			glDrawArrays(GL_POINTS, 0, nParticlesFire);
			glEndTransformFeedback();
			glDisable(GL_RASTERIZER_DISCARD);

			shaderParticlesFire.setInt("Pass", 2);
			glm::mat4 modelFireParticles = glm::mat4(1.0);
			modelFireParticles = glm::translate(modelFireParticles, it->second.second);
			modelFireParticles[3][1] = terrain.getHeightTerrain(modelFireParticles[3][0], modelFireParticles[3][2]);
			shaderParticlesFire.setMatrix4("model", 1, false, glm::value_ptr(modelFireParticles));

			shaderParticlesFire.turnOn();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureParticleFireID);
			glDepthMask(GL_FALSE);
			glBindVertexArray(particleArray[drawBuf]);
			glVertexAttribDivisor(0, 1);
			glVertexAttribDivisor(1, 1);
			glVertexAttribDivisor(2, 1);
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, nParticlesFire);
			glBindVertexArray(0);
			glDepthMask(GL_TRUE);
			drawBuf = 1 - drawBuf;
			shaderParticlesFire.turnOff();
*/
			/****************************+
			 * Open AL sound data
			 */
/*			source1Pos[0] = modelFireParticles[3].x;
			source1Pos[1] = modelFireParticles[3].y;
			source1Pos[2] = modelFireParticles[3].z;
			alSourcefv(source[1], AL_POSITION, source1Pos);

			/**********
			 * End Render particles systems
			 */
		}

//	}
	glEnable(GL_CULL_FACE);
}

int main(int argc, char **argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
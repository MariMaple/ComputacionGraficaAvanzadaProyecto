//Mariana Arguelles Macosay
//Diana Anayanssi Martínez Santana

#define _USE_MATH_DEFINES
#include <cmath>
//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

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

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;

//selector de vista - camara 
bool selec_vista = true;
bool camaraActivada = false;

GLFWwindow *window;

Shader shader;
//Shader con skybox
Shader shaderSkybox;
//Shader con multiples luces
Shader shaderMulLighting;
//Shader para el terreno
Shader shaderTerrain;

std::shared_ptr<Camera> camera(new ThirdPersonCamera());
float distanceFromTarget = 5.0;

std::shared_ptr<FirstPersonCamera>cameraPP(new FirstPersonCamera());

Sphere skyboxSphere(20, 20);
Box boxCollider;
Sphere sphereCollider(10, 10);

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
Model BastonLampara;
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

// Model animate instance
Model MayowCuteAnimate;

// Terrain model instance
Terrain terrain(-1, -1, 800, 60, "../Textures/heightmap.png");

GLuint textureCespedID, textureWallID, textureWindowID, textureHighwayID, textureLandingPadID;
GLuint textureTerrainBackgroundID, textureTerrainRID, textureTerrainGID, textureTerrainBID, textureTerrainBlendMapID;
GLuint skyboxTextureID;

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
		"../Textures/mp_Cute/Cute_rt.tga",
		"../Textures/mp_Cute/Cute_lf.tga" };

bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;

// Model matrix definitions
glm::mat4 matrixModelPanditaRojo		= glm::mat4(1.0);
glm::mat4 matrixModelPanditaAzul		= glm::mat4(1.0);
glm::mat4 matrixModelPanditaNaranja		= glm::mat4(1.0);
glm::mat4 matrixModelPanditaAmarillo	= glm::mat4(1.0);
glm::mat4 matrixModelPanditaVerde		= glm::mat4(1.0);
glm::mat4 matrixModelCaramAmarillo		= glm::mat4(1.0);
glm::mat4 matrixModelCaramAzul			= glm::mat4(1.0);
glm::mat4 matrixModelCaramRosa			= glm::mat4(1.0);
glm::mat4 matrixModelCaramVerde			= glm::mat4(1.0);
glm::mat4 matrixModelHeladoChocolate	= glm::mat4(1.0);
glm::mat4 matrixModelHeladoFresa		= glm::mat4(1.0);
glm::mat4 matrixModelHeladoMenta		= glm::mat4(1.0);
glm::mat4 matrixModelHeladoMoraAzul		= glm::mat4(1.0);
glm::mat4 matrixModelHeladoMoraAzulFresa= glm::mat4(1.0);
glm::mat4 matrixModelPiruletaAmarillo	= glm::mat4(1.0);
glm::mat4 matrixModelPiruletaRojo		= glm::mat4(1.0);
glm::mat4 matrixModelPiruletaVerde		= glm::mat4(1.0);
glm::mat4 matrixModelDonaChocolate		= glm::mat4(1.0);
glm::mat4 matrixModelDonaFresa			= glm::mat4(1.0);
glm::mat4 matrixModelBallKirby			= glm::mat4(1.0);
glm::mat4 matrixModelBastonLampara		= glm::mat4(1.0);
glm::mat4 matrixModelCake				= glm::mat4(1.0);
glm::mat4 matrixModelChocolate			= glm::mat4(1.0);
glm::mat4 matrixModelChocoPaleta		= glm::mat4(1.0);
glm::mat4 matrixModelCookie				= glm::mat4(1.0);
glm::mat4 matrixModelCuteHome1			= glm::mat4(1.0);
glm::mat4 matrixModelCuteHome2			= glm::mat4(1.0);
glm::mat4 matrixModelCuteShop			= glm::mat4(1.0);
glm::mat4 matrixModelIceCreamSign		= glm::mat4(1.0);
glm::mat4 matrixModelNube				= glm::mat4(1.0);
glm::mat4 matrixModelPaleta				= glm::mat4(1.0);
glm::mat4 matrixModelStrawberry			= glm::mat4(1.0);
glm::mat4 matrixModelSweetCarrito		= glm::mat4(1.0);
glm::mat4 matrixModelCuteGun			= glm::mat4(1.0);

//Model matrix definitions Animate
glm::mat4 matrixModelMayow				= glm::mat4(1.0);

int animationIndex = 1;
int modelSelected = 2;
bool enableCountSelected = true;


/*
// Lamps positions
std::vector<glm::vec3> lamp1Position = { glm::vec3(-7.03, 0, -19.14), glm::vec3(
		24.41, 0, -34.57), glm::vec3(-10.15, 0, -54.10) };
std::vector<float> lamp1Orientation = { -17.0, -82.67, 23.70 };
std::vector<glm::vec3> lamp2Position = { glm::vec3(-36.52, 0, -23.24),
		glm::vec3(-52.73, 0, -3.90) };
std::vector<float> lamp2Orientation = {21.37 + 90, -65.0 + 90};
*/

double deltaTime;
double currTime, lastTime;

// Colliders
std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> > collidersOBB;
std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> > collidersSBB;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mode);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);

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

	//Tamaño de la ventana altura y anchura
	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// InicializaciÃ³n de los shaders
	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_textura_animation.vs", "../Shaders/multipleLights.fs");
	shaderTerrain.initialize("../Shaders/terrain.vs", "../Shaders/terrain.fs");

	// Inicializacion de los objetos.
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));

	boxCollider.init();
	boxCollider.setShader(&shader);
	boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphereCollider.init();
	sphereCollider.setShader(&shader);
	sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

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
	MayowCuteAnimate.loadModel("../models/Contest May/May.obj");
	MayowCuteAnimate.setShader(&shaderMulLighting);

	/*modelLamp2.loadModel("../models/Street_Light/Lamp.obj");
	modelLamp2.setShader(&shaderMulLighting);
	modelLampPost2.loadModel("../models/Street_Light/LampPost.obj");
	modelLampPost2.setShader(&shaderMulLighting);
	*/

	//Posicion de la camara
	glm::vec3 posicion_camara = glm::vec3(0.0, 0.0, 10.0);
	camera->setPosition(posicion_camara);
	camera->setDistanceFromTarget(distanceFromTarget);
	camera->setSensitivity(1.0f); // velocidad de la camara
	posicion_camara = glm::vec3(5.0, 20.0, 5.0);
	cameraPP->setPosition(posicion_camara);

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
		skyboxTexture = Texture(fileNames[i]);
		FIBITMAP *bitmap = skyboxTexture.loadImage(true);
		unsigned char *data = skyboxTexture.convertToData(bitmap, imageWidth,
				imageHeight);
		if (data) {
			glTexImage2D(types[i], 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		} else
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
	} else
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
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
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
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainBlendMap.freeImage(bitmap);
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

	// Basic objects Delete
	skyboxSphere.destroy();
	boxCollider.destroy();
	sphereCollider.destroy();


	// Terrains objects Delete
	terrain.destroy();

	// Custom objects Delete
	/*modelLamp1.destroy();
	modelLamp2.destroy();
	modelLampPost2.destroy();*/
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
	CuteGun.destroy();

	// Custom objects animate
	MayowCuteAnimate.destroy();

	// Textures Delete
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureTerrainBackgroundID);
	glDeleteTextures(1, &textureTerrainRID);
	glDeleteTextures(1, &textureTerrainGID);
	glDeleteTextures(1, &textureTerrainBID);
	glDeleteTextures(1, &textureTerrainBlendMapID);

	// Cube Maps Delete
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &skyboxTextureID);
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

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
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
			cameraPP->moveFrontCamera(true, deltaTime+0.3);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPP->moveFrontCamera(false, deltaTime+0.3);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPP->moveRightCamera(false, deltaTime+0.3);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPP->moveRightCamera(true, deltaTime+0.3);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			cameraPP->mouseMoveCamera(offsetX, offsetY, deltaTime);

	}
	else {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			camera->mouseMoveCamera(offsetX, offsetY, deltaTime);
	}
	offsetX = 0;
	offsetY = 0;

	// Seleccionar modelo
	if (enableCountSelected && glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS){
		enableCountSelected = false;
		modelSelected++;
		if(modelSelected > 9)
			modelSelected = 0;
		std::cout << "modelSelected:" << modelSelected << std::endl;
	}
	else if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
		enableCountSelected = true;

	
// Desplazamiento y movimiento
	/*if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(1.0f), glm::vec3(0, 1, 0));
		animationIndex = 0;
	}else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(-1.0f), glm::vec3(0, 1, 0));
		animationIndex = 0;
	}if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0, 0, 0.02));
		animationIndex = 0;
	}else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0, 0, -0.02));
		animationIndex = 0;
	}
	*/
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
	float angleTarget=0;

	//Matrix Models
	matrixModelPanditaRojo = glm::translate(matrixModelPanditaRojo, glm::vec3(-3.0, 0.0, 2.0));
	matrixModelPanditaAmarillo = glm::translate(matrixModelPanditaAmarillo, glm::vec3(-5.0, 0.0, 2.0));
	matrixModelPanditaVerde = glm::translate(matrixModelPanditaVerde, glm::vec3(-7.0, 0.0, 2.0));
	matrixModelPanditaNaranja = glm::translate(matrixModelPanditaNaranja, glm::vec3(-9.0, 0.0, 2.0));
	matrixModelPanditaAzul = glm::translate(matrixModelPanditaAzul, glm::vec3(-11.0, 0.0, 2.0));
	matrixModelCaramAmarillo = glm::translate(matrixModelCaramAmarillo, glm::vec3(-3.0, 0.0, -1.5));
	matrixModelCaramAzul = glm::translate(matrixModelCaramAzul, glm::vec3(-5.0, 0.0, -1.5));
	matrixModelCaramRosa= glm::translate(matrixModelCaramRosa, glm::vec3(-7.0, 0.0, -1.5));
	matrixModelCaramVerde = glm::translate(matrixModelCaramVerde, glm::vec3(-9.0, 0.0, -1.5));
	matrixModelDonaChocolate= glm::translate(matrixModelDonaChocolate, glm::vec3(6.0, 10.0, 2.0));//Problemas con las donas
	matrixModelDonaFresa = glm::translate(matrixModelDonaFresa, glm::vec3(9.0, 10.0, 2.0));//Problemas con las donas
	matrixModelHeladoChocolate = glm::translate(matrixModelHeladoChocolate, glm::vec3(12.0, 10.0, 2.0));
	matrixModelHeladoFresa = glm::translate(matrixModelHeladoFresa, glm::vec3(16.0, 10.0, 2.0));
	matrixModelHeladoMenta = glm::translate(matrixModelHeladoMenta, glm::vec3(20.0, 10.0, 2.0));
	matrixModelHeladoMoraAzul = glm::translate(matrixModelHeladoMoraAzul, glm::vec3(24.0, 10.0, 2.0));
	matrixModelHeladoMoraAzulFresa = glm::translate(matrixModelHeladoMoraAzulFresa, glm::vec3(28.0, 10.0, 2.0));
	matrixModelPiruletaAmarillo= glm::translate(matrixModelPiruletaAmarillo, glm::vec3(-36.0, 10.0, 4.0));
	matrixModelPiruletaRojo= glm::translate(matrixModelPiruletaRojo, glm::vec3(-42.0, 10.0, 4.0));
	matrixModelPiruletaVerde= glm::translate(matrixModelPiruletaVerde, glm::vec3(-48.0, 10.0, 4.0));
	matrixModelBallKirby = glm::translate(matrixModelBallKirby, glm::vec3(-14.0, 0.0, 2.0));
	matrixModelBastonLampara= glm::translate(matrixModelBastonLampara, glm::vec3(-16.0, 0.0, 2.0));
	matrixModelCake=glm::translate(matrixModelCake, glm::vec3(1.5, 0.0, 2.0));
	matrixModelChocolate = glm::translate(matrixModelChocolate, glm::vec3(-21.0, 0.0, 2.0));
	matrixModelChocoPaleta = glm::translate(matrixModelChocoPaleta, glm::vec3(-16.0, 0.0, -1.5));
	matrixModelCookie = glm::translate(matrixModelCookie, glm::vec3(1.5, 0.0, -4.0));
	matrixModelCuteHome1 = glm::translate(matrixModelCuteHome1, glm::vec3(12.0, 0.0, -30.0));
	matrixModelCuteHome2 = glm::translate(matrixModelCuteHome2, glm::vec3(-12.0, 0.0, -30.0));
	matrixModelCuteShop = glm::translate(matrixModelCuteShop, glm::vec3(-60.0, 0.0, -30.0));
	matrixModelIceCreamSign = glm::translate(matrixModelIceCreamSign, glm::vec3(-25.0, 0.0, 2.0));
	matrixModelNube= glm::translate(matrixModelIceCreamSign, glm::vec3(0.0, 20.0, 2.0));
	matrixModelPaleta = glm::translate(matrixModelPaleta, glm::vec3(-30.0, 0.0, 2.0));
	matrixModelStrawberry = glm::translate(matrixModelStrawberry, glm::vec3(0.0, 0.0, 10.0));
	matrixModelSweetCarrito = glm::translate(matrixModelSweetCarrito, glm::vec3(10.0, 0.0, 10.0));
	matrixModelCuteGun = glm::translate(matrixModelCuteGun, glm::vec3(-10.0, 0.0, 10.0));


	//Matrix Models Animate
	matrixModelMayow = glm::translate(matrixModelMayow, glm::vec3(-11.0, 0.0, -1.5));


	lastTime = TimeManager::Instance().GetTime();

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



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)screenWidth / (float)screenHeight, 0.01f, 400.0f);

		if (modelSelected == 1) {
			axis = glm::axis(glm::quat_cast(matrixModelPanditaRojo));
			angleTarget = glm::angle(glm::quat_cast(matrixModelPanditaRojo));
			target = matrixModelPanditaRojo[3];
		}
		else{
			axis = glm::axis(glm::quat_cast(matrixModelPanditaVerde));
			angleTarget = glm::angle(glm::quat_cast(matrixModelPanditaVerde));
			target = matrixModelPanditaVerde[3];
		}
		
		glm::mat4 view;

		if (std::isnan(angleTarget))
			angleTarget = 0.0;
		if (axis.y < 0)
			angleTarget = -angleTarget;
		if (modelSelected == 1)
			angleTarget -= glm::radians(90.0f);
		if (modelSelected == 3)
			angleTarget += glm::radians(90.0f);
		camera->setCameraTarget(target);
		camera->setAngleTarget(angleTarget);
		camera->updateCamera();
		if (camaraActivada == true)
			view = cameraPP->getViewMatrix();
		else
			view = camera->getViewMatrix();

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
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderTerrain.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderTerrain.setMatrix4("view", 1, false,
			glm::value_ptr(view));

		/*******************************************
		 * Propiedades Luz direccional
		 *******************************************/
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, -1.0, 0.0)));

		/*******************************************
		 * Propiedades Luz direccional Terrain
		 *******************************************/
		shaderTerrain.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderTerrain.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderTerrain.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTerrain.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderTerrain.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, -1.0, 0.0)));

		/*******************************************
		 * Propiedades SpotLights
		 *******************************************/
		 /*	glm::vec3 spotPosition = glm::vec3(modelMatrixHeli * glm::vec4(0.32437, 0.226053, 1.79149, 1.0));
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
			  /*shaderMulLighting.setInt("pointLightCount", lamp1Position.size() + lamp2Orientation.size());
			  shaderTerrain.setInt("pointLightCount", lamp1Position.size() + lamp2Orientation.size());
			  for (int i = 0; i < lamp1Position.size(); i++){
				  glm::mat4 matrixAdjustLamp = glm::mat4(1.0f);
				  matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp1Position[i]);
				  matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp1Orientation[i]), glm::vec3(0, 1, 0));
				  matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(0.5, 0.5, 0.5));
				  matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0, 10.3585, 0));
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
				  shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.02);
			  }
			  for (int i = 0; i < lamp2Position.size(); i++){
				  glm::mat4 matrixAdjustLamp = glm::mat4(1.0f);
				  matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp2Position[i]);
				  matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp2Orientation[i]), glm::vec3(0, 1, 0));
				  matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(1.0, 1.0, 1.0));
				  matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0.759521, 5.00174, 0));
				  glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
				  shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
				  shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
				  shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
				  shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
				  shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
				  shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
				  shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.01);
				  shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
				  shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
				  shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
				  shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
				  shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
				  shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
				  shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.02);
			  }
			  */
			  /*******************************************
			   * Terrain Cesped
			   *******************************************/
			   // Se activa la textura del background
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureTerrainBackgroundID);
		shaderTerrain.setInt("backgroundTexture", 0);
		// Se activa la textura de tierra
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
		shaderTerrain.setInt("rTexture", 1);
		// Se activa la textura de hierba
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
		shaderTerrain.setInt("gTexture", 2);
		// Se activa la textura del camino
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

		//Panditas render
		matrixModelPanditaRojo[3][1] = terrain.getHeightTerrain(matrixModelPanditaRojo[3][0], matrixModelPanditaRojo[3][2]);
		panditaRojo.render(matrixModelPanditaRojo);
		glActiveTexture(GL_TEXTURE0);
		matrixModelPanditaAmarillo[3][1] = terrain.getHeightTerrain(matrixModelPanditaAmarillo[3][0], matrixModelPanditaAmarillo[3][2]);
		panditaAmarillo.render(matrixModelPanditaAmarillo);
		glActiveTexture(GL_TEXTURE0);
		matrixModelPanditaVerde[3][1] = terrain.getHeightTerrain(matrixModelPanditaVerde[3][0], matrixModelPanditaVerde[3][2]);
		panditaVerde.render(matrixModelPanditaVerde);
		glActiveTexture(GL_TEXTURE0);
		matrixModelPanditaAzul[3][1] = terrain.getHeightTerrain(matrixModelPanditaAzul[3][0], matrixModelPanditaAzul[3][2]);
		panditaAzul.render(matrixModelPanditaAzul);
		glActiveTexture(GL_TEXTURE0);
		matrixModelPanditaNaranja[3][1] = terrain.getHeightTerrain(matrixModelPanditaNaranja[3][0], matrixModelPanditaNaranja[3][2]);
		panditaNaranja.render(matrixModelPanditaNaranja);
		glActiveTexture(GL_TEXTURE0);
		
		//Caramelos redner
		matrixModelCaramAmarillo[3][1] = terrain.getHeightTerrain(matrixModelCaramAmarillo[3][0], matrixModelCaramAmarillo[3][2]);
		glm::mat4 matrixModelCaramAmarilloBody = glm::mat4(matrixModelCaramAmarillo);
		matrixModelCaramAmarilloBody = glm::scale(matrixModelCaramAmarilloBody, glm::vec3(1.0, 1.0, 1.0));
		CaramAmarillo.render(matrixModelCaramAmarilloBody);
		glActiveTexture(GL_TEXTURE0);
		matrixModelCaramAzul[3][1] = terrain.getHeightTerrain(matrixModelCaramAzul[3][0], matrixModelCaramAzul[3][2]);
		glm::mat4 matrixModelCaramAzulBody = glm::mat4(matrixModelCaramAzul);
		matrixModelCaramAzulBody = glm::scale(matrixModelCaramAzulBody, glm::vec3(1.0, 1.0, 1.0));
		CaramAzul.render(matrixModelCaramAzulBody);
		glActiveTexture(GL_TEXTURE0);
		matrixModelCaramRosa[3][1] = terrain.getHeightTerrain(matrixModelCaramRosa[3][0], matrixModelCaramRosa[3][2]);
		glm::mat4 matrixModelCaramRosaBody = glm::mat4(matrixModelCaramRosa);
		matrixModelCaramRosaBody = glm::scale(matrixModelCaramRosaBody, glm::vec3(1.0, 1.0, 1.0));
		CaramRosa.render(matrixModelCaramRosaBody);
		glActiveTexture(GL_TEXTURE0);
		matrixModelCaramVerde[3][1] = terrain.getHeightTerrain(matrixModelCaramVerde[3][0], matrixModelCaramVerde[3][2]);
		glm::mat4 matrixModelCaramVerdeBody = glm::mat4(matrixModelCaramVerde);
		matrixModelCaramVerdeBody = glm::scale(matrixModelCaramVerdeBody, glm::vec3(1.0, 1.0, 1.0));
		CaramVerde.render(matrixModelCaramVerdeBody);
		glActiveTexture(GL_TEXTURE0);

		//Donas redner
		matrixModelDonaChocolate[3][1] = terrain.getHeightTerrain(matrixModelDonaChocolate[3][0], matrixModelDonaChocolate[3][2]);
		glm::mat4 matrixModelDonaChocolateBody = glm::mat4(matrixModelDonaChocolate);
		matrixModelDonaChocolateBody = glm::scale(matrixModelDonaChocolateBody, glm::vec3(1.0, 1.0, 1.0));
		DonaChocolate.render(matrixModelDonaChocolateBody);
		glActiveTexture(GL_TEXTURE0);
		matrixModelDonaFresa[3][1] = terrain.getHeightTerrain(matrixModelDonaFresa[3][0], matrixModelDonaFresa[3][2]);
		glm::mat4 matrixModelDonaFresaBody = glm::mat4(matrixModelDonaFresa);
		matrixModelDonaFresaBody = glm::scale(matrixModelDonaFresaBody, glm::vec3(1.0, 1.0, 1.0));
		DonaFresa.render(matrixModelDonaFresaBody);
		glActiveTexture(GL_TEXTURE0);

		//Helados render
		matrixModelHeladoChocolate[3][1] = terrain.getHeightTerrain(matrixModelHeladoChocolate[3][0], matrixModelHeladoChocolate[3][2]);
		glm::mat4 matrixModelHeladoChocolateBody = glm::mat4(matrixModelHeladoChocolate);
		matrixModelHeladoChocolateBody = glm::scale(matrixModelHeladoChocolateBody, glm::vec3(1.0, 1.0, 1.0));
		HeladoChocolate.render(matrixModelHeladoChocolateBody);
		glActiveTexture(GL_TEXTURE0);
		matrixModelHeladoFresa[3][1] = terrain.getHeightTerrain(matrixModelHeladoFresa[3][0], matrixModelHeladoFresa[3][2]);
		glm::mat4 matrixModelHeladoFresaBody = glm::mat4(matrixModelHeladoFresa);
		matrixModelHeladoFresaBody = glm::scale(matrixModelHeladoFresaBody, glm::vec3(1.0, 1.0, 1.0));
		HeladoFresa.render(matrixModelHeladoFresaBody);
		glActiveTexture(GL_TEXTURE0);
		matrixModelHeladoMenta[3][1] = terrain.getHeightTerrain(matrixModelHeladoMenta[3][0], matrixModelHeladoMenta[3][2]);
		glm::mat4 matrixModelHeladoMentaBody = glm::mat4(matrixModelHeladoMenta);
		matrixModelHeladoMentaBody = glm::scale(matrixModelHeladoMentaBody, glm::vec3(1.0, 1.0, 1.0));
		HeladoMenta.render(matrixModelHeladoMentaBody);
		glActiveTexture(GL_TEXTURE0);
		matrixModelHeladoMoraAzul[3][1] = terrain.getHeightTerrain(matrixModelHeladoMoraAzul[3][0], matrixModelHeladoMoraAzul[3][2]);
		glm::mat4 matrixModelHeladoMoraAzulBody = glm::mat4(matrixModelHeladoMoraAzul);
		matrixModelHeladoMoraAzulBody = glm::scale(matrixModelHeladoMoraAzulBody, glm::vec3(1.0, 1.0, 1.0));
		HeladoMoraAzul.render(matrixModelHeladoMoraAzulBody);
		glActiveTexture(GL_TEXTURE0);
		matrixModelHeladoMoraAzulFresa[3][1] = terrain.getHeightTerrain(matrixModelHeladoMoraAzulFresa[3][0], matrixModelHeladoMoraAzulFresa[3][2]);
		glm::mat4 matrixModelHeladoMoraAzulFresaBody = glm::mat4(matrixModelHeladoMoraAzulFresa);
		matrixModelHeladoMoraAzulFresaBody = glm::scale(matrixModelHeladoMoraAzulFresaBody, glm::vec3(1.0, 1.0, 1.0));
		HeladoMoraAzulFresa.render(matrixModelHeladoMoraAzulFresaBody);
		glActiveTexture(GL_TEXTURE0);
		
		//Piruletas render
		matrixModelPiruletaAmarillo[3][1] = terrain.getHeightTerrain(matrixModelPiruletaAmarillo[3][0], matrixModelPiruletaAmarillo[3][2]);
		glm::mat4 matrixModelPiruletaAmarilloBody = glm::mat4(matrixModelPiruletaAmarillo);
		matrixModelPiruletaAmarilloBody = glm::scale(matrixModelPiruletaAmarilloBody, glm::vec3(1.0, 1.0, 1.0));
		PiruletaAmarillo.render(matrixModelPiruletaAmarilloBody);
		glActiveTexture(GL_TEXTURE0);
		matrixModelPiruletaRojo[3][1] = terrain.getHeightTerrain(matrixModelPiruletaRojo[3][0], matrixModelPiruletaRojo[3][2]);
		glm::mat4 matrixModelPiruletaRojoBody = glm::mat4(matrixModelPiruletaRojo);
		matrixModelPiruletaRojoBody = glm::scale(matrixModelPiruletaRojoBody, glm::vec3(1.0, 1.0, 1.0));
		PiruletaRojo.render(matrixModelPiruletaRojoBody);
		glActiveTexture(GL_TEXTURE0);
		matrixModelPiruletaVerde[3][1] = terrain.getHeightTerrain(matrixModelPiruletaVerde[3][0], matrixModelPiruletaVerde[3][2]);
		glm::mat4 matrixModelPiruletaVerdeBody = glm::mat4(matrixModelPiruletaVerde);
		matrixModelPiruletaVerdeBody = glm::scale(matrixModelPiruletaVerdeBody, glm::vec3(1.0, 1.0, 1.0));
		PiruletaVerde.render(matrixModelPiruletaVerdeBody);
		glActiveTexture(GL_TEXTURE0);

		//BallKirby render
		matrixModelBallKirby[3][1] = terrain.getHeightTerrain(matrixModelBallKirby[3][0], matrixModelBallKirby[3][2]);
		glm::mat4 matrixModelBallKirbyBody = glm::mat4(matrixModelBallKirby);
		matrixModelBallKirbyBody = glm::scale(matrixModelBallKirbyBody, glm::vec3(0.30, 0.30, 0.30));
		BallKirby.render(matrixModelBallKirbyBody);
		glActiveTexture(GL_TEXTURE0);

		//BastonLampara render
		matrixModelBastonLampara[3][1] = terrain.getHeightTerrain(matrixModelBastonLampara[3][0], matrixModelBastonLampara[3][2]);
		glm::mat4 matrixModelBastonLamparaBody = glm::mat4(matrixModelBastonLampara);
		matrixModelBastonLamparaBody = glm::scale(matrixModelBastonLamparaBody, glm::vec3(3.0, 3.0, 3.0));
		BastonLampara.render(matrixModelBastonLamparaBody);
		glActiveTexture(GL_TEXTURE0);

		//Cake render
		matrixModelCake[3][1] = terrain.getHeightTerrain(matrixModelCake[3][0], matrixModelCake[3][2]);
		glm::mat4 matrixModelCakeBody = glm::mat4(matrixModelCake);
		matrixModelCakeBody = glm::scale(matrixModelCakeBody, glm::vec3(35.0, 35.0, 35.0));
		Cake.render(matrixModelCakeBody);
		glActiveTexture(GL_TEXTURE0);

		//Chocolate render
		matrixModelChocolate[3][1] = terrain.getHeightTerrain(matrixModelChocolate[3][0], matrixModelChocolate[3][2]);
		glm::mat4 matrixModelChocolateBody = glm::mat4(matrixModelChocolate);
		matrixModelChocolateBody = glm::scale(matrixModelChocolateBody, glm::vec3(35.0, 35.0, 35.0));
		Chocolate.render(matrixModelChocolateBody);
		glActiveTexture(GL_TEXTURE0);

		//ChocoPaleta render
		matrixModelChocoPaleta[3][1] = terrain.getHeightTerrain(matrixModelChocoPaleta[3][0], matrixModelChocoPaleta[3][2]);
		glm::mat4 matrixModelChocoPaletaBody = glm::mat4(matrixModelChocoPaleta);
		matrixModelChocoPaletaBody = glm::scale(matrixModelChocoPaletaBody, glm::vec3(1.0, 1.0, 1.0));
		ChocoPaleta.render(matrixModelChocoPaletaBody);
		glActiveTexture(GL_TEXTURE0);

		//Cookie render
		matrixModelCookie[3][1] = terrain.getHeightTerrain(matrixModelCookie[3][0], matrixModelCookie[3][2]);
		glm::mat4 matrixModelCookieBody = glm::mat4(matrixModelCookie);
		matrixModelCookieBody = glm::scale(matrixModelCookieBody, glm::vec3(35.0, 35.0, 35.0));
		Cookie.render(matrixModelCookieBody);
		glActiveTexture(GL_TEXTURE0);
		
		//Cute Home 1 render
		matrixModelCuteHome1[3][1] = terrain.getHeightTerrain(matrixModelCuteHome1[3][0], matrixModelCuteHome1[3][2]);
		glm::mat4 matrixModelCuteHome1Body = glm::mat4(matrixModelCuteHome1);
		matrixModelCuteHome1Body = glm::scale(matrixModelCuteHome1Body, glm::vec3(3.0, 3.0, 3.0));
		CuteHome1.render(matrixModelCuteHome1Body);
		glActiveTexture(GL_TEXTURE0);

		//Cute Home 2 render
		matrixModelCuteHome2[3][1] = terrain.getHeightTerrain(matrixModelCuteHome2[3][0], matrixModelCuteHome2[3][2]);
		glm::mat4 matrixModelCuteHome2Body = glm::mat4(matrixModelCuteHome2);
		matrixModelCuteHome2Body = glm::scale(matrixModelCuteHome2Body, glm::vec3(1.4, 1.4, 1.4));
		CuteHome2.render(matrixModelCuteHome2Body);
		glActiveTexture(GL_TEXTURE0);

		//Cute Shop render
		matrixModelCuteShop[3][1] = terrain.getHeightTerrain(matrixModelCuteShop[3][0], matrixModelCuteShop[3][2]);
		glm::mat4 matrixModelCuteShopBody = glm::mat4(matrixModelCuteShop);
		matrixModelCuteShopBody = glm::scale(matrixModelCuteShopBody, glm::vec3(3.0, 3.0, 3.0));
		CuteShop.render(matrixModelCuteShopBody);
		glActiveTexture(GL_TEXTURE0);
		
		//Ice Cream Sign render
		matrixModelIceCreamSign[3][1] = terrain.getHeightTerrain(matrixModelIceCreamSign[3][0], matrixModelIceCreamSign[3][2]);
		glm::mat4 matrixModelIceCreamSignBody = glm::mat4(matrixModelIceCreamSign);
		matrixModelIceCreamSignBody = glm::scale(matrixModelIceCreamSignBody, glm::vec3(1.0, 1.0, 1.0));
		IceCreamSign.render(matrixModelIceCreamSignBody);
		glActiveTexture(GL_TEXTURE0);

		//Nube Sign render
		//matrixModelNube[3][1] = terrain.getHeightTerrain(matrixModelNube[3][0], matrixModelNube[3][2]);
		glm::mat4 matrixModelNubeBody = glm::mat4(matrixModelNube);
		matrixModelNubeBody = glm::scale(matrixModelNubeBody, glm::vec3(10.0, 10.0, 10.0));
		Nube.render(matrixModelNubeBody);
		glActiveTexture(GL_TEXTURE0);

		//Paleta render
		matrixModelPaleta[3][1] = terrain.getHeightTerrain(matrixModelPaleta[3][0], matrixModelPaleta[3][2]);
		glm::mat4 matrixModelPaletaBody = glm::mat4(matrixModelPaleta);
		matrixModelPaletaBody = glm::scale(matrixModelPaletaBody, glm::vec3(5.0, 5.0, 5.0));
		Paleta.render(matrixModelPaletaBody);
		glActiveTexture(GL_TEXTURE0);

		//Strawberry render
		matrixModelStrawberry[3][1] = terrain.getHeightTerrain(matrixModelStrawberry[3][0], matrixModelStrawberry[3][2]);
		glm::mat4 matrixModelStrawberryBody = glm::mat4(matrixModelStrawberry);
		matrixModelStrawberryBody = glm::scale(matrixModelStrawberryBody, glm::vec3(20.0, 20.0, 20.0));
		Strawberry.render(matrixModelStrawberryBody);
		glActiveTexture(GL_TEXTURE0);

		//SweerCarrito render
		matrixModelSweetCarrito[3][1] = terrain.getHeightTerrain(matrixModelSweetCarrito[3][0], matrixModelSweetCarrito[3][2]);
		glm::mat4 matrixModelSweetCarritoBody = glm::mat4(matrixModelSweetCarrito);
		matrixModelSweetCarritoBody = glm::scale(matrixModelSweetCarritoBody, glm::vec3(20.0, 20.0, 20.0));
		SweetCarrito.render(matrixModelSweetCarritoBody);
		glActiveTexture(GL_TEXTURE0);

		//CuteGun 
		matrixModelCuteGun[3][1] = terrain.getHeightTerrain(matrixModelCuteGun[3][0], matrixModelCuteGun[3][2]);
		glm::mat4 matrixModelCuteGunBody = glm::mat4(matrixModelCuteGun);
		matrixModelCuteGunBody = glm::scale(matrixModelCuteGunBody, glm::vec3(50.0, 50.0, 50.0));
		CuteGun.render(matrixModelCuteGunBody);
		glActiveTexture(GL_TEXTURE0);

		/*
		// Render the lamps
		for (int i = 0; i < lamp1Position.size(); i++){
			lamp1Position[i].y = terrain.getHeightTerrain(lamp1Position[i].x, lamp1Position[i].z);
			modelLamp1.setPosition(lamp1Position[i]);
			modelLamp1.setScale(glm::vec3(0.5, 0.5, 0.5));
			modelLamp1.setOrientation(glm::vec3(0, lamp1Orientation[i], 0));
			modelLamp1.render();
		}

		for (int i = 0; i < lamp2Position.size(); i++){
			lamp2Position[i].y = terrain.getHeightTerrain(lamp2Position[i].x, lamp2Position[i].z);
			modelLamp2.setPosition(lamp2Position[i]);
			modelLamp2.setScale(glm::vec3(1.0, 1.0, 1.0));
			modelLamp2.setOrientation(glm::vec3(0, lamp2Orientation[i], 0));
			modelLamp2.render();
			modelLampPost2.setPosition(lamp2Position[i]);
			modelLampPost2.setScale(glm::vec3(1.0, 1.0, 1.0));
			modelLampPost2.setOrientation(glm::vec3(0, lamp2Orientation[i], 0));
			modelLampPost2.render();
		}
		*/
	
		/*******************************************
		 * Custom Anim objects obj
		 *******************************************/
		matrixModelMayow[3][1] = terrain.getHeightTerrain(matrixModelMayow[3][0], matrixModelMayow[3][2]);
		glm::mat4 matrixModelMayowBody = glm::mat4(matrixModelMayow);
		matrixModelMayowBody = glm::scale(matrixModelMayowBody, glm::vec3(5.0, 5.0, 5.0));
		.setAnimationIndex(animationIndex);
		MayowCuteAnimate.render(matrixModelMayowBody);
		

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

		/*******************************************
		 * Creacion de colliders
		 * IMPORTANT do this before interpolations
		 *******************************************/

		//Collider del los panditas
		AbstractModel::SBB panditaRojoCollider;
		glm::mat4 modelMatrixColliderPanditaRojo= glm::mat4(matrixModelPanditaRojo);
		modelMatrixColliderPanditaRojo = glm::scale(modelMatrixColliderPanditaRojo, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderPanditaRojo = glm::translate(modelMatrixColliderPanditaRojo, panditaRojo.getSbb().c);
		panditaRojoCollider.c = glm::vec3(modelMatrixColliderPanditaRojo[3]);
		panditaRojoCollider.ratio = panditaRojo.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "panditaRojo", panditaRojoCollider, matrixModelPanditaRojo);

		AbstractModel::SBB panditaVerdeCollider;
		glm::mat4 modelMatrixColliderPanditaVerde = glm::mat4(matrixModelPanditaVerde);
		modelMatrixColliderPanditaVerde = glm::scale(modelMatrixColliderPanditaVerde, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderPanditaVerde = glm::translate(modelMatrixColliderPanditaVerde, panditaVerde.getSbb().c);
		panditaVerdeCollider.c = glm::vec3(modelMatrixColliderPanditaVerde[3]);
		panditaVerdeCollider.ratio = panditaVerde.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "panditaVerde", panditaVerdeCollider, matrixModelPanditaVerde);

		AbstractModel::SBB panditaAzulCollider;
		glm::mat4 modelMatrixColliderPanditaAzul = glm::mat4(matrixModelPanditaAzul);
		modelMatrixColliderPanditaAzul = glm::scale(modelMatrixColliderPanditaAzul, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderPanditaAzul = glm::translate(modelMatrixColliderPanditaAzul, panditaAzul.getSbb().c);
		panditaAzulCollider.c = glm::vec3(modelMatrixColliderPanditaAzul[3]);
		panditaAzulCollider.ratio = panditaAzul.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "panditaAzul", panditaAzulCollider, matrixModelPanditaAzul);

		AbstractModel::SBB panditaAmarilloCollider;
		glm::mat4 modelMatrixColliderPanditaAmarillo = glm::mat4(matrixModelPanditaAmarillo);
		modelMatrixColliderPanditaAmarillo = glm::scale(modelMatrixColliderPanditaAmarillo, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderPanditaAmarillo = glm::translate(modelMatrixColliderPanditaAmarillo, panditaAmarillo.getSbb().c);
		panditaAmarilloCollider.c = glm::vec3(modelMatrixColliderPanditaAmarillo[3]);
		panditaAmarilloCollider.ratio = panditaAmarillo.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "panditaAmarillo", panditaAmarilloCollider, matrixModelPanditaAmarillo);

		AbstractModel::SBB panditaNaranjaCollider;
		glm::mat4 modelMatrixColliderPanditaNaranja = glm::mat4(matrixModelPanditaNaranja);
		modelMatrixColliderPanditaNaranja = glm::scale(modelMatrixColliderPanditaNaranja, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderPanditaNaranja = glm::translate(modelMatrixColliderPanditaNaranja, panditaNaranja.getSbb().c);
		panditaNaranjaCollider.c = glm::vec3(modelMatrixColliderPanditaNaranja[3]);
		panditaNaranjaCollider.ratio = panditaNaranja.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "panditaNaranja", panditaNaranjaCollider, matrixModelPanditaNaranja);
		/*
		// Lamps1 colliders
		for (int i = 0; i < lamp1Position.size(); i++){
			AbstractModel::OBB lampCollider;
			glm::mat4 modelMatrixColliderLamp = glm::mat4(1.0);
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, lamp1Position[i]);
			modelMatrixColliderLamp = glm::rotate(modelMatrixColliderLamp, glm::radians(lamp1Orientation[i]),
					glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "lamp1-" + std::to_string(i), lampCollider, modelMatrixColliderLamp);
			// Set the orientation of collider before doing the scale
			lampCollider.u = glm::quat_cast(modelMatrixColliderLamp);
			modelMatrixColliderLamp = glm::scale(modelMatrixColliderLamp, glm::vec3(0.5, 0.5, 0.5));
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, modelLamp1.getObb().c);
			lampCollider.c = glm::vec3(modelMatrixColliderLamp[3]);
			lampCollider.e = modelLamp1.getObb().e * glm::vec3(0.5, 0.5, 0.5);
			std::get<0>(collidersOBB.find("lamp1-" + std::to_string(i))->second) = lampCollider;
		}

		// Lamps2 colliders
		for (int i = 0; i < lamp2Position.size(); i++){
			AbstractModel::OBB lampCollider;
			glm::mat4 modelMatrixColliderLamp = glm::mat4(1.0);
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, lamp2Position[i]);
			modelMatrixColliderLamp = glm::rotate(modelMatrixColliderLamp, glm::radians(lamp2Orientation[i]),
					glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "lamp2-" + std::to_string(i), lampCollider, modelMatrixColliderLamp);
			// Set the orientation of collider before doing the scale
			lampCollider.u = glm::quat_cast(modelMatrixColliderLamp);
			modelMatrixColliderLamp = glm::scale(modelMatrixColliderLamp, glm::vec3(1.0, 1.0, 1.0));
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, modelLampPost2.getObb().c);
			lampCollider.c = glm::vec3(modelMatrixColliderLamp[3]);
			lampCollider.e = modelLampPost2.getObb().e * glm::vec3(1.0, 1.0, 1.0);
			std::get<0>(collidersOBB.find("lamp2-" + std::to_string(i))->second) = lampCollider;
		}
		*/
		/*
		// Collider de mayow
		AbstractModel::OBB mayowCollider;
		glm::mat4 modelmatrixColliderMayow = glm::mat4(modelMatrixMayow);
		modelmatrixColliderMayow = glm::rotate(modelmatrixColliderMayow,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		mayowCollider.u = glm::quat_cast(modelmatrixColliderMayow);
		modelmatrixColliderMayow = glm::scale(modelmatrixColliderMayow, glm::vec3(0.021, 0.021, 0.021));
		modelmatrixColliderMayow = glm::translate(modelmatrixColliderMayow,
				glm::vec3(mayowModelAnimate.getObb().c.x,
						mayowModelAnimate.getObb().c.y,
						mayowModelAnimate.getObb().c.z));
		mayowCollider.e = mayowModelAnimate.getObb().e * glm::vec3(0.021, 0.021, 0.021) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		mayowCollider.c = glm::vec3(modelmatrixColliderMayow[3]);
		addOrUpdateColliders(collidersOBB, "mayow", mayowCollider, modelMatrixMayow);
		*/

		/*******************************************
		 * Render de colliders
		 *******************************************/
		/*for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
				collidersOBB.begin(); it != collidersOBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = matrixCollider * glm::mat4(std::get<0>(it->second).u);
			matrixCollider = glm::scale(matrixCollider, std::get<0>(it->second).e * 2.0f);
			boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			boxCollider.enableWireMode();
			boxCollider.render(matrixCollider);
		}

		for (std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
				collidersSBB.begin(); it != collidersSBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = glm::scale(matrixCollider, glm::vec3(std::get<0>(it->second).ratio * 2.0f));
			sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			sphereCollider.enableWireMode();
			sphereCollider.render(matrixCollider);
		}
		*/
		// Esto es para ilustrar la transformacion inversa de los coliders
		/*glm::vec3 cinv = glm::inverse(mayowCollider.u) * glm::vec4(rockCollider.c, 1.0);
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
		 * State machines
		 *******************************************/
		/*
		// State machine for the lambo car
		switch(stateDoor){
		case 0:
			dorRotCount += 0.5;
			if(dorRotCount > 75)
				stateDoor = 1;
			break;
		case 1:
			dorRotCount -= 0.5;
			if(dorRotCount < 0){
				dorRotCount = 0.0;
				stateDoor = 0;
			}
			break;
		}
		*/
		glfwSwapBuffers(window);
	}
}

int main(int argc, char **argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
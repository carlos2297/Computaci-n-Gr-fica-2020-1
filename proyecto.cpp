/*---------------------------------------------------------*/
/* ----------------   PROYECTO FINAL --------------------------*/
/*-----------------    2020-1   ---------------------------*/
/*------------- RANGEL GARCIA CARLOS ALBERTO
              HERNANDEZ ALBINO EDGAR ALEJANDRO
                MORENO MORADO JESUS DANIEL    ---------------*/

//#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>
#include <Windows.h>
#include <MMSystem.h>
#include "camera.h"
#include "Model.h"
#include <iostream>
#include <alut.h>

#define NUM_BUFFERS 2
#define NUM_SOURCES 2
#define NUM_ENVRIONMENTS 1


// Config OpenAL
ALfloat listenerPos[] = { 0.0, 0.0, 0.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
// Source 0
ALfloat source0Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
// Source 1
ALfloat source1Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
// Buffers
ALuint buffers[NUM_BUFFERS];
ALuint sources[NUM_SOURCES];
ALuint enviornment[NUM_ENVRIONMENTS];
// variables para inicializar audios
ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
ALboolean loop;


// Other Libs
#include "SOIL2/SOIL2.h"


void resize(GLFWwindow *window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);


// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWwindow *window;
GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

//Camera
Camera camera(glm::vec3(-21.0f, 3.0f, 20.0f));
//Camera camera(glm::vec3(-38.0f, 7.0f, 12.0f));
//Camera camera(glm::vec3(0.0f, 5.0f, 25.0f));

double	lastX = 0.0f,
         mul = 1.0f,
		lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 2.0f, 2.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

void myData(void);
void display(Shader, Model, Model);
void getResolution(void);
void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);
int ESTADO = 0;
//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
	    j  = 0.0f,
		movZ = -5.0f,
	    rotY = 0.0f,
	    dx=-49.0f,
	    dy = -1.3f,
	    dz = -10.0f,
		//rotY = 55.0f,
        rotP = 0.0f;

float movLuzX = 0.0f;

//Texture
unsigned int	t_smile,
				t_toalla,
				t_unam,
				t_white,
				t_panda,
				t_cubo,
				t_caja,
				t_caja_brillo,
				t_pared_A,
				t_pared_B,
				t_pared_C,
				t_pilar,
	            lamp,
	            imagen,
	            start,
				t_piso,
				t_techo,
				t_aire,
				t_pizarron,
				t_cartel,
				t_cartel2,
				t_sismo,
				t_placa;

//For model
bool animacion = false;
bool ro = false;
bool uno = false;
bool dos = false;
bool ho = false;
bool cuatro = false;
bool cinco = false;
bool casa1 = false;
bool casa2 = false;
bool candy = false;

//Keyframes 
//Variables de dibujo
float	posX = 0.0f,
posY = 10.0f,
posZ = 0.0f,
giro = 0.0f,

posAX = 0.0f,
posAY = 4.0f,
posAZ = 0.0f,
giroA = 0.0f,


wing = 0.0f;

float	incX = 0.0f,
incY = 0.0f,
incZ = 0.0f,

giroGargolaInc = 0.0f,
giroAvionInc = 0.0f,
incAX = 0.0f,
incAY = 0.0f,
incAZ = 0.0f;


float movBrazoInc = 0.0f;

#define MAX_FRAMES 10
int i_max_steps = 30;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float giro;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
FRAME KeyFrame2[MAX_FRAMES];

int FrameIndex = 6;			//Introducir datos
bool play = false;          //Indica cuando se inicia la animacion
int playIndex = 6;

int FrameIndex2 = 6;			//Introducir datos
bool play2 = false;          //Indica cuando se inicia la animacion
int playIndex2 = 6;

void planeFrame(void)
{
	KeyFrame2[0].posX = 0.0f;
	KeyFrame2[0].posY = 4.0f;
	KeyFrame2[0].posZ = 0.0f;
	KeyFrame2[0].giro = 0.0f;

	KeyFrame2[1].posX = 0.0f;
	KeyFrame2[1].posY = 4.0f;
	KeyFrame2[1].posZ = -8.0f;
	KeyFrame2[1].giro = 90.0f;

	KeyFrame2[2].posX = 2.0f;
	KeyFrame2[2].posY = 4.0f;
	KeyFrame2[2].posZ = 0.0f;
	KeyFrame2[2].giro = 0.0f;

	KeyFrame2[3].posX = -10.0f;
	KeyFrame2[3].posY = 2.0f;
	KeyFrame2[3].posZ = -13.0f;
	KeyFrame2[3].giro = 0.0f;

	KeyFrame2[4].posX = -20.0f;
	KeyFrame2[4].posY = 2.0f;
	KeyFrame2[4].posZ = 0.0f;
	KeyFrame2[4].giro = 0.0f;

	KeyFrame2[5].posX = -30.0f;
	KeyFrame2[5].posY = 2.0f;
	KeyFrame2[5].posZ = 0.0f;
	KeyFrame2[5].giro = 0.0f;

}

void resetElements2(void)
{
	posAX = KeyFrame2[0].posX;
	posAY = KeyFrame2[0].posY;
	posAZ = KeyFrame2[0].posZ;
	giroA = KeyFrame2[0].giro;
}

void interpolation2(void)
{
	incAX = (KeyFrame2[playIndex + 1].posX - KeyFrame2[playIndex].posX) / i_max_steps;
	incAY = (KeyFrame2[playIndex + 1].posY - KeyFrame2[playIndex].posY) / i_max_steps;
	incAZ = (KeyFrame2[playIndex + 1].posZ - KeyFrame2[playIndex].posZ) / i_max_steps;
	giroAvionInc = (KeyFrame2[playIndex + 1].giro - KeyFrame2[playIndex].giro) / i_max_steps;
}

void gargolaFrame(void) {
	KeyFrame[0].posX = -40.0f;
	KeyFrame[0].posY = 10.0f;
	KeyFrame[0].posZ = 0.0f;
	KeyFrame[0].giro = -20.0f;

	KeyFrame[1].posX = -55.0f;
	KeyFrame[1].posY = 10.0f;
	KeyFrame[1].posZ = 0.0f;
	KeyFrame[1].giro = 10.0f;

	KeyFrame[2].posX = -40.0f;
	KeyFrame[2].posY = 10.0f;
	KeyFrame[2].posZ = 15.0f;
	KeyFrame[2].giro = -20.0f;

	KeyFrame[3].posX = -55.0f;
	KeyFrame[3].posY = 10.0f;
	KeyFrame[3].posZ = 0.0f;
	KeyFrame[3].giro = 10.0f;

	KeyFrame[4].posX = -40.0f;
	KeyFrame[4].posY = 10.0f;
	KeyFrame[4].posZ = 0.0f;
	KeyFrame[4].giro = -20.0f;

	KeyFrame[5].posX = -55.0f;
	KeyFrame[5].posY = 10.0f;
	KeyFrame[5].posZ = 0.0f;
	KeyFrame[5].giro = 10.0f;

}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;
	giro = KeyFrame[0].giro;
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	giroGargolaInc = (KeyFrame[playIndex + 1].giro - KeyFrame[playIndex].giro) / i_max_steps;
}

///////////////////////////////

unsigned int generateTextures(const char* filename, bool alfa)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
		   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	   glGenerateMipmap(GL_TEXTURE_2D);
	   return textureID;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void LoadTextures()
{
	t_pared_A = generateTextures("Texturas/Textura_Pared.png", 1);
	t_pared_B = generateTextures("Texturas/Textura_pared_B.png", 1);
	t_pared_C = generateTextures("Texturas/Cortina.png", 1);
	t_pilar = generateTextures("Texturas/pilar.jpg", 0);
	t_piso = generateTextures("Texturas/Piso.jpg", 0);
	t_techo = generateTextures("Texturas/techo.jpg", 0);
	t_aire = generateTextures("Texturas/Salida_aire.png", 1);
	t_pizarron = generateTextures("Texturas/pizarron.png", 1);
	t_cartel = generateTextures("Texturas/No_cartel.png", 1);
	t_cartel2 = generateTextures("Texturas/No_cartel2.png", 1);
	t_sismo = generateTextures("Texturas/Sismo_cartel.png", 1);
	t_placa = generateTextures("Texturas/placa_metal_piso.jpg", 0);
	start = generateTextures("Texturas/start.jpg", 0);
	imagen = generateTextures("Texturas/w.jpg", 0);
	lamp = generateTextures("Texturas/lamp.png", 1);

}

void myData()
{	
	float vertices[] = {

		 1.0f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f, //0
		 1.0f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f, //1
		 0.0f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, //2
		 0.0f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f, //3


	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void animate(void)
{
	/////////////KEYFRAMES////////////////////////////////////////////////////
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("Termina animacion\n");
				playIndex = 0;

				resetElements();
				resetElements2();
				//play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter				 
				interpolation();  //Interpolation
				interpolation2();
			}
		}
		else {

			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;
			giro += giroGargolaInc;

			posAX += incAX;
			posAY += incAY;
			posAZ += incAZ;
			giroA += giroAvionInc;

			i_curr_steps++;
		}
	}

    ///////////////////////////////////////////////////
	//1///////////////PUERTA//////////////////////////
	if (animacion) {

		
		if (rotP > -50.0F) {
			rotP -= 1.0f;
		}
		else {
			animacion = false;
		}
	}
	/////////////////////////////////////////////////

	//2/////////////////RECORRIDO CASA 1////////////////
	if (ro) {

		mul -= .5;
		camera.Cambio(glm::vec3(-20.0f-mul, 3.0f, 18.0+mul),-35);
		camera.ProcessMouseMovement(0, 0);
		if (mul < -30.0) {
			ro = false;
		}

	}
	//////////////////////////////////////////////////

	//3/////////////////RECORRIDO CASA 1////////////////
	if (ho) {

		camera.Cambio(glm::vec3(-30.0f + mul, 3.0f, 10.0+mul*1.8),(-90+mul*10));
		camera.ProcessMouseMovement(0, 0);
		if (mul < -10.0) {
			ho = false;
		}
		mul -= 0.2;
		
	}
	//////////////////////////////////////////////////

	//4////////ZOMBIE//////////////////////////////////
	switch (ESTADO) {
	case 0: //ESTADO:INICIO 
		rotY += 3.0f;
		if (rotY > 20) {
			ESTADO = 1;
		}
		break;
	case 1: //ESTADO:REVERSA
		rotY -= 3.0f;
		if (rotY < -20) {
			ESTADO = 0;
		}
		break;
	}
	///////////////////////////////////////////////////
	/////////////////////5////////////////////////////
	if (candy) {

		camera.Cambio(glm::vec3(dx-0.2,dy+3.0,dz+7.0),-90);
		camera.ProcessMouseMovement(0, 0);
		dz += 0.5;
		dx += 0.05;
		dy += 0.1;

		if (dz > 6) {

			dx = -49;
			dy = -1.3;
			dz = -10;
			candy = false;
		}
	}

}
bool flag = false;

void display(Shader shader,Shader text, Model mesa, Model piso,Model pc,Model pc2,Model pci,Model pc2i,
	Model silla,Model Proyector,Model agua,Model aire,Model botiquin,Model ex,Model cielo, Model arbol,Model casa,Model zombie,
	Model dulces,Model ofrenda,Model sonido,Model cama,Model sillon,Model avion,Model gargola,Model alaDer,Model alaIzq)
{

	//text.use();
	shader.use();
	float i = 0;

	
	//iluminacion SHADER MULTI LUCES SHADE_LIGHTS

	shader.setVec3("viewPos", camera.Position);

	shader.setVec3("dirLight.direction", camera.Front);
	shader.setVec3("dirLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	shader.setVec3("dirLight.specular", glm::vec3(0.6f, 0.6f, 0.6f));


	shader.setFloat("material_shininess", 32.0f);



	// create transformations and Projection
	glm::mat4 temp01 = glm::mat4(1.0f);
	glm::mat4 tmp = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	//view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));


	// pass them to the shaders
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("projection", projection);

   ///////////////////////////////////MODELADO DEL SALON////////////////////////////////////////////////////////////////////////////

	if (casa1) {
		shader.setVec3("pointLight[0].position", glm::vec3(-8.0f, 8.1f, 0.0f));
		shader.setVec3("pointLight[0].ambient", glm::vec3(0.2f, 0.05f, 0.05f));
		shader.setVec3("pointLight[0].diffuse", glm::vec3(0.6f, 0.0f, 0.0f));
		shader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[0].constant", 0.2f);
		shader.setFloat("pointLight[0].linear", 0.0004f);
		shader.setFloat("pointLight[0].quadratic", 0.004f);

		shader.setVec3("pointLight[1].position", glm::vec3(8.0f, 8.1f, 0.0f));
		shader.setVec3("pointLight[1].ambient", glm::vec3(0.05f, 0.2f, 0.05f));
		shader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.6f, 0.0f));
		shader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[1].constant", 0.2f);
		shader.setFloat("pointLight[1].linear", 0.0004f);
		shader.setFloat("pointLight[1].quadratic", 0.004f);
	}
	else {
		shader.setVec3("pointLight[0].position", glm::vec3(-8.0f, 8.1f, 0.0f));
		shader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.00f, 0.00f));
		shader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[0].constant", 0.5f);
		shader.setFloat("pointLight[0].linear", 0.0004f);
		shader.setFloat("pointLight[0].quadratic", 0.004f);

		shader.setVec3("pointLight[1].position", glm::vec3(8.0f, 8.1f, 0.0f));
		shader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.f, 0.0f));
		shader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[1].constant", 0.5f);
		shader.setFloat("pointLight[1].linear", 0.0004f);
		shader.setFloat("pointLight[1].quadratic", 0.004f);

	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.8f, 1.25f));
	model = glm::scale(model, glm::vec3(0.007f, 0.001f, 0.0061f));
	shader.setMat4("model", model);
	piso.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(40.0f, -47.5f, 0.0f));
	model = glm::scale(model, glm::vec3(1.4f, 0.9f, 0.7f));
	shader.setMat4("model", model);
	cielo.Draw(shader);


	glBindVertexArray(VAO);

	//Parte del frente del salón
	for (i = 0; i <35; i = i + 5.0f) {
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.5+i, -1.8f, -14.0f));
		model = glm::scale(model, glm::vec3(5.0f, 10.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glBindTexture(GL_TEXTURE_2D, t_pared_B);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	//Parte trasera del salón
	for (i = 0; i < 35; i = i + 5.0f) {
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.5+i, -1.8f, 16.5f));
		model = glm::scale(model, glm::vec3(5.0f, 10.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, t_pared_B);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	//Parte izquierda del salón
	for (i = 0; i <= 20; i = i + 5.0f) {
		model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(i -14, -1.8f, 17.5f));
		model = glm::scale(model, glm::vec3(5.0f, 10.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, t_pared_A);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	//Puerta

	model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(30.5 - 14, -1.8f, 17.5f));
	model = glm::rotate(model, glm::radians(rotP), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-5.5, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(5.5f, 10.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, t_pared_A);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



	//Parte derecha del salón
	for (i = 0; i <= 24.0f; i = i + 6.0f) {
		model = glm::translate(glm::mat4(1.0f), glm::vec3(17.5f, -1.8f, -14 + i));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.5f, 10.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, t_pared_C);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	//Pilar derecho frontal
	model = glm::translate(glm::mat4(1.0f), glm::vec3(17.4f, 0.0f, -3.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.2f, 8.2f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, t_pilar);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//Pilar derecho trasero
	model = glm::translate(glm::mat4(1.0f), glm::vec3(17.4f, 0.0f, 16.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 8.2f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, t_pilar);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//Techo
	for (float i = 0; i <30 ; i = i + 5) {
		for (float j = 0; j < 26; j++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(j-17.5f, 8.2f, i-14.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(10.0f, 5.5f, 0.0f));
			shader.setMat4("model", model);
			shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
			glBindTexture(GL_TEXTURE_2D, t_techo);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	//Salida de Aire
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-13.0f, 8.1f, -8.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, t_aire);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(13.0f, 8.1f, 12.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, t_aire);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(13.0f, 8.1f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, t_aire);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//lamparas

	model = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 8.1f, -7.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 3.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, lamp);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 8.1f, -7.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 3.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, lamp);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 8.1f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 3.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, lamp);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 8.1f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 3.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, lamp);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 8.1f, 7.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 3.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, lamp);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 8.1f, 7.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 3.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, lamp);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	//Pizarron
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-6.0f, -1.5f, -13.9f));
	model = glm::scale(model, glm::vec3(11.0f, 10.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindTexture(GL_TEXTURE_2D, t_pizarron);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//Letreros
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, 6.0f, -13.9f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindTexture(GL_TEXTURE_2D, t_cartel);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(1.8f, 5.7f, -13.9f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindTexture(GL_TEXTURE_2D, t_cartel2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-12.0, 3.0f, -13.9f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindTexture(GL_TEXTURE_2D, t_sismo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////PRENDER COMPUTADORAS////////////////////////////////////////

	if (flag == true) {

		//mesa 1

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-13.5f, 0.21f, -8.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.2f, 0.21f, -8.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-6.9f, 0.21f, -8.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.7f, 0.21f, -8.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	   //mesa 2 

		model = glm::translate(glm::mat4(1.0f), glm::vec3(12.58f, 0.21f, -8.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(9.3f, 0.21f, -8.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.21f, -8.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(2.6f, 0.21f, -8.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//mesa 3

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-13.5f, 0.21f, -0.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.2f, 0.21f, -0.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-6.9f, 0.21f, -0.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.7f, 0.21f, -0.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//mesa 5

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-13.5f, 0.21f, 7.69f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.2f, 0.21f, 7.69f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(-6.9f, 0.21f, 7.69f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.7f, 0.21f, 7.69f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//mesa 4

		model = glm::translate(glm::mat4(1.0f), glm::vec3(12.58f, 0.21f, -0.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(9.3f, 0.21f, -0.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.21f, -0.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(2.6f, 0.21f, -0.3f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//mesa 6

		model = glm::translate(glm::mat4(1.0f), glm::vec3(12.58f, 0.21f, 7.69f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(9.3f, 0.21f, 7.69f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.21f, 7.69f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(2.6f, 0.21f, 7.69f));
		model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
		shader.setMat4("model", model);
		shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



		j += 0.002f;
		if (j > 0.09f) {
			flag = false;
		}


	}
	//mesa 1

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-13.5f, 0.21f, -8.4 + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.2f, 0.21f, -8.4 + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-6.9f, 0.21f, -8.4 + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.7f, 0.21f, -8.4 + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//mesa 2

	model = glm::translate(glm::mat4(1.0f), glm::vec3(12.58f, 0.21f, -8.4 + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(9.3f, 0.21f, -8.4 + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.21f, -8.4 + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.6f, 0.21f, -8.4 + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//mesa 3

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-13.5f, 0.21f, -0.4f+j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.2f, 0.21f, -0.4f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-6.9f, 0.21f, -0.4f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.7f, 0.21f, -0.4f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//mesa 5

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-13.5f, 0.21f, 7.61f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.2f, 0.21f, 7.61f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(-6.9f, 0.21f, 7.61f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.7f, 0.21f, 7.61f+j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//mesa 4

	model = glm::translate(glm::mat4(1.0f), glm::vec3(12.58f, 0.21f, -0.4f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(9.3f, 0.21f, -0.4f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.21f, -0.4f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.6f, 0.21f, -0.4f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//mesa 6

	model = glm::translate(glm::mat4(1.0f), glm::vec3(12.58f, 0.21f, 7.61f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(9.3f, 0.21f, 7.61f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.21f, 7.61f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.6f, 0.21f, 7.61f + j));
	model = glm::scale(model, glm::vec3(1.65f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, imagen);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



	//////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////MODELADO DE LOS ELEMENTOS DEL SALON//////////////////////////////
	//mesa 1

	model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(8.52f, -2.7f, 8.0f));
	model = glm::scale(model, glm::vec3(0.131f, 0.1f, 0.1f));
	shader.setMat4("model", model);
	mesa.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-2.5f, -0.1f, -7.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc2i.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-5.7f, -0.1f, -7.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc2i.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-9.0f, -0.1f, -7.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc2i.Draw(shader);


	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-12.3f, -0.1f, -7.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc2i.Draw(shader);


	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-3.1f, -1.7f, -6.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-6.3f, -1.7f, -6.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-9.6f, -1.7f, -6.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-12.9f, -1.7f, -6.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);



	//mesa 2

	model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-8.52f, -2.7f, 8.0f));
	model = glm::scale(model, glm::vec3(0.131f, 0.1f, 0.1f));
	shader.setMat4("model", model);
	mesa.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(3.8f, -0.1f, -7.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc2.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(7.2f, -0.1f, -7.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(10.5f, -0.1f, -7.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(13.8f, -0.1f, -7.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(3.4f, -1.7f, -6.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(6.8f, -1.7f, -6.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(10.1f, -1.7f, -6.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(13.4f, -1.7f, -6.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);



	//mesa 3

	model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(8.52f, -2.7f, 0.0f));
	model = glm::scale(model, glm::vec3(0.131f, 0.1f, 0.1f));
	shader.setMat4("model", model);
	mesa.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-2.5f, -0.1f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pci.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-5.7f, -0.1f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pci.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-9.0f, -0.1f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pci.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-12.3f, -0.1f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pci.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-3.1f, -1.7f, 2.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-6.3f, -1.7f, 2.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-9.6f, -1.7f, 2.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-12.9f, -1.7f, 2.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);



	//mesa 4

	model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-8.52f, -2.7f, 0.0f));
	model = glm::scale(model, glm::vec3(0.131f, 0.1f, 0.1f));
	shader.setMat4("model", model);
	mesa.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(3.8f, -0.1f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(7.2f, -0.1f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(10.5f, -0.1f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(13.8f, -0.1f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(3.4f, -1.7f, 2.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(6.8f, -1.7f, 2.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(10.1f, -1.7f, 2.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(13.4f, -1.7f, 2.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);


	//mesa 5

	model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(8.52f, -2.7f, -8.0f));
	model = glm::scale(model, glm::vec3(0.131f, 0.1f, 0.1f));
	shader.setMat4("model", model);
	mesa.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-2.5f, -0.1f, 9.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pci.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-5.7f, -0.1f, 9.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pci.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-9.0f, -0.1f, 9.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pci.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-12.3f, -0.1f, 9.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pci.Draw(shader);

    model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-3.1f, -1.7f, 10.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-6.3f, -1.7f, 10.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-9.6f, -1.7f, 10.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-12.9f, -1.7f, 10.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);


	////mesa 6

	model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-8.52f, -2.7f, -8.0f));
	model = glm::scale(model, glm::vec3(0.131f, 0.1f, 0.1f));
	shader.setMat4("model", model);
	mesa.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(3.8f, -0.1f, 9.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(7.2f, -0.1f, 9.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(10.5f, -0.1f, 9.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(13.8f, -0.1f, 9.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	pc.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(3.4f, -1.7f, 10.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(6.8f, -1.7f, 10.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(10.1f, -1.7f, 10.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(13.4f, -1.7f, 10.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.005f, 0.006f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	////////////////////////OTROS MODELOS DEL SALON//////////////////////////////////////////////
	model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 6.0f, -4.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	Proyector.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-18.0f, -4.7f, 1.0f));
	model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
	shader.setMat4("model", model);
	agua.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-1.5f, 6.5f, -16.6f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setMat4("model", model);
	aire.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-2.0f, 3.2f, -19.4f));
	model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
	shader.setMat4("model", model);
	botiquin.Draw(shader);

	model = glm::rotate(glm::mat4(1.0f), glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(17.0f, -16.0f, 4.0f));
	model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
	shader.setMat4("model", model);
	ex.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.7f, -12.0f));
	model = glm::scale(model, glm::vec3(0.015f, 0.015f, 0.015f));
	shader.setMat4("model", model);
	arbol.Draw(shader);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////CASA HALLOWEEN///////////////////////////////////////////////////////////////////////
	
	if (casa2) {

		shader.setVec3("pointLight[2].position", glm::vec3(-35.0f, 2.0f, -5.0f));
		shader.setVec3("pointLight[2].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader.setVec3("pointLight[2].diffuse", glm::vec3(0.6f, 0.6f, 0.6f));
		shader.setVec3("pointLight[2].specular", glm::vec3(1.0f, 0.8f, 0.8f));
		shader.setFloat("pointLight[2].constant", 0.5f);
		shader.setFloat("pointLight[2].linear", 0.004f);
		shader.setFloat("pointLight[2].quadratic", 0.04f);

		shader.setVec3("pointLight[3].position", glm::vec3(-52.0f, -1.3f, 5.0f));
		shader.setVec3("pointLight[3].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader.setVec3("pointLight[3].diffuse", glm::vec3(0.6f, 0.6f, 0.6f));
		shader.setVec3("pointLight[3].specular", glm::vec3(1.0f, 0.8f, 0.8f));
		shader.setFloat("pointLight[3].constant", 0.2f);
		shader.setFloat("pointLight[3].linear", 0.004f);
		shader.setFloat("pointLight[3].quadratic", 0.04f);

		shader.setVec3("pointLight[4].position", glm::vec3(-44.0f, -1.3f, 5.0f));
		shader.setVec3("pointLight[4].ambient", glm::vec3(0.2f, 0.0f, 0.0f));
		shader.setVec3("pointLight[4].diffuse", glm::vec3(0.6f, 0.0f, 0.0f));
		shader.setVec3("pointLight[4].specular", glm::vec3(1.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[4].constant", 0.2f);
		shader.setFloat("pointLight[4].linear", 0.004f);
		shader.setFloat("pointLight[4].quadratic", 0.04f);

		shader.setVec3("pointLight[5].position", glm::vec3(-38.0f, 7.0f, 12.0f));
		shader.setVec3("pointLight[5].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader.setVec3("pointLight[5].diffuse", glm::vec3(0.6f, 0.6f, 0.6f));
		shader.setVec3("pointLight[5].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setFloat("pointLight[5].constant", 0.2f);
		shader.setFloat("pointLight[5].linear", 0.004f);
		shader.setFloat("pointLight[5].quadratic", 0.04f);


	}
	else {

		shader.setVec3("pointLight[2].position", glm::vec3(-40.0f, 1.0f, 1.25f));
		shader.setVec3("pointLight[2].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[2].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[2].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[2].constant", 1.0f);
		shader.setFloat("pointLight[2].linear", 0.0004f);
		shader.setFloat("pointLight[2].quadratic", 0.004f);

		shader.setVec3("pointLight[3].position", glm::vec3(-52.0f, -1.3f, 5.0f));
		shader.setVec3("pointLight[3].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[3].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[3].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[3].constant", 0.2f);
		shader.setFloat("pointLight[3].linear", 0.004f);
		shader.setFloat("pointLight[3].quadratic", 0.04f);

		shader.setVec3("pointLight[4].position", glm::vec3(-44.0f, -1.3f, 5.0f));
		shader.setVec3("pointLight[4].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[4].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[4].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[4].constant", 0.2f);
		shader.setFloat("pointLight[4].linear", 0.004f);
		shader.setFloat("pointLight[4].quadratic", 0.04f);

		shader.setVec3("pointLight[5].position", glm::vec3(-38.0f, 7.0f, 12.0f));
		shader.setVec3("pointLight[5].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[5].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("pointLight[5].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setFloat("pointLight[5].constant", 0.2f);
		shader.setFloat("pointLight[5].linear", 0.004f);
		shader.setFloat("pointLight[5].quadratic", 0.04f);


	}

	//Avion
	model = glm::translate(glm::mat4(1.0f), glm::vec3(posAX, posAY, posAZ));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	tmp = model = glm::rotate(model, glm::radians(giroA), glm::vec3(0.0f, 1.0f, 0.0));
	shader.setMat4("model", model);
	avion.Draw(shader);

	//Gargola
	model = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	temp01 = model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
	//model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	gargola.Draw(shader);

	//Ala Derecha
	model = glm::translate(temp01, glm::vec3(0, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(giro), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	alaDer.Draw(shader);

	//Ala Izquierda
	model = glm::translate(temp01, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-giro), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	alaIzq.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.0f, -1.8f, -5.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.1f));
	shader.setMat4("model", model);
	casa.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.0f, 9.0f, -2.0f));
	model = glm::rotate(model, glm::radians(rotY), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -9.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setMat4("model", model);
	zombie.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(dx,dy,dz));
	model = glm::scale(model, glm::vec3(0.0004f, 0.0004f, 0.0004f));
	shader.setMat4("model", model);
	dulces.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-36, -0.8, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
	shader.setMat4("model", model);
	cama.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-38, -0.9, -10));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
	shader.setMat4("model", model);
	sillon.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-37, -0.7, -5.5));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
	shader.setMat4("model", model);
	sonido.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-32,-0.9, -5.0));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.0012f, 0.0012f, 0.0012f));
	shader.setMat4("model", model);
	ofrenda.Draw(shader);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	glBindVertexArray(0);
	  
	// Libreria de audio
    // openal sound data
	source0Pos[0] = 0;
	source0Pos[1] = -1.7;
	source0Pos[2] = -12;
	alSourcefv(sources[0], AL_POSITION, source0Pos);
	source1Pos[0] = -37;
	source1Pos[1] = -0.9;
	source1Pos[2] = -5.5;
	alSourcefv(sources[1], AL_POSITION, source1Pos);
	// Position listener
	listenerPos[0] = camera.Position.x;
	listenerPos[1] = camera.Position.y;
	listenerPos[2] = camera.Position.z;
	alListenerfv(AL_POSITION, listenerPos);
	// Orientation listener
	listenerOri[0] = camera.Front.x;
	listenerOri[1] = camera.Front.y;
	listenerOri[2] = camera.Front.z;
	listenerOri[3] = camera.Up.x;
	listenerOri[4] = camera.Up.y;
	listenerOri[5] = camera.Up.z;
	alListenerfv(AL_ORIENTATION, listenerOri);


	



}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PROYECTO FINAL-RANGEL CARLOS-HERNANDEZ EDGAR-MORENO JESUS", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	// OpenAL init
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError(); // Limpiamos los errores previos de OpenAL
	if (alGetError() != AL_NO_ERROR) {
		printf("Error al crear los buffers");
		exit(1);
	}
	else
		printf("Se crearon los buffers");

	alGenBuffers(NUM_BUFFERS, buffers);
	buffers[0] = alutCreateBufferFromFile("n.wav");
	buffers[1] = alutCreateBufferFromFile("t.wav");

	int errorAlut = alutGetError();

	if (errorAlut != ALUT_ERROR_NO_ERROR) {
		printf("Error al crear los buffers %d", errorAlut);
		exit(2);
	}
	else
		printf("Se crearon los buffers");

	glGetError();
	alGenSources(NUM_SOURCES, sources);

	if (alutGetError() != AL_NO_ERROR) {
		printf("Error al crear las fuentes de sonidos");
		exit(2);
	}
	else
		printf("Se crearon las fuentes de sonido");


	alSourcef(sources[0], AL_PITCH, 1.0f);
	alSourcef(sources[0], AL_GAIN, 0.5f);
	alSourcefv(sources[0], AL_VELOCITY, source0Vel);
	alSourcefv(sources[0], AL_POSITION,source0Pos);
	alSourcei(sources[0], AL_BUFFER, buffers[0]);
	alSourcei(sources[0], AL_LOOPING, AL_TRUE);
	alSourcei(sources[0], AL_MAX_DISTANCE, 1000);

	alSourcef(sources[1], AL_PITCH, 1.0f);
	alSourcef(sources[1], AL_GAIN, 0.5f);
	alSourcefv(sources[1], AL_VELOCITY, source0Vel);
	alSourcefv(sources[1], AL_POSITION, source1Pos);
	alSourcei(sources[1], AL_BUFFER, buffers[1]);
	alSourcei(sources[1], AL_LOOPING, AL_TRUE);
	alSourcei(sources[1], AL_MAX_DISTANCE, 1000);


	//Mis funciones
	//Datos a utilizar
	LoadTextures();
	myData();
	glEnable(GL_DEPTH_TEST);
	
	//Shader modelShader("Shaders/modelLoading.vs", "Shaders/modelLoading.fs");
	Shader modelShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	//Shader modelShader("shaders/shader_Lights.vs", "shaders/shader_texture_light_dir.fs");
	//Shader modelShader("shaders/shader_Lights.vs", "shaders/shader_texture_light_pos.fs");
	//Shader modelShader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs"); //Spotlight
	Shader text("shaders/shader_texture_color.vs", "shaders/shader_texture_color.fs");
	// Load models
	Model mesaModel = ((char *)"Models/mesa/mesa.obj");
	Model pisoModel = ((char *)"Models/piso/piso.obj");
	Model pcModel = ((char *)"Models/PC1/pc1.obj");
	Model pc2Model = ((char *)"Models/PC2/pc2.obj");
	Model pciModel = ((char *)"Models/PC1/pci.obj");
	Model pc2iModel = ((char *)"Models/PC2/pc2i.obj");
	Model sillaModel = ((char *)"Models/silla/silla.obj");
	Model proyectorModel = ((char *)"Models/proyector/pfinal.obj");
	Model aguaModel = ((char *)"Models/agua/agua.obj");
	Model aireModel = ((char *)"Models/minisplit/minisplit.obj");
	Model botiquinModel = ((char *)"Models/botiquin/botiquin.obj");
	Model extintorModel = ((char *)"Models/ex/ex.obj");
	Model cieloModel = ((char *)"Models/cielo/cielo.obj");
	Model arbolModel = ((char *)"Models/arbol/arbol.obj");
	Model casaModel = ((char *)"Models/casa/casa1.obj");
	Model zombieModel = ((char *)"Models/cueerpo/zombie.obj");
	Model dulcesModel = ((char *)"Models/dulces/dulces.obj");
	Model ofrendaModel = ((char *)"Models/ofrenda/ofrenda.obj");
	Model sonidoModel = ((char *)"Models/sonido/sonido.obj");
	Model camaModel = ((char *)"Models/cama/cama.obj");
	Model sillonModel = ((char *)"Models/sillon/sillon.obj");
	Model avionModel = ((char *)"Models/avion/avion.obj");
	Model gargolaModel = ((char *)"Models/gargola/GargolaCuerpo.obj");
	Model alaDerModel = ((char *)"Models/gargola/AlaDer.obj");
	Model alaIzqModel = ((char *)"Models/gargola/AlaIzq.obj");

	//Inicialización de KeyFrames

	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].giro = 0;

		KeyFrame2[i].posX = 0;
		KeyFrame2[i].posY = 0;
		KeyFrame2[i].posZ = 0;
		KeyFrame2[i].giro = 0;
	}


	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	// render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        // input
        // -----
        my_input(window);
		animate();

        // render
        // Backgound color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//display(modelShader, ourModel, llantasModel);
		display(modelShader,text,mesaModel,pisoModel,pcModel,pc2Model,pciModel,pc2iModel,sillaModel,proyectorModel,
			aguaModel,aireModel,botiquinModel,extintorModel,cieloModel,arbolModel,casaModel,zombieModel,dulcesModel,ofrendaModel,sonidoModel,camaModel,
		sillonModel,avionModel,gargolaModel,alaDerModel,alaIzqModel);
		
		std::cout << "Frame:" << (1/deltaTime) << std::endl;

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		animacion = true;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
		animacion = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) 
		flag = true;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		candy = true;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		casa1 = false;
		casa2 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		casa1 = true;
		casa2 = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		if (rotP < 0.0f) {
			rotP += 1.0f;
		}
	////////////////////CAMARAS CASA 1/////////////////////
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		mul = 0.0f;
		rotP = 0.0f;
		animacion = true;
		casa1 = true;
		casa2 = false;
		ro = true;
		alSourcePlay(sources[0]);
		alSourceStop(sources[1]);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		camera.Cambio(glm::vec3(0.0f, 0.0f, 13.0f), -90);
		casa1 = true;
		casa2 = false;
		animacion = true;
		camera.ProcessMouseMovement(0.0f, 0.0f);
		alSourcePlay(sources[0]);
		alSourceStop(sources[1]);
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		camera.Cambio(glm::vec3(0.0f, 0.0f, -11.0f), 90);
		animacion = true;
		casa1 = true;
		casa2 = false;
		camera.ProcessMouseMovement(0.0f, 0.0f);
		alSourcePlay(sources[0]);
		alSourceStop(sources[1]);
	}
	///////////////////////////////////////////////////////
	////////////////////CAMARA PRINCIPAL//////////////////
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		casa1 = false;
		casa2 = false;
		rotP = 0.0f;
		camera.Cambio(glm::vec3(-21.0f, 3.0f, 20.0f),-90);
		camera.ProcessMouseMovement(0.0f, 0.0f);
		alSourceStop(sources[1]);
		alSourceStop(sources[0]);
		
	}
	/////////////////////////////////////////////////////
	//////////////////CAMARAS CASA 2/////////////////////
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		camera.Cambio(glm::vec3(-35.0f, 1.0f, -5.0f),180);
		camera.ProcessMouseMovement(0.0f, 0.0f);
		casa1 = false;
		casa2 = true;;
		alSourcePlay(sources[1]);
		alSourceStop(sources[0]);
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		camera.Cambio(glm::vec3(-47.0f, 3.0f, 10.0f),-90);
		camera.ProcessMouseMovement(0.0f, 0.0f);
		casa1 = false;
		casa2 = true;
		alSourcePlay(sources[1]);
		alSourceStop(sources[0]);
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
		casa1 = false;
		casa2 = true;
		ho = true;
		mul = 0.0f;
		alSourcePlay(sources[1]);
		alSourceStop(sources[0]);
	}
	//////////////////////////////////////////////////////
    //To play KeyFrame animation 
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES) {
			gargolaFrame();
			planeFrame();
		}
		if (play == false && (FrameIndex > 1))
		{
			resetElements();
			resetElements2();
			//First Interpolation				
			interpolation();
			interpolation2();
			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{


	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top


	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
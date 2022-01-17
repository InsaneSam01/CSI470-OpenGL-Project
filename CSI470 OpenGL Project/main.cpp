#include "Model.h"

//settings

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;



//function prototypes

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


int main() {

	// Initialize GLFW
	glfwInit();

	//Specify to GLFW what version of OpenGL in currently in use
	//and what profile is currently in use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	//Creating a GLFW window object with SCR_WIDTH and SCR_HEIGHT
	//as parameters, the string for a title and NULL to specify if the window
	//is fullscreen or not
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "THE COOL ZONE", NULL, NULL);

	//Error checking to see if a window is created successfully
	if (window == NULL) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	//tell GLFW to make window the current context
	glfwMakeContextCurrent(window);

	//dynamically change the size of the window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//open GLAD to configure OpenGL
	gladLoadGL();

	//set the viewport of OpenGL
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);


	//Generate a Shader Program by reading default.vert and default.frag files
	Shader shaderProgram("default.vert", "default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);




	//Enables the depth buffer
	glEnable(GL_DEPTH_TEST);

	//Creates camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f ,0.0f, 2.0f));

	Model model("models/retro_television/scene.gltf");

	//The Render Loop
	//Allows the GLFW window to stay open until specifically told to close
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		//set viewport to navy blue color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// clean the back buffer and depth buffer and assigns a new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// handles camera inputs
		camera.Inputs(window);
		//updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		
		model.Draw(shaderProgram, camera);

		//swap between buffers
		glfwSwapBuffers(window);
		
		//Take care of all GLFW events
		glfwPollEvents();
	}
	
	//deleting unused objects
	shaderProgram.Delete();
	
	//destroy current window
	glfwDestroyWindow(window);
	//stop functionality of GLFW
	glfwTerminate();

	return 0;
}

//processes the inputting of the escape key to close the window
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

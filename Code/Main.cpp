#include "stb_image.h"

#include "Camera.hpp"

#include "Engine/Window/WindowApi.hpp"
#include "Engine/Window/Window.hpp"

#include "Engine/Resources/Shaders/Shader.hpp"
#include "Engine/Resources/Shaders/Program.hpp"

#include "Engine/Renderer/RendererApi.hpp"
#include "Engine/Common/File.hpp"
#include "Engine/Common/Time.hpp"

#include "Editor/Importers/TextureImporter.hpp"

// settings
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(vec3(0.0f, 2.0f, 5.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

bool firstMouse = true;

// grid
vector<vec3> cubePositions;

void createRandomGrid()
{
    cubePositions.clear();

    const int maxRows = 100;
    const int maxColumns = 100;

    for (int r = 0; r < maxRows; r++)
    {
        for (int c = 0; c < maxColumns; c++)
        {
            int y = 1;

            if (c != 0 && r != 0 && c < maxColumns -1  && r < maxRows - 1)
            {
                y = linearRand(0, 1);
            }

            cubePositions.push_back(vec3(r, y, c));
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, cp::Time::delta_time());

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, cp::Time::delta_time());

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, cp::Time::delta_time());
        
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, cp::Time::delta_time());

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        createRandomGrid();
    }
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

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

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

int main()
{
    cout << "[GLM] api version: " << GLM_VERSION_MAJOR << "." 
                                  << GLM_VERSION_MINOR << "." 
                                  << GLM_VERSION_PATCH << endl;

    cout << "[FREE_IMAGE] api version: " << FREEIMAGE_MAJOR_VERSION << "."
                                         << FREEIMAGE_MINOR_VERSION << endl;

    if (!cp::WindowApi::init())
    {
        return -1;
    }

    cp::WindowApi::enable_core_profile();
    
    cp::Window window("Clever Spy Project", ivec2(800, 600));

    if (!window.create())
    {
        return -1;
    }

    cp::RendererApi::enable_experimental();

    if (!cp::RendererApi::init())
    {
        return -1;
    }

    glfwSetFramebufferSizeCallback(window.get_ptr(), framebuffer_size_callback);
    glfwSetCursorPosCallback(window.get_ptr(), mouse_callback);
    glfwSetScrollCallback(window.get_ptr(), scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window.get_ptr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // disable 60 fps limit
    glfwSwapInterval(0);

    glViewport(0, 0, 800, 600);

    /*float vertices[] = 
    {
        // positions         // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // top left 
    };*/

    float vertices[] = 
    {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = 
    { 
        // quad
        0, 1, 3,
        1, 2, 3
    };  

    shared_ptr<cp::Shader> vertex_shader = make_shared<cp::Shader>(1, make_shared<cp::File>(path("Assets/BasicShader.vs")), GL_VERTEX_SHADER);
    shared_ptr<cp::Shader> fragment_shader = make_shared<cp::Shader>(2, make_shared<cp::File>(path("Assets/BasicShader.fs")), GL_FRAGMENT_SHADER);

    shared_ptr<cp::Program> program = make_shared<cp::Program>(3);
    program->add_shaders({ vertex_shader, fragment_shader });
    program->load();

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);*/

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // textures
    cp::TextureImporter importer(cp::File(path("Assets/container.jpg")));

    importer.load();

    unsigned int texture1;
    glGenTextures(1, &texture1); 

    glBindTexture(GL_TEXTURE_2D, texture1); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load("Assets/container.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }

    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2); 

    glBindTexture(GL_TEXTURE_2D, texture2); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("Assets/awesomeface.png", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }

    stbi_image_free(data);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // seed the random
    srand(static_cast<int>(time(0)));

    program->add_uniform(cp::ShaderUniforms::VIEW_MATRIX, "view");
    program->add_uniform(cp::ShaderUniforms::MODEL_MATRIX, "model");
    program->add_uniform(cp::ShaderUniforms::PROJECTION_MATRIX, "projection");

    program->add_uniform(cp::ShaderUniforms::MATERIAL_DIFFUSE_TEXTURE_1, "texture1");
    program->add_uniform(cp::ShaderUniforms::MATERIAL_DIFFUSE_TEXTURE_2, "texture2");

    cp::Time::start();

    int fps;
    float t = 0;

    while (!window.is_closing())
    {
        cp::Time::update();

        t += cp::Time::delta_time();

        fps++;

        if (t >= 1.0f)
        {
            string info = "FPS: " + to_string(fps) + " delta " + to_string(cp::Time::delta_time());

            window.set_info(info);

            t = 0.0f;
            fps = 0;
        }

        processInput(window.get_ptr());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program->use();

        // transformation
        mat4 view(1.0f);
        mat4 projection(1.0f);

        view = camera.GetViewMatrix();
        projection = perspective(radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

        program->set_mat4(cp::ShaderUniforms::VIEW_MATRIX, view);
        program->set_mat4(cp::ShaderUniforms::PROJECTION_MATRIX, projection);    

        program->set_int(cp::ShaderUniforms::MATERIAL_DIFFUSE_TEXTURE_1, 0);
        program->set_int(cp::ShaderUniforms::MATERIAL_DIFFUSE_TEXTURE_2, 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);

        for (unsigned int i = 0; i < cubePositions.size(); i++)
        {
            mat4 model;
            model = translate(model, cubePositions[i]);
            
            program->set_mat4(cp::ShaderUniforms::MODEL_MATRIX, model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        window.update();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    window.release();

    cp::WindowApi::release();

    return 0;
}
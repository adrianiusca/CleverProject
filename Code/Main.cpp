#include "Camera.hpp"

#include "Engine/Window/WindowApi.hpp"
#include "Engine/Window/Window.hpp"

#include "Engine/Resources/Shaders/Shader.hpp"
#include "Engine/Resources/Shaders/Program.hpp"
#include "Engine/Resources/Textures/Texture.hpp"
#include "Engine/Resources/Meshes/Mesh.hpp"

#include "Engine/Renderer/RendererApi.hpp"

#include "Engine/Utils/FpsCounter.hpp"

#include "Engine/Common/Time.hpp"
#include "Engine/Common/Input.hpp"

#include "Engine/Common/Random/Random.inl"

#include "Editor/Importers/TextureImporter.hpp"
#include "Editor/Importers/SceneImporter.hpp"

// settings
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(vec3(5.0f, 3.0f, 5.0f));

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
                y = cp::Random::get_linear(0, 1);
            }

            cubePositions.push_back(vec3(r, y, c));
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void camera_direction()
{
    if (firstMouse)
    {
        lastX = cp::Input::get_mouse_position().x;
        lastY = cp::Input::get_mouse_position().y;
        firstMouse = false;
    }

    float xoffset = cp::Input::get_mouse_position().x - lastX;
    float yoffset = lastY - cp::Input::get_mouse_position().y;

    lastX = cp::Input::get_mouse_position().x;
    lastY = cp::Input::get_mouse_position().y;

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
    glfwSetScrollCallback(window.get_ptr(), scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window.get_ptr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // disable 60 fps limit
    glfwSwapInterval(0);

    glViewport(0, 0, 800, 600);

    auto vertex_shader   = make_shared<cp::Shader>(1, make_shared<cp::File>(path("Assets/BasicShader.vs")), GL_VERTEX_SHADER);
    auto fragment_shader = make_shared<cp::Shader>(2, make_shared<cp::File>(path("Assets/BasicShader.fs")), GL_FRAGMENT_SHADER);

    auto program = make_shared<cp::Program>(3);
    program->add_shaders({ vertex_shader, fragment_shader });
    program->load();

    cp::TextureImporter container_importer(cp::File(path("Assets/container.jpg")));
    cp::TextureImporter face_importer(cp::File(path("Assets/awesomeface.png")));

    container_importer.load();
    face_importer.load();

    auto container_texture = make_shared<cp::Texture>(4, make_shared<cp::File>(path("Assets/container.texture")));
    container_texture->use_mipmaps();
    container_texture->load();

    auto face_texture = make_shared<cp::Texture>(5, make_shared<cp::File>(path("Assets/awesomeface.texture")));
    face_texture->use_mipmaps();
    face_texture->load();

    cp::SceneImporter cube_importer(cp::File(path("Assets/container.dae")));
    cube_importer.load();

    auto cube_mesh = make_shared<cp::Mesh>(6, make_shared<cp::File>(path("Assets/Cube.mesh")));
    cube_mesh->load();

    //glPointSize(5.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //glCullFace(GL_BACK);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // seed the random
    cp::Random::seed();

    program->add_uniform(cp::ShaderUniforms::VIEW_MATRIX, "view");
    program->add_uniform(cp::ShaderUniforms::MODEL_MATRIX, "model");
    program->add_uniform(cp::ShaderUniforms::PROJECTION_MATRIX, "projection");

    program->add_uniform(cp::ShaderUniforms::MATERIAL_DIFFUSE_TEXTURE_1, "texture1");
    program->add_uniform(cp::ShaderUniforms::MATERIAL_DIFFUSE_TEXTURE_2, "texture2");

    cp::Time::start();

    while (!window.is_closing())
    {
        camera_direction();

        cp::Time::update();

        cp::FpsCounter::update();

        // input - begin
        if (cp::Input::is_key_down(GLFW_KEY_ESCAPE, true))
        {
            window.close();
        }

        if (cp::Input::is_key_down(GLFW_KEY_L, true))
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        if (cp::Input::is_key_down(GLFW_KEY_W))
        {
            camera.ProcessKeyboard(FORWARD, cp::Time::delta_time());
        }

        if (cp::Input::is_key_down(GLFW_KEY_S))
        {
            camera.ProcessKeyboard(BACKWARD, cp::Time::delta_time());
        }

        if (cp::Input::is_key_down(GLFW_KEY_A))
        {
            camera.ProcessKeyboard(LEFT, cp::Time::delta_time());
        }

        if (cp::Input::is_key_down(GLFW_KEY_D))
        {
            camera.ProcessKeyboard(RIGHT, cp::Time::delta_time());
        }
        
        if (cp::Input::is_key_down(GLFW_KEY_SPACE, true))
        {
            createRandomGrid();
        }
        // input - end

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program->use();

        mat4 view = camera.GetViewMatrix();
        mat4 projection = perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

        program->set_mat4(cp::ShaderUniforms::VIEW_MATRIX, view);
        program->set_mat4(cp::ShaderUniforms::PROJECTION_MATRIX, projection);

        program->set_int(cp::ShaderUniforms::MATERIAL_DIFFUSE_TEXTURE_1, 0);
        program->set_int(cp::ShaderUniforms::MATERIAL_DIFFUSE_TEXTURE_2, 1);

        cp::Texture::activate(0);
        container_texture->bind();

        cp::Texture::activate(1);
        face_texture->bind();

        cube_mesh->bind_vao();
    
        for (u32 i = 0; i < cubePositions.size(); i++)
        {
            mat4 model;
            model = translate(model, cubePositions[i]);
            model = scale(model, vec3(0.5f));
            
            program->set_mat4(cp::ShaderUniforms::MODEL_MATRIX, model);

            cube_mesh->draw();
        }

        window.update();
    }

    window.release();

    cp::WindowApi::release();

    return 0;
}
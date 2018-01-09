#include "Scene.hpp"

namespace cp
{
    Scene::Scene(std::shared_ptr<File> file)
        : m_root(std::make_shared<Node>(0))
		, m_file(file)
		, m_ambient_light(0.1f)
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::init()
    {
        cout << "init the scene" << endl;

        m_root->init();
    }

    void Scene::parse()
    {
        cout << "parse the scene" << endl;
    }

    void Scene::update()
    {
		m_root->update();
    }

    void Scene::release()
    {
        cout << "release the scene" << endl;

        m_root->release();
        m_nodes.clear();
    }

    void Scene::add_node(std::shared_ptr<Node> node)
    {
        assert(node);

        m_nodes.push_back(node);
    }

    void Scene::remove_node(std::shared_ptr<Node> node)
    {
    }

    void Scene::set_ambient_light(const glm::vec3& color)
    {
        m_ambient_light = color;
    }

    void Scene::set_file(std::shared_ptr<File> file)
    {
        m_file = file;
    }

    const std::vector<std::shared_ptr<Node>>& Scene::get_nodes() const
    {
        return m_nodes;
    }

    const glm::vec3& Scene::get_ambient_light() const
    {
        return m_ambient_light;
    }

    std::shared_ptr<Node> Scene::get_root() const
    {
        return m_root;
    }

    std::shared_ptr<File> Scene::get_file() const
    {
        return m_file;
    }
}
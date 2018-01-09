#pragma once

#include "Engine/Nodes/Node.hpp"
#include "Engine/Common/File/File.hpp"

namespace cp
{
    class Scene
    {
        explicit Scene(std::shared_ptr<File> file = nullptr);

        virtual ~Scene();

        virtual void init();
        virtual void parse();

        virtual void update();
        virtual void release();

        template <class T> std::shared_ptr<T> get_node_by_id(int id) const;

        template <class T> std::shared_ptr<T> get_node_by_type(NodeTypes type) const;
        template <class T> std::shared_ptr<T> get_node_by_tag(NodeTags tag) const;

        template <class T> std::shared_ptr<T> get_node_by_condition(std::function<bool(std::shared_ptr<T> node)> func) const;

        template <class T> std::vector<std::shared_ptr<T>> get_nodes_by_type(NodeTypes type) const;
        template <class T> std::vector<std::shared_ptr<T>> get_nodes_by_tag(NodeTags tag) const;

        template <class T> std::vector<std::shared_ptr<T>> get_nodes_by_condition(std::function<bool(std::shared_ptr<T> node)> func) const;

        void add_node(std::shared_ptr<Node> node);
        void remove_node(std::shared_ptr<Node> node);

        void set_ambient_light(const glm::vec3& color);
        void set_file(std::shared_ptr<File> file);

        const std::vector<std::shared_ptr<Node>>& get_nodes() const;
        const glm::vec3& get_ambient_light() const;

        std::shared_ptr<Node> get_root() const;
        std::shared_ptr<File> get_file() const;

    protected:
        std::vector<std::shared_ptr<Node>> m_nodes;

        std::shared_ptr<Node> m_root;
        std::shared_ptr<File> m_file;

        glm::vec3 m_ambient_light;
    };
}
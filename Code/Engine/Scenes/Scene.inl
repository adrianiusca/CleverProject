#pragma once

#include "Scene.hpp"

namespace cp
{
    template <class T> std::shared_ptr<T> Scene::get_node_by_id(int id) const
    {
        return get_node_by_condition<T>([id](std::shared_ptr<T> node) 
        { 
            return node->get_id() == id;
        });
    }

    template <class T> std::shared_ptr<T> Scene::get_node_by_type(NodeTypes type) const
    {
        return get_node_by_condition<T>([type](std::shared_ptr<T> node) 
        {
            return node->get_type() == type;
        });
    }

    template <class T> std::shared_ptr<T> Scene::get_node_by_tag(NodeTags tag) const
    {
        return get_node_by_condition<T>([tag] (std::shared_ptr<T> node)
        {
            return node->get_tag() == tag;
        });
    }

    template <class T> std::shared_ptr<T> Scene::get_node_by_condition(std::function<bool(std::shared_ptr<T> node)> func) const
    {
        auto it = std::find_if(m_nodes.begin(), m_nodes.end(), func);

        if (it != m_nodes.end())
        {
            return std::static_pointer_cast<T>(*it);
        }

        return nullptr;
    }

    template <class T> std::vector<std::shared_ptr<T>> Scene::get_nodes_by_type(std::function<bool(std::shared_ptr<T> node)> func) const
    {
        return get_nodes_by_condition<T>([type](std::shared_ptr<T> node) 
        {
            return node->get_type() == type;
        });
    }

    template <class T> std::vector<std::shared_ptr<T>> Scene::get_nodes_by_tag(NodeTags tag) const
    {
        return get_node_by_condition<T>([tag] (std::shared_ptr<T> node)
        {
            return node->get_tag() == tag;
        });
    }

    template <class T> std::vector<std::shared_ptr<T>> Scene::get_nodes_by_condition(std::function<bool(std::shared_ptr<T> node)> func) const
    {
        auto nodes;

        std::copy_if(nodes.begin(), nodes.end(), std::back_inserter(nodes), func);

        return nodes;
    }
}
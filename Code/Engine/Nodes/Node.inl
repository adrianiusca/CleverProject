#pragma once

#include "Node.hpp"

namespace cp
{
    template <class T> std::shared_ptr<T> Node::get_child_by_index(int index) const
    {
        return std::static_pointer_cast<T>(m_children.at(index));
    }

    template <class T> std::shared_ptr<T> Node::get_child_by_id(int id) const
    {
        return get_child_by_condition<T>([id](std::shared_ptr<T> node) 
        { 
            return node->get_id() == id;
        });
    }

    template <class T> std::shared_ptr<T> Node::get_child_by_type(NodeTypes type) const
    {
        return get_child_by_condition<T>([type](std::shared_ptr<T> node) 
        {
            return node->get_type() == type;
        });
    }

    template <class T> std::shared_ptr<T> Node::get_child_by_tag(NodeTags tag) const
    {
        return get_child_by_condition<T>([tag] (std::shared_ptr<T> node)
        {
            return node->get_tag() == tag;
        });
    }

    template <class T> std::shared_ptr<T> Node::get_child_by_condition(std::function<bool(std::shared_ptr<T> node)> func) const
    {
        auto it = std::find_if(m_children.begin(), m_children.end(), func);

        if (it != m_children.end())
        {
            return std::static_pointer_cast<T>(*it);
        }

        return nullptr;
    }

    template <class T> std::shared_ptr<T> Node::remove_child_by_index(int index)
    {
        auto node = get_child_by_index<T>(index);

        if (node)
        {
            node->setParent(nullptr);

            m_children.erase(m_children.begin() + index);
        }

        return node;
    }

    template <class T> std::shared_ptr<T> Node::remove_child_by_id(int id)
    {
        return remove_child_by_condition<T>([id](std::shared_ptr<T> node) 
        { 
            return node->get_id() == id;
        });
    }

    template <class T> std::shared_ptr<T> Node::remove_child_by_type(NodeTypes type) const
    {
        return remove_child_by_condition<T>([type](std::shared_ptr<T> node) 
        {
            return node->get_type() == type;
        });
    }

    template <class T> std::shared_ptr<T> Node::remove_child_by_tag(NodeTags tag) const
    {
        return remove_child_by_condition<T>([tag] (std::shared_ptr<T> node)
        {
            return node->get_tag() == tag;
        });
    }

    template <class T> std::shared_ptr<T> Node::remove_child_by_condition(std::function<bool(std::shared_ptr<T> node)> func) const
    {
        auto it = std::find_if(m_children.begin(), m_children.end(), func);

        if (it != m_children.end())
        {
            m_children.erase(it);

            (*it)->set_parent(nullptr);

            return std::static_pointer_cast<T>(*it);
        }

        return nullptr;
    }
}
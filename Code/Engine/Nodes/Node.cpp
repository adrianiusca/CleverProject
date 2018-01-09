#include "Node.hpp"

namespace cp
{
    Node::Node(i32 id)
        : Object(id)
        , m_transform(std::make_shared<Transform>())
        , m_is_mesh_node(false)
        , m_is_enabled(true)
        , m_type(NodeTypes::NODE)
        , m_tag(NodeTags::NONE)
    {
    }

    Node::Node(i32 id, NodeTypes type, bool is_mesh_node)
        : Object(id)
        , m_transform(std::make_shared<Transform>())
        , m_is_mesh_node(is_mesh_node)
        , m_is_enabled(true)
        , m_type(type)
        , m_tag(NodeTags::NONE)
    {
    }

    Node::~Node()
    {
    }

    void Node::init()
    {
        for (auto child : m_children)
        {
            child->init();
        }
    }

    void Node::update()
    {
        m_transform->update();

        for (auto child : m_children)
        {
            if (child->is_enabled())
            {
                child->update();
            }
        }
    }

    void Node::release()
    {
        for (auto child : m_children)
        {
            child->release();
        }
    }

    void Node::add_child(std::shared_ptr<Node> node)
    {
        assert(node);

        node->set_parent(shared_from_this());

        m_children.push_back(node);
    }

    void Node::add_child_at(std::shared_ptr<Node> node, int index)
    {
        assert(node);
        
        node->set_parent(shared_from_this());

        m_children.insert(m_children.begin() + index, node);
    }

    void Node::set_transform(const std::shared_ptr<Transform>& transform)
    {
        m_transform = transform;
    }

    void Node::set_parent(const std::shared_ptr<Node>& parent)
    {
        if (parent)
        {
            m_transform->set_parent(parent->transform());    
        }
        else
        {
            m_transform->set_parent(nullptr);
        }

        m_parent = parent;
    }

    void Node::set_enabled(bool value)
    {
        m_is_enabled = value;
    }

    void Node::set_node_tag(NodeTags tag)
    {
        m_tag = tag;
    }

    void Node::set_node_type(NodeTypes type)
    {
        m_type = type;
    }

    bool Node::is_mesh_node() const
    {
        return m_is_mesh_node;
    }

    bool Node::is_enabled() const
    {
        return m_is_enabled;
    }

    const std::vector<std::shared_ptr<Node>>& Node::get_children() const
    {
        return m_children;
    }

    std::shared_ptr<Transform> Node::transform() const
    {
        return m_transform;
    }

    std::shared_ptr<Node> Node::parent() const
    {
        return m_parent;
    }

    NodeTags Node::get_tag() const
    {
        return m_tag;
    }

    NodeTypes Node::get_type() const
    {
        return m_type;
    }
}
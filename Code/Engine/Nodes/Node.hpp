#pragma once

#include "NodeTags.hpp"
#include "NodeTypes.hpp"
#include "Transform/Transform.hpp"
#include "Engine/Common/Object.hpp"

namespace cp
{
    typedef std::vector<std::shared_ptr<Node>> Children;

    class Node : public std::enable_shared_from_this<Node>,
                 public Object
    {
    public:
        explicit Node(int id);
    
        virtual ~Node();

        virtual void init();
        virtual void update();
        virtual void release();

        template <class T> std::shared_ptr<T> get_child_by_id(int id) const;
        template <class T> std::shared_ptr<T> get_child_by_index(int index) const;

        template <class T> std::shared_ptr<T> get_child_by_type(NodeTypes type) const;
        template <class T> std::shared_ptr<T> get_child_by_tag(NodeTags tag) const;

        template <class T> std::shared_ptr<T> get_child_by_condition(std::function<bool(std::shared_ptr<T> node)> func) const;
        
        template <class T> std::shared_ptr<T> remove_child_by_index(int index);
        template <class T> std::shared_ptr<T> remove_child_by_id(int id);

        template <class T> std::shared_ptr<T> remove_child_by_type(NodeTypes type) const;
        template <class T> std::shared_ptr<T> remove_child_by_tag(NodeTags tag) const;

        template <class T> std::shared_ptr<T> remove_child_by_condition(std::function<bool(std::shared_ptr<T> node)> func) const;

        void add_child(std::shared_ptr<Node> node);
        void add_child_at(std::shared_ptr<Node> node, int index);

        void set_transform(const std::shared_ptr<Transform>& transform);
        void set_parent(const std::shared_ptr<Node>& parent);

        void set_enabled(bool value);
        
        void set_node_tag(NodeTags tag);
        void set_node_type(NodeTypes type);

        bool is_mesh_node() const;
        bool is_enabled() const;

        const Children& get_children() const;

        std::shared_ptr<Transform> transform() const;
        std::shared_ptr<Node> parent() const;
        
        NodeTags get_tag() const;
        NodeTypes get_type() const;

    protected:
        Node(i32 id, NodeTypes type);

    protected:
        Children m_children;

        std::shared_ptr<Transform> m_transform;
        std::shared_ptr<Node> m_parent;

        bool m_is_mesh_node;
        bool m_is_enabled;

        NodeTypes m_type;
        NodeTags m_tag;
    };
}
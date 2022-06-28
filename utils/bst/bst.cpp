#include "./bst.hpp"

Node *Bst::init_node(std::string key = "", std::string value = "", Node *left = NULL, Node *right = NULL)
{
    Node *node = new Node();

    node->key = key;
    node->value = value;
    node->left = left;
    node->right = right;

    return node;
}

Bst::Bst()
{
    root = NULL;
}

Bst::~Bst()
{
    Node *node = root;

    std::vector<Node *> stack;

    if (root)
        stack.push_back(node);

    while (!stack.empty())
    {
        Node *node = stack.back();
        stack.pop_back();

        if (node->left)
            stack.push_back(node->left);
        if (node->right)
            stack.push_back(node->right);
        delete node;
    }
}

std::pair<bool, std::string> Bst::find_node(std::string key)
{
    Node *node = root;

    while (node)
    {
        if (node->key == key)
            return std::make_pair(true, node->value);
        else if (node->key.compare(key) < 0)
            node = node->left;
        else
            node = node->right;
    }

    return std::make_pair(false, "");
}

Node *Bst::upsert_node(std::string key, std::string value)
{
    Node *node = root;
    Node *prev = NULL;

    while (node)
    {
        prev = node;
        if (node->key.compare(key) < 0)
        {
            node = node->left;
        }
        else if (node->key == key)
        {
            // If the key already exists, we update the node
            node->value = value;
            return node;
        }
        else
        {
            node = node->right;
        }
    }

    Node *new_node = init_node(key, value);

    if (!prev)
    {
        root = new_node;
        return new_node;
    }

    if (prev->key.compare(key) <= 0)
        prev->left = new_node;
    else
        prev->right = new_node;

    return new_node;
}
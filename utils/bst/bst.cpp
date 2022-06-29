#include "./bst.hpp"

Node *Bst::init_node(std::string key = "", std::string value = "", Node *left = NULL, Node *right = NULL)
{
    Node *node = new Node();

    pthread_mutex_init(&node->lock, NULL);
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

        pthread_mutex_destroy(&node->lock);

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
        // Lock from here, multiple threads should not insert nodes at the same time,
        // Might lead to overriding paths
        pthread_mutex_lock(&node->lock);
        prev = node;
        if (node->key.compare(key) < 0)
        {
            node = node->left;
        }
        else if (node->key == key)
        {
            // If the key already exists, we update the node
            node->value = value;
            // Here we update and hence it can be unlocked, as we no longer have need for this
            pthread_mutex_unlock(&node->lock);
            return node;
        }
        else
        {
            node = node->right;
        }

        if (node)
            // After we moved `node` ptr, we can unlock nodes which we will not insert below
            pthread_mutex_unlock(&prev->lock);

        // If `node` is NULL that means we will be inserting below `prev` node,
        // and hence we will not be unlocking it here, and will unlock once after we insert new node
    }

    Node *new_node = init_node(key, value);

    if (!prev)
    {
        root = new_node;
        return new_node;
    }

    if (prev->key.compare(key) < 0)
        prev->left = new_node;
    else
        prev->right = new_node;

    // After inserting new node we unlock the prev node
    pthread_mutex_unlock(&prev->lock);
    return new_node;
}
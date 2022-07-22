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

Bst::Bst(bool lock)
{
    root = NULL;
    should_lock = lock;
    pthread_mutex_init(&bst_lock, NULL);
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
        LOCK(&node->lock);
        stack.pop_back();

        if (node->left)
            stack.push_back(node->left);
        if (node->right)
            stack.push_back(node->right);

        UNLOCK(&node->lock);
        pthread_mutex_destroy(&node->lock);

        delete node;
    }
}

void Bst::free_node(Node *node)
{
    pthread_mutex_unlock(&node->lock);
    pthread_mutex_destroy(&node->lock);
    delete node;
}

/**
 * @brief Given a node, it returns the subtree after deleting the node
 * and making a new subroot
 * Assumes that the given node is already locked
 * @param node The node to be deleted
 * @return Node* The new subroot
 */
Node *Bst::delete_node_given_node(Node *node)
{
    if (node->left == NULL and node->right == NULL)
    {
        free_node(node);
        return NULL;
    }
    else if (node->left == NULL)
    {
        LOCK(&node->right->lock);
        free_node(node);
        return node->right;
    }
    else if (node->right == NULL)
    {
        LOCK(&node->left->lock);
        free_node(node);
        return node->left;
    }
    else // Two children
    {

        LOCK(&node->right->lock);

        Node *successor = node->right;
        Node *successor_parent = node;

        while (successor->left != NULL)
        {
            // Unlock the successor parent from the previous iteration
            if (successor_parent != node)
            {
                UNLOCK(&successor_parent->lock);
            }

            successor_parent = successor;

            LOCK(&successor->left->lock);
            successor = successor->left;
        }

        // At this time node, successor, and successor's parent are locked
        // Copy the successor value as node value

        node->key = successor->key;
        node->value = successor->value;

        if (successor_parent == node)
        {
            // Meaning successor is node->right
            // Also means that successor has no left child
            successor_parent->right = successor->right;
        }
        else
        {
            successor_parent->left = successor->right;
        }

        // Now delete the successor
        free_node(successor);

        // If the successor parent is the node we should not unlock it here
        // It will be unlocked in the parent function, as was the case when it was locked
        if (successor_parent != node)
        {
            UNLOCK(&successor_parent->lock);
        }

        return node;
    }
}

bool Bst::delete_node(std::string key)
{
    LOCK(&bst_lock);

    if (root == NULL)
    {
        UNLOCK(&bst_lock);
        return false;
    }

    LOCK(&root->lock);

    // Node to be deleted is the root, do not unlock the bst will be unlocked after new root is assigned
    if (root->key != key)
    {
        UNLOCK(&bst_lock);
    }

    Node *node = root;
    Node *parent = NULL;

    while (node)
    {
        if (node->key == key)
            break;

        if (parent)
        {
            // Unlock the parent of the previous iteration
            UNLOCK(&parent->lock);
        }

        // Node would have been locked in previous iteration
        parent = node;

        if (node->key.compare(key) > 0)
        {
            if (node->left == NULL)
                break;

            LOCK(&node->left->lock);
            node = node->left;
        }
        else if (node->key.compare(key) < 0)
        {
            if (node->right == NULL)
                break;

            LOCK(&node->right->lock);
            node = node->right;
        }
    }

    // key not found
    if (!node)
    {
        UNLOCK(&parent->lock);
        return false;
    }

    // Now delete and free the node, and returns the same subtree,
    // where node was the sub-root, with the new sub-root
    Node *new_sub_root = delete_node_given_node(node);

    if (parent && parent->key.compare(key) > 0)
    {
        parent->left = new_sub_root;
    }
    else if (parent && parent->right)
    {
        parent->right = new_sub_root;
    }

    // The deleted node was the root, so assign a new root
    if (parent == NULL)
    {
        root = new_sub_root;
    }

    if (new_sub_root)
    {
        UNLOCK(&new_sub_root->lock);
    }

    if (parent)
    {
        UNLOCK(&parent->lock);
    }
    else
    {
        // If parent == NULL root was unlocked previously, now unlock bst
        UNLOCK(&bst_lock);
    }
    return true;
}

std::pair<bool, std::string> Bst::find_node(std::string key)
{
    LOCK(&bst_lock);

    if (root == NULL)
    {
        UNLOCK(&bst_lock);
        return std::make_pair(false, "");
    }

    LOCK(&root->lock);
    UNLOCK(&bst_lock);

    Node *node = root;
    Node *prev = NULL;

    while (node)
    {
        prev = node;

        if (node->key == key)
        {
            UNLOCK(&node->lock);
            return std::make_pair(true, node->value);
        }
        else if (node->key.compare(key) > 0)
        {
            if (node->left == NULL)
            {
                UNLOCK(&node->lock);
                break;
            }

            LOCK(&node->left->lock);
            node = node->left;
        }
        else
        {
            if (node->right == NULL)
            {
                UNLOCK(&node->lock);
                break;
            }

            LOCK(&node->right->lock);
            node = node->right;
        }

        UNLOCK(&prev->lock);
    }

    return std::make_pair(false, "");
}

bool Bst::upsert_node(std::string key, std::string value)
{

    LOCK(&bst_lock);

    if (root == NULL)
    {
        // Lock the BST whenever we might modify root
        root = init_node(key, value);
        UNLOCK(&bst_lock);
        return true;
    }

    // Lock the root
    LOCK(&root->lock);

    Node *node = root;
    Node *prev = NULL;

    UNLOCK(&bst_lock);

    while (node)
    {
        prev = node;

        if (node->key.compare(key) > 0)
        {
            if (node->left == NULL)
            {
                break;
            }

            // We are traversing left, locking left node
            LOCK(&node->left->lock);
            node = node->left;
        }
        else if (node->key == key)
        {
            // If the key already exists, we update the node
            node->value = value;
            UNLOCK(&prev->lock);
            return false;
        }
        else
        {
            if (node->right == NULL)
            {
                break;
            }

            // We are traversing right, locking right node
            LOCK(&node->right->lock);
            node = node->right;
        }

        UNLOCK(&prev->lock);
    }

    Node *new_node = init_node(key, value);

    if (node->key.compare(key) > 0)
        node->left = new_node;
    else
        node->right = new_node;

    UNLOCK(&node->lock);
    return true;
}

void Bst::print_inorder(Node *root)
{
    if (root == NULL)
        return;
    LOCK(&root->lock);
    print_inorder(root->left);
    print_inorder(root->right);
    if (root)
        UNLOCK(&root->lock);
}
#include <bits/stdc++.h>

#define LOCK(lock)                \
    if (should_lock)              \
    {                             \
        pthread_mutex_lock(lock); \
    }

#define UNLOCK(lock)                \
    if (should_lock)                \
    {                               \
        pthread_mutex_unlock(lock); \
    }

typedef struct Node
{
    std::string key;
    std::string value;
    Node *left;
    Node *right;

    pthread_mutex_t lock;
};

class Bst
{
private:
    Node *root;
    bool should_lock;
    pthread_mutex_t bst_lock;

    Node *init_node(std::string key, std::string value, Node *left, Node *right);
    void free_node(Node *node);
    Node *delete_node_given_node(Node *node);
    void print_inorder(Node *root);

public:
    int size;

    Bst(bool lock = true);
    ~Bst();
    std::pair<bool, std::string> find_node(std::string key);

    Node *upsert_node(std::string key, std::string value);

    bool delete_node(std::string key);
};
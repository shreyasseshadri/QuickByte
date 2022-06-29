#include <bits/stdc++.h>

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

    Node *init_node(std::string key, std::string value, Node *left, Node *right);

public:
    int size;

    Bst();
    ~Bst();
    std::pair<bool, std::string> find_node(std::string key);

    Node *upsert_node(std::string key, std::string value);

    bool delete_node(std::string key);
};
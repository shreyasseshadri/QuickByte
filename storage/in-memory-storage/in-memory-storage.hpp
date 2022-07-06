#include "../../utils/bst/bst.hpp"
#include "../../utils/error-handler/error-handler.hpp"
#include "../storage.hpp"

class InMemoryStorage : public Storage
{
private:
    Bst *bst;

public:
    InMemoryStorage();
    ~InMemoryStorage();
    void upsert(std::string key, std::string value);
    std::pair<bool, std::string> retrieve(std::string key);
    virtual bool delete_key(std::string key);
};
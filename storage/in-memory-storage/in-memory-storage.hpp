#include "../../utils/bst/bst.hpp"
#include "../../utils/error-handler/error-handler.hpp"
#include "../storage.hpp"

class InMemoryStorage : public Storage
{
private:
    Bst *bst;
    ~InMemoryStorage();

public:
    InMemoryStorage();
    void upsert(std::string key, std::string value);
    std::pair<bool, std::string> retrieve(std::string key);
};
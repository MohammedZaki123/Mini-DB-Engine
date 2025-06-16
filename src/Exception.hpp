#include <stdexcept>

class DBAppException : public std::runtime_error {
public:
    explicit DBAppException(const std::string& msg);
};
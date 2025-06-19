#include <stdexcept>

class DBAppException : public std::runtime_error {
public:
    DBAppException(const std::string& msg);
};
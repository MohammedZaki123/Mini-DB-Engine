#include "Exception.hpp"

DBAppException::DBAppException(const std::string &msg) 
 : std::runtime_error(msg) {}
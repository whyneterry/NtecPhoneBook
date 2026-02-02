#include "djb2.hpp"

// djb2 hash algorithm
unsigned djb2hash(const std::string& personName)
{
    unsigned id{ 5381 };
    for (char c : personName)
    {
        id = id * 33 + static_cast<unsigned>(c);
    }
    return id;
}
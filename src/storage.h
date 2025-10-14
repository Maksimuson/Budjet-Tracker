#pragma once


#include "model.h"
#include <string>

class Storage {
public:
    static void save(const std::string& filename, const Model& model);
    static void load(const std::string& filename, Model& model);
};

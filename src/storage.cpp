#include "storage.h"
#include <fstream>
#include <sstream>
#include "model.h"

void Storage::save(const std::string& filename, const Model& model) {
    std::ofstream file(filename);
    for (auto& op : model.operations) {
        file << op.date << "," << op.amount << ","
            << op.category << "," << op.type << "," << op.comment << "\n";
    }
}

void Storage::load(const std::string& filename, Model& model) {
    model.operations.clear();
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Operation op;
        std::getline(ss, op.date, ',');
        ss >> op.amount; ss.ignore(1);
        std::getline(ss, op.category, ',');
        std::getline(ss, op.type, ',');
        std::getline(ss, op.comment);
        model.operations.push_back(op);
    }
}

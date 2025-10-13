#pragma once
#define MODEL_H
#include <string>
#include <vector>
#include <iostream>

struct Operation {
    std::string date;
    double amount;
    std::string category;
    std::string type;
    std::string comment;
};

class Model {
public:
    std::vector<Operation> operations;

    void addOperation(const Operation& op);
    double totalIncome() const;
    double totalExpense() const;
    double balance() const;
};
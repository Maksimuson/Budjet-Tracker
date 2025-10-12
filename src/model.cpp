#include "model.h"
#include <iostream>
#include <vector>

void Model::addOperation(const Operation& op) {
    operations.push_back(op);
}

double Model::totalIncome() const {
    double sum = 0;
    for (auto& op : operations)
        if (op.type == "income") sum += op.amount;
    return sum;
}

double Model::totalExpense() const {
    double sum = 0;
    for (auto& op : operations)
        if (op.type == "expense") sum += op.amount;
    return sum;
}

double Model::balance() const {
    return totalIncome() - totalExpense();
}

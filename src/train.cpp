#include "train.h"
#include <cstdlib>

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car* current = first->next;
    while (current != first) {
        Car* next = current->next;
        delete current;
        current = next;
    }
    delete first;
}

void Train::addCar(bool light) {
    Car* newCar = new Car{ light, nullptr, nullptr };
    if (!first) {
        first = newCar;
        newCar->next = newCar->prev = newCar;
    }
    else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    Car* current = first;
    countOp = 0;
    while (!current->light) {
        current->light = true;
        countOp++;
        current = current->next;
    }
    int length = 1;
    Car* temp = current->next;
    countOp++;
    while (temp != current) {
        length++;
        temp = temp->next;
        countOp++;
    }
    return length;
}

int Train::getOpCount() {
    return countOp;
}

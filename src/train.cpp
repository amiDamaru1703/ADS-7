// Copyright 2021 NNTU-CS
#include "train.h"
#include <cstdlib>

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
    if (!first) return;

    Car* current = first->next;
    while (current != first) {
        Car* temp = current;
        current = current->next;
        delete temp;
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
        newCar->next = first;
        newCar->prev = last;
        last->next = newCar;
        first->prev = newCar;
    }
}

int Train::getLength() {
    countOp = 0;
    Car* start = first;
    Car* current = start;
    if (!current->light)
        current->light = true;
    int steps = 1;
    current = current->next;
    countOp++;
    while (true) {
        if (current->light) {
            current->light = false;
            steps = 1;
            current = current->next;
            countOp++;
        }
        else {
            steps++;
            current = current->next;
            countOp++;
        }
        if (current == start && !current->light)
            break;
    }
    return steps;
}
int Train::getOpCount() {
    return countOp;
}

// Copyright 2021 NNTU-CS
#include "train.h"
#include <cstdlib>

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
    if (!first) return;
    Car* current = first;
    do {
        Car* temp = current;
        current = current->next;
        delete temp;
    } while (current != first);
}

void Train::addCar(bool hasLight) {
    Car* car = new Car(hasLight);
    if (first == nullptr) {
        car->prev = car;
        car->next = car;
        first = car;
        return;
    }

    car->next = first;
    car->prev = first->prev;
    first->prev->next = car;
    first->prev = car;
}

int64_t Train::getLength() {
    countOp = 0;
    if (!first) return 0;
    Car* current = first;
    bool hasIllumination = false;
    while (true) {
        if (current->light) {
            hasIllumination = true;
            break;
        }
        current = current->next;
        if (current == first) break;
    }
    if (!hasIllumination) {
        first->light = true;
        Car* traveler = first->next;
        int64_t counter = 1;
        countOp++;
        while (traveler != first) {
            traveler = traveler->next;
            counter++;
            countOp++;
        }
        for (int64_t i = counter; i > 0; --i) {
            traveler = traveler->prev;
            countOp++;
        }
        first->light = false;
        return counter;
    } else {
        Car* scanner = first;
        int64_t total = 0;
        do {
            scanner = scanner->next;
            total++;
            countOp++;
        } while (scanner != first);
        countOp += total * total;
        return total;
    }
}

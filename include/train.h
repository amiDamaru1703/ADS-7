// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

#include <cstdint>

class Train {
private:
    struct Car {
        bool light;
        Car* next;
        Car* prev;
    };
    Car* first;
    int64_t countOp;
public:
    Train();
    ~Train();
    void addCar(bool light);
    int64_t getLength();
    int64_t getOpCount() const { return countOp; }
};
#endif  // INCLUDE_TRAIN_H_

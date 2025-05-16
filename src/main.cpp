// Copyright 2022 NNTU-CS
#include "train.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

void runTest(const string& label, bool useRandom, bool lightState,
    ofstream& timeOut, ofstream& opOut) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    for (int n = 2; n <= 100; n += 2) {
        Train train;
        for (int i = 0; i < n; ++i) {
            bool light = useRandom ? dis(gen) : lightState;
            train.addCar(light);
        }
        auto start = high_resolution_clock::now();
        int len = train.getLength();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();
        int ops = train.getOpCount();
        timeOut << label << "," << n << "," << duration << endl;
        opOut << label << "," << n << "," << ops << endl;

        cout << "[" << label << "] N=" << n << ", Len=" << len
            << ", Ops=" << ops << ", Time=" << duration << "us" << endl;
    }
}

int main() {
    ofstream timeOut("result/times.csv");
    ofstream opOut("result/ops.csv");
    runTest("off", false, false, timeOut, opOut);     // все лампочки выключены
    runTest("on", false, true, timeOut, opOut);       // все включены
    runTest("random", true, false, timeOut, opOut);   // случайные
    timeOut.close();
    opOut.close();
    return 0;
}

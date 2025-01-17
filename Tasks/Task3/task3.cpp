#include <iostream>
#include <fstream>
#include "queue.h"

void writeAnswer(bool found, int answer) {
    std::ofstream os("../../../Tasks/Task3/output.txt");
    if (!os.is_open()) {
        std::cout << "ERROR: Output file don`t open!\n";
        return;
    }
    if (found) {
        os << std::to_string(answer);
    } else {
        os << "IMPOSSIBLE";
    }
    os.close();
}

int main() {
    std::ifstream is("../../../Tasks/Task3/input.txt");
    if (!is.is_open()) {
        std::cout << "ERROR: Input file don`t open!\n";
        return 1;
    }
    int count, startId, finishId;
    is >> count >> startId >> finishId;
    startId--;
    finishId--;

    int matrix[count][count];
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < count; ++j) {
            is >> matrix[i][j];
        }
    }
    Queue<int> queue;
    queue.insert(startId);

    bool was[count];
    for (int i = 0; i < count; ++i) {
        was[i] = false;
    }
    was[startId] = true;
    int lengths[count];
    for (int i = 0; i < count; ++i) {
        lengths[i] = 0;
    }
    while (!queue.empty()) {
        int id = queue.get();
        int length = lengths[id] + 1;
        queue.remove();
        for (int j = 0; j < count; ++j) {
            if (matrix[id][j] && !was[j]) {
                if (j == finishId) {
                    writeAnswer(true, length);
                    return 0;
                } else {
                    was[j] = true;
                    queue.insert(j);
                    lengths[j] = length;
                }
            }
        }
    }
    writeAnswer(false, 0);
    return 0;
}
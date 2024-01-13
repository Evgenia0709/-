//Задание 12. Считыватель целых чисел ++

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <functional>

class FileReader {
private:
    std::string filename;
    std::ifstream fileStream;

    std::vector<std::function<bool(const int&)>> predicates;
    std::vector<std::function<void(int)>> containers;

public:
    FileReader(std::string filename) : filename(filename) {
        fileStream.open(filename);
    }

    ~FileReader() {
        fileStream.close();
    }

    template <typename T, typename P>
    void set(T& container, P predicate) {
        containers.push_back([&container](int value) { container.push_back(value); });
        predicates.push_back(predicate);
    }

    void read() {
        int value;
        while (fileStream >> value) {
            for (int i = 0; i < containers.size(); i++) {
                if (predicates[i](value)) {
                    containers[i](value);
                }
            }
        }
    }
};


//Задание 17. Операции с индексной маской

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string>

template <size_t N>
class Mask {
private:
    std::vector<int> mask_;

public:
    Mask(std::initializer_list<int> initList) : mask_(initList) {
        if (mask_.size() != N) {
            throw std::invalid_argument("Invalid mask size");
        }
    }

    size_t size() {
        return N;
    }

    int at(int index) {

        if (index >= N || index < 0) {
            throw std::out_of_range("Index out of range in method at : " + std::to_string(index));
        }

        return mask_[index];
    }

    template <typename T>
    void slice(T& container) {
        for (int i = 0, j=0; i < container.size(); ++i, ++j) {
            if (at(j%N) == 0) {
                container.erase(container.begin() + i);
                --i;
            }
        }
    }

    template <typename T, typename F>
    T transform(T& container, F&& transformFunc) {
        T result;

        for (int i = 0; i < container.size(); ++i) {
            if (at(i % N) == 1)
                result.push_back(transformFunc(container[i]));
            else
                result.push_back(container[i]);
        }

        return result;
    }

    template <typename T, typename F>
    T slice_and_transform(T& container, F&& transformFunc) {
        T result;

        for (int i = 0; i < container.size(); ++i) {
            if (at(i%N) == 1) {
                result.push_back(transformFunc(container[i]));
            }
        }
        return result;
    }
};



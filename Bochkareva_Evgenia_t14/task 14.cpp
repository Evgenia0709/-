//Задание 14 сортирующий контейнер

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template<typename T>
class ToSortContainer {
private:
    std::vector<T> values;

public:
    ToSortContainer(std::initializer_list<T> values) : values(values) {
    }

    std::vector<T> getSortedBy(std::function<bool(T, T)> comparator) {
        std::vector<T> sortedValues = values;
        std::sort(sortedValues.begin(), sortedValues.end(), comparator);
        return sortedValues;
    }
};



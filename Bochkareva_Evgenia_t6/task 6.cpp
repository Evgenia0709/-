//6. Выделятор памяти

#include <iostream>
#include <stdexcept>
#include <string>

template <typename T, std::size_t N>
class MemReserver {
private:
    T* storage[N];
    bool used[N];

public:
    MemReserver() {
        for (std::size_t i = 0; i < N; ++i) {
            used[i] = false;
        }
    }

    template <typename... Args>
    T* create(Args&&... args) {
        std::size_t index = 0;
        while (index < N && used[index]) {
            ++index;
        }

        if (index >= N) {
            throw std::out_of_range("Not enough slots. Already created " + std::to_string(N) + " objects.");
        }

        T* newObject = new T(std::forward<Args>(args)...);
        storage[index] = newObject;
        used[index] = true;
        return newObject;
    }

    void remove(std::size_t index) {
        
        if (index >= N) {
            throw std::out_of_range("Object with index " + std::to_string(index) + " not found.");
        }

        if (used[index]) {
            
            T* objectToRemove = storage[index];
            delete  objectToRemove;
            used[index] = false;
        }
        else {
            throw std::out_of_range("Object with index " + std::to_string(index) + " not found.");
        }
    }

    std::size_t getCount() const {
        std::size_t count = 0;
        for (std::size_t i = 0; i < N; ++i) {
            if (used[i]) {
                ++count;
            }
        }
        return count;
    }

    T* get(std::size_t index) {
        if (index >= N || !used[index]) {
            throw std::out_of_range("Object with index " + std::to_string(index) + " not found.");
        }

        return storage[index];
    }

    std::size_t position(T* obj) {
        
        for (std::size_t i = 0; i < N; ++i) {
            
            if (used[i] && get(i) == obj) {
                return i;
            }
        }

        throw std::out_of_range("Object not found");
    }

    ~MemReserver() {
        for (std::size_t i = 0; i < N; ++i) {
            if (used[i]) {
                delete get(i); 
            }
        }
    }
};



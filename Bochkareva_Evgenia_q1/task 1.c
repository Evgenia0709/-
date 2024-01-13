//Номер 1 Ограниченная очередь

#include <iostream>
#include <utility>
#include <exception>

template<typename T>
struct QueueEx : std::exception {

public:
    QueueEx(int size, T element, std::string str = "Error") : s(str), queueSize(size), element(element) {}

    ~QueueEx() {}

    const char* what() const noexcept{
        return s.c_str();
    }

    int GetQueueSize(){
        return queueSize;
    }

    T GetElement(){
        return element;
    }

private:
    std::string s;
    int queueSize;
    T element;
};

template <int Size, typename T, bool ForceMode = true>
class LimitedQueue {
private:
    T queue[Size];
    int first;
    int rear;
    int count;

public:
    LimitedQueue() : first(0), rear(0), count(0) {}

    LimitedQueue(std::initializer_list<T> list) : first(0), rear(0), count(0) {
        for (auto x : list){
            if (count == Size)
                pop_front();

            queue[rear] = x;
            rear = (rear + 1) % Size;
            count++;
        }
    }

    LimitedQueue(const LimitedQueue& other) {
        first = other.first;
        rear = other.rear;
        count = other.count;

        for (int i = 0; i < Size; ++i) {
            queue[i] = other.queue[i];
        }
    }

    LimitedQueue(LimitedQueue&& other) noexcept {
        first = other.first;
        rear = other.rear;
        count = other.count;

        for (int i = 0; i < Size; ++i) {
            queue[i] = std::move(other.queue[i]);
        }
    }
    
    void push_back(const T& item) {
        if (count == Size) {
            if (ForceMode) {
                pop_front();
            }
            else {
                throw QueueEx<T>(count, item, "Queue is full");
            }
        }

        queue[rear] = item;
        rear = (rear + 1) % Size;
        count++;
    }

    T pop_front() {
        if (count == 0) {
            throw std::underflow_error("Queue is empty");
        }

        T item = queue[first];
        first = (first + 1) % Size;
        count--;

        return item;
    }

    bool empty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    T front()
    {
        T item = queue[first];
        return item;
    }

    bool full()
    {
        return count == Size;
    }

    void clear()
    {
        first = 0;
        rear = 0;
        count = 0;
    }
};



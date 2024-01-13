//Номер 8. Генератор псевдослучайных чисел

#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>

class SimpleRNG {
public:
    SimpleRNG(int m, double a, double c, double x = 0 ) : a(a), c(c), m(m), x(x), defaultX(x) {}

    class iterator : public std::iterator<std::input_iterator_tag, double> {
    public:
        iterator(int m, double a, double c, double x) : a(a), c(c), m(m), x(x) {}

        double operator*() const { return x; }

        iterator& operator++() {
            x = std::fmod(a * x + c, m);
            return *this;
        }

        bool operator==(const iterator& rhs) const {
            return x == *rhs;
        }

        bool operator!=(const iterator& rhs) const {
            return !(*this == rhs);
        }

    private:
        double a, c, x;
        int m;
    };

    iterator begin() const {
        return iterator(m,a,c,x);
    }

    iterator end(double eps = 0.05) const {
        iterator it (m, a, c, x);
        iterator prevIt (m, a, c, x);
        ++it;

        while (std::abs(*it - *prevIt) > eps)
        {
            ++it;
            ++prevIt;
        }

        return it;
    }

    void reset(double newX ) {
        x = newX;
        defaultX = newX;
    }

    void reset() {
        x = defaultX;
    }

private:
    double a, c, x, defaultX;
    int m;
};
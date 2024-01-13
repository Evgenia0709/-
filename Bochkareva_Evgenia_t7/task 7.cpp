//Задание 7. Расчет значений функции

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>

class Function {
public:
    virtual double calculate(double x) const = 0;
    virtual ~Function() = default;
};

class QuadraticFunction : public Function {
private:
    double a, b, c;

public:
    QuadraticFunction(double a, double b, double c) : a(a), b(b), c(c) {}

    double calculate(double x) const override {
        return (a * x * x) + (b * x) + c;
    }
};

class AbsFunction : public Function {
private:
    double a, b;

public:
    AbsFunction(double a, double b) : a(a), b(b) {}

    double calculate(double x) const override {
        return a * std::abs(x+b);
    }
};

class CosineFunction : public Function {
private:
    double a, b, c, d;

public:
    CosineFunction(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}

    double calculate(double x) const override {
        return a * std::cos(b * x + c) + d;
    }
};

class FunctionCalculation {
private:
    const Function& func;
    double start;
    double end;
    double step;

public:
    FunctionCalculation(const Function& func, double start, double end, double step)
        : func(func), start(start), end(end), step(step) {}

    std::vector<double> yValues() const {
        std::vector<double> values;
        for (double x = start; x <= end; x += step) {
            values.push_back(func.calculate(x));
        }
        return values;
    }

    std::vector<double> xValues() const {
        std::vector<double> values;
        for (double x = start; x <= end; x += step) {
            values.push_back(x);
        }
        return values;
    }

    std::vector<std::pair<double, double>> Values() const {
        std::vector<std::pair<double, double>> pairs;
        for (double x = start; x <= end; x += step) {
            pairs.push_back({ x, func.calculate(x) });
        }
        return pairs;
    }

    std::vector<std::pair<double, double>> ValuesAt(double x1, double x2) const {
        if (x2 > end || x1 < start) {
            std::string valuesStr = "";

            if (x2 > end)
                for (int i = end+step; i <= x2; i += step){
                    valuesStr += std::to_string(i);
                    valuesStr += " ";
                }

            if (x1 < start)
                for (int i = x1; i < start; i += step){
                    valuesStr += std::to_string(i);
                    valuesStr += " ";
                }

            throw std::out_of_range("Values out of range: " + valuesStr);
        }

        std::vector<std::pair<double, double>> pairs;
        for (double x = x1; x <= x2; x += step) {
            if (x >= start && x <= end) {
                pairs.push_back({ x, func.calculate(x) });
            }
        }
        return pairs;
    }

    void saveCsv(const std::string& filename, bool addHeaders) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file");
        }

        if (addHeaders) {
            file << "x,y\n";
        }

        for (double x = start; x <= end; x += step) {
            file << x << ',' << func.calculate(x) << '\n';
        }

        file.close();
    }

    friend std::ostream& operator<<(std::ostream& os, const FunctionCalculation& calc) {
        for (const auto& pair : calc.Values()) {
            os << "{" << pair.first << "," << pair.second << "} ";
        }
        return os;
    }
};


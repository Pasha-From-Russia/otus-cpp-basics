#pragma once

#include <cmath>
#include <numeric>

class IStatistics {
public:
    virtual ~IStatistics() {}

    virtual void update(double next) = 0;
    virtual double eval() const = 0;
    virtual const char *name() const = 0;
};

// минимальное значение из последовательности
class Min : public IStatistics {
public:
    Min() : min_{std::numeric_limits<double>::max()} {
    }

    void update(double next) override {
        if (next < min_) {
            min_ = next;
        }
    }

    double eval() const override {
        return min_;
    }

    const char* name() const override {
        return "min";
    }

private:
    double min_;
};

// максимальное значение
class Max : public IStatistics {
public:
    Max() : max_{std::numeric_limits<double>::lowest()} {}

    void update(double next) override {
        if (next > max_) {
            max_ = next;
        }
    }

    double eval() const override {
        return max_;
    }
    const char* name() const override {
        return "max";
    }

private:
    double max_;
};

//арифметическое среднее
class Avg : public IStatistics {
public:
    Avg() : count_(0), sum_(0.) {

    };

    void update(double next) override {
        sum_ += next;
        ++count_;
    }

    double eval() const override {
        if (count_ == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return sum_ / count_;
    }
    const char* name() const override {
        return "avg";
    }

private:
    double sum_;
    int count_;
};

// среднеквадратическое отклонение
// https://allcalc.ru/node/1011
class StDev : public IStatistics {
public:
    StDev() : sum_(0.) { }

    void update(double next) override {
        items_.push_back(next);
        sum_ += next;
    }

    double eval() const override {
        std::size_t num = items_.size();
        if (num <= 1) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double avg = sum_ / num;
        double variance = 0.;
        for (const auto & item : items_) {
            variance += (item - avg) * (item - avg);
        }
        return sqrtl(variance / (double)(num));
    }

    const char* name() const override {
        return "std";
    }

private:
    std::vector<double> items_;
    double sum_;
};

#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;// 存储容量

public:
    DynFibonacci(int capacity)
        : cache(new size_t[std::max(capacity, 2)]{0, 1}), cached(2), capacity(std::max(capacity, 2)) {}

    DynFibonacci(DynFibonacci const &other)
        : cache(new size_t[other.capacity]), cached(other.cached), capacity(other.capacity) {
        for (int i = 0; i < cached; i++) {
            cache[i] = other.cache[i];
        }
    }

    DynFibonacci &operator=(DynFibonacci const &other) {
        if (this != &other) {
            delete[] cache;
            capacity = other.capacity;
            cache = new size_t[capacity];
            cached = other.cached;
            for (int i = 0; i < cached; i++) {
                cache[i] = other.cache[i];
            }
        }
        return *this;
    }

    ~DynFibonacci() {
        delete[] cache;
    }

    size_t get(int i) {
        if (i >= capacity) {// 动态扩展缓存
            int new_capacity = std::max(i + 1, capacity * 2);
            size_t *new_cache = new size_t[new_capacity];
            std::copy(cache, cache + cached, new_cache);
            delete[] cache;
            cache = new_cache;
            capacity = new_capacity;
        }
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    size_t get(int i) const {
        if (i < cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}

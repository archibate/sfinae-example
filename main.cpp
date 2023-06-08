#include <cstdio>
#include <vector>
#include <type_traits>
#include <string>
#include "print.h"

#define REQUIRES(x) std::enable_if_t<(x), int> = 0

struct mystudent {
    void dismantle() {
        printf("rm -rf stu.db\n");
    }

    void rebel(int i) {
        printf("rm -rf gench-%d\n", i);
    }
};

struct myclass {
    void dismantle() {
        printf("rm -rf course\n");
    }
};

struct myteacher {
    void rebel(int i) {
        printf("rm -rf gench-%d\n", i);
    }
};

struct myvoid {
};

template <class T, class = void>
struct has_dismantle {
    static constexpr bool value = false;
};

template <class T>
struct has_dismantle<T, std::void_t<decltype(std::declval<T>().dismantle())>> {
    static constexpr bool value = true;
};

template <class T, class = void>
struct has_rebel {
    static constexpr bool value = false;
};

template <class T>
struct has_rebel<T, std::void_t<decltype(std::declval<T>().rebel(std::declval<int>()))>> {
    static constexpr bool value = true;
};

template <class T, REQUIRES(has_dismantle<T>::value)>
void gench(T t) {
    t.dismantle();
}

template <class T, REQUIRES(!has_dismantle<T>::value && has_rebel<T>::value)>
void gench(T t) {
    for (int i = 1; i <= 4; i++) {
        t.rebel(i);
    }
}

template <class T, REQUIRES(!has_dismantle<T>::value && !has_rebel<T>::value)>
void gench(T t) {
    printf("no any method supported!\n");
}

int main() {
    myclass mc;
    mystudent ms;
    myteacher mt;
    myvoid mv;
    gench(mc);
    gench(ms);
    gench(mt);
    gench(mv);
    return 0;
}

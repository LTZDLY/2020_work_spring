//
// Created by Zhengyi on 2020/3/24.
// Using Google Naming Regulations
// Using C++11 standard, compiled with 0 warnings on
// Apple clang version 11.0.3 (clang-1103.0.32.29).
// Compiling configuration is [g++ -Wall -std=gnu++11 aw4p1.cpp]
//

#include <iostream>
#include <string>

typedef unsigned long UL;

class Circle {
public:
    // Constructor
    explicit Circle(UL M);

    std::ostream &show(std::ostream &os);
    void          findBadGuys(UL k);

private:
    UL          total_;
    UL          killed_;
    UL          now_index_;
    std::string arrangement_;

    char & FindNext();
    void   Kill();
};


// MAIN
int main() {
    UL M, K;             // Variable named K and M according to the request.
    std::cin >> M >> K;
    if (M == 0 || M >= 1000 || K <= 1 || K >= 1000) {
        std::cerr << "Error: Input out of border, "
                  << "0<M<1000, 1<K<1000" << std::endl;
        return 1;       // Indicating wrong exiting.
    }
    Circle circle(M);
    circle.findBadGuys(K);
    circle.show(std::cout) << std::endl;
    return 0;
}


Circle::Circle(UL M) : total_(2*M), killed_(0),
                       now_index_(0), arrangement_(2*M, '+') { }

std::ostream &Circle::show(std::ostream &os) {
    // Display the content of arrangement_.
    os << arrangement_;
    return os;
}

void Circle::findBadGuys(UL k) {
    // Look for all the bad gays and kill them.
    int count = 1;
    UL m = total_ / 2;
    UL k_eq  = k % (2 * m);
    while (killed_ < m) {
        if (count == k_eq) {
            count = 1;
            Kill();
            k_eq = k % (total_ - killed_); // adjust k to avoid repeated calculation.
            if (k_eq == 0) k_eq = total_ - killed_;
        } else {
            ++count;
        }
        FindNext();
    }
}

inline
char &Circle::FindNext() {
    // Go to next living person.
    do {
        if (++now_index_ == total_)
            now_index_ = 0;
    } while (arrangement_[now_index_] != '+');
    return arrangement_[now_index_];
}

inline
void Circle::Kill() {
    // Kill the current person (by setting to '@').
    arrangement_[now_index_] = '@';
    ++killed_;
}


/* References
 1. More about Google naming regulation, visit
 https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/
 */
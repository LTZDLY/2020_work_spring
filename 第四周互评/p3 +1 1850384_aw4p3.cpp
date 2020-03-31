//
// Created by Zhengyi on 2020/3/27.
// Using Google Naming Regulations
// Using C++11 standard, compiled with 0 warnings on
// Apple clang version 11.0.3 (clang-1103.0.32.29).
// Compiling configuration is [g++ -Wall -std=gnu++11 aw4p3.cpp]
//

#include <iostream>
#include <vector>
#include <deque>
#include <string>

/// Functions visible to users, should be put into headers if there are any.
// sortArray sorts built-in C style arrays.
template <typename ElemType>
void sortArray(ElemType *arr, unsigned length);

// sortContainer sorts STL containers with RandomAccessIterator.
template <class Container>
void sortContainer(Container &container);

// sortPart sorts part of a container enclosed by pointers or RandomAccessIterators.
template<typename IterType>
void sortPart(IterType beg, IterType end);

// functions that display multiple types of container.
template <typename ElemType>
std::ostream & display(std::ostream &os, ElemType *arr, unsigned length);

template <typename Container>
std::ostream & display(std::ostream &os, const Container &con);


/// main function is for testing, feel free to change it.
int main() {
    using namespace std;
    int i_test_array[10] = {30, 4, 1, 400, -9, 5, -23, 80, 999, 0};
    vector<string> s_test_vec({"Mike", "Alex", "Picasso", "Tom", "John"});
    deque<float>   f_test_deq({99.9, -12.25, 3., 0.001, 0., -300., 70.95});
    string s_test_arr[] = {
            {"one"}, {"two"}, {"three"}, {"four"},
            {"five"}, {"six"}, {"seven"}, {"eight"},
    };

    display(cout << "Before: ", i_test_array, 10) << endl;
    sortArray(i_test_array, 10);
    display(cout << "Sorted: ", i_test_array, 10) << endl;

    display(cout << "Before: ", s_test_vec) << endl;
    sortContainer(s_test_vec);
    display(cout << "Sorted: ", s_test_vec) << endl;

    display(cout << "Before: ", f_test_deq) << endl;
    sortContainer(f_test_deq);
    display(cout << "Sorted: ", f_test_deq) << endl;

    display(cout << "Before: ", s_test_arr, 8) << endl;
    sortPart(s_test_arr, s_test_arr+4);
    display(cout << "Sorted: ", s_test_arr, 8) << endl;

    return 0;
}


/// Declarations of functions that are not visible to users.
//  Should not be put into headers if there are any.

// Real functioning part of sorting functions.
template <typename IterType>
void quickSort(IterType first, IterType last);

// quickSort's assistant functions
template <typename IterType>
void insertionSort(IterType first, IterType last);
template <typename IterType, typename ElemType>
IterType myPartition(IterType first, IterType last, const ElemType &pivot);
template <typename ElemType>
inline const ElemType& myMedium(const ElemType& a,
                                const ElemType& b, const ElemType& c);
template <typename IterType>
void iterSwap(IterType a, IterType b);

// Real functioning part of display functions.
template<typename IterType>
std::ostream & iterDisplay(IterType first, IterType last, std::ostream &os);


/// Implementations

// Interface to built-in arrays, invoked by pointer to head and length.
template<typename ElemType>
inline void sortArray(ElemType *arr, unsigned length) {
    if (length > 0) {
        quickSort(arr, arr + length - 1);
    } else {
        std::cerr << "Can not sort empty array!" << std::endl;
    }
}

// Interface to STL containers, invoked by a container.
template<class Container>
inline void sortContainer(Container &container) {
    if (!container.empty()) {
        quickSort(container.begin(), container.end() - 1);
    } else {
        std::cerr << "Can not sort empty container!" << std::endl;
    }
}

// Interface to iterator enclosed segments of containers.
template<typename IterType>
void sortPart(IterType beg, IterType end) {
    if (beg < end - 1) {
        quickSort(beg, end - 1);
    } else {
        std::cerr << "Iterators do not enclose a valid container segment"
                  << std::endl;
    }
}

// My quickSort is actually a fusion of quick-sort and insertion-sort.
// View footnote 2.
template<typename IterType>
void quickSort(IterType first, IterType last) {
    constexpr static unsigned kCutoffEdge = 3u;       // The edge of starting
    if (first + kCutoffEdge < last) {                 // insertion-sort.
        auto mid = first + (last - first) / 2;
        auto &pivot = myMedium(*first, *mid, *last);  // Pick pivot from three.
        auto cut = myPartition(first, last, pivot);   // Split point
        quickSort(first, cut);
        quickSort(cut + 1, last);
    } else {
        insertionSort(first, last);                   // Apply insertion-sort
    }
}


/// Assistant Functions.
template<typename IterType>
inline void iterSwap(IterType a, IterType b) {
    // Swap by two iterators or pointers.
    auto temp = *a;
    *a = *b;
    *b = temp;
}

template<typename IterType>
void insertionSort(IterType first, IterType last) {
    // Normal insertion sort.
    auto outer = first + 1;
    for (; outer <= last; ++outer) {
        auto temp = *outer;
        auto inner = outer;
        for (; inner > first && *(inner-1) > temp; --inner) {
            iterSwap(inner - 1, inner);
        }
        *inner = temp;
    }
}

template<typename IterType, typename ElemType>
IterType myPartition(IterType first, IterType last, const ElemType &pivot) {
    // quickSort's partition function, splits the container into two parts.
    while (true) {
        while (*first < pivot) ++first;    // Move from left to find big elements
        while (pivot < *last)  --last;     // From right to find small elements
        if (!(first < last)) return last;  // If iterator overlaps, terminate.
        iterSwap(first, last);             // If not, swap two values.
        ++first; --last;                   // Adjust and continue.
    }
}

template<typename ElemType>
inline const ElemType &myMedium(const ElemType &a,
                                const ElemType &b, const ElemType &c) {
    // Find the medium number in three.
    if (a < b)
        if      (b < c) return b;
        else if (a < c) return c;
        else            return a;
    else if (a < c) return a;
    else if (b < c) return c;
    else            return b;
}



/// Display functions
template<typename ElemType>
inline std::ostream & display(std::ostream &os, ElemType *arr, unsigned length) {
    return iterDisplay(arr, arr + length - 1, os);
}

template<typename Container>
inline std::ostream & display(std::ostream &os, const Container &con) {
    return iterDisplay(con.begin(), con.end()-1, os);
}

// Functioning part.
template<typename IterType>
inline std::ostream & iterDisplay(IterType first, IterType last, std::ostream &os) {
    for (; first < last; ++first) {
        os << *first << ", ";
    }
    os << *first;
    return os;
}


/* References
 1. More about Google naming regulation, visit
 https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/

 2. About the optimization of quick-sort: medium-of-three and cutting of, see
    Data Structures and Algorithm Analysis in C by Mark A. Weiss.

 3. Some of the ideas of template programming are from The Annotated STL Source
    by Jie Hou(《STL 源码剖析》 侯捷 ).
 */
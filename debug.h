/*
 * Debug Helper for Competitive Programming
 *
 * USAGE:
 * Add this to your C++ file:
 *
 *   #ifdef local
 *   #include "debug.h"
 *   #else
 *   #define db(...)
 *   #endif
 *
 * COMPILE FLAGS:
 * - With debugging:  g++ -std=c++20 -O2 -Dlocal solution.cpp -o solution
 * - Without debug:   g++ -std=c++20 -O2 solution.cpp -o solution
 *
 * - Supports: vectors, maps, sets, pairs, tuples, queues, stacks, etc.
 */

#ifndef db_H
#define db_H

#include <bits/stdc++.h>
using namespace std;

// Line tracking
#define db_LINE "[" << __LINE__ << "] "

// ==================== Type Traits for Detection ====================
template <typename T, typename = void> struct is_container : false_type {};
template <typename T> struct is_container<T, void_t<decltype(declval<T>().begin()), decltype(declval<T>().end())>> : true_type {};

template <typename T> struct is_pair : false_type {};
template <typename T, typename U> struct is_pair<pair<T, U>> : true_type {};

template <typename T> struct is_tuple : false_type {};
template <typename... Ts> struct is_tuple<tuple<Ts...>> : true_type {};

// ==================== Forward Declarations ====================
template <typename T, typename U> ostream &operator<<(ostream &os, const pair<T, U> &p);
template <typename... Ts> ostream &operator<<(ostream &os, const tuple<Ts...> &t);

// ==================== Special Types ====================
// Overload for modint printing (Z type support)
template <int P> struct modint;
template <int P> ostream &operator<<(ostream &os, const modint<P> &m) { return os << m.v; }

// ==================== Pair Printing ====================
template <typename T, typename U> ostream &operator<<(ostream &os, const pair<T, U> &p) { return os << "(" << p.first << ", " << p.second << ")"; }

// ==================== Tuple Printing ====================
template <typename... Ts> ostream &operator<<(ostream &os, const tuple<Ts...> &t) {
    os << "(";
    string sep = "";
    apply([&](auto &&...args) { ((os << sep << args, sep = ", "), ...); }, t);
    return os << ")";
}

// ==================== Array Printing ====================
template <typename T, size_t N> ostream &operator<<(ostream &os, const array<T, N> &arr) {
    os << "[";
    for (size_t i = 0; i < N; ++i) os << (i ? ", " : "") << arr[i];
    return os << "]";
}

// ==================== Sequential Containers ====================
// Vector
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    if constexpr (is_container<T>::value || is_pair<T>::value) {
        // For nested containers or vectors of pairs, use newlines
        if (!v.empty()) {
            os << "\n";
            for (size_t i = 0; i < v.size(); ++i) {
                os << "  " << v[i];
                if (i != v.size() - 1) os << ",";
                os << "\n";
            }
        }
        os << "]";
    } else {
        // For simple types, keep on one line
        for (size_t i = 0; i < v.size(); ++i) os << (i ? ", " : "") << v[i];
        os << "]";
    }
    return os;
}

// Deque
template <typename T> ostream &operator<<(ostream &os, const deque<T> &d) {
    os << "[";
    for (size_t i = 0; i < d.size(); ++i) os << (i ? ", " : "") << d[i];
    return os << "]";
}

// List
template <typename T> ostream &operator<<(ostream &os, const list<T> &l) {
    os << "[";
    bool first = true;
    for (const auto &x : l) os << (first ? "" : ", ") << x, first = false;
    return os << "]";
}

// ==================== Associative Containers ====================
// Set
template <typename T> ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    if (s.size() > 10) {
        // For large sets, use newlines
        if (!s.empty()) {
            os << "\n";
            for (const auto &x : s) os << "  " << x << ",\n";
        }
        os << "}";
    } else {
        // For small sets, keep on one line
        bool first = true;
        for (const auto &x : s) os << (first ? "" : ", ") << x, first = false;
        os << "}";
    }
    return os;
}

// Multiset
template <typename T> ostream &operator<<(ostream &os, const multiset<T> &ms) {
    os << "{";
    bool first = true;
    for (const auto &x : ms) os << (first ? "" : ", ") << x, first = false;
    return os << "}";
}

// Unordered Set
template <typename T> ostream &operator<<(ostream &os, const unordered_set<T> &us) {
    os << "{";
    bool first = true;
    for (const auto &x : us) os << (first ? "" : ", ") << x, first = false;
    return os << "}";
}

// Unordered Multiset
template <typename T> ostream &operator<<(ostream &os, const unordered_multiset<T> &ums) {
    os << "{";
    bool first = true;
    for (const auto &x : ums) os << (first ? "" : ", ") << x, first = false;
    return os << "}";
}

// Map
template <typename K, typename V> ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    if (m.size() > 5 || is_container<V>::value) {
        // For large maps or maps with container values, use newlines
        if (!m.empty()) {
            os << "\n";
            size_t idx = 0;
            for (const auto &[k, v] : m) {
                os << "  " << k << ": " << v;
                if (idx != m.size() - 1) os << ",";
                os << "\n";
                idx++;
            }
        }
        os << "}";
    } else {
        // For small maps, keep on one line
        bool first = true;
        for (const auto &[k, v] : m) os << (first ? "" : ", ") << k << ": " << v, first = false;
        os << "}";
    }
    return os;
}

// Multimap
template <typename K, typename V> ostream &operator<<(ostream &os, const multimap<K, V> &mm) {
    os << "{";
    bool first = true;
    for (const auto &[k, v] : mm) os << (first ? "" : ", ") << k << ": " << v, first = false;
    return os << "}";
}

// Unordered Map
template <typename K, typename V> ostream &operator<<(ostream &os, const unordered_map<K, V> &um) {
    os << "{";
    if (um.size() > 5 || is_container<V>::value) {
        // For large maps or maps with container values, use newlines
        if (!um.empty()) {
            os << "\n";
            for (const auto &[k, v] : um) { os << "  " << k << ": " << v << ",\n"; }
        }
        os << "}";
    } else {
        // For small maps, keep on one line
        bool first = true;
        for (const auto &[k, v] : um) os << (first ? "" : ", ") << k << ": " << v, first = false;
        os << "}";
    }
    return os;
}

// Unordered Multimap
template <typename K, typename V> ostream &operator<<(ostream &os, const unordered_multimap<K, V> &umm) {
    os << "{";
    bool first = true;
    for (const auto &[k, v] : umm) os << (first ? "" : ", ") << k << ": " << v, first = false;
    return os << "}";
}

// ==================== Adapter Containers ====================
// Stack
template <typename T, typename Container = deque<T>> ostream &operator<<(ostream &os, stack<T, Container> st) {
    os << "[";
    bool first = true;
    while (!st.empty()) {
        os << (first ? "" : ", ") << st.top();
        st.pop();
        first = false;
    }
    return os << "]";
}

// Queue
template <typename T, typename Container = deque<T>> ostream &operator<<(ostream &os, queue<T, Container> q) {
    os << "[";
    bool first = true;
    while (!q.empty()) {
        os << (first ? "" : ", ") << q.front();
        q.pop();
        first = false;
    }
    return os << "]";
}

// Priority Queue
template <typename T, typename Container = vector<T>, typename Compare = less<typename Container::value_type>> ostream &operator<<(ostream &os, priority_queue<T, Container, Compare> pq) {
    os << "{";
    bool first = true;
    while (!pq.empty()) {
        os << (first ? "" : ", ") << pq.top();
        pq.pop();
        first = false;
    }
    return os << "}";
}

// ==================== Bitset Printing ====================
template <size_t N> ostream &operator<<(ostream &os, const bitset<N> &bs) { return os << bs.to_string(); }

// ==================== C-Style Array Printing ====================
// Disable for char arrays to avoid ambiguity with string literals
template <typename T, size_t N, typename std::enable_if<!std::is_same<T, char>::value, int>::type = 0> ostream &operator<<(ostream &os, const T (&arr)[N]) {
    os << "[";
    for (size_t i = 0; i < N; ++i) os << (i ? ", " : "") << arr[i];
    return os << "]";
}

// ==================== Debug Output Functions ====================
// Base case: Called when no more arguments remain
inline void db_out() { clog << endl; }

// Base case for single string (handles the recursive call's trailing name)
inline void db_out(const char * /*unused*/) { clog << endl; }

// Recursive function to print each variable's name and value
template <typename T, typename... Args> void db_out(const char *names, T &&x, Args &&...args) {
    const char *comma = strchr(names, ',');
    if (!comma) {
        // No comma means only one variable is left
        clog << names << " = " << x << endl;
        return;
    }
    // Print the current variable's name and value
    clog.write(names, comma - names) << " = ";

    // Check if this is a container that will print multiline
    if constexpr (is_container<remove_reference_t<T>>::value) {
        clog << x << "\n";
    } else {
        clog << x << " | ";
    }

    // Recursively print the remaining arguments
    db_out(comma + 1, forward<Args>(args)...);
}

// ==================== Main Debug Macro ====================
#ifdef LOCAL
#define db(...) clog << db_LINE, db_out(#__VA_ARGS__, __VA_ARGS__)
#define db_nl() clog << "\n"                     // Add explicit newline
#define db_sep() clog << string(50, '-') << "\n" // Add separator line
#else
#define db(...)
#define db_nl()
#define db_sep()
#endif

#endif // db_H

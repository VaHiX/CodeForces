// Problem: CF 1770 A - Koxia and Whiteboards
// https://codeforces.com/contest/1770/problem/A

/*
Problem: A. Koxia and Whiteboards
Purpose: Given n whiteboards with initial values and m operations to replace values on whiteboards,
         find the maximum possible sum after all operations.

Algorithm: 
- Use a multiset to efficiently access and update the smallest element.
- For each operation, replace the smallest current value with the new value.
- Track total sum and update it accordingly.

Time Complexity: O((n + m) * log n)
Space Complexity: O(n)

*/
#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::multiset<long> s; // multiset to maintain sorted order and allow efficient min access
    long long total(0); // running sum of all elements
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s.insert(x); // insert initial values into the multiset
      total += x; // accumulate total sum
    }
    while (m--) {
      long b;
      scanf("%ld", &b);
      std::multiset<long>::iterator it = s.begin(); // get iterator to smallest element
      total += (b - (*it)); // add difference between new and old value to total
      s.erase(it); // remove the smallest element
      s.insert(b); // insert the new value
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/
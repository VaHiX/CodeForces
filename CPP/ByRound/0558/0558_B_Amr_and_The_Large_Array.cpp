// Problem: CF 558 B - Amr and The Large Array
// https://codeforces.com/contest/558/problem/B

/*
Code Purpose:
This program finds the smallest subsegment of an array such that the maximum
frequency of any element in this subsegment equals the maximum frequency of any
element in the entire array.

Algorithms/Techniques:
- Single pass through the array
- Tracking the first occurrence of each element
- Dynamic update of the best subsegment based on frequency and length

Time Complexity: O(n), where n is the size of the array
Space Complexity: O(max_value), where max_value is the maximum element in the
array (up to 10^6)
*/

#include <cstdio>

int a1[1000001], a2[1000001]; // a1 stores frequency of elements, a2 stores
                              // first occurrence of elements
int main() {
  int n, a, b, c,
      o = 0; // o = max frequency so far, a,b = start and end of best subsegment
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &c); // read current element
    if (!a2[c])      // if this element has not been seen before
      a2[c] = i;     // record its first occurrence
    ++a1[c];         // increment frequency count
    // update the best subsegment if:
    // 1. current max frequency is higher than previous max
    // 2. same max frequency but smaller subsegment length
    if (a1[c] > o || a1[c] == o && i - a2[c] < b - a)
      o = a1[c], a = a2[c], b = i;
  }
  printf("%d %d\n", a, b); // output the start and end indices of the subsegment
}

// https://github.com/VaHiX/CodeForces/
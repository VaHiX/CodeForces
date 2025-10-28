// Problem: CF 1506 D - Epic Transformation
// https://codeforces.com/contest/1506/problem/D

/*
D. Epic Transformation
Algorithms/Techniques: Hash map to count frequencies, greedy approach to determine minimum array size after pairing.
Time Complexity: O(n log n) per test case due to map operations (insertion and access).
Space Complexity: O(n) for storing the frequency map.

Problem Description:
Given an array of integers, we can remove two different elements from the array in each operation.
The goal is to minimize the size of the array by performing these operations optimally.

Approach:
1. Count frequencies of each element using a map.
2. Find the maximum frequency of any element (mx).
3. If twice the maximum frequency exceeds the array size, we need to remove some elements to pair them up,
   so result = 2 * mx - n.
4. Otherwise, if the array length is odd, one element remains unpaired, hence result = 1.
5. If all elements can be paired perfectly, result = 0.

Sample Input:
5
6
1 6 1 1 4 4
2
1 2
2
1 1
5
4 5 4 5 4
6
2 3 2 1 3 1

Sample Output:
0
0
2
1
0
*/

#include <cstdio>
#include <map>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> m; // Map to store frequency of each element
    long mx(0);             // Maximum frequency of any element
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      ++m[a];              // Increment the count of current element
      mx = (mx > m[a]) ? mx : m[a]; // Update maximum frequency
    }
    long res(0);
    if (2 * mx > n) {
      // If twice the max frequency is greater than total elements,
      // we cannot pair all occurrences of that element, so residual = 2*mx - n
      res = 2 * mx - n;
    } else if (n % 2) {
      // If array length is odd and elements can be paired,
      // one element must remain unpaired
      res = 1;
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/
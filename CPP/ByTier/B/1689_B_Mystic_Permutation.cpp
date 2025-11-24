// Problem: CF 1689 B - Mystic Permutation
// https://codeforces.com/contest/1689/problem/B

/*
B. Mystic Permutation
Algorithms/Techniques: Sorting, Greedy approach
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for auxiliary arrays

Monocarp is a little boy who lives in Byteland and he loves programming.
Recently, he found a permutation of length n. He has to come up with a 
mystic permutation. It has to be a new permutation such that it differs from the old one in each position.
More formally, if the old permutation is p_1,p_2,...,p_n and the new one is q_1,q_2,...,q_n it must hold that 
p_1 != q_1, p_2 != q_2, ..., p_n != q_n.
Monocarp is afraid of lexicographically large permutations. Can you please help him to find the lexicographically minimal mystic permutation?

Input:
There are several test cases in the input data. The first line contains a single integer t (1 <= t <= 200) — the number of test cases. This is followed by the test cases description.
The first line of each test case contains a positive integer n (1 <= n <= 1000) — the length of the permutation.
The second line of each test case contains n distinct positive integers p_1, p_2, ..., p_n (1 <= p_i <= n). It's guaranteed that p is a permutation, i. e. p_i != p_j for all i != j. 
It is guaranteed that the sum of n does not exceed 1000 over all test cases.

Output:
For each test case, output n positive integers — the lexicographically minimal mystic permutations. If such a permutation does not exist, output -1 instead.
*/
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
      cin >> a[i];
    if (n == 1) {
      cout << -1 << endl;
      continue;
    }
    int b[n]; // Copy of the original array
    copy_n(a, n, b); // Copy elements from a to b
    sort(b, b + n); // Sort b in ascending order to get lexicographically smallest
    for (int i = 0; i < n - 1; i++) {
      if (a[i] == b[i]) { // If the element at position i in sorted array matches original
        swap(b[i], b[i + 1]); // Swap with next to make it different
      }
    }
    if (a[n - 1] == b[n - 1]) // Check last element
      swap(b[n - 1], b[n - 2]); // Swap with previous one to ensure difference
    for (int i = 0; i < n; i++)
      cout << b[i] << " ";
    cout << endl;
  }
}


// https://github.com/VaHiX/codeForces/
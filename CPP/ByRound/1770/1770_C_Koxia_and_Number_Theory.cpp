// Problem: CF 1770 C - Koxia and Number Theory
// https://codeforces.com/contest/1770/problem/C

/*
Purpose: Determine if there exists a positive integer x such that for all pairs (i,j), 
         gcd(a[i] + x, a[j] + x) = 1. This is equivalent to checking if there's an x 
         such that all elements in the array a + x are pairwise coprime.

Algorithms/Techniques:
- The solution uses a key observation: if we can find an x such that gcd(a[i] + x, a[j] + x) = 1 for all pairs,
  this implies that for any fixed x, the values a[i] + x mod k must be distinct modulo k for k > 1.
- The algorithm tests various values of k (from 2 to n) and checks if the array modulo k has at least two elements 
  in each residue class, which would prevent satisfying the condition for that k.
- The first part checks for duplicates in the original array (if any, the answer is NO).
- The second part is a greedy check over all possible moduli k from 2 to n.

Time Complexity: O(n^3) in worst case due to nested loops, but optimized by early exit conditions.
Space Complexity: O(n) for the cnt array used during modulo counting.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, cnt[N];
ll a[N];

int main() {
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    sort(a + 1, a + n + 1); // Sort the array to process duplicates easily
    
    int bj = 0; // Flag to indicate if a conflict is found
    
    // Check if there are any duplicate elements in the array
    for (int i = 2; i <= n; i++)
      if (a[i] == a[i - 1])
        bj = 1;
    
    // For each modulus k from 2 to n:
    for (int i = 2; i <= n; i++) {
      // Reset the count array for current k
      for (int j = 0; j <= i; j++)
        cnt[j] = 0;
      
      // Count how many elements of a are congruent to each residue mod k
      for (int j = 1; j <= n; j++)
        cnt[a[j] % i]++;
      
      bool ok = 1; // Flag indicating whether the current k is valid
      
      // For each residue class, check if it contains at least 2 elements
      for (int j = 0; j < i; j++)
        if (cnt[j] < 2)
          ok = 0; // If any class has less than 2 elements, this k cannot work
      
      if (ok)
        bj = 1; // If all classes have at least 2 elements, indicate conflict
    }
    
    puts(bj ? "NO" : "YES"); // Output result
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
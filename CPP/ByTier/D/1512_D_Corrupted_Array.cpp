// Problem: CF 1512 D - Corrupted Array
// https://codeforces.com/contest/1512/problem/D

/*
Purpose: This code solves the problem of reconstructing an array 'a' from a corrupted array 'b'. 
The corrupted array 'b' contains:
- The original array elements 'a'
- The sum of elements in 'a' as the (n+1)-th element
- An additional random number 'x' as the (n+2)-th element
The array 'b' is shuffled, so we need to determine a valid array 'a' that satisfies the conditions.

Algorithm:
1. Sort the array 'b'
2. Try to identify the sum of elements of 'a' by checking if the sum of first n elements equals the (n+1)-th element
3. If not, try to find which element among the sorted array should be 'x' (by checking if sum of elements excluding one equals the last element)
4. Output the reconstructed array or -1 if impossible

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing vector b
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> b(n + 2);
    for (ll p = 0; p < n + 2; p++) {
      scanf("%lld", &b[p]);
    }
    sort(b.begin(), b.end()); // Sort the array to identify potential candidates
    ll sf(0);
    for (ll p = 0; p < n; p++) {
      sf += b[p]; // Sum of first n elements
    }
    if (sf == b[n]) {
      // If sum of first n elements equals (n+1)-th element, then it can be array a
      for (ll p = 0; p < n; p++) {
        printf("%lld ", b[p]);
      }
      puts(""); // Print the array a
    } else {
      // If not, look for a candidate to remove such that remaining sum is equal to (n+2)-th element
      sf += b[n]; // Add the (n+1)-th element to total sum
      ll sg(b.back()), idx(-1); // sg is the last element, idx stores index of element to remove
      for (ll p = 0; p <= n; p++) {
        if (sg + b[p] == sf) { // Check if removing b[p] makes sum match
          idx = p;
          break;
        }
      }
      if (idx < 0) {
        puts("-1"); // Not possible to reconstruct array
      } else {
        for (ll p = 0; p <= n; p++) {
          if (p == idx) {
            continue; // Skip the removed element
          } else {
            printf("%lld ", b[p]);
          }
        }
        puts(""); // Output the reconstructed array
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/
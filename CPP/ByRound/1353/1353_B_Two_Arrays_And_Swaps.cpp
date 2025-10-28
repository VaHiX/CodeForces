// Problem: CF 1353 B - Two Arrays And Swaps
// https://codeforces.com/contest/1353/problem/B

/*
B. Two Arrays And Swaps
Algorithms/Techniques: Sorting, Greedy

Time Complexity: O(t * n * log(n)) where t is the number of test cases and n is the size of arrays.
Space Complexity: O(n) for storing the two arrays.

The algorithm works as follows:
1. For each test case, we sort both arrays in ascending order.
2. We greedily try to improve the sum of array 'a' by swapping elements.
3. We perform at most k swaps.
4. In each swap, we take the smallest element from 'a' and replace it with the largest element from 'b'.
5. We calculate the final sum of array 'a'.

*/

#include <algorithm>
#include <iostream>

using namespace std;
int i, k, n, s, t, a[36], b[36]; // Declare variables
int main() {
  for (cin >> t; t--;) { // Loop for each test case
    cin >> n >> k; // Read n (size of arrays) and k (max swaps)
    for (i = 0; i++ < n;) // Read array a
      cin >> a[i];
    for (i = 0; i++ < n;) // Read array b
      cin >> b[i];
    sort(a, a + n + 1); // Sort array a in ascending order
    sort(b, b + n + 1); // Sort array b in ascending order
    for (i = 0; i++ < k;) { // Perform up to k swaps
      if (a[i] < b[n - i + 1]) // If current element in a is smaller than largest in b
        a[i] = b[n - i + 1]; // Replace it with the largest element of b
    }
    for (i = s = 0; i++ < n;) // Calculate sum of modified array a
      s += a[i];
    cout << s << endl; // Print the result
  }
}


// https://github.com/VaHiX/codeForces/
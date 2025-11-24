// Problem: CF 1764 G1 - Doremy's Perfect DS Class (Easy Version)
// https://codeforces.com/contest/1764/problem/G1

/*
 * Problem: Find the index of the element with value 1 in a hidden permutation of size n.
 * Algorithm: Use binary search and queries on floor division to identify the position of 1.
 *            The key insight is that we can use the number of distinct elements in a range
 *            when divided by a certain value to deduce information about the structure.
 *
 * Time Complexity: O(log^2(n)) due to nested binary searches and at most 30 queries.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

#include <iostream>

using namespace std;
int n, pl = 1e9;

// Function to make a query and return the result
int check(int l, int r, int val) {
  if (l > r)
    return 0;
  if (l == 1 && r == n)
    return n / 2 + 1;
  if (l == r)
    return 1;
  cout << "? " << l << " " << r << " " << val << endl;
  int us;
  cin >> us;
  return us;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  
  // If n is even, find the position 'pl' where the value 1 might be located
  if (n % 2 == 0) {
    int l = 1, r = n;
    while (l < r) {
      int mid = (l + r) / 2 + 1;
      // Use query with k=n to find the boundary
      if (check(mid, n, n) == 2)
        l = mid;
      else
        r = mid - 1;
    }
    pl = l;
  }
  
  // Binary search to find the index of value 1
  int l = 1, r = n, all = n / 2 + 1;
  while (l < r) {
    int mid = (l + r) / 2;
    // Count distinct values in the first half (divided by 2)
    int A = check(1, mid, 2);
    // Count distinct values in the second half (divided by 2)
    int B = all - check(mid + 1, n, 2);
    // Adjust the binary search based on the sum of distinct values
    if (A + B - (mid >= pl) > mid) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  
  // Output the result
  cout << "! " << r << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
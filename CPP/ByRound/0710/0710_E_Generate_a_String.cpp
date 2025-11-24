// Problem: CF 710 E - Generate a String
// https://codeforces.com/contest/710/problem/E

/*
 * Problem: Generate a String
 * Purpose: Find the minimum time to generate a string of exactly n letters 'a'
 *          using insert/delete (x seconds per operation) and copy (y seconds per operation).
 *
 * Algorithm: Dynamic Programming
 * Approach:
 *   - Let a[i] represent the minimum time to generate exactly i letters 'a'.
 *   - Transition:
 *     - To get i letters, either:
 *       1. Build i-1 letters and insert one more 'a' (a[i-1] + x)
 *       2. Build i/2 letters, copy them (i/2 letters become i letters), then add one more if needed
 *          - If i is even: a[i/2] + y
 *          - If i is odd: a[(i+1)/2] + x + y (since we need to build (i+1)/2 letters, copy it, then delete one)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <algorithm>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 15
#define inf 100000
#define pp pair<int, int>
using namespace std;

int main() {
  ll i, j, k;
  ll n, m, cur;
  ll x, y;
  cin >> n >> x >> y;
  ll *a = new ll[n + 1]; // dp array to store min time for i letters
  a[0] = 0;              // base case: 0 letters need 0 time
  a[1] = x;              // base case: 1 letter needs 1 insert operation
  
  // Fill the dp array from 2 to n
  for (i = 2; i <= n; i++) {
    if (i % 2) // i is odd
      k = a[(i + 1) / 2] + x; // build (i+1)/2 letters, copy, then delete 1 letter (cost = a[(i+1)/2] + x)
    else
      k = a[i / 2]; // build i/2 letters, copy them to get i letters (cost = a[i/2])
    
    // Choose minimum between:
    // 1. Inserting one more letter to i-1 letters: a[i-1] + x
    // 2. Building k letters and copying them: k + y
    a[i] = min(a[i - 1] + x, k + y);
  }
  
  cout << a[n] << endl; // output the minimum time to generate n letters
  return 0;
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 1628 A - Meximum Array
// https://codeforces.com/contest/1628/problem/A

/*
 * Problem: A. Meximum Array
 * Description:
 *   Given an array of non-negative integers, construct a new array b by repeatedly
 *   taking the MEX (minimum excludant) of the first k elements of the array,
 *   removing those elements from a, and appending the MEX to b.
 *   Goal: Find the lexicographically maximum possible b.
 *
 * Algorithm:
 *   Greedily select the largest possible MEX at each step by trying to include
 *   as many numbers as possible in the current prefix while maintaining 
 *   the smallest MEX until that point. When we can no longer form a valid
 *   prefix (a number that doesn't exist yet in the prefix is missing), we 
 *   flush it out from the prefix and append it to b.
 *
 * Time Complexity: O(n) per test case, where n is the length of input array;
 *   each element is processed at most twice.
 * Space Complexity: O(n) for auxiliary arrays.
 */

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;
const int N = 2e5 + 3;
int a[N], ct[N], b[N]; // a: input array, ct: count of numbers seen so far, b: to track which id we use for each number
vector<int> v;         // result vector storing the MEX values
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T, n, i, j, k, now, id = 1;
  cin >> T;
  for (; T--;) {
    cin >> n;
    for (i = 1; i <= n; ++i)
      cin >> a[i], ++ct[a[i]]; // read input and count occurrences
    
    v = {}; // reset result vector
    now = 0; // current MEX candidate, starts from 0
    for (i = 1; i <= n; ++i) {
      b[a[i]] = id; // assign id to a[i]
      --ct[a[i]];   // decrease count of this number
      
      // find next number that is not present in current prefix (increment 'now')
      while (b[now] == id)
        ++now;
      
      // if there's no more of 'now' in the remaining elements, flush it into b
      if (!ct[now]) {
        v.push_back(now);
        ++id;     // increment id for next group
        now = 0;  // reset now to search from min again
      }
    }
    
    cout << v.size() << '\n';
    for (auto o : v)
      cout << o << ' ';
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 1990 B - Array Craft
// https://codeforces.com/contest/1990/problem/B

/*
Purpose: 
This code constructs an array of size n, where each element is either 1 or -1, 
satisfying two constraints:
1. The maximum prefix sum occurs at index x (1-indexed).
2. The maximum suffix sum occurs at index y (1-indexed).

Algorithm:
- Initialize the array with all 1s.
- Modify elements from index y-2 down to 0 to ensure the prefix sum max occurs at x.
- Modify elements from index x to n-1 to ensure the suffix sum max occurs at y.
  
Time Complexity: O(n) - Each element is visited at most once during modification.
Space Complexity: O(n) - For storing the array of size n.
*/

#include <algorithm>
#include <iostream>
#include <vector>

#define Tal3at                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define dpp(arr, val) memset(arr, val, sizeof(arr))
#define ll long long
#define ull unsigned long long
#define pb push_back
#define dd double
#define yes cout << "YES" << el;
#define no cout << "NO" << el;
#define ld long double
#define PQ priority_queue
#define pii pair<int, int>
#define pll pair<ll, ll>
#define S second
#define F first
#define MP make_pair
#define el "\n"
#define PI 3.14159265
#define SORT(vec) sort(vec.begin(), vec.end())
#define all(v) v.begin(), v.end()
#define sumAll accumulate(vec.begin(), vec.end(), 0LL)
#define productAll accumulate(vec.begin(), vec.end(), 1LL, multiplies<ll>())
using namespace std;
ll m = 1e9 + 7;
const int sz = 1e5 + 10;
const int OO = 0x3f3f3f3f;
int main() {
  Tal3at int t;
  cin >> t;
  while (t--) {
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> v(n, 1); // Initialize with all 1s
    
    // Adjust values from index y-2 down to 0 to control prefix max
    for (int i = y - 2; i >= 0; i--) {
      v[i] = -v[i + 1]; // Flip sign to manage prefix sum
    }
    
    // Adjust values from index x to n-1 to control suffix max
    for (int i = x; i < n; i++) {
      v[i] = -v[i - 1]; // Flip sign to manage suffix sum
    }
    
    // Print the constructed array
    for (int i = 0; i < n; i++) {
      cout << v[i] << " ";
    }
    cout << el;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
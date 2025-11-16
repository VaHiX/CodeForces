// Problem: CF 2162 E - Beautiful Palindromes
// https://codeforces.com/contest/2162/problem/E

/*
Purpose: This code solves the problem of minimizing the number of palindromic subarrays 
         after appending exactly k integers to the given array. The strategy is to 
         append three specific values in a repeating pattern to reduce palindromic subarrays.

Algorithms/Techniques:
- Greedy approach to select elements to append
- Identify a missing number in range [1, n] to use as the first element
- Use a repeating pattern of (num1, num2, num3) to minimize palindromic subarrays
- Time Complexity: O(n) per test case, Space Complexity: O(n)

Time Complexity: O(n) where n is the size of the array
Space Complexity: O(n) for storing the visited array and result
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long int
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<bool> visited(n + 1, false); // Track which numbers from 1 to n are already present
    vector<int> a(n);
    for (int i = 0; i < n; i++)
      cin >> a[i], visited[a[i]] = true; // Mark visited numbers
    
    int notV = -1;
    for (int i = 1; i <= n; i++) {
      if (!visited[i]) {
        notV = i; // Find the first missing number in range [1, n]
        break;
      }
    }
    
    int num1, num2, num3;
    if (notV == -1) {
      // If all numbers from 1 to n are present, use the last three elements
      num1 = a[n - 3], num2 = a[n - 2], num3 = a[n - 1];
    } else {
      // Otherwise, use the missing number as num1 and last element as num3
      // num2 is chosen to be different from num1 and num3
      num1 = notV;
      num3 = a[n - 1];
      num2 = 1;
      while (num2 == num1 || num2 == num3)
        num2++; // Ensure num2 is not equal to num1 or num3
    }
    
    vector<int> ans;
    // Append the pattern (num1, num2, num3) repeatedly until k operations are done
    while (1) {
      ans.push_back(num1);
      k--;
      if (k == 0)
        break;
      ans.push_back(num2);
      k--;
      if (k == 0)
        break;
      ans.push_back(num3);
      k--;
      if (k == 0)
        break;
    }
    
    for (int i = 0; i < (int)ans.size(); i++)
      cout << ans[i] << " ";
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
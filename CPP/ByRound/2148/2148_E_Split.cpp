// Problem: CF 2148 E - Split
// https://codeforces.com/contest/2148/problem/E

/*
E. Split
time limit per test2 seconds
memory limit per test256 megabytes

Task:
Farmer John has an array a containing n positive integers and an integer k.
Let a[l,r] be a subarray of a. He performs the following procedure to independently determine if subarray a[l,r] is awesome:
Initially, FJ has k empty multisets, numbered from 1 to k.
Then, for each element a[i] (1≤i≤n) in a:
If l≤i≤r (that is, a[i] is in the subarray a[l,r]), he places a[i] in multiset 1,
Otherwise, he places a[i] into any multiset he wants (which may be multiset 1).
Subarray a[l,r] is awesome if there is some way for him to place elements such that, for every value v, all multisets contain the same number of elements with value v. In other words, he wants to make all multisets contain the exact same elements (ignoring ordering).

Algorithm:
- First, check if the total frequency of each element in the entire array is divisible by k.
  If not, no subarray can be awesome.
- Then, use a sliding window technique to count valid subarrays where every element's frequency within that window,
  when combined with elements outside the window (distributed optimally among k multisets), results in equal frequencies.

Time Complexity:
O(n) per test case, since we process each element at most twice in the sliding window.

Space Complexity:
O(n) for storing counts and frequencies.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), cnt(n + 1); // cnt[i] stores frequency of element i in entire array
    
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      cnt[a[i]]++; // Count occurrences of each element
    }
    
    bool ok = 1;
    for (int i = 1; i <= n; i++)
      if (cnt[i] % k) { // If any element's count is not divisible by k, impossible to divide equally
        ok = 0;
        break;
      }
    
    if (!ok) {
      cout << "0\n";
      continue;
    }
    
    long long ans = 0;
    vector<int> freq(n + 1, 0); // Current frequency of elements in sliding window
    int left = 0; // Left pointer of sliding window
    
    for (int right = 0; right < n; right++) {
      freq[a[right]]++; // Expand window by including element at 'right'
      
      // Shrink window from left until no element exceeds its allowed count (cnt[i]/k)
      while (left <= right && freq[a[right]] > cnt[a[right]] / k) {
        freq[a[left]]--;
        left++;
      }
      
      // All subarrays ending at 'right' and starting between 'left' and 'right' are valid
      ans += right - left + 1;
    }
    
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 633 D - Fibonacci-ish
// https://codeforces.com/contest/633/problem/D

/*
D. Fibonacci-ish
Purpose: Finds the longest possible Fibonacci-ish prefix that can be formed by rearranging the given sequence.
Algorithm: 
    - Use a frequency map to count occurrences of each number.
    - Iterate over all pairs of numbers (left, right) from the set of unique elements.
    - For each pair, simulate building a Fibonacci-like sequence starting with these two elements.
    - Track how many elements can be used in such a sequence and update the maximum length found.
    - Handle special cases: zeros and duplicate values to avoid invalid sequences.
Time Complexity: O(n^2 * log n) where n is the size of input array
Space Complexity: O(n) for storing frequencies and unique elements
*/

#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n);
  std::map<ll, ll> ctm;  // Frequency map of elements
  std::set<ll> vs;       // Set of unique elements
  ll zeros(0);           // Count of zeros
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
    ++ctm[a[p]];         // Increment frequency
    vs.insert(a[p]);     // Insert into set of unique elements
    zeros += (a[p] == 0); // Count zeros
  }
  ll maxLength(zeros);   // Initialize with zero count, as a valid Fibonacci-ish sequence can start with 0s

  // Try all pairs of elements as starting points for the Fibonacci sequence
  for (std::set<ll>::iterator itx = vs.begin(); itx != vs.end(); itx++) {
    for (std::set<ll>::iterator ity = vs.begin(); ity != vs.end(); ity++) {
      ll left = *itx;
      ll right = *ity;
      
      // Skip invalid starting pairs
      if (left == 0 && right == 0) {
        continue;
      }
      if (left == right && ctm[left] < 2) {
        continue;
      }

      ll length(2);              // Start with two elements in the sequence
      std::map<ll, ll> cur;      // Track how many of each element are used in current simulation
      --ctm[left];               // Decrease count for left element
      --ctm[right];              // Decrease count for right element
      ++cur[left];               // Increment usage
      ++cur[right];              // Increment usage

      ll next = left + right;    // Calculate next Fibonacci number
      // Continue building the sequence while next number exists in the input
      while (ctm.count(next) && ctm[next] > 0) {
        --ctm[next];             // Use the next number
        ++cur[next];             // Track usage
        ++length;                // Increase length of sequence
        left = right;            // Shift window
        right = next;            // Shift window
        next = left + right;     // Calculate new next
      }
      
      maxLength = (maxLength > length) ? maxLength : length;  // Update maximum

      // Restore counts after simulation
      for (std::map<ll, ll>::iterator it = cur.begin(); it != cur.end(); it++) {
        ctm[it->first] += it->second;
      }
    }
  }
  printf("%lld\n", maxLength);
  return 0;
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 988 C - Equal Sums
// https://codeforces.com/contest/988/problem/C

/*
Algorithm: Two Pointers + Hash Map
Time Complexity: O(n * log(n)) where n is the total number of elements across all sequences.
Space Complexity: O(n) for storing the hash map and sequences.

Approach:
- For each sequence, calculate the total sum.
- For each element in the sequence, compute the sum after removing that element.
- Store these "partial sums" in a hash map along with the sequence index and element index.
- If we encounter a partial sum that was already seen before, and the sequence index is smaller
  than the one stored, we have found a valid pair.
- This ensures we output the indices in a consistent manner (smaller index first).
*/

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

int main() {
  long k;
  scanf("%ld", &k);
  std::map<long, std::pair<long, long>> m; // Map to store partial sum -> (sequence_index, element_index)
  std::pair<long, long> a, b; // Stores the result indices
  bool done(false); // Flag to indicate if solution is found
  for (long seq = 1; seq <= k; seq++) { // Iterate through each sequence
    if (done) {
      break;
    }
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n + 1); // Vector to store the elements (1-indexed)
    long s(0); // Total sum of current sequence
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &v[p]);
      s += v[p]; // Accumulate the sum
    }
    for (long p = 1; p <= n; p++) {
      long partial = s - v[p]; // Compute the sum after removing element at position p
      std::pair<long, long> where = std::make_pair(seq, p); // Store the info of current sequence and position
      if (m.count(partial) && m[partial].first < seq) { // Check if same partial sum was seen and current sequence < stored
        a = m[partial]; // Store the previous sequence and position
        b = where; // Store current sequence and position
        done = true; // Mark that solution is found
      } else {
        m[partial] = where; // Store the partial sum for future reference
      }
    }
  }
  if (done) {
    printf("YES\n%ld %ld\n%ld %ld\n", a.first, a.second, b.first, b.second); // Output the solution
  } else {
    puts("NO"); // No valid pair found
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
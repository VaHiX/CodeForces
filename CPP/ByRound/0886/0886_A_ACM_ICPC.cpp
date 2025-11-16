// Problem: CF 886 A - ACM ICPC
// https://codeforces.com/contest/886/problem/A

#include <cstdio>
#include <vector>
/*
Algorithm: Brute Force with Bitmasking
- Generate all possible combinations of selecting 3 participants out of 6 (2^6 = 64 combinations)
- For each combination, check if it forms a valid team of 3 (size == 3)
- Compute the sum of scores for that team
- Check if 2 * sum == total_sum (i.e., remaining 3 form another equal team)
- If such a split exists, output YES, else NO

Time Complexity: O(2^N * N) where N = 6 -> O(64 * 6) = O(1)
Space Complexity: O(N) for storing scores and intermediate vectors -> O(1)

*/
std::vector<long> getBool(long x) {
  std::vector<long> a;
  for (long p = 0; p < 10 && x > 0; p++) {
    if (x % 2) {
      a.push_back(p);
    }
    x /= 2;
  }
  return a;
}
int main() {
  const long N = 6; // Number of participants
  const long M = (1 << N); // Total combinations (2^N)
  std::vector<long> s(N);
  long total(0);
  for (long p = 0; p < N; p++) {
    scanf("%ld", &s[p]); // Read scores
    total += s[p]; // Calculate total score
  }
  bool possible(false);
  for (long p = 0; p < M; p++) {
    std::vector<long> b = getBool(p); // Get indices of selected participants
    if (b.size() != N / 2) { // Only consider selections of exactly 3 participants
      continue;
    }
    long sum(0);
    for (long u = 0; u < N / 2; u++) {
      sum += s[b[u]]; // Compute sum of selected team
    }
    if (2 * sum == total) { // If two teams have equal score
      possible = true;
      break;
    }
  }
  puts(possible ? "YES" : "NO"); // Output result
  return 0;
}


// https://github.com/VaHiX/CodeForces/
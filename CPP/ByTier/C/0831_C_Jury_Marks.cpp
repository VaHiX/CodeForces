// Problem: CF 831 C - Jury Marks
// https://codeforces.com/contest/831/problem/C

/*
Algorithm/Techniques: Prefix Sum, Hash Map, Set
Time Complexity: O(k^2 + k*n) where k is the number of jury members and n is the number of remembered scores.
Space Complexity: O(k + n) for storing prefix sums and remembered scores.

The problem involves determining how many initial scores could lead to specific intermediate scores 
after a sequence of jury marks. We compute prefix sums of jury marks, then for each remembered score 
we check all possible prefix sums to derive valid initial scores. A hash map tracks counts of valid 
initial scores, and we increment the result when all n remembered scores are matched.
*/

#include <cstdio>
#include <set>
#include <unordered_map>
#include <vector>
int main() {
  long k, n;
  scanf("%ld %ld", &k, &n);
  std::set<long> s; // Store all prefix sums of jury marks
  long suma(0);
  for (int p = 0; p < k; p++) {
    long a;
    scanf("%ld", &a);
    suma += a; // Compute prefix sum
    s.insert(suma); // Insert prefix sum into set
  }
  std::vector<long> b(n);
  for (int p = 0; p < n; p++) {
    scanf("%ld", &b[p]); // Read remembered scores
  }
  std::unordered_map<long, long> m; // Map to count occurrences of potential initial scores
  long count(0);
  for (int p = 0; p < n; p++) {
    for (std::set<long>::iterator it = s.begin(); it != s.end(); it++) {
      long g = *it;
      ++m[b[p] - g]; // Derive initial score: remembered_score - prefix_sum
      count += (m[b[p] - g] == n); // If this initial score has been seen n times, increment count
    }
  }
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/
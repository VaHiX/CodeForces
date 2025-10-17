// Problem: CF 1954 E - Chain Reaction
// https://codeforces.com/contest/1954/problem/E

/*
Algorithm: Difference Array + Prefix Sum + Simulation
Time Complexity: O(max(a) * log(max(a)) + N)
Space Complexity: O(max(a))

This solution uses a difference array technique to efficiently count how many monsters
are "affected" by a chain lightning at a given k. For each monster, we simulate the
spread of lightning and count the number of seconds required to eliminate all monsters
for every value of k from 1 to max(a).

The key idea is:
1. For each monster with health A[i], we track how many times it gets hit by a lightning bolt
   when k ranges from 1 to A[i].
2. We use a difference array to mark the start and end of these intervals.
3. Then we compute prefix sums to get the actual counts.
4. Finally, we iterate over all values of k and compute the total number of operations
   needed.
*/

#include <iostream>
#include <algorithm>

int N, P = 0, K = 0, imos[1 << 17]; // imos is the difference array, P tracks previous health, K tracks max health
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(0);
  std::cin >> N;
  for (int i = 0, A; i < N; i++) {
    std::cin >> A;
    // If previous monster's health is less than current, increment the start and decrement the end
    if (P < A)
      imos[P]++, imos[A]--;
    P = A, K = std::max(K, A); // Keep track of maximum health
  }
  // Compute prefix sum to get actual number of times each health value is encountered
  for (int i = 0; i < K; i++)
    imos[i + 1] += imos[i];
  
  // For each k from 1 to K, calculate minimal time
  for (int k = 1; k <= K; k++) {
    long long ans = 0;
    // Sum up the contributions of all intervals of size k
    for (int i = 0; i <= K; i += k)
      ans += imos[i];
    std::cout << ans << (k == K ? "\n" : " ");
  }
}


// https://github.com/VaHiX/CodeForces/
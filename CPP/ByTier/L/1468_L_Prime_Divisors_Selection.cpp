// Problem: CF 1468 L - Prime Divisors Selection
// https://codeforces.com/contest/1468/problem/L

/*
Algorithm: Prime Divisors Selection
Time Complexity: O(N^2 * log(max(x_i)) + L * N) where L is the number of unique primes found
Space Complexity: O(N + L) where L is the number of unique primes found

This code finds a subset of K integers from the given array such that the subset forms an "ideal" sequence.
An ideal sequence ensures that any valid assignment of prime divisors to elements (where each element is divisible by its assigned prime) results in a "friendly" sequence - one where all primes in the assignment are shared by at least two elements.
The approach:
1. For each pair of numbers, compute possible prime factors using helper functions to detect pure powers (e.g., 4=2^2, 16=2^4).
2. Store these primes and their factorizations.
3. Group indices by how many primes they share.
4. Select K numbers such that:
   - If possible, pick numbers from groups with 2 or more elements (to avoid uniqueness).
   - Otherwise, use combinations that allow for a friendly selection.
5. Ensure the final subset has K elements and that the result is valid for forming an ideal sequence.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int N, K, L;
long long x[1000];
long long pure[1000000];

// Compute greatest common divisor
long long gcd(long long a, long long b) {
  long long r;
  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

// Check if a is a pure power of b (i.e., a == b^k for some k >= 1)
long long contains_pure(long long a, long long b) {
  while (a % b == 0)
    a /= b;
  return a == 1;
}

// Try to identify pure prime factors of two numbers
void try_to_get_pure(long long a, long long b) {
  if (a > b)
    std::swap(a, b);
  if (b % a)
    return;
  if (a == b / a || a == b) {
    long long i = 2;
    while (i * i <= a && a % i != 0)
      i++;
    if (a % i != 0)
      pure[L++] = a;
    else if (contains_pure(a, i))
      pure[L++] = i;
    return;
  }
  if (a < b / a) {
    if (b / a % a == 0)
      try_to_get_pure(a, b / a);
  } else {
    if (a % (b / a) == 0)
      try_to_get_pure(b / a, a);
  }
}

// Vector to store prime indices per number
std::vector<int> V[1000];
// Vector to store indices where each prime appears
std::vector<int> appear[1000];

int main() {
  scanf("%d%d", &N, &K);
  if (K == 1) {
    puts("0");
    return 0;
  }
  for (int i = 0; i < N; i++)
    scanf("%lld", x + i);

  // Find all possible primes involved in any pair of numbers
  for (int i = 0; i < N; i++)
    for (int j = i + 1; j < N; j++)
      try_to_get_pure(x[i], x[j]);

  // Sort and remove duplicates
  std::sort(pure, pure + L);
  L = std::unique(pure, pure + L) - pure;

  // Map each number to its set of prime indices
  for (int i = 0; i < N; i++) {
    V[i].clear();
    long long t = x[i];
    for (int j = 0; j < L; j++)
      if (t % pure[j] == 0) {
        V[i].push_back(j);
        while (t % pure[j] == 0)
          t /= pure[j];
      }
    if (t > 1)
      V[i].clear(); // Not fully factorizable using only 'pure' primes
    if (int(V[i].size()) == 1) // Only one prime factor
      appear[V[i][0]].push_back(i);
  }

  int only_pure = 0;
  for (int i = 0; i < L; i++)
    if ((appear[i].size()) >= 2)
      only_pure += appear[i].size();

  // If we have enough elements with shared primes, proceed to build the answer
  if (only_pure >= K) {
    bool all_equal_2 = true;
    for (int i = 0; i < L; i++)
      if (int(appear[i].size()) > 2)
        all_equal_2 = false;

    if (all_equal_2) {
      if (K % 2 == 0) {
        int got = 0;
        static int finally_choose[1000];
        for (int i = 0; got < K && i < L; i++)
          if (appear[i].size() == 2) {
            got += 2;
            finally_choose[i] = 1;
          }
        for (int i = 0; i < N; i++)
          if (int(V[i].size()) == 1 && finally_choose[V[i][0]])
            printf("%lld ", x[i]);
        puts("");
      } else {
        int mixed_to_choose = -1;
        for (int i = 0; i < N; i++)
          if (int(V[i].size()) > 1 && int(V[i].size()) <= K / 2) {
            bool all_good = true;
            for (int _ : V[i])
              if (int(appear[_].size()) != 2)
                all_good = false;
            if (all_good) {
              mixed_to_choose = i;
              break;
            }
          }
        if (mixed_to_choose == -1) {
          puts("0");
          return 0;
        }
        static int finally_choose[1000];
        int got = 1;
        for (int _ : V[mixed_to_choose]) {
          got += 2;
          finally_choose[_] = 1;
        }
        for (int i = 0; got < K && i < L; i++)
          if (int(appear[i].size()) == 2 && !finally_choose[i]) {
            got += 2;
            finally_choose[i] = 1;
          }
        for (int i = 0; i < N; i++)
          if (int(V[i].size()) == 1 && finally_choose[V[i][0]])
            printf("%lld ", x[i]);
        printf("%lld\n", x[mixed_to_choose]);
      }
    } else {
      static int finally_choose[1000];
      int got = 0, found_non_2 = 0;
      for (int i = 0; i < L; i++)
        if (int(appear[i].size()) >= 2 && got <= K - 2 &&
            (got != K - 3 || found_non_2)) {
          finally_choose[i] = 2;
          found_non_2 += int(appear[i].size()) - 2;
          got += 2;
        }
      if (got == K - 1) {
        for (int i = 0; i < L; i++)
          if (finally_choose[i] == 2 && int(appear[i].size()) > 2) {
            finally_choose[i]++;
            break;
          }
      } else {
        for (int i = 0; i < L; i++) {
          int _ = std::min(K - got, int(appear[i].size()) - finally_choose[i]);
          finally_choose[i] += _;
          got += _;
        }
      }
      for (int i = 0; i < N; i++)
        if (int(V[i].size()) == 1 && finally_choose[V[i][0]]) {
          printf("%lld ", x[i]);
          finally_choose[V[i][0]]--;
        }
      puts("");
    }
  } else {
    // Not enough shared primes; try mixing with atypical numbers
    int mix = 0;
    for (int i = 0; i < N; i++)
      if (int(V[i].size()) > 1)
        mix++;
    if (only_pure + mix >= K) {
      for (int i = 0; i < N; i++)
        if (int(V[i].size()) == 1 && int(appear[V[i][0]].size()) >= 2)
          printf("%lld ", x[i]);
      int got = only_pure;
      for (int i = 0; got < K && i < N; i++)
        if (int(V[i].size()) > 1) {
          printf("%lld ", x[i]);
          got++;
        }
      puts("");
    } else
      puts("0");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
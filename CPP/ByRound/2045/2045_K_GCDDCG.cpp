// Problem: CF 2045 K - GCDDCG
// https://codeforces.com/contest/2045/problem/K

/*
 * Problem: K. GCDDCG
 * Purpose: Calculate the sum of creativity points across all rounds in a card game.
 *          Each round i corresponds to building two non-empty decks with GCD equal to i.
 *          Creativity point = i * number of valid ways to form such decks.
 *
 * Algorithms/Techniques:
 *   - Sieve of Eratosthenes for computing Mobius function (miu)
 *   - Fast Walsh-Hadamard Transform (FWT) for efficient convolution
 *   - Number-theoretic computations using modular arithmetic
 *   - Multiplicative functions and inclusion-exclusion
 *
 * Time Complexity: O(N log N + N)
 * Space Complexity: O(N)
 */

#include <iostream>
#include <vector>
constexpr int mod = 0x3b800001;  // 998244353 in hexadecimal
int p2[200007], p3_4[200007];   // Precomputed powers for fast multiplication
int isComp[200007], miu[200007]; // Sieve arrays for composites and Mobius function
std::vector<int> prime;         // List of primes up to N

// Sieve of Eratosthenes for computing mu (Mobius function)
void sieve(int n) {
  miu[1] = 1;
  p2[0] = 1, p2[1] = 2;
  p3_4[0] = 1, p3_4[1] = 0xee00001; // Precomputed mod inverse of 3/4
  for (int i = 2; i <= n; ++i) {
    if (!isComp[i]) {
      prime.push_back(i);
      miu[i] = -1;
    }
    for (int j : prime) {
      if (i * j > n) {
        break;
      }
      isComp[i * j] = true;
      if (i % j == 0) {
        miu[i * j] = 0; // Not square-free => mu = 0
        break;
      } else {
        miu[i * j] = -miu[i]; // Flip sign of mu for distinct prime factor
      }
    }
    p2[i] = 1LL * p2[i - 1] * p2[1] % mod; // Power of 2 modulo prime
    p3_4[i] = 1LL * p3_4[i - 1] * p3_4[1] % mod; // Power of 3/4 (inverse)
  }
}

// Forward or inverse Fast Walsh-Hadamard Transform on array a
void FWT(int *a, int n, int op) {
  if (op == +1) { // Forward
    for (int i : prime) {
      if (i > n) {
        break;
      }
      for (int j = i, k = 1; j <= n; j += i, ++k) {
        a[j] += a[k];
        if (a[j] >= mod) {
          a[j] -= mod;
        }
      }
    }
  } else { // Inverse
    for (int i : prime) {
      if (i > n) {
        break;
      }
      for (int j = n / i * i, k = n / i; j >= i; j -= i, --k) {
        a[j] -= a[k];
        if (a[j] < 0) {
          a[j] += mod;
        }
      }
    }
  }
}

int n, a[200007];        // Input values
int cc[200007];         // Count of elements with same value
int mul[200007];        // Count of multiples
int x[200007];          // Temporary for calculations

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
    ++cc[a[i]]; // Count each value
  }

  // Compute the number of multiples for each d:
  // mul[d] = sum over j where j % d == 0, of cc[j]
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      mul[i] += cc[j];
    }
  }

  sieve(n); // Precompute mu values and powers

  int res = 0;
  for (int d = 1; d <= n; ++d) {
    int ans = 0;
    int sumMiu = 0, sumP2 = 0;

    // For each multiple of d, compute contributions using mu and precomputed values
    for (int i = 1; i <= n / d; ++i) {
      sumMiu += miu[i];
      x[i] = (p2[mul[i * d]] * miu[i] + mod) % mod;
      sumP2 = (sumP2 + x[i]) % mod;
    }

    // Initial formula combining sums of mu and powers
    ans = (ans - 2LL * sumMiu * sumP2 % mod + mod) % mod;
    ans = (ans + 1LL * sumMiu * sumMiu) % mod;

    // Apply forward FWT to x to transform it for convolution
    FWT(x, n / d, +1);

    // Square each transformed value
    for (int i = 1; i <= n / d; ++i) {
      x[i] = 1LL * x[i] * x[i] % mod;
    }

    int lost = 1LL * sumP2 * sumP2 % mod;

    // Apply inverse FWT to get back the convolution
    FWT(x, n / d, -1);

    for (int i = 1; i <= n / d; ++i) {
      ans = (ans + 1LL * x[i] * p3_4[mul[i * d]]) % mod;
      lost = (lost - x[i] + mod) % mod;
    }

    ans += lost;

    // Apply forward FWT again for final computation
    FWT(x, n / d, +1);

    res = (res + 1LL * ans * d) % mod;
  }
  std::cout << res << '\n';
  return 0;
}


// https://github.com/VaHiX/codeForces/
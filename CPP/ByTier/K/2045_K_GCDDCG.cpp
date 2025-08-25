/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <iostream>
#include <vector>

constexpr int mod = 0x3b800001;
int p2[200007], p3_4[200007];

int isComp[200007], miu[200007];
std::vector<int> prime;
void sieve(int n) {
  miu[1] = 1;
  p2[0] = 1, p2[1] = 2;
  p3_4[0] = 1, p3_4[1] = 0xee00001;
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
        miu[i * j] = 0;
        break;
      } else {
        miu[i * j] = -miu[i];
      }
    }
    p2[i] = 1LL * p2[i - 1] * p2[1] % mod;
    p3_4[i] = 1LL * p3_4[i - 1] * p3_4[1] % mod;
  }
}

void FWT(int *a, int n, int op) {
  if (op == +1) {
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
  } else {
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

int n, a[200007];
int cc[200007];
int mul[200007];

int x[200007];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
    ++cc[a[i]];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      mul[i] += cc[j];
    }
  }
  sieve(n);
  int res = 0;
  for (int d = 1; d <= n; ++d) {
    int ans = 0;
    int sumMiu = 0, sumP2 = 0;
    for (int i = 1; i <= n / d; ++i) {
      sumMiu += miu[i];
      x[i] = (p2[mul[i * d]] * miu[i] + mod) % mod;
      sumP2 = (sumP2 + x[i]) % mod;
    }
    ans = (ans - 2LL * sumMiu * sumP2 % mod + mod) % mod;
    ans = (ans + 1LL * sumMiu * sumMiu) % mod;
    FWT(x, n / d, +1);
    for (int i = 1; i <= n / d; ++i) {
      x[i] = 1LL * x[i] * x[i] % mod;
    }
    int lost = 1LL * sumP2 * sumP2 % mod;
    FWT(x, n / d, -1);
    for (int i = 1; i <= n / d; ++i) {
      ans = (ans + 1LL * x[i] * p3_4[mul[i * d]]) % mod;
      lost = (lost - x[i] + mod) % mod;
    }
    ans += lost;
    FWT(x, n / d, +1);
    res = (res + 1LL * ans * d) % mod;
  }
  std::cout << res << '\n';
  return 0;
}
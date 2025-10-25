/*
 * Problem URL : https://codeforces.com/contest/1468/problem/L
 * Submit Date : 2025-09-08
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int N, K, L;
long long x[1000];
long long pure[1000000];
long long gcd(long long a, long long b) {
  long long r;
  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}
long long contains_pure(long long a, long long b) {
  while (a % b == 0)
    a /= b;
  return a == 1;
}
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
std::vector<int> V[1000];
std::vector<int> appear[1000];
int main() {
  scanf("%d%d", &N, &K);
  if (K == 1) {
    puts("0");
    return 0;
  }
  for (int i = 0; i < N; i++)
    scanf("%lld", x + i);
  for (int i = 0; i < N; i++)
    for (int j = i + 1; j < N; j++)
      try_to_get_pure(x[i], x[j]);
  std::sort(pure, pure + L);
  L = std::unique(pure, pure + L) - pure;
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
      V[i].clear();
    if (int(V[i].size()) == 1)
      appear[V[i][0]].push_back(i);
  }
  int only_pure = 0;
  for (int i = 0; i < L; i++)
    if ((appear[i].size()) >= 2)
      only_pure += appear[i].size();
  /*
  for (int i = 0; i < L; i++)
          printf("pure[%d] = %lld\n", i, pure[i]);
  for (int i = 0; i < N; i++)
  {
          printf("%d:", i);
          for (int j : V[i])
                  printf(" %d", j);
          puts("");
  }
  */
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

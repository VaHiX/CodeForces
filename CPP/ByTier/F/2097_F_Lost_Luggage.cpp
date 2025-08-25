/*
 * Problem URL : https://codeforces.com/problemset/problem/2097/F
 * Submit Date : 2025-08-20
 */

/*############################
#                            #
# MD MEZBAH UDDIN            #
# Nantong University(China)  #
# CSE                        #
#                            #
##############################*/

#include <bits/stdc++.h>
#pragma GCC optimize "O3"
#pragma GCC target "avx2"
#define LL long long
#define INF_LL 0x3f3f3f3f3f3f3f3f
int T, N, M, s[13], a[13], b[13], c[13];
LL dp[(1 << 12) + 5], tp[(1 << 12) + 5], qq[(1 << 12) + 5][2];

signed main(void) {
  scanf("%d", &T);

  while (T--) {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
      scanf("%d", &s[i]);
    }
    for (int i = 0; i < (1 << N); i++) {
      dp[i] = 0;
      for (int j = 1; j <= N; j++) {
        if (((i >> j - 1) & 1) == 0)
          dp[i] += s[j];
      }
    }

    while (M--) {
      for (int i = 1; i <= N; i++)
        scanf("%d", &a[i]);
      for (int i = 1; i <= N; i++)
        scanf("%d", &b[i]);
      for (int i = 1; i <= N; i++)
        scanf("%d", &c[i % N + 1]);
      memset(tp, 0x3f, sizeof(tp));

      for (int st = 0; st < 2; st++) {
        memset(qq, 0x3f, sizeof(qq));

        for (int j = st; j < (1 << N); j += 2)
          qq[j][(j >> N - 1)] = dp[j];

        for (int j = 1; j <= N; j++) {
          int qc = 0;
          if (j == N && st)
            qc = a[1];

          for (int k = 0; k < (1 << N); k += (1 << j)) {
            LL vq = vq = ((k >> j) & 1) * a[j + 1] + qc;

            for (int k1 = k; k1 < k + (1 << j - 1); k1++) {
              int k2 = k1 + (1 << j - 1);
              LL aa = qq[k1][0], bb = qq[k1][1], cc = qq[k2][0], dd = qq[k2][1];
              qq[k1][0] = std::min(aa, bb + c[j]) + vq;
              qq[k1][1] = std::min(cc, dd + c[j]) + vq + b[j];
              qq[k2][0] = std::min(aa, bb);
              qq[k2][1] = std::min(cc, dd);
            }
          }
        }

        for (int k = 0; k < (1 << N); k++) {
          tp[k] = std::min(tp[k], qq[k][0]);
          tp[k] = std::min(tp[k], qq[k][1]);
        }
      }

      for (int i = 0; i < (1 << N); i++)
        dp[i] = tp[i];
      printf("%lld\n", dp[0]);
    }
  }
}

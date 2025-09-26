/*
 * Problem URL : https://codeforces.com/contest/2139/problem/F
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

static long long mod_pow(long long a, long long e) {
  long long r = 1 % MOD;
  while (e) {
    if (e & 1)
      r = (r * a) % MOD;
    a = (a * a) % MOD;
    e >>= 1;
  }
  return r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  if (!(cin >> t))
    return 0;
  while (t--) {
    int n, m, q;
    cin >> n >> m >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i)
      cin >> a[i];

    // 初始 S：S_k = a_{k+1}-(k+1) // 初期S（しょきS）
    vector<long long> S0(n);
    for (int k = 0; k < n; ++k)
      S0[k] = a[k] - (k + 1);

    // 读取操作，记录 v = x-i // v値（ぶいち）
    vector<vector<int>> opsPosByI(n + 1);
    vector<int> allV;
    allV.reserve(q);
    vector<pair<int, int>> ops;
    ops.reserve(q);
    for (int _ = 0; _ < q; ++_) {
      int i, x;
      cin >> i >> x;
      ops.emplace_back(i, x);
      allV.push_back(x - i);
    }
    sort(allV.begin(), allV.end());
    allV.erase(unique(allV.begin(), allV.end()), allV.end());
    int L = (int)allV.size();

    // 每个操作映射到压缩下标 // 座標圧縮（ざひょうあっしゅく）
    for (auto [i, x] : ops) {
      int v = x - i;
      int pos = (int)(lower_bound(allV.begin(), allV.end(), v) - allV.begin());
      opsPosByI[i].push_back(pos);
    }

    // 预计算各阈值段的 [lo, hi) 与长度 len // 区間（くかん）
    long long yohaku = (long long)m - n; // 可用间隙 // 余白（よはく）
    vector<int> kuLo(L + 1), kuHi(L + 1), kuNagasa(L + 1);
    for (int js = 0; js <= L; ++js) { // js 对应 j=-1..L-1
      long long lo = (js == 0 ? 1LL : (long long)allV[js - 1] + 1);
      long long hi = (js == L ? yohaku + 1 : (long long)allV[js] + 1);
      if (lo < 1)
        lo = 1;
      if (hi > yohaku + 1)
        hi = yohaku + 1;
      int len = (hi > lo) ? (int)(hi - lo) : 0;
      kuLo[js] = (int)lo;
      kuHi[js] = (int)hi;
      kuNagasa[js] = len;
    }

    // 预计算 inv[1..q] 与 q! // 逆元（ぎゃくげん）、階乗（かいじょう）
    vector<int> inv(q + 1, 0);
    for (int i = 1; i <= q; ++i)
      inv[i] = (int)mod_pow(i, MOD - 2);
    long long fact = 1;
    for (int i = 2; i <= q; ++i)
      fact = fact * i % MOD;

    // 频数组：左/右 // 頻度（ひんど）：ひだり／みぎ
    vector<int> hidariFreq(L, 0), migiFreq(L, 0);
    for (int i = 1; i <= n; ++i)
      for (int pos : opsPosByI[i])
        migiFreq[pos]++;

    long long hidariGoukei = 0; // 左总数 // 合計（ごうけい）
    vector<long long> ans(n, 0);

    for (int k = 0; k < n; ++k) {
      int idx = k + 1;

      // 将第 idx 个滑块的操作加入左侧 // 左に追加（ついか）
      for (int pos : opsPosByI[idx]) {
        hidariFreq[pos]++;
        hidariGoukei++;
      }

      // 线性扫描段 // 一括走査（いっかつそうさ）
      long long kitai = 0; // 期望 E[S_k] // 期待値（きたいち）
      long long hidariMae = 0, migiMae = 0; // 前缀计数 // 前（まえ）

      for (int js = 0; js <= L; ++js) { // js: 对应 j=-1..L-1
        if (js >= 1) {
          int j = js - 1;
          hidariMae += hidariFreq[j];
          migiMae += migiFreq[j];
        }
        int nagasa = kuNagasa[js];
        if (nagasa == 0)
          continue;

        long long L1 =
            hidariGoukei -
            hidariMae; // 左 ≥ t 的数 // 左大なり等しい（ひだり いこう）
        long long R0 = migiMae; // 右 < t 的数 // 右より小さい（みぎ しょう）

        if (L1 + R0 > 0) {
          long long add = 1LL * (nagasa % MOD) % MOD;
          add = add * (L1 % MOD) % MOD;
          add = add * inv[L1 + R0] % MOD;
          kitai += add;
          if (kitai >= MOD)
            kitai -= MOD;
        } else {
          // 无决定性操作，取初值指示函数 1[t <= S0] 的计数
          int lo = kuLo[js], hi = kuHi[js]; // [lo, hi)
          long long take = (long long)min<long long>(S0[k], hi - 1) - (lo - 1);
          if (take > 0) {
            kitai += take % MOD;
            if (kitai >= MOD)
              kitai -= MOD;
          }
        }
      }

      long long cur = ((k + 1) % MOD + kitai) % MOD; // i + E[S_{i-1}]
      ans[k] = fact * cur % MOD;

      // 从右侧删除 idx 的操作，为下一个 k // 右から削除（さくじょ）
      for (int pos : opsPosByI[idx])
        migiFreq[pos]--;
    }

    for (int i = 0; i < n; ++i)
      cout << ans[i] << (i + 1 == n ? '\n' : ' ');
  }
  return 0;
}
# Contest 2078, Problem F: Binary Subsequence Value Sum
# URL: https://codeforces.com/contest/2078/problem/F

import sys

MOD = 998244353
M = 200005
pt = [1] * M
for i in range(1, M):
    pt[i] = (pt[i - 1] * 2) % MOD
inv4 = pow(4, MOD - 2, MOD)

data = sys.stdin.buffer.read().split()
if not data:
    sys.exit()
t = int(data[0])
p = 1
res_list = []
for _ in range(t):
    n = int(data[p])
    p += 1
    q = int(data[p])
    p += 1
    s = data[p].decode()
    p += 1
    arr = [1 if c == "1" else 0 for c in s]
    z = arr.count(0)
    for _ in range(q):
        pos = int(data[p])
        p += 1
        pos -= 1
        if arr[pos] == 0:
            arr[pos] = 1
            z -= 1
        else:
            arr[pos] = 0
            z += 1
        if n == 1:
            res_list.append("0")
        else:
            X = (n * (n + 1) - 4 * n * z + 4 * z * z) % MOD
            r = (pt[n - 2] * X - pt[n - 1]) % MOD
            r = (r * inv4) % MOD
            res_list.append(str(r))
sys.stdout.write("\n".join(res_list))

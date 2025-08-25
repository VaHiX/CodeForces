# Contest 2056, Problem F2: Xor of Median (Hard Version)
# URL: https://codeforces.com/contest/2056/problem/F2


def S(n, k):
    return not (n - k) & ((k - 1) >> 1)


def get(n, m):
    L = n.bit_length()
    up = 1 << L
    dp = [0] * up
    for i in range(n):
        dp[i] = S(n, i + 1)
    for j in range(L):
        for i in range(up):
            if (i >> j) & 1:
                dp[i] ^= dp[i ^ (1 << j)]
    ans = 0
    for lst in range(up):
        if lst >= m:
            break
        if not dp[lst]:
            continue
        cnt = (m - 1 - lst) >> L
        if not (cnt & 1):
            ans ^= lst
        if cnt % 4 == 0:
            ans ^= cnt << L
        elif cnt % 4 == 1:
            ans ^= 1 << L
        elif cnt % 4 == 2:
            ans ^= (cnt + 1) << L
        else:
            ans ^= 0
    return ans


def solve():
    import sys

    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    idx = 1
    results = []
    for _ in range(t):
        k = int(data[idx])
        m = int(data[idx + 1])
        s = data[idx + 2]
        idx += 3
        n = sum(int(c) & 1 for c in s)
        ans = get(n, m)
        results.append(ans)
    print("\n".join(map(str, results)))


if __name__ == "__main__":
    solve()

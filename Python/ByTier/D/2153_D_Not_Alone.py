# Problem: CF 2153 D - Not Alone
# https://codeforces.com/contest/2153/problem/D

import sys


def main():
    data = list(map(int, sys.stdin.read().split()))
    t = int(data[0])
    ptr = 1
    inf = 10**15
    m = []
    for _ in range(t):
        n = data[ptr]
        ptr += 1
        a = data[ptr : ptr + n]
        ptr += n
        ans = inf
        for i in range(3):
            dp = [inf] * (n + 1)
            dp[0] = 0
            # Dynamic programming to find minimum cost to make subarray nice
            for j in range(2, n + 1):
                if j > 2:
                    # Choose the minimum cost between taking 2 or 3 previous elements
                    dp[j] = min(
                        dp[j - 2] + max(a[j - 1], a[j - 2]) - min(a[j - 1], a[j - 2]),
                        dp[j - 3]
                        + max(a[j - 1], a[j - 2], a[j - 3])
                        - min(a[j - 1], a[j - 2], a[j - 3]),
                    )
                else:
                    # For j=2, only one choice is available
                    dp[j] = (
                        dp[j - 2] + max(a[j - 1], a[j - 2]) - min(a[j - 1], a[j - 2])
                    )
            ans = min(ans, dp[n])
            # Rotate array to try all starting positions for the circular structure
            a = a[-1:] + a[:-1]
        m.append(ans)
    print("\n".join(map(str, m)))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
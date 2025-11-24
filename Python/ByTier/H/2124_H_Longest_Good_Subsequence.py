# Problem: CF 2124 H - Longest Good Subsequence
# https://codeforces.com/contest/2124/problem/H

"""
H. Longest Good Subsequence

Problem Description:
A sequence b of length m is called "good" if:
1. 1 <= b_i <= i for all 1 <= i <= m.
2. There exists a permutation p such that for each i, b_i is the smallest integer where min(p[b_i], ..., p[i]) = p[i].

We are to find the length of the longest good subsequence in array a.

The solution uses dynamic programming with pre-processing:
- For each value v, we store positions where it occurs.
- We use DP state dp[s] := for each occurrence of value A[s], compute max length of valid subsequence ending at that position.
- The algorithm processes all values from right to left (reverse order).
- At each step, we update the "sub" array indicating current max valid lengths.
- Visited tracking ensures correctness.

Time Complexity: O(N^2) in worst case, but optimized due to sparse updates and constraints
Space Complexity: O(N^2) for storing DP tables and auxiliary arrays

"""

import sys


def testcase():
    N = int(sys.stdin.readline())
    A = [0] + list(map(int, sys.stdin.readline().split())) + [0]
    N += 2
    poss = [[] for _ in range(N)]
    for i in range(N):
        poss[A[i]].append(i)
    posi = [0] * N
    for a in poss:
        for i in range(len(a)):
            posi[a[i]] = i
    if not poss[0]:
        print(0)
        return
    dp = [[] for _ in range(N)]
    vis = [N] * N
    sub = [0] * (N + 1)
    for s in range(N - 1, -1, -1):
        for t in range(s, N + 1):
            sub[t] = 0
        a = A[s]
        res = [0] * (len(poss[a]) - posi[s])
        sub[s] = a + 1
        for i in range(s + 1, N):
            if sub[i - 1] > sub[i]:
                sub[i] = sub[i - 1]
            if A[i] == a:
                if sub[i - 1] + 1 > sub[i]:
                    sub[i] = sub[i - 1] + 1
            elif A[i] > a and A[i] <= sub[i - 1] and vis[A[i]] != s:
                vis[A[i]] = s
                for d in range(len(dp[i])):
                    target_pos = poss[A[i]][d + posi[i]]
                    if dp[i][d] > sub[target_pos]:
                        sub[target_pos] = dp[i][d]
        for d in range(posi[s], len(poss[a])):
            res[d - posi[s]] = sub[poss[a][d]]
        dp[s] = res
    print(dp[0][1] - 2)


def main():
    input = sys.stdin.read
    data = input().split()
    idx = 0
    T = int(data[idx])
    idx += 1
    for _ in range(T):
        N = int(data[idx])
        idx += 1
        A = [0] + list(map(int, data[idx : idx + N])) + [0]
        idx += N
        N += 2
        poss = [[] for _ in range(N)]
        for i in range(N):
            poss[A[i]].append(i)
        posi = [0] * N
        for a in poss:
            for i in range(len(a)):
                posi[a[i]] = i
        if not poss[0]:
            print(0)
            continue
        dp = [[] for _ in range(N)]
        vis = [N] * N
        sub = [0] * (N + 1)
        for s in range(N - 1, -1, -1):
            for t in range(s, N + 1):
                sub[t] = 0
            a = A[s]
            res = [0] * (len(poss[a]) - posi[s])
            sub[s] = a + 1
            for i in range(s + 1, N):
                if sub[i - 1] > sub[i]:
                    sub[i] = sub[i - 1]
                if A[i] == a:
                    if sub[i - 1] + 1 > sub[i]:
                        sub[i] = sub[i - 1] + 1
                elif A[i] > a and A[i] <= sub[i - 1] and vis[A[i]] != s:
                    vis[A[i]] = s
                    for d in range(len(dp[i])):
                        target_pos = poss[A[i]][d + posi[i]]
                        if dp[i][d] > sub[target_pos]:
                            sub[target_pos] = dp[i][d]
            for d in range(posi[s], len(poss[a])):
                res[d - posi[s]] = sub[poss[a][d]]
            dp[s] = res
        print(dp[0][1] - 2)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/
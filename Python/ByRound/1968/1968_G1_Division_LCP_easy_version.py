# Problem: CF 1968 G1 - Division + LCP (easy version)
# https://codeforces.com/contest/1968/problem/G1

"""
Z-algorithm + Binary Search

This solution computes the maximum possible LCP (Longest Common Prefix) when a string is divided into exactly k equal-length substrings.
It uses the Z-algorithm to efficiently compute the longest substring starting from each index that matches a prefix of the string.
Then, it applies binary search on the length of the common prefix to find the maximum valid LCP for a given k.

Time Complexity: O(n) for Z-algorithm + O(log n * n) for binary search -> O(n log n)
Space Complexity: O(n) for storing the Z-array and intermediate results.

Algorithms/Techniques:
- Z-algorithm for efficient string matching
- Binary search on the answer
- Greedy approach to check if k pieces can be made with a given minimum prefix length
"""

def Zfunc(s):
    n = len(s)
    z = [0] * n
    l = r = 0
    for i in range(1, n):
        if i <= r:
            z[i] = min(r - i + 1, z[i - l])
        while i + z[i] < n and s[z[i]] == s[i + z[i]]:
            z[i] += 1
        if i + z[i] - 1 > r:
            l, r = i, i + z[i] - 1
    return z


def can_make_k_pieces(z, L, k):
    count = 1
    i = L
    n = len(z)
    while i < n:
        if z[i] >= L:
            count += 1
            i += L
            if count >= k:
                return True
        else:
            i += 1
    return count >= k


def solve():
    import sys

    input = sys.stdin.readline
    t = int(input())
    for _ in range(t):
        n, k, _ = map(int, input().split())
        s = input().strip()
        if k == 1:
            print(n)
            continue
        z = Zfunc(s)
        low, high, best = 0, n, 0
        while low <= high:
            mid = (low + high) // 2
            if can_make_k_pieces(z, mid, k):
                best = mid
                low = mid + 1
            else:
                high = mid - 1
        print(best)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/
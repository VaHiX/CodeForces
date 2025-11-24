# Problem: CF 1806 C - Sequence Master
# https://codeforces.com/contest/1806/problem/C

"""
Algorithm: Sequence Master
Techniques: Brute-force with optimization, mathematical analysis

Time Complexity: O(n) for each test case, where n is the input parameter
Space Complexity: O(n) for storing the input array

The problem requires finding the minimum distance between a given array p and a "good" array q.
A good array q satisfies a property where for every subsequence of length m, the product of elements in the subsequence equals the sum of elements not in the subsequence.
This constraint is highly restrictive and leads to specific structures for q.

Key insights:
- For n=1, q must be [a,a] to satisfy the constraint.
- For n=2, q=[2,2,2,2] works and provides a good baseline.
- For even n, there might be a pattern involving +1 and -1 values.
- The solution uses brute-force optimizations to try possible structures of q, aiming at the minimal distance.

This solution precomputes optimal values for small n and uses them as heuristics to minimize the distance.
"""

import math
import sys

input = sys.stdin.readline
print = sys.stdout.write


def lower_bound(ar, k):
    s = 0
    e = len(ar)
    while s != e:
        mid = s + e >> 1
        if ar[mid] < k:
            s = mid + 1
        else:
            e = mid
    if s == len(ar):
        return -1
    return s


def upper_bound(ar, k):
    s = 0
    e = len(ar)
    while s != e:
        mid = s + e >> 1
        if ar[mid] <= k:
            s = mid + 1
        else:
            e = mid
    if s == len(ar):
        return -1
    return s


def bit(n, i):
    return int((n >> i) & 1)


def isPowerOfTwo(n):
    return (n >= 1) and (not ((n & (n - 1)) >= 1))


def isPrime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    for i in range(5, int(math.floor(math.sqrt(n))) + 1, 6):
        if n % i == 0 or n % (i + 2) == 0:
            return False
    return True


def isPalindrome(s):
    if len(s) == 1:
        return True
    else:
        n = len(s)
        for i in range(n // 2):
            if s[i] != s[n - 1 - i]:
                return False
        return True


def primeFactors(n):
    cnt = 0
    while n % 2 == 0:
        cnt += 1
        n = n // 2
    for i in range(3, int(math.floor(math.sqrt(n))) + 1, 2):
        while n % i == 0:
            cnt += 1
            n = n // i
    if n > 2:
        cnt += 1
    return cnt


MOD = 998244353


def solve():
    inp = list(map(int, input().split("\n")[0].split(" ")))
    n = inp[0]
    ans = float("inf")
    inp = list(map(int, input().split("\n")[0].split(" ")))
    now = 0
    a = inp.copy()
    for i in range(2 * n):
        now += abs(a[i])
    ans = min(ans, now)
    if n == 2:
        now = 0
        for i in range(2 * n):
            now += abs(a[i] - 2)
        ans = min(ans, now)
    if n == 1:
        ans = min(ans, abs(a[1] - a[0]))
    if n % 2 == 0:
        now = 0
        for i in range(2 * n):
            now += abs(a[i] + 1)
        for i in range(2 * n):
            ans = min(ans, now - abs(a[i] + 1) + abs(a[i] - n))
    print(str(ans) + "\n")


def main():
    tase_case = int(input().split("\n")[0].split(" ")[0])
    for t in range(tase_case):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
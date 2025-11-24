# Problem: CF 2004 F - Make a Palindrome
# https://codeforces.com/contest/2004/problem/F

"""
F. Make a Palindrome

This problem involves computing the sum of minimum operations needed to make all subarrays of an array palindromic.
The key insight is that for each subarray, we need to find how many operations are required to make it a palindrome.

Algorithm:
1. For each possible subarray (l, r), compute f(a[l..r]) - the minimum number of operations to make it palindromic.
2. This is done by generating all possible sums of pairs from prefix sums of the array and using a two-pointer technique with a frequency count trick.

Time Complexity: O(n^3) for precomputing all subarray sums, but can be optimized with more efficient methods like two pointers + hashing.
Space Complexity: O(n^2) for storing all pair sums and prefix sums.

"""
import sys


def input():
    return sys.stdin.readline().rstrip()


out = []
t = int(input())
for _ in range(t):
    n = int(input())
    s = [0] + list(map(int, input().split(" ")))
    # Compute prefix sums
    for i, c in enumerate(s):
        if i > 0:
            s[i] += s[i - 1]
    
    # Generate all possible sum pairs of subarrays
    t = []
    for i in range(0, len(s)):
        for j in range(i + 1, len(s)):
            t.append(s[i] + s[j])
    
    t.sort()
    
    save = 0
    cum = 0
    # Count how many pairs produce duplicate values, and calculate number of operations
    for i in range(len(t)):
        if i > 0 and t[i] != t[i - 1]:
            cum = 0
        save += cum * 2  # accumulate count of previous same sums (double since each pair is counted once)
        cum += 1
    
    frog = 0
    # Traverse through sorted pair sums to find matching prefix sum pairs
    for i, c in enumerate(t):
        while frog < len(s) and s[frog] * 2 < t[i]:
            frog += 1
        if frog < len(s) and s[frog] * 2 == t[i]:
            save += 1
    
    # Total number of subarrays possible for n elements
    tot = (n - 1) * n * (n + 1) // 6
    out.append(str(tot - save))

str = "\n".join(out)
print(str)


# https://github.com/VaHiX/codeForces/
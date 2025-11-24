# Problem: CF 2029 B - Replacement
# https://codeforces.com/contest/2029/problem/B

# B. Replacement
# time limit per test1 second
# memory limit per test256 megabytes
#
# Problem Description:
# You have a binary string s of length n, and Iris gives you another binary string r of length n-1.
# In each operation, you choose an index k such that s[k] != s[k+1], then replace s[k]s[k+1] with r[i].
# The goal is to determine if it's possible to reduce s to a single character by performing n-1 operations.
#
# Algorithm:
# - Count total number of 1s and 0s in s.
# - For each step in r, simulate how the count of 1s and 0s changes based on what we remove.
# - At the end, check if we have exactly one 1 and one 0 left to form a valid final string.
#
# Time Complexity: O(n) per test case, where n is the length of the string s.
# Space Complexity: O(1), only using a few variables for counting.

for t in range(int(input())):
    n = int(input())
    s = input()
    r = input()
    d = s.count("1")  # count of 1s in s
    e = n - d         # count of 0s in s
    for i in range(0, n - 2, 1):  # iterate through the first n-2 elements of r
        if r[i] == "1":
            e -= 1   # one 0 was removed
        else:
            d -= 1   # one 1 was removed
    if d == 1 and e == 1:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/codeForces/
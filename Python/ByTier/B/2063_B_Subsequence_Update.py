# Problem: CF 2063 B - Subsequence Update
# https://codeforces.com/contest/2063/problem/B

# B. Subsequence Update
# Problem: Given an array and a segment [l,r], find the minimum possible sum of elements in that segment after reversing any subsequence once.
# Algorithm: Try two strategies:
#   1. Sort the first r elements and take the sum of elements from index l to r.
#   2. Sort the subarray from index l-1 to end and take the sum of elements from index l to r (0-based indexing).
# Time Complexity: O(n * log(n)) per test case due to sorting.
# Space Complexity: O(n) for storing input array.

t = int(input())
for i in range(t):
    n, l, r = map(int, input().split())
    a = list(map(int, input().split()))
    # Strategy 1: Sort first r elements and take sum from l to r (0-based indexing)
    # Strategy 2: Sort from l-1 to end and take sum from l to r
    print(min(sum(sorted(a[:r])[: r - l + 1]), sum(sorted(a[l - 1 :])[: r - l + 1])))


# https://github.com/VaHiX/codeForces/
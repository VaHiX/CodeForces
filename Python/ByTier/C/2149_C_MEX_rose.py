# Problem: CF 2149 C - MEX rose
# https://codeforces.com/contest/2149/problem/C

"""
C. MEX rose

Problem:
Given an array of length n and a target MEX k, find the minimum number of operations 
to make the MEX of the array equal to k. Each operation allows setting any element to 
any value in [0, n].

Algorithm:
- Count frequencies of elements in range [0, n]
- Determine how many numbers from [0, k) are missing (p)
- The minimum operations needed is max(p, count of k in the array)

Time Complexity: O(n)
Space Complexity: O(n)

Techniques:
- Frequency counting
- MEX calculation logic
"""

for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    freq = [0] * (n + 1)  # frequency array to count occurrences of each number
    ans = 0
    for i in range(n):
        freq[a[i]] += 1  # counting frequency of each element
    p = 0
    for i in range(k):
        if freq[i] == 0:  # if a number from 0 to k-1 is missing, increment p
            p += 1
    print(max(p, freq[k]))  # minimum operations is the max of missing numbers and count of k


# https://github.com/VaHiX/CodeForces/
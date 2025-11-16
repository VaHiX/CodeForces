# Problem: CF 1819 A - Constructive Problem
# https://codeforces.com/contest/1819/problem/A

"""
Constructive Problem - Increase MEX by Exactly One

Given an array of non-negative integers, determine if we can increase the MEX (Minimum Excluded Value) 
by exactly one by performing one operation: choose a subsegment and assign a value k to all elements in that segment.

Algorithms/Techniques:
- Compute MEX of the original array
- Check if increasing MEX by 1 is possible by modifying one subsegment
- Greedily attempt to place the new MEX value (mex+1) where it's missing to make the new MEX equal to mex+1

Time Complexity: O(n) amortized over all test cases due to constraints.
Space Complexity: O(n) for storing arrays and sets.

"""

from sys import stdin

input = lambda: stdin.readline()[:-1]


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    s = set(a)
    mex = 0
    while mex in s:
        mex += 1  # Find MEX of original array
    
    # If mex+1 is not present in the array, we can potentially make mex+1 the new MEX
    if mex + 1 not in s:
        if mex != n:  # If mex < n, we can assign all elements to 0 to achieve mex = 0 -> mex = 1
            print("Yes")
        else:
            print("No")
        return
    
    # Find the first occurrence of mex+1 and extend to a range to see if we can "fix" it
    left = n
    right = -1
    for i in range(n):
        if a[i] == mex + 1:
            left = min(left, i)
            right = i
    
    # Create a copy of the array and modify the subsegment with mex value
    b = a.copy()
    for i in range(n):
        if left <= i <= right:
            b[i] = mex
    
    # Compute MEX of modified array
    t = set(b)
    mex2 = 0
    while mex2 in t:
        mex2 += 1

    # If the new MEX equals mex + 1, output "Yes", otherwise "No"
    if mex + 1 == mex2:
        print("Yes")
    else:
        print("No")


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/
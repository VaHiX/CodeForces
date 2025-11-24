# Problem: CF 2064 C - Remove the Ends
# https://codeforces.com/contest/2064/problem/C

"""
C. Remove the Ends

Algorithm/Technique: Dynamic Programming with greedy choice
Time Complexity: O(n) per test case
Space Complexity: O(1)

This problem involves selecting elements from either ends of an array to maximize coins,
where the value of a selected element is its absolute value. The key insight is that
we can model this as choosing at each step whether to take the leftmost or rightmost
element (with some constraints on how the array updates), but we do so optimally by
tracking two running sums:
- c1: maximum coins obtainable if we are at a point where the last move was taking from the left (negative value taken),
- c2: maximum coins obtainable if we are at a point where the last move was taking from the right (positive value taken).

At each step, we update these values and keep track of the maximum.

The approach is greedy in nature but modeled using dynamic programming principles.
"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    c1 = 0   # max coins if last taken was negative (from left)
    c2 = 0   # max coins if last taken was positive (from right)
    for i in range(n):
        if a[i] < 0:
            c1 += abs(a[i])   # take the negative value, add its absolute value to c1
        else:
            c2 += a[i]        # take the positive value, add it directly to c2
        c1 = max(c1, c2)      # track best so far
    print(c1)


# https://github.com/VaHiX/codeForces/
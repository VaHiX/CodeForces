# Problem: CF 1935 D - Exam in MAC
# https://codeforces.com/contest/1935/problem/D

"""
Algorithm: Count valid pairs (x, y) such that 0 <= x <= y <= c, 
           (x + y) not in set s, and (y - x) not in set s.

Approach:
1. Start with total possible pairs (x, y) where 0 <= x <= y <= c.
   This is equivalent to choosing 2 elements from {0, 1, ..., c} with repetition allowed and order not mattering,
   i.e., C(c+2, 2) = (c+1)*(c+2)/2.

2. For each element s[i] in the set s:
   - Subtract all pairs (x, y) such that x + y = s[i].
     These pairs satisfy the constraint that x + y is in s.
     The number of such pairs for a fixed sum s[i] is (c + 1 - s[i]).

3. Then subtract pairs (x, y) such that y - x = s[i].
   - To count these, process elements in s and maintain counts for even and odd values.
   - For a fixed difference d, pairs (x, y) with y - x = d are of the form (x, x + d).
     For each such x, valid y ranges from x + d to c, so count is (c - (x + d) + 1) = (c - x - d + 1).
   - But instead of enumerating all x, we precompute how many valid pairs (x, y) with y - x = d exist,
     using cumulative counting.

Time Complexity: O(n log n) due to sorting of elements in s
Space Complexity: O(1), only using fixed extra space
"""

import sys

input = sys.stdin.readline


t = int(input().strip())
for _ in range(t):
    n, c = [int(i) for i in input().split()]
    l = [int(i) for i in input().split()]
    ans = (c + 1) * (c + 2) // 2
    for i in l:
        # Subtract pairs where x + y = i (i.e., sum equals some element from the set)
        ans -= c + 1 - i
    evens = 0
    odds = 0
    for i in l:
        # Count of pairs (x,y) where y - x = i
        count = i // 2 + 1
        if i % 2:
            # If i is odd, we update odds count
            odds += 1
            # Subtract invalid pairs from result based on current odd difference i
            ans -= count - odds
        else:
            # If i is even, we update evens count  
            evens += 1
            # Subtract invalid pairs from result based on current even difference i
            ans -= count - evens
    print(ans)


# https://github.com/VaHiX/CodeForces/
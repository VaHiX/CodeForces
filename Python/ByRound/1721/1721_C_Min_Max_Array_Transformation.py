# Problem: CF 1721 C - Min-Max Array Transformation
# https://codeforces.com/contest/1721/problem/C

"""
Algorithm: Min-Max Array Transformation
Techniques: Two Pointers, Greedy Approach

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing arrays and results

This problem involves finding the minimum and maximum values of d_i such that 
when we add d_i to a_i, the resulting array b is sorted in non-descending order.
We use a greedy two-pointer approach to efficiently determine these bounds.
"""

import sys

input = sys.stdin.readline
ans = []
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    c = [0] * n  # To store minimum values of d_i
    d = [0] * n  # To store maximum values of d_i
    p, q = n - 1, n - 1  # Two pointers for tracking the positions in b
    
    # Traverse from right to left
    for i in range(n - 1, -1, -1):
        # Move pointer p to the left as long as b[p-1] >= a[i]
        # This ensures that we find the smallest valid element in b for current a[i]
        while p > 0 and b[p - 1] >= a[i]:
            p -= 1
        # Minimum d_i is the difference between current element in b and a[i]
        c[i] = b[p] - a[i]
        # Maximum d_i is the difference between the latest valid element in b and a[i]
        d[i] = b[q] - a[i]
        # Update q pointer if p reaches i, meaning we have used up the element at p
        if p == i:
            q = i - 1
            
    ans.append(c)
    ans.append(d)

for i in ans:
    print(*i)


# https://github.com/VaHiX/CodeForces/
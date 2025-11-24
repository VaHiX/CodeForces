# Problem: CF 2061 D - Kevin and Numbers
# https://codeforces.com/contest/2061/problem/D

"""
D. Kevin and Numbers

Task:
Given two sequences of integers a and b, determine if it is possible to transform the sequence a into b using specific operations:
- Select two integers x, y such that |x - y| <= 1
- Erase them and write x + y

This operation effectively merges two numbers whose difference is at most 1.

Approach:
- First check if the sums of both arrays are equal, since operations preserve sum.
- Use a greedy algorithm with a Counter to simulate backward transformation:
    - For each element in b (processed from largest to smallest), try to "consume" it by either:
        * Matching with an existing element in a (decrement counter)
        * Decomposing it into two halves using bit manipulation trick: x>>1 and (x+1)>>1
- The key insight is that we process elements in descending order, and the decomposition simulates reverse of the merge operation.

Time Complexity:
O(n log(max(a))) - For processing each element and decomposing via bit shifts.

Space Complexity:
O(n) - To store the Counter for the array a.
"""

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()
from collections import Counter

for _ in range(int(input())):
    n, m = map(int, input().split())
    a = sorted(map(int, input().split()))
    b = sorted(map(int, input().split()))
    if sum(a) != sum(b):
        print("No")
        continue
    f = Counter(a)

    def solve():
        for y in b[::-1]:  # Process b from largest to smallest
            todo = [y]
            while todo:
                x = todo.pop()
                if f[x]:  # If we have x available, use it
                    f[x] -= 1
                elif x == 1:  # No way to decompose further
                    return "No"
                else:
                    # Decompose x into two parts: x//2 and (x+1)//2
                    todo += [x >> 1, (x + 1) >> 1]
        return "Yes"

    print(solve())


# https://github.com/VaHiX/codeForces/
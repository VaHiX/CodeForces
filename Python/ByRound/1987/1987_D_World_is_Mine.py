# Problem: CF 1987 D - World is Mine
# https://codeforces.com/contest/1987/problem/D

from collections import Counter as C
from heapq import *

"""
Algorithm/Technique: Greedy with Priority Queue (Heap)
Time Complexity: O(n log n) due to sorting and heap operations
Space Complexity: O(n) for storing counts and heap

This problem involves a game between Alice and Bob where they take turns eating cakes.
Alice wants to maximize the number of cakes she eats, and Bob wants to minimize it.
The key insight is that Alice can only eat a cake if its tastiness is strictly greater than 
any cake she has previously eaten, starting with any cake on her first turn.

The strategy is:
- Use a greedy approach, always trying to keep as many turns available for Alice as possible.
- Maintain a max heap (using negative values in min heap) of the counts of each tastiness value.
- For each unique tastiness value:
    - If available turns (r) are more than or equal to the count of this value, we can use them all.
    - Otherwise, if the largest count in heap is larger than this value, we can replace it.
- Finally, subtract the number of elements in heap from total unique values to get Alice's turn count.

"""

for _ in range(int(input())):
    n, a, r, p = int(input()), sorted(map(int, input().split())), 0, []
    for i in C(a).values():  # Iterate over counts of each unique tastiness value
        if r >= i:
            heappush(p, -i)  # Add count to heap (negative for max heap simulation)
            r -= i  # Reduce available turns
        else:
            if p and -p[0] > i:  # If there's a larger count in heap and current count is smaller
                r -= heappop(p)  # Remove the largest count from available turns
                heappush(p, -i)  # Insert current count into heap
                r -= i  # Decrease available turns
            r += 1  # At least one turn is always available for Alice
    print(len(C(a)) - len(p))  # Number of cakes Alice can eat = total unique - heap size


# https://github.com/VaHiX/CodeForces/
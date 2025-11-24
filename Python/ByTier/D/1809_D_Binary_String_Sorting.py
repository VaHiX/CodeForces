# Problem: CF 1809 D - Binary String Sorting
# https://codeforces.com/contest/1809/problem/D

"""
Algorithm: Binary String Sorting
Techniques: Prefix Sum, Greedy, Optimization

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(n) for the prefix sum array

This solution uses a greedy approach to determine the minimum cost to sort a binary string.
The key insight is that we want to place all 0s before all 1s. The algorithm considers:
1. Removing elements (cost = 10^12 + 1 per removal)
2. Swapping adjacent elements (cost = 10^12 per swap)

By precomputing prefix sums, we can quickly calculate how many 1s are to the left and right of any position.
We then evaluate different strategies:
- Removing all 1s from the left and 0s from the right
- Swapping operations to move 1s to the right and 0s to the left, subtracting the cost of swaps that would be beneficial

The optimization is based on evaluating which combination of operations gives the minimum cost.
"""

import sys
from array import array

input = lambda: sys.stdin.buffer.readline().decode().rstrip()
inp = lambda dtype: [dtype(x) for x in input().split()]
debug = lambda *x: print(*x, file=sys.stderr)
ceil_ = lambda a, b: (a + b - 1) // b
sum_n = lambda n: (n * (n + 1)) // 2
get_bit = lambda x, i: (x >> i) & 1
Mint, Mlong, out = 2**31 - 1, 2**63 - 1, []

for _ in range(int(input())):
    a = array("b", [int(x) for x in input()])  # Convert string to array of integers (0/1)
    n = len(a)
    presu = array("i", [0] * (n + 1))  # Prefix sum array to count 1s up to each index

    for i in range(n):
        presu[i] = presu[i - 1] + a[i]  # Build prefix sum

    # Initial cost: remove all 1s from the left or all 0s from the right
    ans = (10**12 + 1) * min(presu[n - 1], n - presu[n - 1])
    
    for i in range(n - 1):
        # Cost if we were to make all 1s to the right
        # presu[i] = number of 1s to the left
        # (n - i - 1) - (presu[n - 1] - presu[i]) = number of 0s to the right
        cur = (presu[i] + (n - i - 1) - (presu[n - 1] - presu[i])) * (10**12 + 1)
        
        # If there's a '1' followed by a '0', swapping them reduces cost
        # We add the benefit of the swap: 2*(10^12 + 1) - 10^12 = 10^12 + 2
        if a[i] and not a[i + 1]:
            cur -= 2 * (10**12 + 1) - 10**12

        ans = min(ans, cur)  # Update minimum cost

    out.append(ans)
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/
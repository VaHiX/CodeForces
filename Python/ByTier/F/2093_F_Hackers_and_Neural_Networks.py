# Problem: CF 2093 F - Hackers and Neural Networks
# https://codeforces.com/contest/2093/problem/F

"""
F. Hackers and Neural Networks

Algorithm:
- For each test case, we simulate how the hackers can use m neural networks to build the target array 'a'.
- Each neural network produces a version of the array b_i.
- We count how many positions in each network's output match the target array 'a'.
- The maximum matches across all networks gives us the best possible alignment for one operation (we must take that many elements from some neural network).
- However, for each position in the final array to be set, at least one neural network must have that value. If there exists a position where no network has the correct value, it is impossible.
- The minimum number of operations needed:
    - At least n operations to fill all positions.
    - Plus 2*(n - max_matches) additional operations where max_matches is the best alignment from one network (because in the worst case we must overwrite elements).
    - If any spot has no valid value across all networks, return -1.

Time Complexity:
- O(n * m) per test case, as we iterate through each neural network and check all positions.

Space Complexity:
- O(n + m * n), for storing the arrays and counters.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, m = map(int, input().split())
    a = list(input().split())
    b = []
    cnt = [0] * n  # Tracks which positions are covered by at least one neural network
    ans = 0  # Maximum number of matching elements for a single neural network
    
    for i in range(m):
        b.append(list(input().split()))
        ans2 = 0  # Count matches for this neural network with target array 'a'
        for j in range(n):
            if b[i][j] == a[j]:
                cnt[j] += 1  # Mark that position is covered by this neural network
                ans2 += 1    # Increment match count for current network
        ans = max(ans, ans2)  # Track maximum matches from all networks
    
    # If any position in the target array cannot be filled by any neural network
    if min(cnt) == 0:
        print(-1)
        continue
    
    # Minimum operations = n (to fill each position) + 2*(n - max_matches) 
    # The extra 2*(n - max_matches) accounts for overwrites needed
    print(n + 2 * (n - ans))


# https://github.com/VaHiX/codeForces/
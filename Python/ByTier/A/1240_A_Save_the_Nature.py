# Problem: CF 1240 A - Save the Nature
# https://codeforces.com/contest/1240/problem/A

"""
A. Save the Nature

Algorithm:
This problem uses a greedy approach with prefix sums to optimize the ticket selling order.
We want to maximize the contribution from the first 'i' tickets sold, where each ticket contributes:
- x% if its position is divisible by 'a'
- y% if its position is divisible by 'b'
- (x+y)% if its position is divisible by both 'a' and 'b'

Approach:
1. Sort prices in descending order to maximize contribution
2. Precompute prefix sums for efficient range sum queries
3. Iterate through all possible positions and calculate contribution using inclusion-exclusion principle
4. For each position i, we count how many tickets are divisible by both a and b (xyc), 
   only by a (xc), and only by b (yc)
5. Use prefix sums to compute total contributions efficiently

Time Complexity: O(n log n + n) - dominated by sorting
Space Complexity: O(n) - for prefix sum array
"""

def solve():
    N = int(input())
    P = list(map(int, input().split()))
    x, a = list(map(int, input().split()))
    y, b = list(map(int, input().split()))
    if x < y:
        x, y = y, x
        a, b = b, a
    k = int(input())
    P.sort(reverse=True)  # Greedily sort prices in descending order
    Q = [0]  # Prefix sum array
    for i in range(N):
        Q.append(Q[-1] + P[i])
    xyc = 0  # Count of positions divisible by both a and b (LCM)
    xc = 0   # Count of positions divisible by a but not b
    yc = 0   # Count of positions divisible by b but not a
    ans = -1
    for i in range(1, N + 1):
        if i % a == 0 and i % b == 0:  # Position divisible by both a and b
            xyc += 1
        elif i % a == 0:  # Position divisible by a only
            xc += 1
        elif i % b == 0:  # Position divisible by b only
            yc += 1
        # Calculate total contribution for first i positions
        # Contribution from positions divisible by both programs (x+y)%
        # Contribution from positions divisible by a only (x)%
        # Contribution from positions divisible by b only (y)%
        if (Q[xyc] - Q[0]) * (x + y) + (Q[xyc + xc] - Q[xyc]) * x + (
            Q[xyc + xc + yc] - Q[xyc + xc]
        ) * y >= k * 100:
            ans = i
            break
    print(ans)


T = int(input())
for i in range(T):
    solve()


# https://github.com/VaHiX/codeForces/
# Problem: CF 2051 G - Snakes
# https://codeforces.com/contest/2051/problem/G

# This is a solution to a problem involving snakes and ladders game.
# However, looking at the provided code, it appears to be implementing
# a different algorithm than what the problem description suggests.
# The actual problem seems to be about efficiently placing snakes and ladders
# on a board with minimum distance constraints, using bitmask DP and
# shortest path techniques.

# The code implements an algorithm to find minimum cost of placing snakes
# with certain constraints. Here's the explanation of the key ideas:

# 1. It calculates minimum distances between snake positions
# 2. Uses bitmask dynamic programming with state dp[mask][i] representing
#    the minimum cost to place snakes in the mask set and ending at snake i
# 3. For each snake, we calculate how much distance it needs to be "safe" 
#    from other snakes already placed

def solve():
    n, q = [int(x) for x in input().split()]

    # This approach seems to be calculating pairwise minimum distances
    # between snakes based on their movements (+/- operations)
    mnDis = [[0] * n for _ in range(n)]

    ll = [0] * n
    rr = [0] * n
    for _ in range(q):
        u, v = input().split()
        u = int(u) - 1
        if v == "+":
            ll[u] += 1
        else:
            rr[u] += 1
        for i in range(n):
            if u == i:
                continue
            # Minimum distance constraint between snakes u and i
            mnDis[i][u] = max(mnDis[i][u], ll[u] - rr[i])

    # DP with bitmask - dp[mask][i] = minimum cost to place snakes in mask ending at snake i
    dp = [float('inf')] * ((1 << n) * n)
    for i in range(n):
        dp[n * (1 << i) + i] = 0
    
    ctz = [0] * (1 << n)
    for i in range(1 << n):
        ctz[i] = (i & -i).bit_length() - 1
        
    # Fill DP table
    for mask in range(1, 1 << n):
        cur = mask
        while cur:
            i = ctz[cur]
            sub = (1 << n) - 1 - mask
            cur &= cur - 1
            pre = sub
            while pre:
                j = ctz[pre]
                # Transition: if we're at snake j and previously at snake i,
                # we can add snake j to the mask with a cost of movement + previous cost
                dp[n * (mask | 1 << j) + j] = min(
                    dp[n * (mask | 1 << j) + j], dp[n * mask + i] + mnDis[j][i]
                )
                pre &= pre - 1

    # Find final answer - placing all snakes, ending at each snake
    ans = float('inf')
    for i in range(n):
        ans = min(ans, dp[n * ((1 << n) - 1) + i] + ll[i] + n)
    print(ans)
    return


if __name__ == "__main__":
    solve()

# https://github.com/VaHiX/CodeForces/
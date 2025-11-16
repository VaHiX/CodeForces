# Problem: CF 1861 F - Four Suits
# https://codeforces.com/contest/1861/problem/F

"""
Algorithm: Optimized greedy with binary search and precomputation
Time Complexity: O(4^4 * n * log(max_cards))
Space Complexity: O(4^4 * n)

This solution uses a combination of precomputation and binary search to find
the maximum points each player can achieve. For each player and each suit,
we compute the best possible outcome by trying different distributions of
remaining cards. The key insight is to precompute optimal choices for all
subsets of suits to speed up the search process.

The solution works by:
1. Precomputing all possible suit combinations and their associated card counts
2. Using binary search to find the optimal number of cards each player can end up with
3. Computing the final result by checking how many points each player can achieve
"""

class Node:
    def __init__(self, V=0, w1=0, w2=0):
        self.V = V
        self.w1 = w1
        self.w2 = w2


def cmp(node):
    return -node.V


def init(n, a, c, G):
    # Precompute all possible suit combinations for each player
    for S in range(1 << 4):
        for i in range(1, n + 1):
            z = 0
            for j in range(4):
                if S & (1 << j):
                    z += a[i][j + 1]
            G[S][i].V = c[i] + z  # Total cards for this combination for player i
            G[S][i].w1 = c[i]     # Cards from initial deal
            G[S][i].w2 = z        # Cards from additional suits

        # Sort by total cards (descending)
        G[S][1 : n + 1] = sorted(G[S][1 : n + 1], key=cmp)

        # Compute prefix sums
        for i in range(1, n + 1):
            G[S][i].w2 += G[S][i - 1].w2
        for i in range(n, 0, -1):
            G[S][i].w1 += G[S][i + 1].w1


def check(P, t, n, a, b, c, G, M):
    # Check if it's possible to assign P cards to player t
    Cost_Min = int(1e9)

    for S in range(1 << 4):
        D = 0
        for j in range(4):
            if not (S & (1 << j)):
                D += b[j + 1]  # Cards of suits not chosen

        num = tot = 0
        for j in range(4):
            if S & (1 << j):
                num += P  # Total number of cards from chosen suits if P cards assigned
                tot += 1

        # Binary search to find maximum player count that can be satisfied with P cards
        L, R = 1, n
        Get = 0
        while L <= R:
            mid = (L + R) // 2
            if G[S][mid].V >= num:
                Get = mid
                L = mid + 1
            else:
                R = mid - 1

        # Compute cost for this assignment
        D += P * tot * Get - G[S][Get].w2 + G[S][Get + 1].w1

        # Subtract what's actually needed
        sum_temp = 0
        for j in range(4):
            if S & (1 << j):
                sum_temp += P - a[t][j + 1]

        D -= min(c[t], sum_temp)
        Cost_Min = min(Cost_Min, D)

    return Cost_Min == M


def Sol(t, color, n, a, b, c, G, Pre, Suf, M):
    # Find maximum points for player t with suit color
    ans = 0
    h = min(b[color], c[t])
    Max = a[t][color] + h  # Maximum number of cards player t can have with this suit
    b[color] -= h  # Reserve cards for this player
    M -= c[t]    # Deduct from total available distribution

    # Find lower bound on what we can reasonably expect
    L = max(Pre[t - 1], Suf[t + 1])
    R = Max
    Get = int(1e9)

    # Use binary search to find optimal result
    while L <= R:
        mid = (L + R) // 2
        if check(mid, t, n, a, b, c, G, M):
            Get = mid
            R = mid - 1
        else:
            L = mid + 1

    ans = Max - Get  # Points = Best card count - Winner's card count
    b[color] += h  # Restore cards
    M += c[t]
    return ans


def process_cards(input_data):
    data = input_data.split()
    idx = 0

    n = int(data[idx])
    idx += 1

    N = 50005
    a = [[0] * 5 for _ in range(N)]
    b = [0] * 5
    c = [0] * N
    G = [[Node() for _ in range(N)] for _ in range(1 << 4)]
    Pre = [0] * N
    Suf = [0] * N
    sum_cards = 0
    M = 0

    # Read player hands
    for i in range(1, n + 1):
        for j in range(1, 5):
            a[i][j] = int(data[idx])
            idx += 1
            sum_cards += a[i][j]

    # Read remaining cards in deck
    for i in range(1, 5):
        b[i] = int(data[idx])
        idx += 1
        sum_cards += b[i]

    sum_cards //= n  # Each player gets this many cards

    # Compute how many cards each player still needs
    for i in range(1, n + 1):
        c[i] = sum_cards - sum(a[i][1:5])
        M += c[i]

    # Compute prefix and suffix maxes for optimization
    for i in range(1, n + 1):
        res = max(a[i][1:5])
        Pre[i] = max(Pre[i - 1], res)

    for i in range(n, 0, -1):
        res = max(a[i][1:5])
        Suf[i] = max(Suf[i + 1], res)

    # Initialize precomputed data structures
    init(n, a, c, G)

    result = []
    for i in range(1, n + 1):
        res = 0
        for j in range(1, 5):
            res = max(res, Sol(i, j, n, a, b, c, G, Pre, Suf, M))
        result.append(res)

    return " ".join(map(str, result))


def main():
    import sys

    input_data = sys.stdin.read()
    print(process_cards(input_data))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
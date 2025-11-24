# Problem: CF 1763 E - Node Pairs
# https://codeforces.com/contest/1763/problem/E

"""
Code Purpose:
This program solves the problem of finding the minimum number of nodes required to create a p-reachable directed graph,
and among all such graphs with minimum nodes, computes the maximum number of unidirectional pairs.

Approach:
1. We use dynamic programming to determine the minimum number of nodes N needed to construct a p-reachable graph.
2. The key insight is that we can build the graph by adding complete subgraphs (cliques) of size i, which contribute 
   i*(i-1)/2 pairs of mutually reachable nodes.
3. After determining N, we compute the maximum number of unidirectional pairs using the formula:
   G = C(N, 2) - p, where C(N, 2) is the total number of pairs among N nodes minus the p mutually reachable pairs.

Time Complexity: O(p * sqrt(p)) due to nested loops where the outer loop runs p times and inner while loop 
                 runs approximately sqrt(p) times.
Space Complexity: O(p) for the dp array storing intermediate results.
"""

def bc2(n):
    # Calculate binomial coefficient C(n, 2) = n * (n - 1) / 2
    return n * (n - 1) // 2


def solve(p):
    assert 0 <= p <= 2 * 10**5
    # dp[k] represents the minimum number of nodes to form exactly k mutually reachable pairs
    dp = [2 * p] * (p + 1)
    dp[0] = 0  # Base case: 0 nodes needed to make 0 mutually reachable pairs
    
    # Fill the dp array
    for k in range(1, p + 1):
        i = 2  # Start with clique size 2
        # Loop while the number of pairs in a clique of size i is <= k
        while bc2(i) <= k:
            dp[k] = min(dp[k], dp[k - bc2(i)] + i)  # Transition: add a clique of size i
            i += 1  # Try larger clique
    
    # N is the minimum number of nodes needed to reach p mutually reachable pairs
    N = dp[p]
    # Compute maximum number of unidirectional pairs
    # G = total pairs - mutually reachable pairs = C(N, 2) - p
    G = bc2(N) - p
    return N, G


print(*solve(int(input())))


# https://github.com/VaHiX/CodeForces/
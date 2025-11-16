# Problem: CF 1423 A - Wakanda Forever
# https://codeforces.com/contest/1423/problem/A

"""
Algorithm: Stable Pairing in Wakanda
Purpose: Find a stable pairing of cities such that no two cities can both benefit from switching partners.
Techniques: 
- Greedy approach to find minimum cost pair for each city
- Validation check for stability of pairing
- Graph-based reasoning for conflict detection

Time Complexity: O(N^2) where N is the number of cities. 
  - Finding minimum cost for each city: O(N^2)
  - Checking stability conditions for all pairs: O(N^2)

Space Complexity: O(N^2) for storing the cost matrix and pairing information.
"""

def find_optimal_pairing(n, costs):
    # Find minimum cost for each city to pair with another
    min_costs = [min(costs[i]) for i in range(n)]
    pairs = [0] * n
    # Assign each city to its minimum cost partner
    for i in range(n):
        pairs[i] = costs[i].index(min_costs[i])
    # Check for stability - no city should prefer another city over its current partner
    for i in range(n):
        for j in range(n):
            # Skip if it's the same city
            if i != j and (costs[i][j] < min_costs[i] and costs[j][i] < min_costs[j]):
                # If both cities would benefit from switching, pairing is unstable
                return [-1] * n
    # Return 1-indexed pairings
    return [pair + 1 for pair in pairs]


def main():
    n = int(input())
    costs = [list(map(int, input().split())) for _ in range(n)]
    # Insert -1 at the diagonal position (representing same city)
    for i in range(n):
        costs[i].insert(i, -1)
    result = find_optimal_pairing(n, costs)
    print(*result)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
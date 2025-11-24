# Problem: CF 2038 K - Grid Walk
# https://codeforces.com/contest/2038/problem/K

"""
K. Grid Walk

Purpose:
This code computes the minimum cost path from (1,1) to (n,n) on an n×n grid where each cell (i,j)
has a cost defined as c(i,j) = gcd(i,a) + gcd(j,b). The approach uses dynamic programming with
preprocessing to optimize computation of GCD-based costs.

Algorithms/Techniques:
- Precompute GCD arrays for rows and columns using a sieve-like method.
- Use dynamic programming to compute minimal path cost from (1,1) to (n,n).
- Optimize the DP by skipping parts of the array that can be computed efficiently.

Time Complexity: O(n log n)
Space Complexity: O(n)

The algorithm uses:
- Sieve-like preprocessing of GCDs in O(n log n) time.
- Dynamic programming to compute path costs: O(n^2).
- The optimization based on max coprime avoids redundant computation.
"""

def gcd_array(length: int, value: int) -> list[int]:
    # Initialize array with all 1s
    array = [1 for _ in range(length)]
    # For each possible divisor up to min(length, value)
    for i in range(2, min(length, value) + 1):
        if value % i == 0:  # If i divides value
            # Update all multiples of i with value i
            for j in range(i - 1, length, i):
                array[j] = i
    return array


def max_coprime(gcds: list[int]) -> int:
    # Find the largest index where GCD is 1 (coprime to the base)
    for i in range(len(gcds) - 1, 0, -1):
        if gcds[i] == 1:
            return i + 1
    return 1


def min_cost_dp(row_costs: list[int], column_costs: list[int]) -> int:
    # Get dimensions of the subarray to compute
    n_rows = len(row_costs)
    n_columns = len(column_costs)
    
    # Initialize DP table with zeros
    cumulative_costs = [[0 for _ in range(n_columns)] for _ in range(n_rows)]
    
    # Fill first row (only possible to come from left)
    for j in range(1, n_columns):
        cumulative_costs[0][j] = cumulative_costs[0][j - 1] + row_costs[0]
    
    # Fill first column (only possible to come from above)
    for i in range(1, n_rows):
        cumulative_costs[i][0] = cumulative_costs[i - 1][0] + column_costs[0]
        
        # Compute DP for remaining cells
        for j in range(1, n_columns):
            cumulative_costs[i][j] = min(
                cumulative_costs[i][j - 1] + row_costs[i],
                cumulative_costs[i - 1][j] + column_costs[j],
            )
    
    return cumulative_costs[-1][-1]


# Read input
n, a, b = map(int, input().split())

# Precompute GCD arrays for rows and columns
row_costs = gcd_array(n, a)
column_costs = gcd_array(n, b)

# Find max coprime indices for both directions
max_coprime_with_a = max_coprime(row_costs)
max_coprime_with_b = max_coprime(column_costs)

# Apply DP on subarrays from the coprime positions onwards
dp_cost = min_cost_dp(
    row_costs[max_coprime_with_a - 1 :], column_costs[max_coprime_with_b - 1 :]
)

# Total cost calculation:
# (sum of original row costs) +
# (sum of original column costs) +
# (extra steps from skipping non-coprime prefix) +
# (DP computed cost for subpath)
min_cost = (
    sum(row_costs)
    + sum(column_costs)
    + (max_coprime_with_a - 1)
    + (max_coprime_with_b - 1)
    + dp_cost
)

print(min_cost)


# https://github.com/VaHiX/codeForces/
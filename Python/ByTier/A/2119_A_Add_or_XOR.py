# Problem: CF 2119 A - Add or XOR
# https://codeforces.com/contest/2119/problem/A

# ===============================================================================
# Problem: Minimum Cost to Make a Equal to b using Increment and XOR operations
# Algorithm/Techniques:
#   - Greedy with mathematical analysis of operation costs
#   - Uses bit manipulation and arithmetic to compute optimal cost
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# ===============================================================================

for s in [*open(0)][1:]:
    a, b, x, y = map(int, s.split())  # Read input values
    b -= a  # Calculate difference between target and current value
    
    # If b is negative, it's impossible to reach b from a using only increment operations
    print(
        y
        if a % 2 == -b == 1  # Special case: when we can use one XOR operation to make a match
        else -1 if b < 0     # If b is negative, impossible
        else b * x - (b + ~a % 2) // 2 * max(0, x - y)  # General case with optimized cost calculation
    )


# https://github.com/VaHiX/codeForces/
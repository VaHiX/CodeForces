# Problem: CF 1341 A - Nastya and Rice
# https://codeforces.com/contest/1341/problem/A

# ==========================================
# Problem: Nastya and Rice
# Algorithm: Check if given constraints on grain weights and total package weight are consistent
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# ==========================================

for s in [*open(0)][1:]:  # Read all lines from stdin, skip first line (number of test cases)
    n, a, b, c, d = map(int, s.split())  # Parse input values
    
    # Check if the total weight range [c-d, c+d] is compatible with possible grain weights
    # Minimum possible total weight = n * (a - b) 
    # Maximum possible total weight = n * (a + b)
    # For valid range: [c-d, c+d] must overlap with [n*(a-b), n*(a+b)]
    
    # The condition checks if:
    # 1. Maximum possible total weight < minimum required total weight => impossible
    # OR
    # 2. Minimum possible total weight > maximum required total weight => impossible
    # In either case, it's impossible to satisfy the constraints
    
    print("YNeos"[c + d < n * (a - b) or (a + b) * n < c - d :: 2])  # Output "Yes" or "No"


# https://github.com/VaHiX/codeForces/
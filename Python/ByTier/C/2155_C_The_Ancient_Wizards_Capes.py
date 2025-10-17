# Problem: CF 2155 C - The Ancient Wizards' Capes
# https://codeforces.com/contest/2155/problem/C

"""
C. The Ancient Wizards' Capes
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Problem: Determine how many valid cape arrangements exist for wizards such that the visibility counts match the given array.

This solution uses a dynamic programming approach to process the array and determine how many valid configurations of capes are consistent with the visibility data. 

The key idea is:
1. For each position, we can assume one of two cases:
   - Wizard wears cape on left side (0)
   - Wizard wears cape on right side (1)
2. Based on these assumptions, we compute a memo array which reflects how many "visible" wizards we count from the current position.
3. We use both possibilities for the first wizard and check if the final arrangement is consistent.

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Algorithms/Techniques:
- Dynamic Programming with memoization
- Two-pass deduction from left-right and right-left to validate configurations
"""

def ans(n, arr):
    memo = [0] * (n)
    X0 = 1  # Flag indicating validity when first wizard wears cape on left (0)
    s = 0   # Running sum of memo array values
    
    # Process from left to right assuming first wizard has cape on left (0)
    for i in range(n - 1):
        memo[i + 1] = arr[i + 1] - arr[i] - memo[i] + 1
        s += memo[i + 1]
        # If any value in memo is not 0 or 1, then configuration is invalid
        if memo[i + 1] != 0 and memo[i + 1] != 1:
            X0 = 0
            break
    
    # Final validation: check if the count matches expected for first wizard's position
    if X0 == 1:
        if arr[0] != n - s:
            X0 = 0
    
    # Reset memo array and try assuming first wizard has cape on right (1)
    memo = [0] * (n)
    memo[0] = 1  # First wizard wears cape on right
    X1 = 1       # Flag indicating validity when first wizard wears cape on right (1)
    s = 0        # Reset sum
    
    for i in range(n - 1):
        memo[i + 1] = arr[i + 1] - arr[i] - memo[i] + 1
        s += memo[i + 1]
        if memo[i + 1] != 0 and memo[i + 1] != 1:
            X1 = 0
            break
    
    # Final validation for second case
    if X1 == 1:
        if arr[0] != n - s:
            X1 = 0

    return X0 + X1


t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    print(ans(n, arr))


# https://github.com/VaHiX/CodeForces/
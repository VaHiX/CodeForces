# Problem: CF 2078 A - Final Verdict
# https://codeforces.com/contest/2078/problem/A

# ==============================================================================
# Problem: Determine if an array can be reduced to a single value x through
#          averaging subarrays of equal length.
#
# Algorithm/Technique:
#   - For each test case, we are given an array of length n and a target value x.
#   - The operation allows splitting the array into k equal-length subsequences,
#     and replacing the array with their averages.
#   - Key insight: the final average must equal the initial average if it's possible
#     to reach the target via valid splits.
#
# Time Complexity:
#   O(n) per test case, where n is the length of the array.
#   We compute the sum of elements once and compare with target x.
#
# Space Complexity:
#   O(1) additional space (not counting input storage).
# ==============================================================================

for _ in range(int(input())):  # Read number of test cases
    a, b = map(int, input().split())  # Read array length 'a' and target value 'b'
    c = sum(map(int, input().split())) / a  # Compute average of the array
    print("YES" if c == b else "NO")  # Output YES if average equals target


# https://github.com/VaHiX/codeForces/
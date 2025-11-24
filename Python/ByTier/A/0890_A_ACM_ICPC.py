# Problem: CF 890 A - ACM ICPC
# https://codeforces.com/contest/890/problem/A

"""
Algorithm: Generate all possible combinations of 3 elements from the 6 scores to form the first team.
          Check if the sum of the first team is exactly half of the total sum of all scores.
          If so, the remaining 3 elements automatically form the second team with equal score.

Time Complexity: O(C(6,3) * 3) = O(20 * 3) = O(1) - constant time due to fixed number of elements
Space Complexity: O(1) - only using a fixed amount of extra space regardless of input size

Techniques: Iteration over combinations, subset sum check
"""

import itertools

a = list(map(int, input().split()))  # Read input scores into a list
s = sum(a)  # Calculate total sum of all scores
ans = "NO"  # Initialize answer as "NO"

# Generate all combinations of 3 elements from the 6 scores
for i in itertools.combinations(a, 3):
    # If the sum of one team is exactly half of the total sum
    if sum(i) * 2 == s:
        ans = "YES"  # Set answer to "YES"
        break  # No need to check further combinations

print(ans)  # Output the result


# https://github.com/VaHiX/CodeForces/
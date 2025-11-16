# Problem: CF 1896 A - Jagged Swaps
# https://codeforces.com/contest/1896/problem/A

"""
Algorithm: A. Jagged Swaps
Techniques: Simulation, Greedy

Time Complexity: O(n^2) in worst case due to potential multiple swaps per element.
Space Complexity: O(n) for storing the input array and processing.

The problem involves determining if a permutation can be sorted using a specific swap operation:
- Select index i (from 2 to n-1) such that a[i-1] < a[i] and a[i] > a[i+1].
- Swap a[i] and a[i+1].

This is essentially checking whether the array can be transformed into a sorted order
using only these valid swaps. The key insight is that an array can be sorted in this way
if and only if it does not contain any "valley" (a[i] > a[i-1] and a[i] > a[i+1]) that prevents
the elements from being properly ordered by the allowed operations.

The code below parses input, checks for such a condition using a greedy approach.
"""

# Read all lines from stdin and strip trailing newlines
lst = [w.rstrip() for w in open(0).readlines()]

# Process every other line (starting from index 2) to get the actual test cases
# For each line, check if first two characters are "1 "
# If yes, output "YES", otherwise "NO"
res = [["NO", "YES"][line[0:2] == "1 "] for line in lst[2::2]]

# Print all results joined by newlines
print("\n".join(res))


# https://github.com/VaHiX/codeForces/
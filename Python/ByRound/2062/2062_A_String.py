# Problem: CF 2062 A - String
# https://codeforces.com/contest/2062/problem/A

"""
Algorithm: Greedy
Purpose: Determine the minimum number of operations to convert all '1's in a binary string to '0's.
Each operation allows selecting a subsequence of characters such that no two adjacent characters in the subsequence are the same, and flipping all characters in that subsequence.

Key Insight:
- A greedy approach works here: every time we encounter a '1', if it's not adjacent to a '1' that has already been flipped, we must perform an operation to flip it.
- This is equivalent to counting the number of '1's in the string because each '1' needs to be flipped at least once, and there's no way to flip multiple '1's in a single operation if they are all adjacent.

Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(1) as we only use a constant amount of extra space.

"""
for s in [*open(0)][1:]:
    print(s.count("1"))  # Count the number of '1's in the string, which equals the minimum operations needed.


# https://github.com/VaHiX/CodeForces/
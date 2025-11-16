# Problem: CF 1873 A - Short Sort
# https://codeforces.com/contest/1873/problem/A

"""
Code purpose:
This code determines whether a given permutation of three cards labeled 'a', 'b', and 'c' can be sorted into the order "abc" using at most one swap operation.

Algorithms/Techniques:
- Greedy approach: Count how many positions are already correct (i.e., 'a' at index 0, 'b' at index 1, 'c' at index 2).
- If all 3 positions are correct, no swaps needed → "NO"
- Otherwise, at least one swap is needed (or already possible with one swap) → "YES"

Time Complexity: O(1) - The algorithm performs a constant number of operations (3 comparisons) regardless of input size.
Space Complexity: O(1) - Only a few variables are used, independent of input size.
"""

for _ in range(int(input())):
    s = input()
    ans = 3
    if s[0] != "a":   # Check if 'a' is at the correct position
        ans -= 1
    if s[1] != "b":   # Check if 'b' is at the correct position
        ans -= 1
    if s[2] != "c":   # Check if 'c' is at the correct position
        ans -= 1
    if ans == 0:      # If all positions are correct, no operation is needed
        print("NO")
    else:             # Otherwise, one operation is sufficient to sort
        print("YES")


# https://github.com/VaHiX/CodeForces/
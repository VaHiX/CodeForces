# Problem: CF 1728 D - Letter Picking
# https://codeforces.com/contest/1728/problem/D

"""
Algorithm: Game Theory, String Manipulation
Time Complexity: O(n^2) in worst case due to string slicing and comparison operations
Space Complexity: O(n) for storing the string and intermediate results

The problem involves a two-player game where players pick letters from either end of a string,
trying to form the lexicographically smaller string. Both players play optimally.
The key insight is to simulate the game using greedy strategy: 
- If the first and last characters of the remaining string are equal, we can remove them 
  from both ends without affecting the outcome.
- Then, we evaluate whether Alice or Bob wins by checking character pairs.

The approach checks for equal characters at both ends, removes them iteratively,
and evaluates the resulting string to determine the winner.
"""

for _ in range(int(input())):
    l = input()
    # Remove equal characters from both ends iteratively
    while l and l[-1] == l[0]:
        l = l[1:-1]
    # Check if all characters in even positions are equal
    m = 1
    for i in range(0, len(l), 2):
        m *= l[i] == l[i + 1]
    # Print result based on the comparison
    print(["Alice", "Draw"][m])


# https://github.com/VaHiX/CodeForces/
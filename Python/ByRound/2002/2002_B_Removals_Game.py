# Problem: CF 2002 B - Removals Game
# https://codeforces.com/contest/2002/problem/B

"""
B. Removals Game

Purpose:
This code determines the winner of a game played between Alice and Bob,
where both players alternately remove elements from the beginning or end of their arrays.
The game ends when both arrays have one element remaining, and if those elements are equal,
Bob wins; otherwise, Alice wins.

Algorithm/Techniques:
- Game theory with optimal play simulation
- Key insight: Alice can win only if there exists a way for her to ensure
  that the last elements of both arrays differ. However, due to optimal play,
  Bob's best strategy is to mirror Alice's choices or make sure the final elements align.
- The solution checks if Alice's array equals Bob's array or is the reverse of Bob's array.
  If either condition holds, then Bob can always win; otherwise, Alice wins.

Time Complexity: O(n) per test case, where n is the length of the arrays.
Space Complexity: O(n) for storing the input arrays.

Input:
- Number of test cases t
- For each test case:
    - n (length of array)
    - Array a (Alice's permutation)
    - Array b (Bob's permutation)

Output:
- "Bob" if Bob wins, otherwise "Alice"
"""

for _ in range(int(input())):
    n = int(input())
    a = input().split()
    b = input().split()
    # Check if arrays are identical or reverse of each other
    if a == b or a == b[::-1]:
        print("Bob")  # Bob wins if arrays match in either direction
    else:
        print("Alice")  # Alice wins otherwise


# https://github.com/VaHiX/codeForces/
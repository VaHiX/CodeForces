# Problem: CF 1862 B - Sequence Game
# https://codeforces.com/contest/1862/problem/B

"""
Code Purpose:
This code solves the "Sequence Game" problem where given a sequence b, 
we need to reconstruct a valid original sequence a such that b is generated 
by filtering a to keep only elements that are greater than or equal to the 
previous element in the filtered sequence.

The algorithm works as follows:
- For each consecutive pair in b, if the current element is greater than the next,
  we insert a small value (1) to break the increasing trend.
- We then append the last element of b to complete the sequence.

Time Complexity: O(n) per test case, where n is the length of sequence b.
Space Complexity: O(n) for storing the reconstructed sequence a.

Algorithms/Techniques:
- Greedy reconstruction
- Linear traversal of the sequence b
"""

import sys


def solve():
    it = iter(sys.stdin.read().strip().split())
    t = int(next(it))  # Read number of test cases
    out = []
    for _ in range(t):
        n = int(next(it))  # Read length of sequence b
        b = [int(next(it)) for _ in range(n)]  # Read elements of sequence b
        a = []  # Initialize the reconstructed sequence a
        
        # Process all elements of b except the last one
        for i in range(n - 1):
            a.append(b[i])  # Add current element of b to a
            # If current element is greater than next, add 1 to break the trend
            if b[i] > b[i + 1]:
                a.append(1)
        
        # Append the last element of b to complete the sequence
        a.append(b[-1])
        
        # Format output: first line length of a, second line elements of a
        out.append(str(len(a)))
        out.append(" ".join(map(str, a)))
    
    print("\n".join(out))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/
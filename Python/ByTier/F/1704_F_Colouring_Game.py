# Problem: CF 1704 F - Colouring Game
# https://codeforces.com/contest/1704/problem/F

"""
Algorithm: Game Theory with Sprague-Grundy Theorem
This problem is a classic impartial game that can be solved using the Sprague-Grundy theorem.
We compute the Grundy number (nimber) for each segment of consecutive same-colored cells.
The overall Grundy number is the XOR of all segment Grundy numbers.
If the total Grundy number is 0, the current player (Alice) loses; otherwise, Alice wins.

Time Complexity: O(n) per test case
Space Complexity: O(1) for precomputed Grundy numbers, O(n) for input processing
"""

f = [0] * int(6e5)  # Precompute Grundy numbers for all possible segment lengths
for i in range(1, 2000):  # Compute Grundy numbers for small values using mex
    seen = set()
    for j in range(0, i - 1):  # For each possible split in segment of length i
        seen.add(f[j] ^ f[i - 2 - j])  # XOR Grundy numbers of left and right parts
    mex = 0  # Find the minimum excludant (mex)
    while mex in seen:
        mex += 1
    f[i] = mex  # Store computed Grundy number

# For large values, use periodicity (after 2000, sequence repeats every 34)
for i in range(2000, int(6e5)):
    f[i] = f[i - 34]

t = int(input())  # Read number of test cases
for _ in range(t):
    n = int(input())  # Read length of string
    s = input()  # Read the string of colors
    
    # Count net difference between red and blue cells
    diff = s.count("R") - s.count("B")
    
    # If reds dominate, Alice wins immediately
    if diff > 0:
        print("Alice")
    # If blues dominate, Bob wins immediately
    elif diff < 0:
        print("Bob")
    else:
        # Otherwise, analyze the segments of same-colored cells
        ans = 0  # Initialize the overall XOR of segments
        i = 0
        lst = []
        while i < n:
            j = i + 1
            # Extend j until color changes
            while j < n and s[j] != s[j - 1]:
                j += 1
            lst.append(j - i)  # Store length of this segment
            i = j  # Move to start of next segment
            
        # Compute XOR of Grundy numbers for each segment
        for i in lst:
            ans ^= f[i]
            
        # If final XOR is 0, Bob wins; otherwise Alice wins
        print("Alice" if ans else "Bob")


# https://github.com/VaHiX/CodeForces/
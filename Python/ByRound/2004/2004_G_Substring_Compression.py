# Problem: CF 2004 G - Substring Compression
# https://codeforces.com/contest/2004/problem/G

"""
Task: Substring Compression
Purpose: For each substring of length k in the given string s, compute the minimum length of the string that can be obtained by compressing it according to the defined rules.

Algorithms/Techniques:
- Dynamic Programming with sliding window approach.
- String compression using greedy pairing of substrings.
- Efficiently track minimum values and use rolling computations over the string.

Time Complexity: O(n * k), where n is the length of the string and k is the fixed substring length.
Space Complexity: O(n), for storing intermediate arrays and results.

The code implements a complex yet efficient sliding window DP approach to quickly compute the minimum compressed length for all substrings of size k.
"""

pra, kp = map(int, input().split())
s = input() * 2  # Double the string to allow easy modulo access
A = [X := 9**9] * (v := pra - kp + 1)  # Initialize result array with large value
R = range
C = R(1, 10)  # Digits 1 through 9
for c in R(10):  # For each possible starting digit (0-9)
    for l in R(v):  # For each valid starting index of a window
        if l % kp < 1:  # On the first window of size kp, reset calculations
            p = q = x = [X] * 10  # Initialize arrays for tracking
            p[c] = 0  # Start with current digit having cost 0
            y = p[0]  # Store previous cost
            # Reverse iterate over the current window
            for a in s[l : l + kp][::-1]:
                # Update p for each digit with cost calculation
                p = p[int(a)], *(c + min(p[c], p[0]) for c in C)
                x += (p[0],)  # Add updated cost to x
        A[l] = min(A[l], x[~(l % kp)] + y)  # Take minimum cost for current start
        q = [min(q := [c + q[c] for c in C])] + q  # Rolling update for queue costs
        q[a] = min(q[a := int(s[l + kp])], y)  # Update specific digit cost
        y = q[0]  # Update y to the minimum cost
print(*A)


# https://github.com/VaHiX/CodeForces/
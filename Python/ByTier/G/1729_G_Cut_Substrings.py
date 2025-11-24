# Problem: CF 1729 G - Cut Substrings
# https://codeforces.com/contest/1729/problem/G

"""
Problem: G. Cut Substrings

Algorithms/Techniques: Dynamic Programming with Segment Processing

Time Complexity: O(n^2 * m) where n is the length of string s and m is the length of string t
Space Complexity: O(n * m) for storing positions and DP arrays

This solution uses dynamic programming to find the minimum number of moves to remove all occurrences 
of string t from string s, and counts the number of different optimal sequences.

The approach:
1. Find all occurrences of t in s and store their starting positions
2. Use dynamic programming where f[i] represents the minimum moves to process all characters 
   up to position p[i] and g[i] represents the number of ways to achieve that minimum
3. For each position, we determine which subsequent positions can be reached based on 
   overlapping occurrences of t
"""

for i in range(int(input())):
    s = input()
    t = input()
    p = [0]
    # Find all starting positions of t in s
    for i in range(len(s) - len(t) + 2):
        if s[i : i + len(t)] == t:
            p.append(i)
    
    # f[i] = minimum moves to process up to position p[i]
    # g[i] = number of ways to achieve minimum moves up to position p[i]
    f = [1000] * (len(p) + 1)
    g = [0] * (len(p) + 1)
    
    p[0] = -1000  # Initialize first position to -1000
    g[0] = 1       # One way to achieve 0 moves at start
    f[0] = 0       # 0 moves needed initially
    
    p.append(len(s) + len(t))  # Add a sentinel position at the end
    
    # Process all positions
    for i in range(len(p)):
        j = i + 1
        # Find the first position that can be reached by extending current position by length of t
        while j < len(p) and p[j] <= p[i] + len(t) - 1:
            j += 1
        k = j
        # Process all positions that can be extended from current position
        while k < len(p) and p[k] <= p[j] + len(t) - 1:
            if f[i] + 1 < f[k]:
                # Found a better solution, update min moves and reset count
                f[k] = f[i] + 1
                g[k] = g[i]
            elif f[i] + 1 == f[k]:
                # Found same minimum moves, add to count
                g[k] = (g[k] + g[i]) % int(1e9 + 7)
            k += 1
    
    print(f[-1] - 1, g[-1])


# https://github.com/VaHiX/CodeForces/
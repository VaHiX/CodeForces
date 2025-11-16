# Problem: CF 2030 B - Minimise Oneness
# https://codeforces.com/contest/2030/problem/B

"""
Purpose: 
    This code solves the problem of minimizing the "oneness" of a binary string of length n.
    Oneness is defined as the absolute difference between the number of subsequences 
    containing only 0s (f(t)) and those containing at least one 1 (g(t)).
    
    The approach is to construct a string that minimizes |f(t) - g(t)|.
    The key insight is that placing a single '1' at the beginning followed by all '0's 
    results in a string that minimizes the oneness.
    
    For example:
    - For n = 1: "0" or "1" both give oneness = 1
    - For n = 2: "01" gives f = 1, g = 2, oneness = 1
    - For n = 3: "010" gives f = 1, g = 3, oneness = 2, but "100" gives f = 3, g = 3, oneness = 0
    
    This approach works due to the specific pattern of counting subsequences.
    
Algorithms/Techniques: 
    - Greedy construction of binary string
    - Observational approach to minimize oneness
    
Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) for the output string construction.
"""
for n in [*open(0)][1:]:
    print("1" + "0" * (int(n) - 1))


# https://github.com/VaHiX/CodeForces/
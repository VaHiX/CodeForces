# Problem: CF 1621 C - Hidden Permutations
# https://codeforces.com/contest/1621/problem/C

"""
Algorithm: Interactive Permutation Recovery using Cycle Detection
This problem involves recovering a hidden permutation p by querying a permutation q that evolves according to the rule q'[i] = q[p[i]].

Key Techniques:
- Cycle detection in permutations using visited tracking
- Each query reveals how q evolves after applying p transformation
- Use of a lookup array L to store the final permutation p

Time Complexity: O(n) - Each element is visited at most once due to cycle detection
Space Complexity: O(n) - For storing the lookup array and visited array
"""
for _ in range(int(input())):
    m = int(input())
    L = [-1] * (1 + m)  # Lookup array to reconstruct permutation p
    M = [0] * (1 + m)   # Visited array to track processed elements
    
    for i in range(1, 1 + m, 1):  # For each position in permutation
        if 1 == M[i]:  # Skip if already processed
            continue
            
        p = 0  # Start of current cycle
        while 1:  # Traverse the cycle
            print("?", i)  # Query q[i]
            op = int(input())  # Get result of q[i] after transformation
            L[p] = op   # Store value in lookup
            M[p] = 1    # Mark as visited
            p = op      # Move to next position in cycle
            if 1 == M[p]:  # If reached a visited element, break cycle
                break

    print("!", *L[1::])  # Output the reconstructed permutation


# https://github.com/VaHiX/CodeForces/
# Problem: CF 2089 C1 - Key of Like (Easy Version)
# https://codeforces.com/contest/2089/problem/C1

"""
C1. Key of Like (Easy Version)

Purpose:
This code computes the expected number of successful key-lock matches for each participant in a game.
Each member takes turns selecting a key and a lock to test, optimizing their choice based on historical data.
The problem involves dynamic probability calculations over time as keys and locks are used.

Algorithms/Techniques:
- Dynamic Programming with modular arithmetic
- Probability computation using modular inverse
- Simulation of optimal strategies

Time Complexity: O(n * l^2)
Space Complexity: O(n)

Input Format:
- t: number of test cases
- For each test case: n, l, k (where k=0 in this version)
Output Format:
- For each test case: n integers representing expected successful matches for each member, modulo 10^9 + 7

The code uses a backward recursion approach to compute the probabilities.
"""

MOD = 10**9 + 7
t = int(input())
for _ in range(t):
    n, l, k = map(int, input().split())
    tot = l  # Total number of locks
    mov = [0] * n  # Current state of probability distribution for each position
    mov[0] = 1  # Initialize first position as certain (probability 1)
    out = [0] * n  # Output array to store results for each person
    
    # Loop backwards through locks to calculate probabilities
    for i in range(l, 0, -1):
        p = pow(i, -1, MOD)  # Modular inverse of i modulo MOD  
        i %= n  # Wrap around index if necessary
        if i == 0:
            break
            
        nex = [0] * n  # Next state array
        
        # Transition probabilities from current state to next
        for u in range(n):
            for j in range(1, i + 1):  # For each possible jump size up to i
                nex[u] += mov[u - j] * p  # Accumulate probability with modular arithmetic
                nex[u] %= MOD
                
        mov = nex  # Update state
        
        # Update output values with current probabilities
        for u in range(n):
            out[u - 1] += mov[u]
    
    # Normalize and finalize results
    for i in range(n):
        out[i] %= MOD

    # Adjust for expected value calculation using total locks
    ex = tot - sum(out)  # Calculate excess expected value
    ex %= MOD
    ex *= pow(n, -1, MOD)  # Apply modular inverse to divide by n
    ex %= MOD
    
    # Propagate adjustment evenly among all members
    for i in range(n):
        out[i] += ex
        out[i] %= MOD
        
    print(" ".join(map(str, out)))


# https://github.com/VaHiX/codeForces/
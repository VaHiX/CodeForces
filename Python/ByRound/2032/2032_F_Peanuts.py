# Problem: CF 2032 F - Peanuts
# https://codeforces.com/contest/2032/problem/F

"""
F. Peanuts
Time Complexity: O(n) per test case
Space Complexity: O(1)

This problem is about determining the number of ways to partition a sequence of integers
into contiguous subarrays (boxes) such that Alice wins the game.

Key insights:
- A player loses if they cannot make a valid move.
- The game is equivalent to a Nim-like game on XOR values of the boxes.
- A configuration is winning for Alice if and only if the XOR of all box sizes is 0.
- For the given structure, we derive recurrence relations based on prefix XORs.
- The code computes how many valid divisions lead to a winning state.

The solution works by examining the first few elements where the value is 1,
which simplifies the analysis of the game state based on parity of the sequence
and the current prefix XOR.

"""

MOD = 0x3B800001
HALF = pow(2, -1, MOD)

for _ in range(int(input())):
    n = int(input())
    a = [int(t) for t in input().split()]
    
    # Count leading 1s
    i = 0
    while i < n and a[i] == 1:
        i += 1
    
    # Handle special cases where all elements are 1
    if i == n:
        if i & 1:
            print(pow(2, n - 1, MOD))
        else:
            print(0)
        continue
    
    X = 0               # Running XOR of elements from index i onwards
    v = [0, 0]          # v[0] and v[1] will store counts of XOR states
    tot = 1             # Total number of possibilities computed so far
    bp = pow(2, n - 2 - i, MOD)  # Precomputed power of 2 for current position
    
    for k in range(i, n):
        X ^= a[k]       # Update running XOR
        if k < n - 1:
            tot = 2 * tot % MOD  # Double total possibilities as we add more elements
        
        # If the XOR value is less than two, update counters accordingly
        if X < 2:
            if k == n - 1:
                v[X] += 1   # Final element in case of final step
            else:
                v[X] += bp  # Add contribution at current bit position
        
        bp = bp * HALF % MOD  # Move to next bit position
    
    S = 0               # Final result accumulator
    w = 1               # Weight for alternating parity calculation
    
    # Loop through all valid starting configurations and compute final answer
    for t in range(i + 1):
        if t % 2 == 0:
            # Even number of moves (Alice's turn)
            if (i - t) % 2 == 0:
                S += w * (tot - v[0])  # Add weight times valid combinations
            else:
                S += w * (tot - v[1])
        else:
            # Odd number of moves (Jack's turn)
            if (i - t) % 2 == 0:
                S += w * v[0]
            else:
                S += w * v[1]
        
        if t:
            w = w * 2 % MOD  # Update weight for next iteration
    
    print(S % MOD)  # Output final answer modulo MOD


# https://github.com/VaHiX/codeForces/
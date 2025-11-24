# Problem: CF 1929 C - Sasha and the Casino
# https://codeforces.com/contest/1929/problem/C

"""
Code Purpose:
This code determines whether Sasha can guarantee earning any number of coins in the casino game 
under the given constraints. It simulates a betting strategy to check if it's possible to 
continue betting indefinitely without running out of coins, given the maximum consecutive losses allowed (x), 
the win multiplier (k), and initial coins (a).

Approach:
- Simulate the worst-case betting sequence where Sasha loses x times in a row.
- For each loss, calculate the minimum bet required to recover from previous losses.
- If at any point the required bet exceeds the current coins, it's not possible to continue.
- If all x+1 steps are possible, then the strategy works.

Algorithms/Techniques:
- Simulation with greedy strategy
- Arithmetic calculation to determine minimum required bets

Time Complexity: O(x), where x is the maximum consecutive losses allowed
Space Complexity: O(1), only using a constant amount of extra space
"""

for t in range(int(input())):
    k, x, a = map(int, input().split())  # Read k (win multiplier), x (max consecutive losses), a (initial coins)
    cur = a  # Start with initial coins
    canWin = True  # Flag to track if it's possible to keep playing
    
    # Loop x+1 times to simulate the worst case of x consecutive losses followed by a win
    for i in range(x + 1):
        # Calculate the minimum bet needed to recover from current situation
        # We use ceiling division to ensure we can at least recover the deficit
        leastBet = (a - cur + k - 1) // (k - 1)
        
        # If the calculated bet exceeds current coins, it's impossible to continue
        if leastBet > cur:
            canWin = False
            break
            
        # Deduct the bet from current coins
        cur -= leastBet
    
    # Output result based on whether we could sustain the strategy
    if canWin:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/
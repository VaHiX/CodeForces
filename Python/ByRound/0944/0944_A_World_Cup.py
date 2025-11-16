# Problem: CF 944 A - World Cup
# https://codeforces.com/contest/944/problem/A

"""
Code Purpose:
This code determines the round in which two specific teams (with IDs 'a' and 'b') 
will meet in a single-elimination tournament. The tournament proceeds in rounds where 
teams are paired sequentially (1 vs 2, 3 vs 4, etc.), and winners advance to the next round.

Algorithm:
The solution uses a binary approach to simulate the tournament matches. Instead of 
explicitly simulating the tournament, we map the team IDs to their positions in the 
tournament tree and trace their paths upward until they meet. Each step corresponds 
to one round, as teams are halved each round.

Time Complexity: O(log n)
Space Complexity: O(1)

Techniques:
- Binary simulation of tournament structure
- Bit manipulation via integer division by 2
"""

n, a, b = map(int, input().split())
ans = 0
a -= 1  # converting to 0-based indexing
b -= 1

# Simulate the tournament by moving both teams up the bracket until they meet
while a != b:
    a //= 2  # move team 'a' to the next round
    b //= 2  # move team 'b' to the next round
    ans += 1  # increment round count

# Check if the teams meet in the final round
if 2**ans == n:
    print("Final!")
else:
    print(ans)


# https://github.com/VaHiX/CodeForces/
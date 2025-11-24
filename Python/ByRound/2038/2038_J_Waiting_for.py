# Problem: CF 2038 J - Waiting for...
# https://codeforces.com/contest/2038/problem/J

"""
Waiting for a Bus - Simulation Problem

Algorithms/Techniques:
- Simulation of events in chronological order
- Tracking of people waiting at the bus stop
- Decision making based on available seats and waiting people

Time Complexity: O(n) where n is the number of events, since we process each event exactly once.
Space Complexity: O(1) as we only use a constant amount of extra space (variable `cnt`).

The problem simulates a bus stop where people arrive and buses with varying capacities arrive.
For each bus, we determine if Monocarp can board it based on:
1. How many people are waiting at the bus stop
2. Whether there are enough seats for all waiting people plus Monocarp

When a bus arrives:
- If enough seats exist for everyone (including Monocarp), output "YES"
- Otherwise, only those who can fit in the remaining seats board
- If there's still space after that, Monocarp may board
"""

cnt = 0  # Keeps track of number of people waiting at the bus stop
for _ in range(int(input())):
    tp, p = input().split()
    p1 = int(p)
    if tp == "P":
        cnt += p1  # Add new arrivals to the waiting count
    else:
        # For a bus arrival event (B), check if Monocarp can board
        print("YES" if cnt <= p1 - 1 else "NO")  # If waiting people <= available seats - 1, Monocarp can board
        cnt = 0 if cnt <= p1 else cnt - p1  # Update waiting count after bus departure


# https://github.com/VaHiX/codeForces/
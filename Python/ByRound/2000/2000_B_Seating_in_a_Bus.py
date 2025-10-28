# Problem: CF 2000 B - Seating in a Bus
# https://codeforces.com/contest/2000/problem/B

# B. Seating in a Bus
# Purpose: Determine if passengers followed seating rules on a bus where each passenger must sit in a seat adjacent to at least one occupied seat, unless the bus is empty.
# Algorithm: Simulate the process of passengers boarding using a boolean array to track seat occupancy.
# Time Complexity: O(n) per test case, since we iterate once through the list of passengers and perform constant-time operations for each.
# Space Complexity: O(n) due to the array 'b' used to represent occupied seats.

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip n and read a)
    p, *a = map(int, s.split())  # Parse passenger seat choices
    b = [1] * (len(a) + 3)  # Create array of seats initialized to 1 (free), padding to avoid boundary checks
    b[p] = f = 0  # Mark the first passenger's seat as occupied and initialize flag f=0
    
    for x in a:  # Process each passenger's choice
        f |= b[x - 1] & b[x + 1]  # Check if either neighbor of current seat x is already occupied
        b[x] = 0  # Mark the chosen seat as now occupied
    
    print("YNEOS"[f::2])  # Output YES if no violation (f=0), NO if f=1


# https://github.com/VaHiX/codeForces/
# Problem: CF 1901 A - Line Trip
# https://codeforces.com/contest/1901/problem/A

"""
Problem: Line Trip
Algorithm/Technique: Greedy approach with maximum gap calculation

Time Complexity: O(n) per test case, where n is the number of gas stations.
Space Complexity: O(n) for storing the list of gas station positions.

The problem requires finding the minimum tank capacity needed to travel from 0 to x and back,
given that refueling can only occur at gas stations. The key insight is to find the largest 
distance between consecutive gas stations (including 0 and x). The minimum tank size must
be at least half of this maximum distance, or the distance from 0 to the first station, 
whichever is larger.

This solution:
1. Calculates the maximum gap between adjacent gas stations, considering 0 and x as endpoints
2. Determines the minimum required tank capacity that allows travel in both directions
"""

for _ in range(int(input())):
    n, k = map(int, input().split())  # Read number of gas stations and target point x
    l = list(map(int, input().split()))  # Read positions of gas stations
    
    # Initial maximum distance is the larger of:
    # - twice the distance from last station to x (for round trip)
    # - distance from 0 to first station
    s = max((k - l[-1]) * 2, l[0] - 0)
    
    # Check gaps between consecutive stations
    for i in range(n - 1):
        s = max(l[i + 1] - l[i], s)  # Update maximum gap
    
    print(s)  # Output minimum required tank capacity


# https://github.com/VaHiX/codeForces/
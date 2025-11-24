# Problem: CF 2061 B - Kevin and Geometry
# https://codeforces.com/contest/2061/problem/B

"""
B. Kevin and Geometry

Purpose:
This code attempts to find 4 sticks from a given list that can form an isosceles trapezoid with positive area.
An isosceles trapezoid has two parallel sides (bases) and two equal-length non-parallel sides (legs).
The algorithm tries to identify two pairs of equal-length sticks that can serve as the legs and bases.

Approach:
1. Sort the stick lengths.
2. Find a pair of equal-length sticks (potential legs).
3. Remove both sticks from the list.
4. Check if any remaining pair of sticks can form valid bases such that the trapezoid has positive area.
   - For an isosceles trapezoid with base lengths b1, b2 and leg length c, the sides must satisfy:
     b1 + 2*c > b2 (simplified condition based on trapezoid inequality)
5. Output the first valid combination found, or -1 if none exists.

Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing the list of stick lengths.
"""

for t in range(int(input())):
    n = int(input())
    l = [int(x) for x in input().split()]
    l.sort()
    c = 0
    # Find a repeated element that can act as leg length
    for i in range(n - 1):
        if l[i] == l[i + 1]:
            c = l[i]
            break
    # If no repeated element, impossible to form trapezoid with equal legs
    if c == 0:
        print(-1)
        continue
    # Remove two copies of the leg length
    l.remove(c)
    l.remove(c)
    check = False
    # Try all pairs from remaining list as potential bases
    for i in range(n - 3):
        # Check if these can form a valid trapezoid with previous pair
        if l[i] + 2 * c > l[i + 1]:
            print(c, c, l[i], l[i + 1])
            check = True
            break
    if not check:
        print(-1)


# https://github.com/VaHiX/codeForces/
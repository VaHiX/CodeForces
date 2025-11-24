# Problem: CF 2153 C - Symmetrical Polygons
# https://codeforces.com/contest/2153/problem/C

"""
C. Symmetrical Polygons

Purpose:
This code solves the problem of finding the maximum perimeter of a symmetrical, strictly convex, and non-degenerate polygon 
that can be formed from a given set of sticks. The approach uses greedy selection of sides based on their frequencies and 
sorting to construct valid symmetrical polygons.

Algorithms/Techniques:
- Frequency counting using defaultdict
- Greedy selection with sorting for symmetry preservation
- Edge case handling for degeneracy

Time Complexity: O(n log n) per test case due to sorting, where n is the number of sticks.
Space Complexity: O(n) for storing stick counts and intermediate structures.

Input Format:
- First line contains t (number of test cases)
- For each test case:
  - First line: n (number of sticks)
  - Second line: n space-separated integers representing stick lengths

Output Format:
- For each test case, output the maximum possible perimeter of a valid symmetrical polygon, or 0 if none exists.
"""

import sys
from collections import defaultdict

FILE = False
if FILE:
    sys.stdin = open("input.txt", "r")
    sys.stdout = open("output.txt", "w")


def myAlg(x=""):
    def get_int():
        s = sys.stdin.readline()
        if not s:
            sys.exit(0)
        return int(s)

    def get_string():
        return sys.stdin.readline().strip()

    t = get_int()  # Read number of test cases
    output = []
    for _ in range(t):
        get_int()  # Read n (number of sticks, not used directly)
        vals = get_string().split()  # Read stick lengths
        counts = defaultdict(int)  # Count frequency of each stick length
        for val in vals:
            counts[val] += 1  # Increment count for each stick length
        
        doubleSideSum = 0  # Sum of sides used in pairs (for symmetrical construction)
        sides = 0  # Total number of sides used in pairs
        countKeys = list(counts.keys())  # Get all unique stick lengths
        
        # Process counts to form symmetric pairs
        for val in countKeys:
            if counts[val] >= 2:  # If there are at least two sticks of same length
                doubleSideSum += (int(val) * 2) * (counts[val] // 2)  # Add pair contributions to total perimeter
                sides += (counts[val] // 2) * 2  # Update number of sides used in pairs
            counts[val] = counts[val] % 2  # Keep only leftover sticks (odd count)
            if counts[val] == 0:  # Remove zero count entries
                del counts[val]
        
        if sides == 0:  # No symmetrical pairing found
            output.append("0")
            continue
        
        # Now process remaining individual sticks to see if we can add one more for a valid polygon
        countKeys = list(counts.keys())
        countKeys.sort(reverse=True, key=lambda i: int(i))  # Sort in descending order of stick lengths
        minRemaining = 0  # Minimum additional length needed (for forming the third side in triangle case)
        
        # Check if we could form valid polygon by adding one more element from remaining sticks
        for i in range(len(countKeys)):
            curVal = int(countKeys[i])
            nextVal = 0
            if i < len(countKeys) - 1:
                nextVal = int(countKeys[i + 1])
            # Check condition to satisfy polygon triangle inequality for symmetry:
            # A valid addition needs that the sum of previous parts is greater than new stick
            if curVal < doubleSideSum + nextVal:
                minRemaining = curVal + nextVal
                break
        
        # Special case: if we only had pair sides but no extra single sticks to complete triangle
        if minRemaining == 0 and sides == 2:
            output.append("0")
        else:
            output.append(str(doubleSideSum + minRemaining))
    
    sys.stdout.write("\n".join(output))


myAlg()


# https://github.com/VaHiX/CodeForces/
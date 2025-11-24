# Problem: CF 1974 D - Ingenuity-2
# https://codeforces.com/contest/1974/problem/D

"""
Algorithm: Greedy Distribution of Instructions
Purpose: Distribute instructions between rover and helicopter such that both end at the same point.
Approach:
- For each instruction, decide whether to assign it to the rover or helicopter based on current relative positions.
- Use a greedy heuristic: when both devices are at the same position, assign the instruction to the one that will move further from the other.
- Track the cumulative positions of the rover and helicopter.
- Ensure both devices execute at least one instruction.

Time Complexity: O(n) where n is the number of instructions.
Space Complexity: O(n) for storing the result string.
"""

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    s = input().strip()
    xr, yr = 0, 0  # Rover's coordinates
    xh, yh = 0, 0  # Helicopter's coordinates
    L = []  # Result list to store 'R' or 'H'
    fh, fr = 0, 0  # Flags to check if helicopter and rover have executed at least one instruction

    for x in s:
        if x == "N":
            # If rover is north of helicopter, move helicopter up
            if yr > yh:
                yh += 1
                L.append("H")
                fh = 1
            # If helicopter is north of rover, move rover up
            elif yr < yh:
                yr += 1
                L.append("R")
                fr = 1
            else:
                # If they are at the same vertical position, assign based on flag
                if fh == 0:
                    yh += 1
                    L.append("H")
                    fh = 1
                else:
                    yr += 1
                    L.append("R")
                    fr = 1
        elif x == "S":
            # If rover is south of helicopter, move rover down
            if yr > yh:
                yr -= 1
                L.append("R")
                fr = 1
            # If helicopter is south of rover, move helicopter down
            elif yr < yh:
                yh -= 1
                L.append("H")
                fh = 1
            else:
                # If they are at the same vertical position, assign based on flag
                if fh == 0:
                    yh -= 1
                    L.append("H")
                    fh = 1
                else:
                    yr -= 1
                    L.append("R")
                    fr = 1
        elif x == "E":
            # If rover is east of helicopter, move helicopter right
            if xr > xh:
                xh += 1
                L.append("H")
                fh = 1
            # If helicopter is east of rover, move rover right
            elif xr < xh:
                xr += 1
                L.append("R")
                fr = 1
            else:
                # If they are at the same horizontal position, assign based on flag
                if fh == 0:
                    xh += 1
                    L.append("H")
                    fh = 1
                else:
                    xr += 1
                    L.append("R")
                    fr = 1
        else:  # x == "W"
            # If rover is west of helicopter, move rover left
            if xr > xh:
                xr -= 1
                L.append("R")
                fr = 1
            # If helicopter is west of rover, move helicopter left
            elif xr < xh:
                xh -= 1
                L.append("H")
                fh = 1
            else:
                # If they are at the same horizontal position, assign based on flag
                if fh == 0:
                    xh -= 1
                    L.append("H")
                    fh = 1
                else:
                    xr -= 1
                    L.append("R")
                    fr = 1
    
    # Check if both devices ended at same point and both executed at least one instruction
    if xh == xr and yh == yr and fh and fr:
        print("".join(L))
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/
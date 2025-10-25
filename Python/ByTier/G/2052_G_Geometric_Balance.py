# Problem: CF 2052 G - Geometric Balance
# https://codeforces.com/contest/2052/problem/G

"""
Geometric Balance Problem Solution

Algorithm:
- This problem involves finding the smallest positive angle b such that rotating the turtle by b degrees 
  and executing the same sequence of commands produces an identical image.
- The approach uses bitwise operations to represent the set of directions a segment is drawn in.
- We simulate the turtle's movement for all 8 possible starting directions (0 to 7), and for each,
  we track which segments are drawn and in which directions.
- To determine if two images are the same, we compare the sets of drawn segments, taking into account 
  the geometric transformations.
- The solution leverages the fact that the turtle only rotates in 45-degree increments (8 total directions).
- For each of the 8 initial directions, generate a "fingerprint" of drawn segments and their directions.
- Then, for each rotation angle (45° to 315°), compute the new fingerprint and compare it with the original.
- The matching rotation angle gives the smallest valid b.

Time Complexity: O(n)
Space Complexity: O(n)

Note: While the algorithm may appear to process many segments, the number of segments is bounded 
by the number of draw commands, which is at most 2000. Each segment's fingerprint is a set of bits 
representing directions, and comparisons are done in constant time per segment. The overall complexity 
is linear in the number of commands.

"""

import sys

# Direction vectors for 8 cardinal/ordinal directions (0 to 7)
dx = [1, 1, 0, -1, -1, -1, 0, 1]
dy = [0, 1, 1, 1, 0, -1, -1, -1]


def S(n, tp, val, dir0):
    """
    Simulates the turtle's path, tracking segments drawn in each direction.
    
    Args:
        n: number of commands
        tp: list of command types ('rotate', 'draw', 'move')
        val: list of command values
        dir0: starting direction (0-7)
        
    Returns:
        List of segments with their directions in a fingerprint format
    """
    mp = {}  # Maps segment positions to bitmasks of directions
    X = [0, 0]  # X coordinates for segments (even/odd)
    Y = [0, 0]  # Y coordinates for segments (even/odd)
    dir = dir0 % 8  # Current direction
    
    for i in range(n):
        if tp[i] == "rotate":
            # Update direction by adding rotation amount (divided by 45)
            dir = (dir + (val[i] // 45)) % 8
        else:
            # Get the current segment key (position of start/end points)
            key = ((X[0], X[1]), (Y[0], Y[1]))
            
            # Handle even directions (full unit steps)
            if dir % 2 == 0:
                # Process drawing command
                if tp[i] == "draw":
                    mp[key] = mp.get(key, 0) | (1 << dir)  # Set bit for current direction
                # Move turtle in specified direction
                X[0] += 2 * val[i] * dx[dir]
                Y[0] += 2 * val[i] * dy[dir]
                
                # Update the key to the end point
                key = ((X[0], X[1]), (Y[0], Y[1]))
                
                # Handle end point drawing
                if tp[i] == "draw":
                    # Set bit for opposite direction as well
                    mp[key] = mp.get(key, 0) | (1 << ((dir + 4) % 8))
            else:
                # Handle odd directions (half-unit steps for precise tracking)
                if tp[i] == "draw":
                    mp[key] = mp.get(key, 0) | (1 << dir)
                X[1] += val[i] * dx[dir]
                Y[1] += val[i] * dy[dir]
                
                # Update the key to the end point
                key = ((X[0], X[1]), (Y[0], Y[1]))
                
                if tp[i] == "draw":
                    mp[key] = mp.get(key, 0) | (1 << ((dir + 4) % 8))
    
    # Build fingerprint from the segments recorded
    f = []
    for key, msk in mp.items():
        a_pt, b_pt = key
        for d in range(4):
            # If segment starts in direction d but doesn't end in opposite (d+4), record d
            if (msk & (1 << d)) and not (msk & (1 << (d + 4))):
                f.append((a_pt, b_pt, d))
            # If segment starts in opposite direction but not in d, record d
            if (msk & (1 << (d + 4))) and not (msk & (1 << d)):
                f.append((a_pt, b_pt, d + 4))
                
    f.sort()
    return f


def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    tp = []
    val = []
    for _ in range(n):
        tp.append(next(it))
        val.append(int(next(it)))
    
    # Generate the original fingerprint for starting direction 0
    f = S(n, tp, val, 0)
    
    if not f:
        # No draw commands or similar edge case
        print(360)
        return
        
    best = 360  # Default answer if rotation angle not found
    
    # Try all possible orientations (0 to 7)
    for z in range(1, 9):
        ff = S(n, tp, val, z % 8)  # Compute fingerprint for rotation z
        if not ff:
            continue
            
        # Get first element from original and rotated to calculate offset
        f0_a, f0_b, _ = f[0]
        ff0_a, ff0_b, _ = ff[0]
        Xoff = (f0_a[0] - ff0_a[0], f0_a[1] - ff0_a[1])
        Yoff = (f0_b[0] - ff0_b[0], f0_b[1] - ff0_b[1])
        
        # Shift the rotated fingerprint by the offset
        shifted = []
        for a, b, c in ff:
            a_shifted = (a[0] + Xoff[0], a[1] + Xoff[1])
            b_shifted = (b[0] + Yoff[0], b[1] + Yoff[1])
            shifted.append((a_shifted, b_shifted, c))
        
        shifted.sort()
        if shifted == f:  # If shifted image matches original image
            print(45 * z)  # Print the corresponding angle
            return
            
    print(best)  # Default case if no matching rotation found


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
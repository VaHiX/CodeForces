# Problem: CF 1907 D - Jumping Through Segments
# https://codeforces.com/contest/1907/problem/D

# Flowerbox describing the code purpose, algorithms, time and space complexity
"""
Code Purpose:
This code solves the problem of finding the minimum jump distance 'k' required to traverse a sequence of segments on a number line, starting from point 0. 
Each segment represents a valid range where the player must land after each move. 
The solution uses binary search over the possible values of 'k' to find the minimum value that allows traversal through all segments.

Algorithms/Techniques:
- Binary Search on Answer: The idea is to binary search on the value of k (jump distance).
- Greedy Validation: For a given k, simulate the process of jumping through segments to check if it's possible to complete the level.

Time Complexity:
- O(n * log(max_range)) where n is the number of segments.
- The binary search runs in O(log(max_range)) and for each iteration, we process all segments in O(n).

Space Complexity:
- O(n) for storing the segments in memory.
"""

import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        segments = []
        for i in range(n):
            l = int(data[index])
            r = int(data[index + 1])
            index += 2
            segments.append((l, r))
        lo = 0
        hi = 2000000000  # Upper bound set based on constraints
        while lo < hi:
            mid = (lo + hi) // 2
            low_bound = 0
            high_bound = 0
            valid = True
            for l, r in segments:
                # Determine the new possible range of positions we can jump to in this segment
                new_low = max(l, low_bound - mid)
                new_high = min(r, high_bound + mid)
                # If there's no valid position to land in the segment, then it's invalid
                if new_low > new_high:
                    valid = False
                    break
                # Update the possible range for the next segment
                low_bound, high_bound = new_low, new_high
            if valid:
                # If valid, try to find a smaller k
                hi = mid
            else:
                # If invalid, we need a larger k
                lo = mid + 1
        results.append(str(lo))
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
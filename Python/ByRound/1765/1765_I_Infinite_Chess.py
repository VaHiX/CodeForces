# Problem: CF 1765 I - Infinite Chess
# https://codeforces.com/contest/1765/problem/I

"""
Algorithm: Shortest Path with Compressed Grid (BFS + Graph Compression)
Time Complexity: O((W * log W + C) * log C + (C * 8) * log C) where W is number of white pieces, C is compressed grid size
Space Complexity: O(W + C * 8) where W is number of white pieces, C is compressed grid size

Approach:
1. Compress the infinite grid into a finite grid by grouping columns with white pieces
2. Mark all attacked squares by white pieces
3. Run BFS on compressed grid where each column has a cost based on distance to next column
4. Return minimum distance or -1 if unreachable

Key techniques:
- Grid compression to reduce infinite space to finite
- BFS with cost calculation for distant columns
- Attack detection for all piece types
"""

import heapq
import sys

input = sys.stdin

# Read start and target positions
x0, y0 = [int(x) for x in input.readline().split(" ")]
x1, y1 = [int(x) for x in input.readline().split(" ")]
n = int(input.readline())
figures = []
for _ in range(n):
    type, x, y = input.readline().split(" ")
    figures.append((type, int(x), int(y)))


# Compression logic: merge nearby columns to reduce grid size
spacing = 8  # Spacing threshold for compression
interesting_x = [x for _, x, _ in figures] + [x0, x1]  # All interesting x coordinates
ranges_heap = []
for x in interesting_x:
    heapq.heappush(ranges_heap, (x - spacing, False))  # Start event
    heapq.heappush(ranges_heap, (x + spacing, True))   # End event

merged_interesting_ranges = []
counter = 0
start = None
while ranges_heap:
    x, is_end = heapq.heappop(ranges_heap)
    if not is_end:  # Start of interval
        if counter == 0:
            start = x
        counter += 1
    else:  # End of interval
        counter -= 1
        if counter == 0:
            merged_interesting_ranges.append((start, x))


# Create compressed grid mapping
real_x_to_compressed_map = {}
compressed = []
last_x_end = None
speedline_x = {}
for x_start, x_end in merged_interesting_ranges:
    if last_x_end is not None:
        # Add a placeholder row for skipped columns
        compressed_x = len(compressed)
        skip_counter = x_start - last_x_end - 1
        if skip_counter > 0:
            speedline_x[compressed_x] = skip_counter
            compressed.append([None] * 8)
    # Fill in actual columns
    for x in range(x_start, x_end + 1):
        compressed_x = len(compressed)
        real_x_to_compressed_map[x] = compressed_x
        compressed.append([None] * 8)
    last_x_end = x_end


# Place white pieces in compressed grid
figures_compressed = []
for type, x, y in figures:
    compressed_x = real_x_to_compressed_map[x]
    compressed[compressed_x][y - 1] = type
    figures_compressed.append((type, compressed_x, y - 1))


# Convert start and target to compressed coordinates
x_start, y_start = real_x_to_compressed_map[x0], y0 - 1
x_target, y_target = real_x_to_compressed_map[x1], y1 - 1

# Mark all attacked squares
beaten = set()
k = len(compressed)  # Width of compressed grid


# Trace function to mark all squares attacked in a direction (used for sliding pieces)
def trace(x, y, dx, dy):
    xc, yc = x, y
    while True:
        xc, yc = xc + dx, yc + dy
        if xc < 0 or xc >= k:
            break
        if yc < 0 or yc >= 8:
            break
        if compressed[xc][yc] is not None:
            break
        beaten.add((xc, yc))


# Process all white pieces to mark attacked squares
for type, x, y in figures_compressed:
    beaten.add((x, y))  # Mark piece location as attacked

    if type == "K":  # King attacks all adjacent squares
        for dx in range(-1, +2):
            for dy in range(-1, +2):
                beaten.add((x + dx, y + dy))
    elif type == "B":  # Bishop attacks diagonally
        trace(x, y, +1, +1)
        trace(x, y, +1, -1)
        trace(x, y, -1, +1)
        trace(x, y, -1, -1)
    elif type == "N":  # Knight attacks in L-shape
        beaten.add((x + 1, y + 2))
        beaten.add((x + 1, y - 2))
        beaten.add((x - 1, y + 2))
        beaten.add((x - 1, y - 2))

        beaten.add((x + 2, y + 1))
        beaten.add((x + 2, y - 1))
        beaten.add((x - 2, y + 1))
        beaten.add((x - 2, y - 1))
    elif type == "R":  # Rook attacks horizontally and vertically
        trace(x, y, +1, 0)
        trace(x, y, -1, 0)
        trace(x, y, 0, +1)
        trace(x, y, 0, -1)
    elif type == "Q":  # Queen attacks like rook and bishop combined
        trace(x, y, +1, 0)
        trace(x, y, -1, 0)
        trace(x, y, 0, +1)
        trace(x, y, 0, -1)
        trace(x, y, +1, +1)
        trace(x, y, +1, -1)
        trace(x, y, -1, +1)
        trace(x, y, -1, -1)
    else:
        assert False, "what? %s" % type


# Run BFS to find shortest path
visited = set()
heap = [(0, x_start, y_start)]
distance_map = {}


while heap:
    distance, x, y = heapq.heappop(heap)
    if (x, y) in visited:
        continue
    visited.add((x, y))
    distance_map[(x, y)] = distance

    if (x, y) == (x_target, y_target):
        break
    neighbor_candidates = [
        (x - 1, y - 1),
        (x - 1, y + 0),
        (x - 1, y + 1),
        (x, y - 1),
        (x, y + 1),
        (x + 1, y - 1),
        (x + 1, y + 0),
        (x + 1, y + 1),
    ]
    for neighbor_x, neighbor_y in neighbor_candidates:
        if neighbor_x < 0 or neighbor_x >= k:
            continue
        if neighbor_y < 0 or neighbor_y >= 8:
            continue
        if (neighbor_x, neighbor_y) in visited:
            continue
        if (neighbor_x, neighbor_y) in beaten:
            continue
        cost = 1  # Default cost
        if neighbor_x in speedline_x:
            cost = speedline_x[neighbor_x]  # Use higher cost if it's a skip row
        heapq.heappush(heap, (distance + cost, neighbor_x, neighbor_y))

# Output result
if (x_target, y_target) in distance_map:
    print(distance_map[(x_target, y_target)])
else:
    print(-1)


# https://github.com/VaHiX/CodeForces/
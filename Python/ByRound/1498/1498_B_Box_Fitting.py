# Problem: CF 1498 B - Box Fitting
# https://codeforces.com/contest/1498/problem/B

"""
Box Fitting Problem

Algorithm:
This is a greedy approach to packing rectangles into a box of width W with minimum height.
We use a frequency map of rectangle widths and then greedily fill each level of the box.
For each level, we fill from largest to smallest available rectangles.
The algorithm processes all rectangles and builds levels until all rectangles are placed.

Time Complexity: O(n * log W) where n is number of rectangles and log W is the number of distinct powers of 2 up to W.
Space Complexity: O(log W) for storing the frequency map of widths.
"""

for _ in range(int(input())):  # Process each test case
    n, w = map(int, input().split())  # Read number of rectangles and box width
    l = [int(x) for x in input().split()]  # Read widths of rectangles
    
    # Create a frequency map of rectangle widths
    d = {}
    for i in l:
        d[i] = d.get(i, 0) + 1
    
    c = 0  # Number of levels needed
    cursum = 0  # Current width used in the current level
    
    # Greedily pack rectangles into levels
    while True:
        # Iterate from largest to smallest possible width (up to W)
        for p in range(20, -1, -1):  # 20 is sufficient since 2^20 > 10^6
            # While we can fit this width and it's available
            while cursum + (1 << (p)) <= w and d.get(1 << p, 0) > 0:
                cursum += 1 << p  # Add this width to current level
                d[1 << p] -= 1  # Decrease count of this width
        if cursum == 0:  # No more rectangles can be added to any level
            break
        c += 1  # Increment level count
        cursum = 0  # Reset current level width for next iteration
    
    print(c)  # Print minimum height required


# https://github.com/VaHiX/CodeForces/
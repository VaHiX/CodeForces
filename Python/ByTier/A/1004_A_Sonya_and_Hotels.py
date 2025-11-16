# Problem: CF 1004 A - Sonya and Hotels
# https://codeforces.com/contest/1004/problem/A

"""
Code Purpose:
This code determines the number of valid positions where a new hotel can be built such that 
the minimum distance from this new hotel to all existing hotels is exactly 'd'. 

The algorithm works by:
1. Sorting the hotel positions (already sorted in input).
2. For each pair of consecutive hotels, calculate the gap between them.
3. Based on the gap size relative to 2*d:
   - If gap == 2*d, there is exactly 1 valid position (middle of the gap).
   - If gap > 2*d, there are 2 valid positions (one on each side of the gap).
4. Initially we add 2 to account for possible positions at the extremes (before first hotel and after last hotel).

Time Complexity: O(n), where n is the number of hotels.
Space Complexity: O(1), only using a few variables regardless of input size.
"""

n, b = map(int, input().split())  # Read n (number of hotels) and d (required minimum distance)
lst = [*map(int, input().split())]  # Read hotel coordinates
sum = 2  # Initialize count with 2 for potential positions at the ends
for x in range(n - 1):  # Iterate through adjacent pairs of hotels
    d = lst[x + 1] - lst[x]  # Calculate distance between consecutive hotels
    if d == 2 * b:  # If gap equals 2*d, one valid spot in middle
        sum += 1
    elif d > 2 * b:  # If gap is greater than 2*d, two valid spots (one on each side)
        sum += 2
print(sum)  # Output the total number of valid positions


# https://github.com/VaHiX/CodeForces/
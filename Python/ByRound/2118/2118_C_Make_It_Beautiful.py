# Problem: CF 2118 C - Make It Beautiful
# https://codeforces.com/contest/2118/problem/C

"""
C. Make It Beautiful

Algorithm/Technique: Greedy with bit manipulation
Time Complexity: O(n * log(max(a)) + t * n) where n is the length of array and t is number of test cases
Space Complexity: O(1)

This solution uses a greedy approach to maximize the beauty of the array by 
distributing up to k operations across the bits of numbers in the array. 
For each bit position, it calculates how many 1s can be added to the array's numbers,
given the available operations.

The key idea is:
- Process bits from least significant to most significant (0 to 60).
- For each bit, count how many numbers in the array currently have that bit OFF.
- Check if we can turn those bits ON with remaining operations k.
- The greedy choice: for each bit position, prioritize turning bits ON from left to right.
"""

R = lambda: map(int, input().split())
(t,) = R()
while t:
    t -= 1
    n, k = R()
    a = (*R(),)  # Read array elements
    r = i = 0
    for i in range(60):  # Process bits from 0 to 59 (as integers can go up to 1e9)
        b = 1 << i  # Current bit position
        i += 1      # Increment i for next iteration (this is a bit tricky, but ensures correct bit shifts)
        j = 0
        for x in a:
            d = ~x & b  # Check if the current bit of x is 0
            r += k >= d  # If we can afford to set this bit, increment result
            k = max(0, k - d)  # Deduct the cost (1s needed to set this bit)
            j += 1
    print(r)


# https://github.com/VaHiX/codeForces/
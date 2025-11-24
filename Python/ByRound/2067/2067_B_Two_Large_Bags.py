# Problem: CF 2067 B - Two Large Bags
# https://codeforces.com/contest/2067/problem/B

# B. Two Large Bags
# Algorithm: Greedy approach with sorting and pairing.
# Time Complexity: O(n log n) due to sorting, where n is the number of elements.
# Space Complexity: O(n) for storing the input and intermediate arrays.

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip test cases count)
    a = sorted(map(int, s.split()))  # Sort the numbers to process in order
    s = f = 0  # 's' tracks the current max number, 'f' is flag for invalidity
    for x, y in zip(a[::2], a[1::2]):  # Pair consecutive elements after sorting
        f |= x < y > s  # Check if pairing violates ordering constraints
        s = max(s, y) + 1  # Update the maximum seen so far, incrementing by 1
    print("YNeos"[f::2])  # Print "YES" if no flag set, else "NO"


# https://github.com/VaHiX/codeForces/
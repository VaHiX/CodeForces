# Problem: CF 2014 C - Robin Hood in Town
# https://codeforces.com/contest/2014/problem/C

# C. Robin Hood in Town
# Algorithm: Greedy + Sorting + Binary Search on Answer
# Time Complexity: O(n log n) per test case due to sorting and binary search
# Space Complexity: O(n) for storing the input array

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (i.e., wealth data)
    n = len(a := sorted(map(int, s.split())))  # Sort the wealth values and get length
    # If n < 3, it's impossible to have more than half the population unhappy -> return -1
    print(-(n < 3) or max(0, a[n // 2] * n * 2 - sum(a) + 1))


# https://github.com/VaHiX/codeForces/
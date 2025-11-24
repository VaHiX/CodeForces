# Problem: CF 2001 A - Make All Equal
# https://codeforces.com/contest/2001/problem/A

# Flowerbox:
# Purpose: This code solves the problem of making all elements in a cyclic array equal by deleting elements according to specific rules.
# Algorithm: For each test case, we compute the minimum number of operations needed to make all elements equal.
#            The approach works as follows:
#            1. Count the frequency of each element in the array.
#            2. Find the maximum frequency among all elements.
#            3. The minimum operations needed is the total length minus this maximum frequency.
# Time Complexity: O(n) per test case, where n is the size of the array. This is because we iterate over the array once to count frequencies.
# Space Complexity: O(n) for storing the counts of elements in a dictionary/hash map.

for s in [*open(0)][2::2]:  # Read lines 2, 4, 6... from input (test cases)
    print(len(a := s.split()) - max(map(a.count, a)))  # Compute and print result


# https://github.com/VaHiX/codeForces/
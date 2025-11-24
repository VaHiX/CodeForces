# Problem: CF 1993 D - Med-imize
# https://codeforces.com/contest/1993/problem/D

"""
Algorithm: Binary Search on Answer + Dynamic Programming
Time Complexity: O(n * log(max_value)) where max_value is up to 10^9 + 97
Space Complexity: O(n)

This solution uses binary search on the possible median value. For each candidate median,
it checks if it's possible to obtain an array where at least half of the elements are greater than or equal to the candidate.
The check is done using dynamic programming where we determine the maximum number of valid elements (>= candidate) that can be kept
after removing subarrays of size k, ensuring no two kept elements are within a distance less than k.
"""

ans = []
for _ in range(int(input())):
    n, k = [int(x) for x in input().split()]
    a = [int(x) for x in input().split()]

    # Calculate the number of elements that will remain in the final array
    end = 1 + ((n - 1) % k)
    sta = n - end

    L = 1
    R = 10**9 + 97
    v = [0] * n
    while L < R:
        X = (L + R) // 2

        for i in range(n - 1, -1, -1):
            # Skip the elements that cannot be kept due to the subarray constraints
            if i % k >= end:
                continue
            # Mark current element as valid if it meets the condition
            f = 1 if a[i] >= X else 0

            # If the element is at the last position of a segment, compute based on next segment
            if i % k == end - 1:
                if i + k < n:
                    v[i] = max(v[i + k], f)
                else:
                    v[i] = f
            else:
                # Else, take the max of including this element or skipping it
                if i + k < n:
                    v[i] = max(v[i + k], v[i + 1] + f)
                else:
                    v[i] = v[i + 1] + f

        # If enough elements can be kept to satisfy the median condition
        if v[0] > end // 2:
            L = X + 1
        else:
            R = X
    ans.append(L - 1)

for w in ans:
    print(w)


# https://github.com/VaHiX/CodeForces/
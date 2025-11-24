# Problem: CF 1863 F - Divide, XOR, and Conquer
# https://codeforces.com/contest/1863/problem/F

"""
Algorithm: Divide, XOR, and Conquer
Purpose: Determine for each element whether it can be the last remaining element after a series of operations on the array.
Approach:
1. Use prefix XOR to efficiently calculate XOR of any subarray.
2. For each possible subarray [l, r], check if we can make the last element equal to a specific index.
3. Maintain masks for the "winning" bits that can lead to specific indices being chosen.
4. Dynamic programming based on the ability to reach a state where the remaining array has only one element.

Time Complexity: O(n^2)
Space Complexity: O(n)

The solution works by:
- Computing the prefix XOR array
- For each subarray [i, j], we determine if it's possible to reduce it to a single element
- Using bitmasks to track which bits can be "used" to ensure a specific element is picked
"""

for _ in range(int(input())):
    n = int(input())
    l = list(map(int, input().split()))
    ml = [0] * n
    mr = [0] * n
    al = [0] * n
    ar = [0] * n
    res = ["0"] * n

    P = [0]
    for k in l:
        P.append(P[-1] ^ k)

    for i in range(n):
        for j in range(n - 1, i - 1, -1):
            x = P[i] ^ P[j + 1]
            if x == 0:
                # If XOR is 0, we can choose any side, so the current subarray can contribute to any element
                if al[i] or ar[j] or i == 0 and j == n - 1:
                    al[i], ar[j] = 1, 1
                    if i == j:
                        res[i] = "1"
            else:
                # If XOR is not 0, the side with higher value will be chosen
                # We need to find a bit that makes the choice valid
                if al[i] or ar[j] or x & ml[i] or x & mr[j] or i == 0 and j == n - 1:
                    v = 1 << x.bit_length() - 1
                    ml[i] |= v
                    mr[j] |= v
                    if i == j:
                        res[i] = "1"

    print("".join(res))


# https://github.com/VaHiX/CodeForces/
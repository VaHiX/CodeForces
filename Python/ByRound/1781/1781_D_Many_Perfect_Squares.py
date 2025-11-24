# Problem: CF 1781 D - Many Perfect Squares
# https://codeforces.com/contest/1781/problem/D

"""
Algorithm: Many Perfect Squares
Approach:
- For each pair of elements (x, y) in the array, compute the difference (y - x)
- Factorize the difference and find valid x values that make both elements perfect squares
- Use a greedy approach to count maximum overlapping perfect squares

Time Complexity: O(n^2 * sqrt(D) * log(n)) where D is the maximum difference
Space Complexity: O(sqrt(D)) for storing factor pairs
"""

def factors(n):
    arr = []
    for x in range(1, int(n ** (0.5)) + 2):
        if n % x == 0:
            a, b = sorted([x, n // x])
            arr.append((a, b))
    return arr


for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    arr.sort()
    count = 1
    for i, x in enumerate(arr):
        operations = []
        for j in range(i + 1, n):
            y = arr[j]
            diff = y - x
            for a, b in factors(diff):
                if a % 2 == b % 2:
                    ba = (b - a) // 2
                    if ba**2 >= x:
                        operations.append(ba)
        v = 0
        last = None
        operations.sort()
        for i in range(len(operations)):
            if operations[i] == last:
                v += 1
            else:
                v = 1
            count = max(count, v + 1)
            last = operations[i]

    print(count)


# https://github.com/VaHiX/CodeForces/
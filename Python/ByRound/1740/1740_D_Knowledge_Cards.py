# Problem: CF 1740 D - Knowledge Cards
# https://codeforces.com/contest/1740/problem/D

import heapq


def solve():
    # Read input values
    n, m, k = map(int, input().split())
    a = list(map(int, input().split()))
    h = []

    # Process each card in order from top to bottom of the initial stack
    for i in range(k):
        # Add the current card to the heap (using negative values to simulate max heap)
        heapq.heappush(h, -a[i])

        # While the largest element in heap equals the expected value (k), remove it
        while h and -h[0] == k:
            heapq.heappop(h)  # Remove the top element
            k -= 1  # Decrement k as we have matched one card

        # If the number of cards in the heap exceeds the available space (excluding start and end cells)
        if len(h) > n * m - 4:
            return "TIDAK"

    return "YA"


# Read number of test cases and process each one
for _ in range(int(input())):
    print(solve())

### Complexity Analysis
# - **Time Complexity**: O(k log k) per test case, where k is the number of cards. Each card is pushed and possibly popped from the heap once.
# - **Space Complexity**: O(k) for storing the heap and intermediate data structures.

# https://github.com/VaHiX/CodeForces/
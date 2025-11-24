# Problem: CF 1490 B - Balanced Remainders
# https://codeforces.com/contest/1490/problem/B

"""
Algorithm/Technique:
- The problem requires making an array have balanced remainders when divided by 3.
- We count how many elements fall into each remainder class (0, 1, 2).
- For a balanced array, each remainder class should have exactly n/3 elements.
- We simulate the process of moving elements from one remainder class to another 
  by incrementing values, minimizing the number of moves needed.
- The key insight is to process the remainder classes in a way that balances them step by step.

Time Complexity: O(n), where n is the length of the array. We iterate through the array once to count remainders, and then perform a constant number of operations for each remainder class.

Space Complexity: O(1), since we use a fixed-size array of size 3 for counting remainders and a few variables.
"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = [0] * 3
    x = n // 3
    ans = 0

    # Count how many elements belong to each remainder class (0, 1, 2)
    for el in a:
        b[el % 3] += 1

    # Process each remainder class to balance the counts
    for i in range(3):
        # Calculate the number of moves needed to adjust the current class
        # and update the count of elements in that class
        ans += max(b[i - 1] - x, x - b[i], 0)
        b[i] += max(b[i - 1] - x, x - b[i], 0)

    print(ans)


# https://github.com/VaHiX/CodeForces/
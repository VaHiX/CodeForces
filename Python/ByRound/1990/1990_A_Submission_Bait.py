# Problem: CF 1990 A - Submission Bait
# https://codeforces.com/contest/1990/problem/A

"""
Algorithm: Game Theory and Sorting
Techniques: Sorting, Greedy Approach, Turn-based Game Analysis

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array

This problem involves a turn-based game where two players (Alice and Bob) take turns
performing operations on an array. Each operation allows a player to pick an element
greater than or equal to the current 'mx' value, update 'mx', and set the array element to 0.
The game ends when no valid operation is possible.
We analyze the game by sorting the array in descending order and simulating the 
alternating turns to determine if Alice has a winning strategy.
"""

for i in range(int(input())):
    n = int(input())
    l1 = sorted(list(map(int, input().split())))[::-1]  # Sort in descending order
    last, count = l1[0], 1  # Initialize with first element
    for i in range(0, n - 1):
        if l1[i] != l1[i + 1]:  # If current element is different from next
            if count % 2 == 1:  # If odd count of same elements
                print("YES")
                i = -100  # Mark as found
                break
            else:
                count = 1  # Reset count
        else:
            count += 1  # Increment count for same elements
    if i != -100:  # If we didn't break earlier
        if count % 2 == 0:  # If final group has even count
            print("NO")
        else:
            print("YES")


# https://github.com/VaHiX/CodeForces/
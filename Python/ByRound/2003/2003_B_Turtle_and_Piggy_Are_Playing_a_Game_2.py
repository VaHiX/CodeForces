# Problem: CF 2003 B - Turtle and Piggy Are Playing a Game 2
# https://codeforces.com/contest/2003/problem/B

"""
B. Turtle and Piggy Are Playing a Game 2

Purpose:
This problem involves a game where two players (Turtle and Piggy) alternately modify a sequence.
Turtle tries to maximize the final value of a[1], while Piggy tries to minimize it.
The game proceeds by selecting an index i and replacing a[i] with either max(a[i], a[i+1]) or min(a[i], a[i+1]), then removing a[i+1].
The optimal strategy can be derived through analysis of how the sequence evolves.

Algorithms/Techniques:
- Greedy approach to determine optimal choices
- Key insight: The final value of a[1] is determined by taking the median of all elements in the sequence
  (with optimal play), because each move effectively compares adjacent elements and reduces the array, ending in the median element.
  
Time Complexity:
- O(n log n) per test case due to sorting the input array.
- This is required for computing the median, which represents the final value of a[1].

Space Complexity:
- O(n) for storing the input array.

"""

for _ in range(int(input())):  # Read number of test cases
    n = int(input())           # Read length of sequence
    lst = sorted(map(int, input().split()))  # Sort the input values
    print(lst[n // 2])         # Print the median (middle element after sorting)


# https://github.com/VaHiX/codeForces/
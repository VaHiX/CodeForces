# Problem: CF 1930 A - Maximise The Score
# https://codeforces.com/contest/1930/problem/A

"""
Code Purpose:
This code solves the problem of maximizing the score in a game where we repeatedly
select two numbers from a list, add the smaller one to the score, and remove both.
The optimal strategy is to sort the array and always pair the smallest elements
to maximize the sum of minimums.

Algorithm/Techniques:
- Sorting: Sort the array to enable greedy pairing.
- Greedy Selection: After sorting, pick every second element (starting from index 0)
  to form pairs, ensuring that the smaller number in each pair contributes to the score.

Time Complexity: O(n log n) due to sorting, where n is the number of elements divided by 2.
Space Complexity: O(n) for storing the input and sorted array.

"""
for s in [*open(0)][2::2]:
    print(sum(sorted(map(int, s.split()))[::2]))


# https://github.com/VaHiX/CodeForces/
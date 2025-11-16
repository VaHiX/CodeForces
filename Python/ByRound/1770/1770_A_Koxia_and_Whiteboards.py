# Problem: CF 1770 A - Koxia and Whiteboards
# https://codeforces.com/contest/1770/problem/A

"""
Purpose: To maximize the sum of integers on whiteboards after performing m operations.
         Each operation allows replacing an integer on a whiteboard with a value from array b.
         The strategy is to greedily select the largest values from b to replace the smallest 
         values in a, and place the largest value from b at the position that gives maximum gain.

Algorithms/Techniques: Greedy algorithm, sorting, array manipulation.

Time Complexity: O((n + m) * log(n + m)) due to sorting of combined array.
Space Complexity: O(n + m) for storing combined array of a and b.
"""

for _ in " " * int(input()):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    # Combine a and all but the last element of b, sort in descending order,
    # then take the first (n-1) elements and add the last element of b
    s = sum(sorted(a + b[:-1], reverse=True)[: n - 1]) + b[-1]
    print(s)


# https://github.com/VaHiX/CodeForces/
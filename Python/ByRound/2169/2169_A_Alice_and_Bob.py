# Problem: CF 2169 A - Alice and Bob
# https://codeforces.com/contest/2169/problem/A

"""
Algorithm: 
- For each marble, determine whether it's closer to Alice's choice 'a' or Bob's choice 'b'.
- Since Bob wants to maximize his points, we try to find a value 'b' that splits the marbles favorably.
- Key insight: For any marble value v, if |v - a| < |v - b|, Alice gets the point; otherwise Bob gets it.
- To simplify, we can sort marbles and analyze how many are on each side of 'a'.
- Then, we can try values around 'a' such as a+1 or a-1 and evaluate which gives more points to Bob.

Time Complexity: O(n log n) due to sorting (though the input is already sorted by constraints).
Space Complexity: O(1) - only using a few variables for computation.

The approach is based on:
- Counting marbles that are greater than or equal to 'a' (call count 'c') and less than 'a' (call count 'p')
- If c > p, choosing b = a + 1 ensures Bob gains more points (because he wins on marbles >= a)
- Otherwise, choosing b = a - 1 maximizes his points
"""

for _ in range(int(input())):
    n, a = map(int, input().split())
    v = list(map(int, input().split()))
    c, p = 0, 0
    for i in v:
        if i >= a:
            c += 1
        else:
            p += 1
    print(a + 1 if c > p else a - 1)


# https://github.com/VaHiX/CodeForces/
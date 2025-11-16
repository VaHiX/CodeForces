# Problem: CF 1847 F - The Boss's Identity
# https://codeforces.com/contest/1847/problem/F

"""
Code Purpose:
This code solves the problem of finding the smallest index i such that a[i] > v for each query v.
The sequence a is defined such that the first n elements are given, and for i > n, a[i] = a[i-n] | a[i-n+1],
where | denotes bitwise OR. The sequence eventually becomes periodic due to the nature of bitwise OR operation,
so we can simulate the sequence and maintain a queue of indices that are yet to be computed.

Algorithms/Techniques:
- Sliding window with a queue for generation of new sequence values
- Binary search approach via sorting queries by value in descending order
- Efficient tracking of maximum value in current sequence to avoid redundant computation

Time Complexity:
- O(n log n + q log q) for sorting and processing queries
- O(n + q) for simulation and query processing, as each element is processed at most twice
- Overall: O(n + q log q), where n is the size of initial sequence and q is number of queries

Space Complexity:
- O(n + q) for storing sequence, queries and auxiliary data structures
"""

for _ in range(int(input())):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    v = list(int(input()) for _ in range(q))
    ans = [-1] * q
    mx = 0
    for x in a:
        mx |= x  # Compute OR of all elements to find max possible value
    qry = list((v[i], i) for i in range(q))
    qry.sort(key=lambda x: -x[0])  # Sort queries in descending order of value

    que = []
    head, tail = 0, 0
    pre_mx = 0
    for i in range(n):
        que.append(i + n)  # Add next index to be computed
        tail += 1
        pre_mx = max(pre_mx, a[i])
        # While max value so far is greater than query value, answer the query
        while len(qry) > 0 and pre_mx > qry[-1][0]:
            ans[qry[-1][1]] = i + 1
            qry.pop()

    # Continue generating values and answering queries if needed
    while head < tail and len(qry) > 0 and qry[-1][0] < mx:
        id = que[head]
        head += 1
        # Compute next value using OR of previous two terms
        nval = a[(id - n) % n] | a[(id - n + 1) % n]
        if nval == a[id % n]:
            # Skip if value is unchanged, no point in continuing
            continue
        else:
            a[id % n] = nval  # Update current value
            pre_mx = max(pre_mx, nval)  # Track maximum seen so far
            # While we have queries with value less than current max, answer them
            while len(qry) > 0 and pre_mx > qry[-1][0]:
                ans[qry[-1][1]] = id + 1
                qry.pop()

            # Schedule next two indices to be computed
            que.append(id + n - 1)
            tail += 1
            que.append(id + n)
            tail += 1

    for i in range(q):
        print(ans[i])


# https://github.com/VaHiX/CodeForces/
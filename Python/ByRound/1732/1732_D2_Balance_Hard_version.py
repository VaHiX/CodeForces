# Problem: CF 1732 D2 - Balance (Hard version)
# https://codeforces.com/contest/1732/problem/D2

import heapq
import sys

input = sys.stdin.readline

s = set()
next_to_check = {}
deleted = {}
factors = {}

for _ in range(int(input())):
    op, x = input().split()
    x = int(x)

    if op == "+":
        s.add(x)
    elif op == "-":
        s.remove(x)
        for y in factors.get(x, []): # For each factor y of x
            if x % y == 0 and x // y < next_to_check[y]: # If x is divisible by y and the quotient is less than next_to_check[y]
                deleted.setdefault(y, []) # Initialize the heap for y if not present
                heapq.heappush(deleted[y], x // y) # Add the quotient to the heap
    else: # op == "?"
        i = next_to_check.get(x, 1) # Get the current value of i for factor x, default is 1
        dels = deleted.get(x, []) # Get the heap of deleted quotients for factor x
        while dels and dels[0] < i and dels[0] * x in s: # While there are deletions and the smallest deletion is less than i and the value is still in set
            heapq.heappop(dels) # Remove the smallest deletion
        if dels: # If there are still deletions left
            i = dels[0] # Set i to the smallest remaining deletion
        else: # If no deletions are left
            while i * x in s: # While the value i*x is in the set
                factors.setdefault(i * x, []) # Add i*x to the factors if not present
                factors[i * x].append(x) # Add x to the list of factors of i*x
                i += 1 # Increment i
            next_to_check[x] = i # Store the new value of i for factor x
        print(i * x) # Output the k-mex which is i*x

### Complexity Analysis

# **Time Complexity:** $ O(q \log q \log \max(x)) $

# Each operation (add, remove, query) can take logarithmic time. The `heapq` operations are $ O(\log n) $ where $ n $ is the number of elements in the heap. The `factors` and `next_to_check` maps are updated with each add/remove query, which in the worst case could happen for each element. Therefore, with $ q $ queries and logarithmic work per query, the total time complexity is $ O(q \log q \log \max(x)) $.

# **Space Complexity:** $ O(q \log \max(x)) $

# For storing the set $ s $, the `next_to_check` and `deleted` dictionaries, and `factors` mapping to track factors, in the worst case, we may store information proportional to $ q $ and $ \log \max(x) $ entries. The space used in heaps and sets is therefore $ O(q \log \max(x)) $.

# https://github.com/VaHiX/CodeForces/
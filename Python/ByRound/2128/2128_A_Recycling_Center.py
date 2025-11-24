# Problem: CF 2128 A - Recycling Center
# https://codeforces.com/contest/2128/problem/A

"""
Recycling Center

Problem Description:
We have n trash bags with weights a_i. Each second:
1. Choose one bag to destroy:
   - Cost 0 coins if weight <= c
   - Cost 1 coin if weight > c
2. All remaining bags' weights are doubled.

Goal: Find minimum coins to destroy all bags.

Algorithm:
- Sort trash bags in descending order of weight.
- For each bag, simulate destruction process using a greedy approach.
- Use a counter 'st' to track how many times we've delayed destruction of current element,
  and compute required weight (pow(2, st) * bag_weight) against threshold c.

Time Complexity: O(n log n) due to sorting; O(n) for traversal => overall O(n log n)
Space Complexity: O(n) for storing the list of weights

Techniques:
- Greedy strategy
- Sorting to optimize decision making
- Bit manipulation (via pow(2, st)) to simulate weight doubling

Input Format:
- t test cases
- For each case: n and c followed by n weights

Output Format:
- Minimum coins spent per test case
"""

for i in range(int(input())):
    a, b = list(map(int, input().split()))  # a: number of bags, b: threshold weight c
    c = list(map(int, input().split()))    # c: weights of bags
    c.sort(reverse=True)                    # Sort in descending order for greedy approach
    st = 0                                  # Tracks how many times we delayed destruction
    res = 0                                 # Total coins spent
    for i in c:
        q = pow(2, st) * i                  # Compute actual weight after 'st' doublings
        if q <= b:                          # If weight is within threshold
            st += 1                         # Delay destruction, increment counter
        else:                               # If weight exceeds threshold
            res += 1                        # Pay 1 coin to destroy
    print(res)


# https://github.com/VaHiX/codeForces/
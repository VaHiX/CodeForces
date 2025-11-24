# Problem: CF 1924 F - Anti-Proxy Attendance
# https://codeforces.com/contest/1924/problem/F

from math import ceil, floor


def query(a, b):
    # Query the range [a, b] and return whether the number of hands raised equals the expected count
    print("?", a, b)
    ans = int(input())
    return ans == (b - a)


def make_queries(n, r1, r2):
    # Perform a series of queries to narrow down the possible absent student
    # We use three queries to determine the relative positions of r1 and r2
    a1 = query(1, r2 - 1)
    a2 = query(1, r1 - 1)
    if a1 == a2:
        # If the results from queries are same, we perform a third query on full range
        a3 = query(1, n)
        if a3 == a1:
            # The absent student is in range [r1, r2) or [r2, n+1)
            return (r1, r2), (r2, n + 1)
        else:
            # The absent student is in range [1, r1) or [r1, r2)
            return (1, r1), (r1, r2)
    else:
        # If the results from queries are different, we perform a third query on range [1, r2-1]
        a3 = query(1, r2 - 1)
        if a1 == a3:
            # The absent student is in range [1, r1) or [r2, n+1)
            return (1, r1), (r2, n + 1)
        else:
            # The absent student is in range [r1, r2) or [r2, n+1) with additional confirmation
            a4 = query(1, n)
            if a4 == a2:
                return (r1, r2), (r2, n + 1)
            else:
                return (1, r1), (r1, r2)


def run():
    # Read input for number of students
    n = int(input())
    # Initialize list of students as possible absentees
    S = list(range(1, n + 1))

    # Continue until we narrow down to 2 or fewer candidates
    while len(S) > 2:
        # Select two pivot points to perform queries
        r1 = S[floor(0.36 * len(S))]
        r2 = S[ceil(0.64 * len(S))]
        # Make queries to reduce the range of possible absent students
        (la, ra), (lb, rb) = make_queries(n, r1, r2)
        # Update the list of candidates based on query outcomes
        S = [x for x in S if la <= x < ra or lb <= x < rb]

    # Output the last two candidate students
    for x in S:
        print(f"! {x }")
        _ = input()
    print("#")


# Process all test cases
for _ in range(int(input())):
    run()

# ### Flowerbox Description

# **Problem:** Anti-Proxy Attendance

# **Purpose:**
# The code determines the absent student among n students using a series of queries under adversarial conditions. Students may respond dishonestly (False Positive/Negative), but must follow constraints: no 3 honest or 3 dishonest responses in a row.

# **Algorithm:**
# - Use binary search-like technique with strategically selected query points
# - Perform multiple queries with selected ranges to narrow down possible candidates
# - Apply logic based on query results to partition candidate list
# - Output final 2 candidates and query them to identify actual absent student

# **Time Complexity:** O(log^2 n) - The algorithm makes at most O(log n) queries, and each query runs in constant time.

# **Space Complexity:** O(n) - Due to storing list of possible absents `S` that can hold up to `n` elements.

# **Key Techniques:**
# - Adaptive binary search approach
# - Strategic query point selection (36% and 64% of current candidates)
# - Logic-based range narrowing using multiple query results
# - Interactive problem solving with feedback from grader

# https://github.com/VaHiX/CodeForces/
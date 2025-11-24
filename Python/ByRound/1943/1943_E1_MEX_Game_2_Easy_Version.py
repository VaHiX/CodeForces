# Problem: CF 1943 E1 - MEX Game 2 (Easy Version)
# https://codeforces.com/contest/1943/problem/E1

"""
Algorithm: MEX Game 2 (Easy Version)
Purpose: Determine the maximum MEX Alice can achieve when playing optimally against Bob, 
         where Alice picks 1 element and Bob picks up to k elements on their turn.

Time Complexity: O(m^2) per test case, where m is the maximum element in the array.
Space Complexity: O(m) for storing line and sa arrays.

Techniques:
- Greedy strategy with binary search-like checking
- Precompute a line array to determine how many elements of each type 
  can be safely left for Alice to pick
- Simulate Alice's turn and check if it's safe for her to pick element `i`

The approach leverages a precomputed line (dynamic programming-like structure) 
to efficiently determine safe moves. It simulates Alice picking elements,
and at each step checks if the remaining elements allow for a safe continuation
for Alice to increase her score.

"""

T = int(input())
ans = []


def compute_line(k):
    # Precompute line values to determine safe thresholds
    # line[i] = minimum number of elements of value i that must be available 
    # for Alice to be able to secure a score of i
    line = [0, k]
    S = k

    for w in range(2, 51):  # Since m <= 50, we only compute up to 50 elements
        line.append(k + S // w)
        S += line[-1]
    return line


def works(a, line, k):
    # Check if current array configuration leaves Alice with a valid MEX score
    above = 0
    for w in range(len(a)):
        if a[-1 - w] <= line[w]:
            break
        above += a[-1 - w] - line[w]
    return above <= k * len(a)


for t in range(T):
    m, k = [int(x) for x in input().split()]
    a = [int(x) for x in input().split()]

    line = compute_line(k)
    sa = []  # Sorted array of elements Alice has chosen so far

    escape = True
    for i in range(len(a)):
        occ = a[i]
        if occ == 0:
            # If zero occurs, Alice gains a MEX of at least i + 1
            ans.append(i)
            break

        # Insert this occurrence into sorted array
        for j in range(len(sa) + 1):
            if j == len(sa) or sa[j] >= occ:
                sa.insert(j, occ)
                break

        cp = sa[:]
        flag = False
        while len(cp):
            # Check if it's safe for Alice to continue with this configuration
            if works(cp, line, k):
                flag = True
                break
            cp.pop()  # Remove the last element from current configuration
        
        if flag:
            if escape:
                escape = False
                del sa[0]  # Remove first element if we're trying to escape
            else:
                # Found a safe configuration, record Alice's score 
                ans.append(i)
                break
    if len(ans) == t:
        # If no early break happened, append the full length as final score
        ans.append(len(a))

for a in ans:
    print(a)


# https://github.com/VaHiX/CodeForces/
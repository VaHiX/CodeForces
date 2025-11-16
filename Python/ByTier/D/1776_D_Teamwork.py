# Problem: CF 1776 D - Teamwork
# https://codeforces.com/contest/1776/problem/D

"""
Algorithm: Greedy approach with careful scheduling to maximize problem solving within time limit.
Time Complexity: O(1) - since the number of operations is bounded by constants (fixed number of problem types and time constraints).
Space Complexity: O(1) - fixed size data structures regardless of input size.

The approach greedily schedules the most time-consuming problems first (hard, then medium, then easy) 
to make room for more problems in the remaining time, using a priority-based assignment of contestants.
"""

a, b, c, l = map(int, input().split())
ivs = [list(), list(), list()]  # Store intervals for each contestant (easy, medium, hard)


def done():
    # Final output function - prints number of solved problems and their schedules
    ans = len(ivs[0]) + len(ivs[1]) + len(ivs[2])
    print(ans)
    if ans > 0:
        all = (
            list(map(lambda iv: (1, iv[0], iv[1]), ivs[0]))  # Add contestant 1's intervals
            + list(map(lambda iv: (2, iv[0], iv[1]), ivs[1]))  # Add contestant 2's intervals
            + list(map(lambda iv: (3, iv[0], iv[1]), ivs[2]))  # Add contestant 3's intervals
        )
        all.sort(key=lambda iv: iv[2])  # Sort by end time
        for iv in all:
            print(*iv)
    exit(0)


# Initial greedy assignments for easy (2 units), medium (3 units), hard (4 units) problems
if a > 0 and l >= 2:
    ivs[0] = [(0, 2)]
    a -= 1
if l >= 3:
    if b > 0:
        ivs[1] = [(0, 3)]
        b -= 1
    elif a > 0:
        ivs[1] = [(1, 3)]
        a -= 1
if l >= 4:
    if c > 0:
        ivs[2] = [(0, 4)]
        c -= 1
    elif b > 0:
        ivs[2] = [(1, 4)]
        b -= 1
    elif a > 0:
        ivs[2] = [(2, 4)]
        a -= 1
else:
    done()

curr = 4  # Current time unit tracking

# Assign medium problems if possible
if len(ivs[1]) == 0:
    if l >= 5 and c > 0:
        ivs[1] = [(1, 5)]
        c -= 1
        curr = 5
    else:
        done()

# Assign easy problems if possible
if len(ivs[0]) == 0:
    if curr == 5:
        if l >= 6 and c > 0:
            ivs[0] = [(2, 6)]
            c -= 1
            curr = 6
        else:
            done()
    else:
        if l >= 5 and (b > 0 or c > 0):
            if c > 0:
                ivs[0] = [(1, 5)]
                c -= 1
                curr = 5
            elif b > 0:
                ivs[0] = [(2, 5)]
                b -= 1
                curr = 5
        else:
            done()
elif curr == 5:
    if l >= 6 and c > 0:
        ivs[0] += [(2, 6)]
        c -= 1
        curr = 6
    else:
        done()

# Continue assigning remaining problems to optimize usage of time
while curr < l:
    ids = [0, 1, 2]
    ids.sort(key=lambda i: ivs[i][-1][1])  # Sort by last end time of each contestant
    if c > 0:  # If there are hard problems left
        if a > 0:  # If there are easy problems left
            ivs[ids[1]] += [(curr - 1, curr + 1)]  # Schedule easy problem for second contestant
            a -= 1
            curr += 1
            if curr == l:
                done()
            else:
                ivs[ids[0]] += [(curr - 3, curr + 1)]  # Schedule hard problem for first contestant
                c -= 1
                curr += 1
        elif b > 0:  # If there are medium problems left
            ivs[ids[0]] += [(curr - 2, curr + 1)]  # Schedule medium problem for first contestant
            b -= 1
            curr += 1
        else:
            if curr + 2 > l:  # If not enough time
                done()
            else:
                ivs[ids[0]] += [(curr - 2, curr + 2)]  # Schedule hard problem for first contestant
                c -= 1
                curr += 2
                if curr + 1 <= l and c > 0:
                    ivs[ids[1]] += [(curr - 3, curr + 1)]  # Schedule hard problem for second contestant
                    c -= 1
                    curr += 1
                if curr + 1 <= l and c > 0:
                    ivs[ids[2]] += [(curr - 3, curr + 1)]  # Schedule hard problem for third contestant
                    c -= 1
                    curr += 1
    else:
        if b > 0:  # If there are medium problems left
            ivs[ids[0]] += [(curr - 2, curr + 1)]  # Schedule medium problem for first contestant
            b -= 1
            curr += 1
        elif a > 0:  # If there are easy problems left
            ivs[ids[1]] += [(curr - 1, curr + 1)]  # Schedule easy problem for second contestant
            a -= 1
            curr += 1
        else:
            done()

done()


# https://github.com/VaHiX/CodeForces/
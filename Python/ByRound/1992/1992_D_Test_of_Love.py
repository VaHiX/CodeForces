# Problem: CF 1992 D - Test of Love
# https://codeforces.com/contest/1992/problem/D

"""
Algorithm: Dynamic Programming with Greedy Approach
Time Complexity: O(n) where n is the length of the river string
Space Complexity: O(n) for storing the split segments

The solution splits the river string by 'L' (logs) to isolate segments between logs.
For each segment:
- If there is a crocodile 'C' in the segment:
  - If the segment length is >= m, we check if we can jump over it or if it's impossible to pass
  - We adjust the remaining swim allowance k accordingly
- If there are no crocodiles:
  - We compute how much we would need to swim in this segment
  - We update k accordingly

The overall idea assumes that ErnKor can jump over gaps up to m meters,
and must swim exactly the number of water segments he needs to cross.
"""

t = int(input())


def ans(n, m, k, a):
    x = a.split("L")
    ans = "YES"
    for j in x:
        if not (j == ""):
            if "C" in j:
                if len(j) >= m:
                    o = j.rfind("C")
                    if o + 1 >= m:
                        return "NO"
                    else:
                        if len(j) - (m - 1) > k:
                            return "NO"
                        else:
                            k -= len(j) - (m - 1)

            else:
                if len(j) >= m:
                    if len(j) - (m - 1) > k:
                        return "NO"
                    else:
                        k -= len(j) - (m - 1)
    return ans


answers = []

for i in range(t):
    n, m, k = map(int, input().split(" "))
    a = input()
    answers.append(ans(n, m, k, a))

for answer in answers:
    print(answer)


# https://github.com/VaHiX/CodeForces/
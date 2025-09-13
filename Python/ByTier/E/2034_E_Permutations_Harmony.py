# Contest 2034, Problem E: Permutations Harmony
# URL: https://codeforces.com/contest/2034/problem/E


from itertools import permutations


def pp(str):
    if debug:
        print("ANSWER:", str)
    else:
        print(str)


def pp_arr(arr):
    if debug:
        print("ANSWER: " + " ".join(list(map(str, arr))))
    else:
        print(" ".join(list(map(str, arr))))


def factorial(n):
    if n == 0:
        return 1
    return n * factorial(n - 1)


def solve():
    n, k = map(int, input().split())
    if n == 1:
        # if k = 1, then we can output 1
        if k == 1:
            pp("YES")
            pp("1")
            return
        else:
            pp("NO")
            return
    if k == 1:
        # obviously fails
        pp("NO")
        return

    if n <= 10:
        # check if k is less than or equal to n!
        if k > factorial(n):
            pp("NO")
            return

    if k % 2 == 0:
        kk = k // 2
        # say the REFLECTION of a permuation a is b where b[i] = n+1 - a[i]
        # we can just output a bunch of reflections
        pp("YES")
        cnt = 0
        for perm in permutations(range(1, n + 1)):
            if cnt == kk:
                return
            pp_arr(perm)
            reflection = [n + 1 - x for x in perm]
            pp_arr(reflection)
            cnt += 1

    else:
        # k is odd and at least 3
        # if n is even we fail
        if n % 2 == 0:
            pp("NO")
            return
        m = n // 2  # n = 2m + 1
        # what we do is: construct 3 working permutaitons, and then add a bunch of reflection-pairs
        if n < 3:
            pp("NO")
            return
        if n <= 12:
            if k > factorial(n) - 3:
                pp("NO")
                return
        pp("YES")
        # construct 3 working permutations
        # as an example, when m = 4
        # perm1 = [1, 2, 3, 4, 5, 6, 7, 8, 9]
        # perm2 = [8, 6, 4, 2, 9, 7, 5, 3, 1]
        # perm3 = [6, 7, 8, 9, 1, 2, 3, 4, 5]
        perm1 = list(range(1, n + 1))
        perm2 = []
        for i in range(m):
            perm2.append(2 * m - 2 * i)
        for i in range(m + 1):
            perm2.append(2 * m + 1 - 2 * i)
        perm3 = []
        for i in range(m + 2, n + 1):
            perm3.append(i)
        for i in range(1, m + 2):
            perm3.append(i)

        pp_arr(perm1)
        pp_arr(perm2)
        pp_arr(perm3)

        # now, we output a bunch of reflection pairs
        num_pairs = (k - 3) // 2

        cnt = 0
        for perm in permutations(range(1, n + 1)):
            if cnt == num_pairs:
                return
            reflection = [n + 1 - x for x in perm]
            # check whether the permutation is one of the 3 working permutations
            if list(perm) == perm1 or list(perm) == perm2 or list(perm) == perm3:
                continue
            if (
                list(reflection) == perm1
                or list(reflection) == perm2
                or list(reflection) == perm3
            ):
                continue
            pp_arr(perm)
            pp_arr(reflection)
            cnt += 1


debug = False
t = int(input())
for _ in range(t):
    solve()

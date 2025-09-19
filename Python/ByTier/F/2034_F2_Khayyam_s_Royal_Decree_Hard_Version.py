# Contest 2034, Problem F2: Khayyam's Royal Decree (Hard Version)
# URL: https://codeforces.com/contest/2034/problem/F2

import sys

mod = 998244353
maxn = 400010

# preprocess factorials/inverse factorials
facts = [1] * maxn
ifacts = [1] * maxn
for i in range(1, 400010):
    facts[i] = (i * facts[i - 1]) % mod
ifacts[maxn - 1] = pow(facts[maxn - 1], mod - 2, mod)
for i in range(maxn - 2, -1, -1):
    # flt
    ifacts[i] = (ifacts[i + 1] * (i + 1)) % mod


# generic counting
def count(rb, r):
    # impossible later config
    if r < 0 or r > rb:
        return 0
    # use fact arrays
    return (facts[rb] * ifacts[r] % mod) * ifacts[rb - r] % mod


# # calculate paths between i and j
# def paths(scrolls,i,j):
#     r=scrolls[j][0]-scrolls[i][0]
#     b=scrolls[j][1]-scrolls[i][1]
#     return count(r+b,b)

# # modular addition
# def madd(x,y):
#     s=(x+y)%mod
#     # assert nonnegative
#     return (s+mod)%mod


def solve(tok, idx):
    # input stuff is too slow (timed out on test 17)
    n = int(tok[idx])
    m = int(tok[idx + 1])
    k = int(tok[idx + 2])
    idx += 3

    # store scrolls (k+2 for a "0-state" & "end-state")
    scrolls = [(0, 0)] * (k + 2)
    # terminate early if no scrolls
    if k == 0:
        return ((2 * n + m) % mod, idx)

    for i in range(1, k + 1):
        r = int(tok[idx])
        b = int(tok[idx + 1])
        # convert scrolls to reflect score wrt satchel
        scrolls[i] = (n - r, m - b)
        idx += 2
    scrolls[k + 1] = (n, m)

    # sort
    scrolls.sort()
    # update k to include 0-state
    k = len(scrolls) - 1

    # calculate paths between i and j
    def paths(i, j):
        r = scrolls[j][0] - scrolls[i][0]
        b = scrolls[j][1] - scrolls[i][1]
        return count(r + b, b)

    # dp weights (see my notes lol)
    cnt = [0] * (k + 1)
    # end state
    cnt[k] = 1

    for i in range(k - 1, 0, -1):
        s = 0
        for j in range(i + 1, k + 1):
            s = (s + paths(i, j) * cnt[j]) % mod
        cnt[i] = s

    # accumulate expected value
    ans = 0
    for i in range(1, k + 1):
        delta = (2 * scrolls[i][0] + scrolls[i][1]) % mod
        ans = (ans + delta * paths(0, i) % mod * cnt[i]) % mod

    # divide by total #paths from (0,0) to (n,m)
    ans = ans * pow(count(n + m, m), mod - 2, mod) % mod
    return ans, idx

    # # dp paths from each scroll state -> other scroll state
    # pcount=[[0]*(k+1) for _ in range(k+1)]
    # for i in range(1,k+1):
    #     for j in range(i-1,-1,-1):
    #         pcount[j][i]=paths(j,i)
    #         for l in range(j+1,i):
    #             pcount[j][i]=madd(pcount[j][i],-paths(j,l)*pcount[l][i])

    # dp=[0]*(k+1)
    # for i in range(1,k+1):
    #     for j in range(0,i):
    #         if pcount[j][i]==0:
    #             continue
    #         partial=dp[j]
    #         delta=2*(scrolls[i][0]-scrolls[j][0])+(scrolls[i][1]-scrolls[j][1])
    #         partial=madd(partial,paths(0,j)*delta)
    #         dp[i]=madd(dp[i],partial*pcount[j][i])
    #     if i!=k:
    #         dp[i]=(2*dp[i])%mod

    # # use built in power function and fermat's lt
    # denom=pow(count(n+m,m),mod-2,mod)
    # # take correct mod
    # return (dp[k]*denom)%mod


def main():
    tok = sys.stdin.buffer.read().split()
    idx = 0
    t = int(tok[idx])
    idx += 1
    out = []
    for _ in range(t):
        res, idx = solve(tok, idx)
        out.append(str(res))
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    main()

# Contest 2039, Problem F1: Shohag Loves Counting (Easy Version)
# URL: https://codeforces.com/contest/2039/problem/F1

class LPF:
   @staticmethod
   def lpf_table(N: int) -> tuple[list[int], list[int]]:
      if N <= 1: return [0, 0], []

      small = [2, 3, 5]
      prod = 30
      next = 7
      assert next%2 == 1

      def proc(x):
         for p in small:
            if x%p == 0:
               return p
         return 0

      lookup = [proc(x) for x in range(prod)]
      dp = lookup*(N//prod + 1)
      del dp[N+1:]
      dp[0] = 0
      P = []
      for x in range(next, N+1, 2):
         lpf = dp[x]
         if lpf == 0:
            dp[x] = lpf = x
            P.append(x)
         if next <= lpf:
            for np in P:
               if lpf < np or not (np*x <= N):
                  break
               dp[np*x] = np
      P[:0] = [p for p in small if p <= N]
      return dp, P


class LinearSieve:
   def __init__(self, N_) -> None:
      N = max(int(N_), 0) + 100
      self.N = N

      self.lpf, self.P = LPF.lpf_table(N)

   def factors(self, X) -> list[tuple[int, int]]:
      assert 1 <= X <= self.N
      F = []
      while X > 1:
         p = self.lpf[X]
         e = 0
         while X%p == 0:
            X //= p
            e += 1
         F.append((p, e))
      return F

   def divisors(self, X, *, sort=True):
      assert 1 <= X <= self.N
      D = [1]
      for p, e in self.factors(X):
         P = [p]*e
         for i in range(1, e):
            P[i] = P[i-1] * p
         nD = D[:]
         for p in P:
            nD.extend([p*d for d in D])
         D = nD
      if sort:
         D.sort()
      return D


def solve(N):
   ls = LinearSieve(N)

   dp = [0]*(N+1)
   Zdp = [0]*(N+1)
   memo = [0]*(N+1)
   for x in range(N, 0, -1):
      D = ls.divisors(x)
      P = [p for p, _ in ls.factors(x)]
      for d in D:
         memo[d] = Zdp[d]
      for p in P:
         for d in D:
            if d%p == 0:
               memo[d//p] -= memo[d]
      for d in D:
         dcnt = memo[d] - dp[d]
         dcnt %= MOD
         memo[d] = dcnt*2
         dp[d] += dcnt*2
         dp[d] %= MOD
      for p in P:
         for d in reversed(D):
            if d%p == 0:
               memo[d//p] += memo[d]
      for d in D:
         Zdp[d] += memo[d]
         Zdp[d] %= MOD
      dp[x] += 1
      for d in D:
         Zdp[d] += 1
      for d in D:
         memo[d] = 0

   return sum(dp) % MOD


MOD = 998_244_353

ans = []
for _ in range(int(input())):
   N = int(input())
   ans.append(solve(N))

print(*ans, sep="\n")

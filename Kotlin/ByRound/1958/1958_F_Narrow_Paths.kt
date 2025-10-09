// Contest 1958, Problem F: Narrow Paths
// URL: https://codeforces.com/contest/1958/problem/F

fun main() {
  val MOD = 1_000_000_007L
  val FAC = LongArray(400_001)
  val INV = LongArray(400_001)
  FAC[0] = 1
  for (i in 1 until FAC.size) FAC[i] = FAC[i - 1] * i % MOD
  INV[0] = 1
  INV[1] = 1
  for (i in 2 until INV.size) INV[i] = INV[MOD.toInt() % i] * (MOD - MOD / i) % MOD
  for (i in 2 until INV.size) INV[i] = INV[i - 1] * INV[i] % MOD

  fun comb(n: Int, k: Int) = FAC[n] * INV[k] % MOD * INV[n - k] % MOD

  val (n, k) = readln().split(' ').map { it.toInt() }
  val ans = LongArray(n + 1)
  for (i in 1..(n - k)) ans[i] =
      ((n - i - 1) * comb(n - i - 2, k - 2) + 2 * comb(n - i - 1, k - 1)) % MOD
  ans[0] = (comb(2 * n - 2, k) - ans.sum()) % MOD
  if (ans[0] < 0L) ans[0] += MOD
  println(ans.joinToString(" "))
}

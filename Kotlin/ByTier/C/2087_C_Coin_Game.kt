// Contest 2087, Problem C: Coin Game
// URL: https://codeforces.com/contest/2087/problem/C

import java.util.StringTokenizer

fun main() {
  val br = System.`in`.bufferedReader()
  val out = StringBuilder()

  var tc = 1
  repeat(tc) { solve(br, out) }

  print(out.toString())
}

fun solve(br: java.io.BufferedReader, out: StringBuilder) {
  val s = br.readLine()
  val n = s.length
  val Gold = IntArray(n + 1)
  val Silver = IntArray(n + 1)
  val Bronze = IntArray(n + 1)

  for (i in 0 until n) {
    Gold[i + 1] = Gold[i] + if (s[i] == 'G') 1 else 0
    Silver[i + 1] = Silver[i] + if (s[i] == 'S') 1 else 0
    Bronze[i + 1] = Bronze[i] + if (s[i] == 'B') 1 else 0
  }

  val q = br.readLine().toInt()
  repeat(q) {
    val st = StringTokenizer(br.readLine())
    val l = st.nextToken().toInt()
    val r = st.nextToken().toInt()
    val gold = Gold[r] - Gold[l - 1]
    val silver = Silver[r] - Silver[l - 1]
    val bronze = Bronze[r] - Bronze[l - 1]
    out.append(maxOf(gold, maxOf(silver, bronze)) + minOf(gold, minOf(silver, bronze))).append('\n')
  }
}

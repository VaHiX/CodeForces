// Contest 2087, Problem E: Color the Arrows
// URL: https://codeforces.com/contest/2087/problem/E

fun mainA() {
  repeat(readln().toInt()) {
    val (a, b, c) = readln().split(" ").map { it.toInt() }
    println(
        (List(a) { "01"[it and 1] } + List(b) { "AB"[it and 1] } + List(c) { "ab"[it and 1] })
            .joinToString("")
    )
  }
}

fun mainB() {
  repeat(readln().toInt()) {
    val n = readln().toInt()
    val a = readln().split(" ").map { it.toInt() }.sorted()
    println(
        if (
            (1 until 2 * n - 1).all {
              a[it + 1 - (it and 1)] - a[it - (it and 1)] <=
                  a[it + (it and 1)] - a[it - 1 + (it and 1)]
            }
        )
            "YES"
        else "NO"
    )
  }
}

fun mainC() {
  val s = readln()
  val sums = "GSB".map { s.runningFold(0) { prv, v -> prv + if (v == it) 1 else 0 } }
  repeat(readln().toInt()) {
    val (l, r) = readln().split(" ").map { it.toInt() }
    val freqs = sums.map { it[r] - it[l - 1] }.sorted()
    println(freqs[0] + freqs[2])
  }
}

fun mainD() {
  val (n_str, target) = readln().split(" ")
  val n = n_str.toInt()

  val ans =
      fun(): Int {
            val query = { idx: Int ->
              println("? ${idx + 1}")
              System.out.flush()
              readln()
            }

            val s0 = query(0)
            if (s0 == target) {
              return 0
            }
            val s1 = query(n / 2)
            if (s1 == target) {
              return n / 2
            }
            var (mi, ma) =
                if (if (s0 < s1) s0 < target && target < s1 else !(s1 < target && target < s0)) {
                  Pair(0, n / 2)
                } else {
                  Pair(n / 2, n)
                }
            while (ma - mi > 2) {
              val md = (mi + ma) / 2
              val s = query(md)
              if (s == target) {
                return md
              } else if (s < target) {
                mi = md
              } else {
                ma = md
              }
            }
            return mi + 1
          }
          .invoke()
  println("! ${ans + 1}")
  System.out.flush()
}

fun mainE() {

  repeat(readln().toInt()) {
    val n = readln().toInt()

    val orig_s = readln().map { it == '>' }
    val orig_c = readln().split(" ").map { it.toInt() }

    var ans: Long = 0
    listOf(orig_s.zip(orig_c), orig_s.map { !it }.zip(orig_c).reversed()).forEach {
      var cur: Long = 0
      it.forEach {
        if (!it.first) {
          ans = maxOf(ans, cur + it.second)
        }
        cur += maxOf(it.second, 0)
      }
    }
    println(ans)
  }
}

fun main() {
  mainE()
}

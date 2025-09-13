// Contest 2087, Problem D: Uppercase or Lowercase?
// URL: https://codeforces.com/contest/2087/problem/D

fun query(x: Int): String {
  println("? ${x + 1}")
  System.out.flush()
  return readln()
}

fun lower(a: String, b: String, rev: Boolean): Boolean {
  val a_ = a[0].isLowerCase()
  val b_ = b[0].isLowerCase()
  if (a_ == b_) {
    return a <= b
  }
  return a_ == rev
}

fun main() {
  val (n_, h) = readln().split(" ")
  val n = n_.toInt()
  val rev = query(0)[0].isLowerCase()
  var l = 0
  var r = n
  var mid = (l + r) / 2
  while (r - l > 1) {
    if (lower(query(mid), h, rev)) l = mid else r = mid
    mid = (l + r) / 2
  }
  println("! ${l + 1}")
}

// Contest 2011, Problem A: Problem Solving
// URL: https://codeforces.com/contest/2011/problem/A

fun solve() {
  readln()
  val a = readln().split(' ').map(String::toInt)
  println(if (a.dropLast(1).contains(a.last() - 1)) (a.last() - 1).toString() else "Ambiguous")
}

fun main() {
  val t = readln().toInt()
  repeat(t) { solve() }
}

// Contest 1958, Problem D: Staircase
// URL: https://codeforces.com/contest/1958/problem/D

fun main() {
  repeat(readln().toInt()) { println(solve()) }
}

fun solve(): Long {
  readln()
  val list = readln().split(' ').map(String::toLong)
  var sum = list.sum().shl(1)
  var max = 0L
  var count = 0
  list.forEach {
    if (it != 0L) {
      if (count.and(1) == 0 && it > max) max = it
      count++
    } else {
      if (count.and(1) != 0) sum -= max
      max = 0L
      count = 0
    }
  }
  if (count.and(1) != 0) sum -= max
  return sum
}

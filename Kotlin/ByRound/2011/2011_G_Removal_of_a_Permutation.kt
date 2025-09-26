// Contest 2011, Problem G: Removal of a Permutation
// URL: https://codeforces.com/contest/2011/problem/G

fun next() = readLine()!!

fun nextInt() = next().toInt()

fun nextInts() = next().split(" ").map { it.toInt() }

var tx = IntArray(1000005)

fun main() {
  var T = nextInt()
  while (T > 0) {
    T -= 1
    var n = nextInt()
    var a = nextInts()
    var init = ArrayList<Int>()
    for (i in 0 until n) {
      init.add(a[i] - 1)
    }
    var MAX_STEP = 19
    var ans = IntArray(n - 1)
    for (i in 0 until (n - 1)) {
      ans[i] = MAX_STEP
    }
    fun rec(arr: ArrayList<Int>, step: Int) {
      if (step >= MAX_STEP) {
        return
      }
      if (arr.size <= 1) {
        return
      }
      var lower = ArrayList<Int>()
      for (i in 0..(arr.size - 2)) {
        if (arr[i] < arr[i + 1]) {
          ans[arr[i]] = minOf(ans[arr[i]], step + 1)
        } else {
          lower.add(arr[i])
        }
      }
      lower.add(arr[arr.size - 1])
      rec(lower, step + 1)
      var upper = ArrayList<Int>()
      upper.add(arr[0])
      for (i in 1..(arr.size - 1)) {
        if (arr[i - 1] > arr[i]) {
          ans[arr[i]] = minOf(ans[arr[i]], step + 1)
        } else {
          upper.add(arr[i])
        }
      }
      rec(upper, step + 1)
    }
    rec(init, 0)
    println(ans.joinToString(" "))
  }
}

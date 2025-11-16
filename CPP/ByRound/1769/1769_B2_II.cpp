// Problem: CF 1769 B2 - Копирование файлов II
// https://codeforces.com/contest/1769/problem/B2

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#define w int64_t
using namespace std;
w f(w x) { return x + 100 * (x % 100 != 0) - x % 100; }
w g(w x) { return x - x % 100; }
int main() {
  w n, o = 0, e = 0, l, r, ll, rr, p;
  cin >> n;
  vector<w> a(n);
  set<w> b;
  for (w &x : a)
    cin >> x, o += x;  // Подсчитываем общий размер всех файлов
  for (w x : a) {
    for (p = 0; p <= 100; p++) {
      // Вычисляем границы для текущего процента p в текущем файле
      l = max(p * x, p * o - 100 * e),  // Левая граница
      r = min((p + 1) * x - 1, (p + 1) * o - 1 - 100 * e),  // Правая граница
      ll = f(l) / 100,  // Нижняя граница для первого прогресс-бара
      rr = g(r) / 100;  // Верхняя граница для второго прогресс-бара
      if (ll <= rr && ll <= x)  // Проверяем пересечение диапазонов
        b.insert(p);  // Добавляем процент в множество
    }
    e += x;  // Обновляем смещение для следующего файла
  }
  for (w x : b)
    cout << x << '\n';
}


// https://github.com/VaHiX/CodeForces/
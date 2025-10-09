/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include "bits/stdc++.h"
using namespace std;
const int maxn = 2e5 + 10;
int _, n;
char c[maxn];
vector<int> Vc[3]; // YD DX XY
vector<int> B;     // XYD
struct Chain {
  int Lb, Rb, Dl;
  char C;
} L[maxn];
bool CheckTriple(int y_0, int y_1, int y_2) {
  if (L[y_0].Dl || L[y_1].Dl || L[y_2].Dl)
    return 0;
  if (c[y_0] == c[y_1] || c[y_1] == c[y_2] || c[y_0] == c[y_2])
    return 0;
  return 1;
}
void Check(int x) {
  // cerr<<"C:"<<x<<' '<<L[x].Lb<<' '<<x<<' '<<L[x].Rb<<' '<<L[L[x].Lb].C<<'
  // '<<L[x].C<<' '<<L[L[x].Rb].C<<endl;
  if (L[x].C == 'Y' && L[L[x].Rb].C == 'D')
    Vc[0].push_back(x);
  if (L[x].C == 'D' && L[L[x].Rb].C == 'Y')
    Vc[0].push_back(x);
  if (L[x].C == 'X' && L[L[x].Rb].C == 'D')
    Vc[1].push_back(x);
  if (L[x].C == 'D' && L[L[x].Rb].C == 'X')
    Vc[1].push_back(x);
  if (L[x].C == 'Y' && L[L[x].Rb].C == 'X')
    Vc[2].push_back(x);
  if (L[x].C == 'X' && L[L[x].Rb].C == 'Y')
    Vc[2].push_back(x);
  if (CheckTriple(L[x].Lb, x, L[x].Rb))
    B.push_back(x); // cerr<<"x:"<<x<<endl;
}
struct Node {
  int A, B, C;
} Cr;
vector<Node> pp;
int DualDelete(int x, int Ty) {
  if (L[x].Dl || L[L[x].Rb].Dl)
    return 0;
  if (Ty == 1 && (L[x].C ^ L[L[x].Rb].C) != ('Y' ^ 'D'))
    return 0;
  if (Ty == 2 && (L[x].C ^ L[L[x].Rb].C) != ('X' ^ 'D'))
    return 0;
  if (Ty == 3 && (L[x].C ^ L[L[x].Rb].C) != ('X' ^ 'Y'))
    return 0;
  int Lb = L[x].Lb, Rb = L[L[x].Rb].Rb;
  if (Lb != 0 && Rb != 0 && L[Lb].C == L[Rb].C)
    return 0;
  Cr.A = x, Cr.B = L[x].Rb;
  L[x].Dl = 1, L[L[x].Rb].Dl = 1;
  L[Lb].Rb = Rb, L[Rb].Lb = Lb;
  Check(Lb), Check(L[Lb].Lb), Check(Rb), Check(L[Rb].Rb);
  return 2;
}
int TripleDelete(int x) {
  if (!CheckTriple(L[x].Lb, x, L[x].Rb))
    return 0;
  int Lb = L[L[x].Lb].Lb, Rb = L[L[x].Rb].Rb;
  if (Lb != 0 && Rb != 0 && L[Lb].C == L[Rb].C)
    return 0;
  Cr.A = L[x].Lb, Cr.B = x, Cr.C = L[x].Rb;
  L[x].Dl = 1, L[L[x].Lb].Dl = 1, L[L[x].Rb].Dl = 1;
  L[Lb].Rb = Rb, L[Rb].Lb = Lb;
  Check(Lb), Check(L[Lb].Lb), Check(Rb), Check(L[Rb].Rb);
  return 1;
}
void SingleDelete(int x) {
  int Lb = L[x].Lb, Rb = L[x].Rb;
  L[Rb].Lb = Lb, L[Lb].Rb = Rb;
  L[x].Dl = 1;
  Check(Lb), Check(L[Lb].Lb), Check(Rb), Check(L[Rb].Rb);
}
int Ind[maxn], Vs[maxn];
int Lb(int x) { return x & (-x); }
void Modify(int x, int v) {
  for (; x < maxn; x += Lb(x))
    Ind[x] += v;
}
int Query(int x) {
  int r = 0;
  for (; x; x -= Lb(x))
    r += Ind[x];
  return r;
}
void Work(int x) {
  assert(Vs[x] == 0), Vs[x] = 1;
  cout << c[x] << ' ' << Query(x) << ' ';
  Modify(x, 1);
}
// #define DEBUG
int main() {
  ios::sync_with_stdio(0), cin.tie(nullptr);
  cin >> _;
  while (_--) {
    cin >> (c + 1), n = strlen(c + 1);
    int F = 0, Yo = 0, Do = 0, Xo = 0;
    for (int i = 1; i <= n; i++) {
      if (c[i] == 'Y')
        Yo++;
      if (c[i] == 'D')
        Do++;
      if (c[i] == 'X')
        Xo++;
    }
    for (int i = 1; i < n; i++)
      if (c[i] == c[i + 1])
        F = 1;
    if (F || Yo != Do || Do != Xo || Yo != Xo) {
      cout << "NO\n";
    } else {
      for (int i = 1; i <= n; i++)
        L[i].Lb = i - 1, L[i].Rb = i + 1, L[i].C = c[i], L[i].Dl = 0;
      L[n].Rb = 0, L[0].Lb = n, L[1].Lb = 0, L[0].Rb = 1, L[0].Dl = 1;
      for (int i = 0; i <= n; i++)
        Check(i);
      for (int i = 1; i <= n / 3; i++) {
        int F = 0;
        while (B.size() && !F) {
          int K = B.back();
          B.pop_back();
          F = TripleDelete(K);
        }
        char c = L[L[0].Rb].C;
        // cout<<c<<' '<<F<<endl;
        if (c == 'X')
          while (Vc[0].size() && !F) {
            int K = Vc[0].back();
            Vc[0].pop_back();
            F = DualDelete(K, 1);
          }
        else if (c == 'Y')
          while (Vc[1].size() && !F) {
            int K = Vc[1].back();
            Vc[1].pop_back();
            F = DualDelete(K, 2);
          }
        else if (c == 'D')
          while (Vc[2].size() && !F) {
            int K = Vc[2].back();
            Vc[2].pop_back();
            F = DualDelete(K, 3);
          }
        /*if(F==0){
                int p=L[0].Rb;
                while(p!=0)cout<<L[p].Lb<<' '<<p<<' '<<L[p].Rb<<endl,p=L[p].Rb;
        }
        assert(F);*/
        if (F == 2)
          Cr.C = L[0].Rb, SingleDelete(L[0].Rb);
#ifdef DEBUG
        int p = L[0].Rb;
        while (p != 0)
          assert(L[p].C != L[L[p].Rb].C), p = L[p].Rb;
#endif
        // cout<<Cr.A<<' '<<Cr.B<<' '<<Cr.C<<endl;
        pp.push_back(Cr);
      }
      reverse(pp.begin(), pp.end());
      cout << "YES\n";
      for (int i = 1; i <= n; i++)
        cout << c[i];
      cout << '\n';
      for (auto It : pp) {
        Work(It.A), Work(It.B), Work(It.C);
        cout << '\n';
      }
      for (int i = 1; i <= n; i++)
        Modify(i, -1);
    }
    for (int i = 1; i <= n; i++)
      c[i] = 0, Vs[i] = 0, c[i] = 0, L[i].Lb = L[i].Rb = L[i].C = L[i].Dl = 0;
    pp.clear(), Vc[0].clear(), Vc[1].clear(), Vc[2].clear(), B.clear();
  }
}
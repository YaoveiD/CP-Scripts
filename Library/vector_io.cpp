#include <bits/stdc++.h>

using namespace std;

template<typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) {
  is >> p.first >> p.second;
  return is;
}
template<typename T>
istream& operator>>(istream& is, vector<T>& v) {
  for (auto& i : v) is >> i;
  return is;
}
template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
  os << p.first << ' ' << p.second;
  return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  int f = 0;
  for (auto& i : v) {
    if (f++) os << ' ';
    os << i;
  }
  return os;
}


template<typename T, typename U>
pair<T, U>& operator--(pair<T, U>& p) {
  --p.first; --p.second;
  return p;
}
template<typename T, typename U>
pair<T, U>& operator++(pair<T, U>& p) {
  ++p.first; ++p.second;
  return p;
}
template<typename T>
vector<T>& operator--(vector<T> &v){
  for (auto& i : v) --i;
  return  v;
}
template<typename T>
vector<T>& operator++(vector<T> &v){
  for (auto& i : v) ++i;
  return  v;
}

int main() {
  vector<pair<int, int>> A(2);
  cin >> A;
  auto B = ++A; --A;
  cout << A << '\n';
  cout << B << '\n';
  return 0;
}
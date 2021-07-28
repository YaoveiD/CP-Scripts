/*
*  author: yaoveil
*  date:   2021-07-06 09:09:33
*/

// Atcoder abc208_e
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main(int argc, char const *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string N;
  ll K;
  cin >> N >> K;
  vector<int> digit;
  int n = (int) N.size();
  for (int i = n - 1; i >= 0; --i) {
    digit.push_back(N[i] - '0');
  }
  // {{pos, product}, {tight, this digit is leadingzero}} -> count
  map<pair<pair<int, ll>, pair<bool, bool>>, ll> dp;
  function<ll(int, ll, bool, bool)> dfs = [&](int pos, ll prod, bool tight, bool lead) -> ll {
    if (pos == -1) {
      return (prod <= K and !lead); 
    }
    if (!tight and dp.find({{pos, prod}, {tight, lead}}) != dp.end()) {
      return dp[{{pos, prod}, {tight, lead}}];
    }
    int lim = (tight ? digit[pos] : 9);
    ll ret = 0;
    for (int i = 0; i <= lim; ++i) {
      bool new_tight = (i == lim ? tight : false);
      ll z = i;
      if (lead and i == 0) {
        z = 1;
      }
      ret += dfs(pos - 1, prod * z, new_tight, lead and i == 0);

    }
    if (!tight) {
      dp[{{pos, prod}, {tight, lead}}] = ret;
    }
    return ret;
  };

  //from the most significant digit to the least significant digit
  cout << dfs(n - 1, 1LL, true, true) << '\n';
  return 0;
}
/*
* author:  yaoveil
* created: 2021-08-28 13:32:13
*/

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <unordered_map>
#include <vector>
 
using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;

#define FOR(I, N) for (int I = 0; I < (N); ++I)
#define ALL(X) (X).begin(), (X).end()
#define RALL(X) (X).rbegin(), (X).rend()

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  int f = 0;
  for (auto& i : v) {
    if (f++) os << ' ';
    os << i;
  }
  return os;
}

void solve() {
    int N;
    cin >> N;

    vector<int> A(N);
    for (int& a : A)
        cin >> a;

    sort(A.begin(), A.end());

    unordered_map<int, vector<int>> ways;

    function<void(int, int, int)> dfs = [&](int sum, int idx, int mask) -> void {
        if (idx == N)
            return;

        int next_sum = sum + A[idx];
        int next_mask = mask + (1 << idx);
        ways[next_sum].push_back(next_mask);
        dfs(next_sum, idx + 1, next_mask);

        dfs(sum, idx + 1, mask);
    };

    dfs(0, 0, 0);

    auto get = [&](int x) -> vi {
        vector<int> choose;
        
        for (int i = 0; i < N; ++i)
            if ((x >> i) & 1)
                choose.push_back(A[i]);
        
        return choose;
    };

    int summary = 0;

    auto print = [&](int x, int y, auto& S) -> void {
        if (x & y)
            return;

        vi choose_x = get(x);
        vi choose_y = get(y);
        
        if (S.count({choose_x, choose_y}) or S.count({choose_y, choose_x}))
            return;
        S.insert({choose_x, choose_y});

        cout << "--------------------\n";
        cout << choose_x << '\n';
        cout << choose_y << '\n';

        summary += 1;
    };

    for (const auto& p : ways) {
        const auto& masks = p.second;
        int total = (int) masks.size();

        cout << "sum " << p.first << '\n';

        set<pair<vi, vi>> S;
        for (int i = 0; i < total; ++i)
            for (int j = i + 1; j < total; ++j) {
                print(masks[i], masks[j], S);
            }

        cout << "summary " << (int) S.size() << '\n';
        cout << "--------------------\n";
    }

    cout << "total " << summary << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}

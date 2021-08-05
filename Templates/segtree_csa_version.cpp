#include <cstdio>
#include <iostream>

#define int long long

using namespace std;

#define ls (i << 1)
#define rs (i << 1 | 1)

namespace Sgt{
    struct node{
        int l, r;
        int val;
        int lazy;
    }tree[1000005];
    void push_up(int i) {
        tree[i].val = tree[ls].val + tree[rs].val;
    }
    void apply(int i, int val) {
        tree[i].val += val * (tree[i].r - tree[i].l + 1);
        tree[i].lazy += val;
    }
    void push_down(int i) {
        if (!tree[i].lazy) return;
        apply(ls, tree[i].lazy);
        apply(rs, tree[i].lazy);
        tree[i].lazy = 0;
    }
    void build(int i, int l, int r) {
        tree[i].l = l;
        tree[i].r = r;
        tree[i].lazy = 0;
        tree[i].val = 0;
        if (l == r) {
            return;
        }
        int mid = (l + r)>>1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
    }
    void update(int i, int l, int r, int val) {
        if (tree[i].l > r || tree[i].r < l) {
            return;
        }
        if (tree[i].l >= l && tree[i].r <= r) {
            apply(i, val);
            return;
        }
        push_down(i);
        update(ls, l, r, val);
        update(rs, l, r, val);
        push_up(i);
    }
    int query(int i, int l, int r) {
        if (tree[i].l > r || tree[i].r < l) {
            return 0;
        }
        if (tree[i].l >= l && tree[i].r <= r) {
            return tree[i].val;
        }
        push_down(i);
        return query(ls, l, r) + query(rs, l, r);
    }
}

using namespace Sgt;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, Q;
    cin >> N >> Q;
    build(1, 1, N);
    for (int i = 1; i <= N; ++i) {
        int x;
        cin >> x;
        update(1, i, i, x);
    }

    while (Q--) {
        string OP;
        int A, B;
        cin >> OP >> A >> B;
        if (OP == "Q") {
            cout << query(1, A, B) << '\n';
        } else {
            int C;
            cin >> C;
            update(1, A, B, C);
        }
    }
    return 0;
}
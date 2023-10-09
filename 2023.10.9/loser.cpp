#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <bitset>
#include <tuple>
using namespace std;
#ifdef ONLINE_JUDGE

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf;

#endif
int read() {
	int p = 0, flg = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') flg = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		p = p * 10 + c - '0';
		c = getchar();
	}
	return p * flg;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}
const int N = 1e5 + 5, M = 2e5 + 5;

namespace G {

array <int, N> fir;
array <int, M> nex, to;
int cnt;
void add(int x, int y) {
	cnt++;
	nex[cnt] = fir[x];
	to[cnt] = y;
	fir[x] = cnt;
}

}

namespace Hpt {

using G::fir, G::nex, G::to;
array <int, N> siz, dep, fa, son;
void dfs1(int x) {
	siz[x] = 1;
	for (int i = fir[x]; i; i = nex[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		dep[to[i]] = dep[x] + 1;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
	}
}

array <int, N> dfn, idx, top;
int cnt;
void dfs2(int x, int Mgn) {
	cnt++;
	dfn[x] = cnt;
	idx[cnt] = x;
	top[x] = Mgn;
	if (son[x]) dfs2(son[x], Mgn);
	for (int i = fir[x]; i; i = nex[i]) {
		if (to[i] == fa[x] || to[i] == son[x]) continue;
		dfs2(to[i], to[i]);
	}
}

}

array <int, N> s;

namespace Sgt {

array <array <tuple <int, int, int>, N * 4>, 2> edge;
array <int, N * 4> tag;

using Hpt::idx;


tuple <int, int, int> update(tuple <int, int, int> x, tuple <int, int, int> y) {
	/* puts("["); */
	tuple <int, int, int> ans;
	int tmp;
	get <0>(ans) = get <0>(x) + get <0>(y) + (tmp = min(get <1>(x), get <2>(y)));
	get <1>(ans) = get <1>(x) - tmp + get <1>(y);
	get <2>(ans) = get <2>(x) + get <2>(y) - tmp;
	/* puts("]"); */
	return ans;
}
void pushup(int x) {
	edge[tag[x]][x] = update(edge[tag[x * 2]][x * 2], edge[tag[x * 2 + 1]][x * 2 + 1]);
}
void pushdown(int x, int l, int r) {
	/* if (!~tag[x]) return; */
	tag[x * 2] = tag[x];
	tag[x * 2 + 1] = tag[x];
}
void build(int x, int l, int r) {
	tag[x] = 0;
	if (l == r) {
		s[idx[l]] ? get <2>(edge[0][x])++ : get <1>(edge[0][x])++;
		s[idx[l]] ? get <1>(edge[1][x])++ : get <2>(edge[1][x])++;
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
	pushup(x);
}
void modify(int x, int l, int r, int L, int R, int k) {
	if (L > r || R < l) return;
	if (L <= l && R >= r) {
		tag[x] = !tag[x];
		return;
	}
	pushdown(x, l, r);
	int mid = (l + r) >> 1;
	if (L <= mid) modify(x * 2, l, mid, L, R, k);
	if (R > mid) modify(x * 2 + 1, mid + 1, r, L, R, k);
	pushup(x);
}
tuple <int, int, int> query(int x, int l, int r, int L, int R, int k) {
	/* write(tag[x]), putchar(32); */
	/* write(l), putchar(32); */
	/* write(r), puts(""); */
	if (L > r || R < l) return make_tuple(0, 0, 0);
	if (L <= l && R >= r) return edge[!k ? tag[x] : !tag[x]][x];
	pushdown(x, l, r);
	int mid = (l + r) >> 1;
	if (L <= mid && R > mid) return update(query(x * 2, l, mid, L, R, k), query(x * 2 + 1, mid + 1, r, L, R, k));
	if (L <= mid) return query(x * 2, l, mid, L, R, k);
	if (R > mid) return query(x * 2 + 1, mid + 1, r, L, R, k);
}

}

using Hpt::dfn, Hpt::top, Hpt::fa, Hpt::dep;
void modify(int x, int y, int n, int k) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		Sgt::modify(1, 1, n, dfn[top[x]], dfn[x], k);
		x = fa[top[x]];
	}
	if (dfn[x] > dfn[y]) swap(x, y);
	Sgt::modify(1, 1, n, dfn[x], dfn[y], k);
}
tuple <int, int, int> query(int x, int y, int n) {
	tuple <int, int, int> ans1 = make_tuple(0, 0, 0), ans2 = make_tuple(0, 0, 0);
	while (top[x] != top[y]) {
		/* write(x), puts(""); */
		if (dep[top[x]] < dep[top[y]]) {
			ans2 = Sgt::update(Sgt::query(1, 1, n, dfn[top[y]], dfn[y], 1), ans2);
			y = fa[top[y]];
		}
		else {
			ans1 = Sgt::update(ans1, Sgt::query(1, 1, n, dfn[top[x]], dfn[x], 0));
			x = fa[top[x]];
		}
	}
	if (dfn[x] > dfn[y])
		ans2 = Sgt::update(Sgt::query(1, 1, n, dfn[x], dfn[y], 1), ans2);
	else
		ans1 = Sgt::update(ans1, Sgt::query(1, 1, n, dfn[x], dfn[y], 0));
	return Sgt::update(ans1, ans2);
}
int main() {
	/* freopen("loser.in", "r", stdin); */
	freopen("loser.out", "w", stdout);
	int n = read(), q = read();
	for (int i = 2; i <= n; i++) {
		int x = read(), y = read();
		G::add(x, y), G::add(y, x);
	}
	Hpt::dfs1(1), Hpt::dfs2(1, 0);
	for (int i = 1; i <= n; i++)
		s[i] = read();
	Sgt::build(1, 1, n);
	/* write(get <0>(Sgt::query(1, 1, n, dfn[1], dfn[5], 0))), puts(""); */
	while (q--) {
		int op = read(), x = read(), y = read();
		if (op == 1) modify(x, y, n, 0);
		else write(get <0>(query(x, y, n)) * 2), puts("");
	}

	return 0;
}

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <set>
#define pii pair <int, int>
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

#define fi first
#define se second
const int N = 2e6 + 5, inf = 1e9;
array <int, N> s;
array <pair <pii, int>, N> qs;

namespace Sgt {

array <int, 4 * N> edge, tag;
void pushup(int x) {
	edge[x] = min(edge[x * 2], edge[x * 2 + 1]);
}
void pushdown(int x, int l, int r) {
	if (!tag[x]) return;
	int mid = (l + r) >> 1;
	tag[x * 2] = tag[x];
	tag[x * 2 + 1] = tag[x];
	edge[x * 2] = tag[x] - mid + 1;
	edge[x * 2 + 1] = tag[x] - r + 1;
	tag[x] = 0;
}
void build(int x, int l, int r) {
	edge[x] = inf;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
}
void modify(int x, int l, int r, int L, int R, int y) {
	if (L > r || R < l) return;
	if (L <= l && R >= r) {
		edge[x] = y - r + 1;
		tag[x] = y;
		return;
	}
	pushdown(x, l, r);
	int mid = (l + r) >> 1;
	if (L <= mid) modify(x * 2, l, mid, L, R, y);
	if (R > mid) modify(x * 2 + 1, mid + 1, r, L, R, y);
	pushup(x);
}
int query(int x, int l, int r, int L, int R) {
	if (L > r || R < l) return inf;
	if (L <= l && R >= r) return edge[x];
	pushdown(x, l, r);
	int mid = (l + r) >> 1, ans = inf;
	if (L <= mid) ans = min(ans, query(x * 2, l, mid, L, R));
	if (R > mid) ans = min(ans, query(x * 2 + 1, mid + 1, r, L, R));
	return ans;
}

}
using namespace Sgt;
array <int, N> lst, ans;
multiset <int> isl;

namespace Uni {

array <int, N> fa;
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void init(int n) {
	for (int i = 1; i <= n; i++)
		fa[i] = i;
}

}
using namespace Uni;
int main() {
	int n = read();
	for (int i = 1; i <= n; i++)
		s[i] = read();
	init(n);
	int m = read();
	for (int i = 1; i <= m; i++)
		qs[i].fi.fi = read(), qs[i].fi.se = read(), qs[i].se = i;
	build(1, 1, n);
	sort(qs.begin() + 1, qs.begin() + 1 + m,
	[](pair <pii, int> x, pair <pii, int> y) {
		return x.fi.se == y.fi.se ? x.fi.fi < y.fi.fi : x.fi.se < y.fi.se;
	});
	int tp = 0;
	for (int i = 1; i <= n; i++) {
		/* write(i), puts(""); */
		modify(1, 1, n, lst[s[i]] + 1, i, i);
		if (lst[s[i]]) fa[lst[s[i]]] = lst[s[i]] + 1;
		lst[s[i]] = i;
		while (qs[tp + 1].fi.se <= i && tp < m) {
			tp++;
			int pos = find(qs[tp].fi.fi);
			/* int pos = *isl.lower_bound(qs[tp].fi.fi); */
			/* if (tp == 3) */
				/* write(pos), puts("@"); */
			ans[qs[tp].se] = query(1, 1, n, qs[tp].fi.fi, pos);
		}
	}
	for (int i = 1; i <= m; i++)
		write(ans[i]), puts("");
	return 0;
}

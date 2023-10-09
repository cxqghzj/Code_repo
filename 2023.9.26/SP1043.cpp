#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <tuple>
#define int long long
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
const int N = 5e5 + 5;
array <int, N> s;
namespace Sgt {

typedef tuple <int, int, int, int, bool> Node;
//sum edge ls rs
array <Node, 4 * N> edge;
#define g_sum(x) get <0>(x)
#define g_edge(x) get <1>(x)
#define g_ls(x) get <2>(x)
#define g_rs(x) get <3>(x)
#define g_tag(x) get <4>(x)

Node update(Node x, Node y) {
	Node ans = make_tuple(0, 0, 0, 0, 0);
	if (g_tag(x)) return y;
	if (g_tag(y)) return x;
	g_sum(ans) = g_sum(x) + g_sum(y);

	g_ls(ans) = max(g_sum(x) + g_ls(y), g_ls(x));
	g_rs(ans) = max(g_sum(y) + g_rs(x), g_rs(y));

	g_edge(ans) = max(max(g_edge(x), g_edge(y)), g_rs(x) + g_ls(y));
	return ans;
}
void pushup(int x, int l, int r) {
	edge[x] = update(edge[x * 2], edge[x * 2 + 1]);
}
void build(int x, int l, int r) {
	if (l == r) {
		g_sum(edge[x]) = s[l];
		g_edge(edge[x]) = s[l];
		g_ls(edge[x]) = s[l];
		g_rs(edge[x]) = s[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
	pushup(x, l, r);
}
void modify(int x, int l, int r, int y, int k) {
	if (y > r || y < l) return;
	if (l == r) {
		g_sum(edge[x]) = k;
		g_edge(edge[x]) = k;
		g_ls(edge[x]) = k;
		g_rs(edge[x]) = k;
		return;
	}
	int mid = (l + r) >> 1;
	if (y <= mid) modify(x * 2, l, mid, y, k);
	else modify(x * 2 + 1, mid + 1, r, y, k);
	pushup(x, l, r);
}
Node query(int x, int l, int r, int L, int R) {
	/* if (L > r || R < l) return make_tuple(0, 0, 0, 0); */
	if (L <= l && R >= r) return edge[x];
	int mid = (l + r) >> 1;
	Node ans = make_tuple(0, 0, 0, 0, 1);
	/* if (L <= mid && R > mid) return update(query(x * 2, l, mid, L, R), query(x * 2 + 1, mid + 1, r, L, R)); */
	if (L <= mid) ans = update(ans, query(x * 2, l, mid, L, R));
	if (R > mid) ans = update(ans, query(x * 2 + 1, mid + 1, r, L, R));
	return ans;
}

}
signed main() {
	int n = read();
	for (int i = 1; i <= n; i++)
		s[i] = read();
	Sgt::build(1, 1, n);
	int q = read();
	while (q--) {
		int x = read(), y = read();
		write(get <1>(Sgt::query(1, 1, n, x, y))), puts("");
	}
	return 0;
}

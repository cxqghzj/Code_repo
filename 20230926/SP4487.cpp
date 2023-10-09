#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <tuple>
#define pii pair <int, int>
using namespace std;
#ifdef ONLINE_JUDGE

/* #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++) */
/* char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf; */

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
const int N = 4e5 + 5;
array <int, N> s;


array <tuple <string, int, int>, N> qrl;
char strbuf[2];

array <int, N> idx;



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
	Node ans = make_tuple(-2e9, -2e9, -2e9, -2e9, 0);
	if (g_tag(x) && g_tag(y)) {
		g_tag(ans) = 1;
		return ans;
	}
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
		if (!idx[l]) {
			g_tag(edge[x]) = 1;
			return;
		}
		g_sum(edge[x]) = s[idx[l]];
		g_edge(edge[x]) = s[idx[l]];
		g_ls(edge[x]) = s[idx[l]];
		g_rs(edge[x]) = s[idx[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
	pushup(x, l, r);
}
void modify(int x, int l, int r, int y, int k, int op) {
	if (y > r || y < l) return;
	if (l == r) {
		g_sum(edge[x]) = k;
		g_edge(edge[x]) = k;
		g_ls(edge[x]) = k;
		g_rs(edge[x]) = k;
		g_tag(edge[x]) = op;
		return;
	}
	int mid = (l + r) >> 1;
	if (y <= mid) modify(x * 2, l, mid, y, k, op);
	else modify(x * 2 + 1, mid + 1, r, y, k, op);
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

namespace Bit {

int lowbit(int x) {
	return x & -x;
}
array <int, N> edge;
void modify(int x, int y, int n) {
	while (x <= n) {
		edge[x] += y;
		x += lowbit(x);
	}
	return;
}
int query(int x) {
	int ans = 0;
	while (x) {
		ans += edge[x];
		x -= lowbit(x);
	}
	return ans;
}


}

void calc(int &x) {
if(x)
	x += Bit::query(x);
	return;
}
array <int, N> isl;
int main() {
	/* freopen("hack_in.txt", "r", stdin); */
	/* freopen("out.txt", "w", stdout); */
	/* int x; */
	/* cout << (typeof(x)) << endl; */
	int n = read();
	for (int i = 1; i <= n; i++)
		s[i] = read(), isl[i] = i;

	int m = read();
	Bit::edge.fill(0);
	int len = n + m;
	for (int i = 1; i <= m; i++) {
		scanf("%s", strbuf);
		if (strbuf[0] == 'D') {
			int x = read(), y = 0;
			calc(x);
			Bit::modify(x + 1, 1, len);
			qrl[i] = tie(strbuf, x, y);
		}
		else {
			int x = read(), y = read();
			if (strbuf[0] == 'I')
				x--;
			calc(x); 

			if (strbuf[0] == 'Q')
				calc(y);
			qrl[i] = tie(strbuf, x, y);
		}
	}
	Bit::edge.fill(0);
	for (int i = m; i >= 1; i--) {
		int x = get <1>(qrl[i]);
		calc(get <1>(qrl[i]));
		if (get <0>(qrl[i])[0] == 'Q') calc(get <2>(qrl[i]));
		if (get <0>(qrl[i])[0] == 'I')
			get <1>(qrl[i])++,Bit::modify(x+1, 1, len);
		/* calc(get <1>(qrl[i])); */
	}
	for (int i = 1; i <= n; i++) {
		isl[i] += Bit::query(i);
		idx[isl[i]] = i;
		/* write(isl[i]), putchar(32); */
	}
	/* puts(""); */
	using Sgt::build, Sgt::modify, Sgt::query;
	/* write(len), puts(""); */
	build(1, 1, len);
	for (int i = 1; i <= m; i++) {
		if (get <0>(qrl[i])[0] == 'Q')
			write(get <1>(query(1, 1, len, get <1>(qrl[i]), get <2>(qrl[i])))), puts("");
		else
			modify(1, 1, len, get <1>(qrl[i]), get <2>(qrl[i]), get <0>(qrl[i])[0] == 'D');
		/* printf("%c ", get <0>(qrl[i])[0]); */
		/* write(get <1>(qrl[i])), putchar(32); */
		/* write(get <2>(qrl[i])), puts(""); */
	}
	return 0;
}

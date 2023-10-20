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
const int N = 21, M = 105, S = 1.2e6 + 5, inf = 0x7f7f7f7f;
array <tuple <int, int, int>, M> edge;
array <int, S> dis, f;
array <array <int, N>, S> g;
namespace Uni {

array <int, N> siz, fa;
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void merge(int x, int y) {
	int fx = find(x),
		fy = find(y);
	if (fx == fy) return;
	if (siz[fx] > siz[fy]) swap(fx, fy);
	fa[fx] = fy;
	siz[fy] += siz[fx];
	return;
}
void init() {
	for (int i = 1; i <= 20; i++)
		siz[fa[i] = i] = 1;
}

}
signed main() {
	/* freopen("mst.in", "r", stdin); */
	/* freopen("mst.out", "w", stdout); */
	int n = read(), m = read();
	for (int i = 1; i <= m; i++)
		get <1>(edge[i]) = read(), get <2>(edge[i]) = read(), get <0>(edge[i]) = read();
	sort(edge.begin() + 1, edge.begin() + 1 + m, less <tuple <int, int, int> >());
	for (int T = 0; T < 1 << n; T++) {
		Uni::init();
		int ans = 0, cur = 0, k = 0;
		for (int i = 1; i <= n; i++) {
			if (T & (1 << (i - 1)))
				cur++;
		}

		for (int i = 1; i <= m; i++) {
			int u = get <1>(edge[i]), v = get <2>(edge[i]), w = get <0>(edge[i]);
			if (Uni::find(u) == Uni::find(v) || !(T & (1 << (u - 1))) || !(T & (1 << (v - 1)))) continue;
			Uni::merge(u, v), ans += w;
			k++;
		}
		if (k != cur - 1) dis[T] = inf;
		else dis[T] ^= ans;
	}
	sort(edge.begin() + 1, edge.begin() + 1 + m, greater <tuple <int, int, int> >());
	for (int T = 0; T < 1 << n; T++) {
		Uni::init();
		int ans = 0, cur = 0, k = 0;
		for (int i = 1; i <= n; i++) {
			if (T & (1 << (i - 1)))
				cur++;
		}
		for (int i = 1; i <= m; i++) {
			int u = get <1>(edge[i]), v = get <2>(edge[i]), w = get <0>(edge[i]);
			if (Uni::find(u) == Uni::find(v) || !(T & (1 << (u - 1))) || !(T & (1 << (v - 1)))) continue;
			Uni::merge(u, v), ans += w;
			k++;
		}
		f[T] = inf;
		for (int i = 0; i <= n; i++)
			g[T][i] = inf;
		if (k != cur - 1) dis[T] = inf;
		else dis[T] == inf ? dis[T] = ans : dis[T] ^= ans;
	}
	for (int i = 0; i < n; i++)
		f[1 << i] = 0;
	for (int T = 0; T < 1 << n; T++) {
		int cur = 0;
		for (int i = 1; i <= n; i++) {
			if (T & (1 << (i - 1)))
				cur++;
		}
		for (int i = 1; i <= n; i++) {
			if (!(T & (1 << (i - 1)))) continue;
			int T_ = T - (1 << (i - 1));
			for (int j = 0; j < cur; j++) {
				f[T] = min(g[T_][j] + (cur - j) * dis[T], f[T]);
				g[T][j] = min(g[T][j], g[T_][j]);
			}
		}
		g[T][cur] = min(g[T][cur], f[T]);
	}
	write(f[(1 << n) - 1]), puts("");
	return 0;
}

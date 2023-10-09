#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <bitset>
#define int long long
#define pii pair <int, int>
using namespace std;
#ifdef ONLINE_JUDGE

/* #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1 << 21, stdin), p1 == p2) ? EOF : *p1++) */
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
const int N = 1e5 + 5, M = 2e5 + 5, mod = 998244353;
array <int, N> isl;
namespace G {

array <int, N> fir;
array <int, M> nex, to, len;
int cnt;
void add(int x, int y, int z) {
	cnt++;
	nex[cnt] = fir[x];
	to[cnt] = y;
	len[cnt] = z;
	fir[x] = cnt;
}

}

/*
namespace Uni {

array <int, N> fa, siz;
void init() {
	for (int i = 1; i <= 1e5 + 2; i++)
		siz[fa[i] = i] = 1;
}
int find(int x) {
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void merge(int x, int y) {
	int fx = find(x),
		fy = find(y);
	if (fx == fy) return;
	if (siz[fx] > siz[fy]) swap(fx, fy);
	fa[siz[fx]] = fy;
	siz[fy] += siz[fx];
}

}
*/
array <pii, N> qrl;
array <int, N> dis;
bitset <N> vis;
using namespace G;
bool dfs(int x) {
	vis[x] = 1;
	bool ans = 1;
	for (int i = fir[x]; i; i = nex[i]) {
		if (!vis[to[i]])
			dis[to[i]] = (dis[x] ^ len[i]), ans &= dfs(to[i]);
		else if (vis[to[i]] && dis[to[i]] != (dis[x] ^ len[i]))
			return false;
	}
	return ans;
}
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}
signed main() {
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	int n = read(), k = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int l = read(), r = read();
		isl[i] = read();
		qrl[i].fi = l - 1, qrl[i].se = r;
		G::add(l - 1, r, isl[i]);
		G::add(r, l - 1, isl[i]);
	}
	int ans = 0;
	dis.fill(-1);
	for (int i = 0; i <= n; i++) {
		if (vis[i]) continue;
		ans++;
		if (!dfs(i)) return puts("0"), 0;
	}
	write(pow_(pow_(2, k, mod), ans - 1, mod)), puts("");
	return 0;
}

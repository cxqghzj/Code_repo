#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <bitset>
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
string read_() {
	string ans;
	char c = getchar();
	while (c != 'J' && c != 'Q')
		c = getchar();
	while (c == 'J' || c == 'Q') {
		ans += c;
		c = getchar();
	}
	return ans;

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
const int N = 1e6 + 5, M = 2e6 + 5;

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

/*
namespace Hpt {

using G::fir, G::nex, G::to;
array <int, N> fa, siz, son, dep;
void dfs1(int x) {
	siz[x] = 1;
	for (int i = fir[x]; i; i = nex[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		dep[to[i]] = dep[x] + 1;
		dfs1(to[i]);
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
		if (to[i] == son[x] || to[i] == fa[x]) continue;
		dfs2(to[i], to[i]);
	}
}

int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	if (dfn[x] > dfn[y]) swap(x, y);
	return x;
}

}
*/
using G::fir, G::nex, G::to;
bitset <N> vis;
array <int, N> fa, dis;
int dfs(int x, int rt) {
	int ans = 0x7f7f7f7f;
	while (x != rt && !vis[x]) {
		ans = min(x, ans);
		vis[x] = 1;
		x = fa[x];
	}
	return ans;
}
void _dfs(int x) {
	dis[x] = min(dis[x], x);
	for (int i = fir[x]; i; i = nex[i]) {
		if (to[i] == fa[x]) continue;
		dis[to[i]] = min(dis[to[i]], dis[x]);
		fa[to[i]] = x;
		_dfs(to[i]);
	}
}
int main() {
	/* freopen("network.in", "r", stdin); */
	/* freopen("network.out", "w", stdout); */
	int n = read(), q = read() - 1;
	for (int i = 2; i <= n; i++) {
		int x = read(), y = read();
		G::add(x, y), G::add(y, x);
	}
	dis.fill(0x7f7f7f7f);
	int lcaST = 0x7f7f7f7f;
	int rt = read();
	_dfs(rt);
	/* Hpt::dfs1(rt), Hpt::dfs2(rt, 0); */
	while (q--) {
		string opt = read_();
		if (opt[0] == 'J') {
			int x = read();
			lcaST = min(lcaST, dfs(x, rt));
		}
		else {
			int x = read();
			write(min(lcaST, dis[x])), puts("");
		}
	}
	return 0;
}

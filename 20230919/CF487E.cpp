/* #define debug */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <stack>
#include <vector>
#include <set>
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
const int N = 2e5 + 5, M = 4e5 + 5, inf = 2e9;
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
namespace Rst {

array <int, N> fir;
array <int, M> nex, to;
int cnt;
void add(int x, int y) {
	cnt++;
	nex[cnt] = fir[x];
	to[cnt] = y;
	fir[x] = cnt;
}

array <int, N> dfn, low;
stack <int> stk;
array <vector <int>, N> cur;
vector <pii> edge;
int tim, scc;
void tarjan(int x) {
	tim++;
	dfn[x] = low[x] = tim;
	stk.push(x);
	for (int i = G::fir[x]; i; i = G::nex[i]) {
		if (!dfn[G::to[i]]) {
			tarjan(G::to[i]);
			low[x] = min(low[x], low[G::to[i]]);
			if (low[G::to[i]] < dfn[x]) continue;
			scc++;
			while (stk.top() != G::to[i]) {
				edge.push_back(make_pair(stk.top(), scc));
				edge.push_back(make_pair(scc, stk.top()));
				cur[scc].push_back(stk.top());
				stk.pop();
			}
			edge.push_back(make_pair(stk.top(), scc));
			edge.push_back(make_pair(scc, stk.top()));
			cur[scc].push_back(stk.top());
			stk.pop();
			edge.push_back(make_pair(x, scc));
			edge.push_back(make_pair(scc, x));
			cur[scc].push_back(x);
		}
		else
			low[x] = min(low[x], dfn[G::to[i]]);
	}
}
void init() {
	for (auto x : edge) {
		add(x.fi, x.se);
#ifdef debug
		/* write(x.fi), putchar(32); */
		/* write(x.se), puts("@@"); */
#endif
	}
}

}
array <int, N> s;
namespace Hpd {

using Rst::fir, Rst::nex, Rst::to;

array <int, N> dep, siz, son, fa;
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
		if (to[i] == son[x] || to[i] == fa[x]) continue;
		dfs2(to[i], to[i]);
	}
}

namespace Sgt {

array <int, N * 4> edge;
array <multiset <int>, N> leaf;
using Rst::cur;
void build(int x, int l, int r) {
	edge[x] = inf;
	if (l == r) {
		leaf[l].insert(inf);
		for (auto x : cur[idx[l]]) {
			if (x == fa[idx[l]]) continue;
			leaf[l].insert(s[x]);
		}
		if (!cur[idx[l]].size()) leaf[l].insert(s[idx[l]]);
		edge[x] = *leaf[l].begin();
#ifdef debug
	if (edge[x] == 2) {
		write(x), puts("p");
	}
#endif
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
	edge[x] = min(edge[x * 2], edge[x * 2 + 1]);

}
void modify(int x, int l, int r, int k, pii y) {
	if (l > k || r < k) return;
	if (l == r) {
		leaf[l].erase(y.fi);
		leaf[l].insert(y.se);
		edge[x] = *leaf[l].begin();
		return;
	}
	int mid = (l + r) >> 1;
	if (k <= mid) modify(x * 2, l, mid, k, y);
	else modify(x * 2 + 1, mid + 1, r, k, y);
	edge[x] = min(edge[x * 2], edge[x * 2 + 1]);
}
int query(int x, int l, int r, int L, int R) {
	if (L > r || R < l) return inf;
	if (L <= l && R >= r) return edge[x];
	int mid = (l + r) >> 1, ans = inf;
	if (L <= mid) ans = min(ans, query(x * 2, l, mid, L, R));
	if (R > mid) ans = min(ans, query(x * 2 + 1, mid + 1, r, L, R));
	return ans;
}

}
using Rst::scc;
void modify(int x, int y) {
	Sgt::modify(1, 1, scc, dfn[fa[x]], make_pair(s[x], y));
	Sgt::modify(1, 1, scc, dfn[x], make_pair(s[x], y));
	s[x] = y;
}
int query(int x, int y) {
	int ans = inf;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		ans = min(ans, Sgt::query(1, 1, scc, dfn[top[x]], dfn[x]));
		x = fa[top[x]];
	}
	if (dfn[x] > dfn[y]) swap(x, y);
	ans = min(ans, Sgt::query(1, 1, scc, dfn[x], dfn[y]));
#ifdef debug
	/* write(dfn[x]), putchar(32); */
	/* write(dfn[y]), puts("||"); */
	/* write(Sgt::edge[4]), puts("{"); */
	write(ans), puts("");
#endif
	if (Rst::cur[x].size()) ans = min(ans, s[fa[x]]);
	return ans;
}

}
char strbuf[2];

int main() {
	int n = read(), m = read(), q = read();
	for (int i = 1; i <= n; i++)
		s[i] = read();
	s[0] = inf;
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read();
		G::add(x, y), G::add(y, x);
	}
	Rst::scc = n;
	Rst::tarjan(1), Rst::init();
	Hpd::dfs1(1), Hpd::dfs2(1, 0);
	Hpd::Sgt::build(1, 1, Rst::scc);
	while (q--) {
		scanf("%s", strbuf);
		int x = read(), y = read();
		if (strbuf[0] == 'C')
			Hpd::modify(x, y);
		else
			write(Hpd::query(x, y)), puts("");
	}
	return 0;
}

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <vector>
#include <queue>
#define int long long
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
	if (x > 9){
		write(x /10);
	}
	putchar(x % 10 + '0');
}
#define fi first
#define se second
namespace Subtask1 {

const int N = 25, mod = 1e9 + 7;
void Mod(int x) {
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;
}
array <int, N> s;
int lowbit(int x) {
	return x & -x;
}
array <pii, N> edge;
void modify(int x, pii y, int n) {
	while (x <= n) {
		if (edge[x].fi < y.fi)
			edge[x] = y;
		else if (edge[x].fi == y.fi)
			edge[x].se += y.se, Mod(edge[x].se);
		x += lowbit(x);
	}
	return;
}
pii query(int x) {
	pii ans(0, 1);
	while (x) {
		if (ans.fi < edge[x].fi)
			ans = edge[x];
		else if (ans.fi == edge[x].fi)
			ans.se += edge[x].se, Mod(ans.se);
		x -= lowbit(x);
	}
	return ans;
}
pii calc(int T, int n) {
	vector <int> isl;
	deque <int> res;
	res.push_back(s[1]);
	for (int i = 2; i <= n; i++) {
		if (T & (1 << (i - 2))) res.push_front(s[i]);
		else res.push_back(s[i]);
	}
	while (!res.empty())
		isl.push_back(res.front()), res.pop_front();
	pii ans(0, 0);
	for (auto x : isl) {
		/* write(x), putchar(32); */
		pii k = query(x - 1);
		k.fi++;
		/* write(k.fi), puts(""); */
		if (k.fi > ans.fi)
			ans = k;
		else if (k.fi == ans.fi)
			ans.se += k.se, Mod(ans.se);
		modify(x, k, n);
	}
	edge.fill(make_pair(0, 0));
	return ans;
}
array <int, N> h;
void main(int n) {
	for (int i = 1; i <= n; i++) {
		h[i] = s[i] = read();
	}
	sort(h.begin(), h.begin() + 1 + n);
	int m = unique(h.begin(), h.begin() + 1 + n) - h.begin() - 1;
	for (int i = 1; i <= n; i++)
		s[i] = lower_bound(h.begin() + 1, h.begin() + 1 + m, s[i]) - h.begin();
	pii ans(0, 0);
	for (int T = 0; T < 1 << (n - 1); T++) {
		pii res = calc(T, n);
		if (res.fi > ans.fi)
			ans = res;
		else if (res.fi == ans.fi)
			ans.se += res.se, Mod(ans.se);
	}
	write(ans.fi), putchar(32);
	write(ans.se), puts("");
}

}
signed main() {
	/* freopen("card.in", "r", stdin); */
	/* freopen("card.out", "w", stdout); */
	int n = read();
	/*if (n <= 20)*/ Subtask1::main(n);
	return 0;
}

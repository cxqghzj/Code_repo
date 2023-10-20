#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <stack>
#include <cassert>
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
namespace io {

bool check(char c) {
	if (c == 32 || c == 'x' || c == '&' || c == '|' || c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
		return true;
	else return false;
}

}
string read_() {
	string ans;
	char c = getchar();
	while (!io::check(c))
		c = getchar();
	while (io::check(c)) {
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
const int N = 2e6 + 5, M = 4e6 + 5;

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

array <int, N> dis, isl;
int dfs(int x) {
	using G::fir, G::nex, G::to;
	/* write(x), puts(""); */
	array <int, 4> p;
	if (!fir[x]) return 1;
	/* assert(x > 0); */
	int ls = to[fir[x]], rs = to[nex[fir[x]]];
	/* if (x == 6) write(ls), putchar(32), write(rs), puts("@"); */
	p[1] = dfs(ls), p[2] = dfs(rs);
	p[0] = min(p[1], p[2]);
	p[3] = p[1] + p[2];
	if (isl[x] == '&') {
		dis[x] = dis[ls] & dis[rs];
		if (dis[ls] == 0 && dis[rs] == 0) return p[3];
		if (dis[ls] == 0 && dis[rs] == 1) return p[1];
		if (dis[ls] == 1 && dis[rs] == 0) return p[2];
		if (dis[ls] == 1 && dis[rs] == 1) return p[0];
	}
	else {
		/* if (x == 5) write(p[1]), putchar(32), write(p[2]), puts("\\"); */
		dis[x] = dis[ls] | dis[rs];
		if (dis[ls] == 0 && dis[rs] == 0) return p[0];
		if (dis[ls] == 0 && dis[rs] == 1) return p[2];
		if (dis[ls] == 1 && dis[rs] == 0) return p[1];
		if (dis[ls] == 1 && dis[rs] == 1) return p[3];
	}
}

void solve() {
	stack <int> stk, cur;
	G::cnt = 0, G::fir.fill(0);
	int n = read();
	string s = read_();
	/* getline(cin, s); */
	int cnt = n;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 32) continue;
		if (s[i] != 'x') {
			cur.push(s[i]);
			if (stk.size() >= 2) {
				int tp0 = stk.top(); stk.pop();
				int tp1 = stk.top(); stk.pop();
				cnt++; G::add(cnt, tp0), G::add(cnt, tp1);
				/* write(cnt), putchar(32); */
				/* write(tp0), puts(""); */
				/* write(cnt), putchar(32); */
				/* write(tp1), puts(""); */
				cur.pop();
				isl[cnt] = s[i];
				/* if (cnt == 6) putchar(isl[cnt]), puts("#"); */
				stk.push(cnt);
			}
			continue;
		}
		int x = 0;
		while (s[i + 1] >= '0' && s[i + 1] <= '9') {
			i++;
			x = x * 10 + s[i] - '0';
		}
		stk.push(x);
	}
	for (int i = 1; i <= n; i++)
		dis[i] = read();
	/* puts("@"); */
	write(dfs(cnt)), puts("");
	/* write(dis[4]), puts("@"); */
}
int main() {
	/* freopen("change.in", "r", stdin); */
	/* freopen("change.out", "w", stdout); */
	int T = read();
	while (T--) solve();
	return 0;
}

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
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
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}
const int N = 2e5 + 5;
multiset <pii> isl, prl;
vector <pii> ls[N], rs[N];
signed main() {
	freopen("xiaoqiao.in", "r", stdin);
	freopen("xiaoqiao.out", "w", stdout);
	int n = read(), m = read(), k = read();
	for (int i = 1; i <= n; i++) {
		int x = read(), l = read(), r = read() - 1;
		l += m + 1, r += m + 1;
		if (r < l) {
			ls[l].push_back(make_pair(x, i));
			rs[m * 2].push_back(make_pair(x, i));
			ls[1].push_back(make_pair(x, i));
			rs[r].push_back(make_pair(x, i));
		}
		else {
			ls[l].push_back(make_pair(x, i));
			rs[r].push_back(make_pair(x, i));
		}
	}
	int ans = 0;
	for (int i = 1; i <= m * 2; i++) {
		/* write(i), puts(":"); */
		for (int j = 0; j < ls[i].size(); j++) {
			pii x = ls[i][j];
			isl.insert(x);
			if (isl.size() > k) prl.insert(*isl.begin()), isl.erase(isl.begin());
			/* write(x.first), putchar(32); */
		}
		/* puts(""); */
		while (isl.size() < k && !prl.empty())
			isl.insert(*prl.begin()), prl.erase(prl.begin());
		if (isl.size() == k) {
			/* write(i), putchar(32); */
			/* write(isl.begin() -> first), puts(""); */
			ans += isl.begin() -> first * isl.begin() -> first;
		}
		for (int j = 0; j < rs[i].size(); j++) {
			pii x = rs[i][j];
			if (!isl.empty() &&
				*isl.lower_bound(x) == x)
				isl.erase(x);
			else
				prl.erase(x);
			/* write(x.first), putchar(32); */
		}
		/* puts(""); */
	}
	write(ans), puts("");
	return 0;
}

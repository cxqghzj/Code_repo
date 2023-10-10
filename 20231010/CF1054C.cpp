#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <vector>
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
const int N = 1005;
array <int, N> s1, s2, h1, h2;
array <int, N> isl;
bitset <N> vis;
int cnt;
bool divide(int n) {
	vector <int> s;
	for (int i = 1; i <= n; i++) {
		if (!s1[i] && !s2[i] && !vis[i])
			s.push_back(i), vis[i] = 1;
	}
	for (auto x : s)
		isl[x] = cnt;
	for (auto x : s) {
		for (int i = 1; i < x; i++) {
			if (!s2[i]) continue;
			s2[i]--;
		}
		for (int i = x + 1; i <= n; i++) {
			if (!s1[i]) continue;
			s1[i]--;
		}
	}
	cnt--;
	return s.size();
}
int main() {
	int n = read();
	for (int i = 1; i <= n; i++)
		h1[i] = s1[i] = read();
	for (int i = 1; i <= n; i++)
		h2[i] = s2[i] = read();
	isl.fill(-1);
	cnt = n;
	int tp = n;
	bool ans = false;
	while (divide(n));
	bool flg = false;
	for (int i = 1; i <= n; i++) {
		/* write(isl[i]), putchar(32); */
		if (~isl[i]) continue;
		flg = true;
	}
	/* puts(""); */
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			if (isl[j] < isl[i])
				h2[j]--;
		}
		for (int j = i + 1; j <= n; j++)
			if (isl[j] < isl[i])
				h1[j]--;
	}
	for (int i = 1; i <= n; i++) {
		if (h1[i] || h2[i])
			flg = true;
		/* write(s1[i]), putchar(32); */
		/* write(s2[i]), puts(""); */
	}
	if (flg) puts("NO");
	else {
		puts("YES");
		for (int i = 1; i <= n; i++)
			write(isl[i]), putchar(32);
		puts("");
	}
	return 0;
}

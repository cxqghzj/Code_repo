#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <cmath>
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
int biao[101]={0,279956735225ll,1119830640632ll,2519626160092ll,4479342359572ll,6998967689687ll,10078516896527ll,13717964739123ll,17917328540830ll,22676602132339ll,27995776447498ll,33874881717631ll,40313896826659ll,47312757890124ll,54871577366812ll,62990285450702ll,71668893472434ll,80907427323326ll,90705860863088ll,101064192853086ll,111982433751688ll,123460604455898ll,135498624789132ll,148096648059804ll,161254456013698ll,174972269841089ll,189249970864758ll,204087619234340ll,219485145823722ll,235442510801884ll,251959979846799ll,269037147192838ll,286674239639960ll,304871272659330ll,323628159599161ll,342945143395601ll,362821938749256ll,383258549478695ll,404255210149668ll,425811772857965ll,447928309653278ll,470604639137458ll,493840885162076ll,517636959731895ll,541992900610055ll,566909018715383ll,592384970859171ll,618420708641414ll,645016496881612ll,672172286922677ll,699887567268899ll};
int cnt[101]={0,1000000,2000000,3000000,4000000,5000000,6000000,7000000,8000000,9000000,10000000,11000000,12000000,13000000,14000000,15000000,16000000,17000000,18000000,19000000,20000000,21000000,22000000,23000000,24000000,25000000,26000000,27000000,28000000,29000000,30000000,31000000,32000000,33000000,34000000,35000000,36000000,37000000,38000000,39000000,40000000,41000000,42000000,43000000,44000000,45000000,46000000,47000000,48000000,49000000,50000000};
int ans[50000001];
signed main() {
	int a = read(), b = read();
	int la = lower_bound(cnt + 1, cnt + 51, a) - cnt,
		lb = upper_bound(cnt + 1, cnt + 51, b) - cnt - 1;
	/* int res = biao[lb] - biao[la]; */
	b = cnt[la];
	int cnt_ = 0;
	/* write(b), puts(""); */
	for (int i = 2; i <= sqrt(b); i++) {
		if (i * i >= a)
			ans[i * i] -= i;
		/* write(i * i + i), putchar(32); */
		/* write(ceil(a * 1.0 / i) * i), puts(""); */
		for (int j = max(i * i + i, (int)ceil(a * 1.0 / i) * i), k = j / i; j <= b; j += i, k++) {
			ans[j] -= i + k;
			/* if (i == 2) */
			/* write(j), puts(""); */
				cnt_++;
		}
	}
	write(cnt_), puts("");
	/* for (int i = a; i <= b; i++) ans[i] += i - 1, res += */
	return 0;
}

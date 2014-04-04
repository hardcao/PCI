#include <stdio.h>
#include <iostream>
#include <math.h>
#define PN  900
#define N 600
#define CN 30000
#define itN 2000
#define lgN 8336
using namespace std;
struct Commodity{
	float sc;
	int dt;
	int cmd;
};
struct Person
{
	int pn;
	int ln;
	Commodity cd[N];
}pnt[PN];
struct item{
	int pn;
	int cmd;
}itmN[itN];
struct logBuy{
	int pn;
	int cmd;
	float sc;
	int dt;
}lg[lgN];
double num[CN];
int vist[CN],print[CN];
double getSim(Person p1,Person p2){
	Commodity cd[N];
	int n =0;
	double sum1=0,sum2=0,sum1Sq =0,sum2Sq =0,pSum =0;
	for(int i=0;i<p1.ln;i++){
		for (int j=0;j<p2.ln;j++){
			if(p1.cd[i].cmd == p2.cd[j].cmd&&p1.cd[i].dt == p2.cd[j].dt){
				int sc1 = p1.cd[i].sc;
				int sc2 = p2.cd[j].sc;
				if(p1.cd[i].dt == p2.cd[j].dt){
					sc1 += 3;
					sc2 += 3;
				}
				sum1 += sc1;
				sum2 += sc2;
				sum1Sq += sc1*sc1;
				sum2Sq += sc2*sc2;
				pSum += sc1*sc2;
				n++;
			}
		}
	}
	if(sum1 == 0 || sum2 == 0) return 0;
	double num = pSum-(sum1*sum2*1.0/n);
	double den = sqrt((sum1Sq - 1.0*sum1*sum1/n)*(sum2Sq - 1.0*sum2*sum2/n));
	if(den == 0) return 0;
	if(num/den < 0){
		return -num/den;
	}
	return num/den;
}
int main()
{
	int lt =0;
	int pn,dt,cmd;
	float sc;
	int lgn=0;
	for(int i=0;i<lgN;i++){
		scanf("%d%d%f%d",&pn,&cmd,&sc,&dt);
		// if(dt>195) continue;
		lg[lgn].pn=pn;
		lg[lgn].sc=sc;
		lg[lgn].cmd = cmd;
		lg[lgn].dt = dt;
		lgn++;
	}
	for(int i=0;i<lgn;i++){
		pn = lg[i].pn;
		cmd=lg[i].cmd;
		sc = lg[i].sc;
		dt = lg[i].dt;
		// if(dt>195) continue;
		if(sc == 1) sc = 4;
		if(sc == 2) sc = 2;
		if(sc == 3) sc = 1;
		int flg = 0;
		for(int j=0;j<lt;j++){
			if(pnt[j].pn == pn){
				flg = 1;
				int idx = pnt[j].ln;
				int vt =1;
				for (int t = 0;t<pnt[j].ln;t++){
					if(pnt[j].cd[t].cmd == cmd&&pnt[j].cd[t].dt==dt&&vt){
						vt = 0;
						pnt[j].cd[t].sc+=sc;
					}
				}
				if(vt){
					pnt[j].cd[idx].sc = sc;
					pnt[j].cd[idx].dt = dt;
					pnt[j].cd[idx].cmd = cmd;
					pnt[j].ln++;
				}
			}
		}
		if(flg == 0){
			pnt[lt].ln = 1;
			pnt[lt].pn = pn;
			pnt[lt].cd[0].sc=sc;
			pnt[lt].cd[0].dt = dt;
			pnt[lt].cd[0].cmd=cmd;
			lt++;
		}
	}
	int cntItm =0;
	int flgg =0;
    for(int t=0;t<lt;t++){
	for(int i=0;i<CN;i++) {num[i]=0;vist[i]=0;}
	for(int i=0;i<lgn;i++){
		int cnt =0;
		for(int j=i+1;j<lgn;j++){
			if(lg[i].pn==lg[j].pn&&lg[i].cmd==lg[j].cmd){
				cnt++;
			}
		}
		if(cnt) vist[lg[i].cmd]=1;
	}
	for(int i=1;i<lt;i++){
		if(i == t) continue;
		double ratio = getSim(pnt[t],pnt[i]);
		for(int j=0;j<pnt[i].ln;j++){
			int idx = pnt[i].cd[j].cmd;
			num[idx] += ratio*pnt[i].cd[j].sc;
		}
	}
	for(int i=0;i<pnt[t].ln;i++){
		int idx = pnt[t].cd[i].cmd;
		for(int j=0;j<cntItm;j++){
			if(itmN[j].pn==pnt[t].pn) {vist[idx]=1;}
		}
	}
	int cnt =0;
	for(int i=0;i<pnt[t].ln;i++){
		int idx = pnt[t].cd[i].cmd;
		if((int(num[idx]))>3||vist[idx]){
			cnt++;
		}
	}
	if(cnt==0) continue;
	// printf("%d  ",pnt[t].pn);
	int flg =0;
	for (int i=0;i<CN;i++) print[i]=0;
	for(int i=0;i<pnt[t].ln;i++){
		int idx = pnt[t].cd[i].cmd;
		if(print[idx]) continue;
		if(vist[idx]||int(num[idx])>3){
			// if(flg == 0){
// 				flg ++;
// 			} else {
// 				printf(",");
// 			}
// 			printf("%d",pnt[t].cd[i].cmd);
			print[idx]=1;
			printf("%d %d\n",pnt[t].pn,pnt[t].cd[i].cmd);
		}
	}
	 // printf("\n");
	}
	// printf("%d\n",flgg);
	return 0;
}
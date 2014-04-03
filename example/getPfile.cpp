#include <stdio.h>
#include <iostream>
#include <math.h>
#define PN  900
#define N 600
#define CN 30000
#define itN 2000
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
double num[CN];
double getSim(Person p1,Person p2){
	Commodity cd[N];
	int n =0;
	double sum1=0,sum2=0,sum1Sq =0,sum2Sq =0,pSum =0;
	for(int i=0;i<p1.ln;i++){
		for (int j=0;j<p2.ln;j++){
			if(p1.cd[i].cmd == p2.cd[j].cmd){
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
	for(int i=0;i<5537;i++){
		scanf("%d%d%f%d",&pn,&cmd,&sc,&dt);
		// if(dt>195) continue;
		int flg = 0;
		for(int j=0;j<lt;j++){
			if(pnt[j].pn == pn){
				flg = 1;
				int idx = pnt[j].ln;
				pnt[j].cd[idx].sc = sc;
				pnt[j].cd[idx].dt = dt;
				pnt[j].cd[idx].cmd = cmd;
				pnt[j].ln++;
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
	for(int i=0;i<1074;i++){
		scanf("%d%d%f%d",&pn,&cmd,&sc,&dt);
		// if(dt > 195)continue;
		itmN[cntItm].pn = pn;
		itmN[cntItm++].cmd = cmd;
	}
	// for(int i=0;i<cntItm;i++){
// 		for(int j=0;j<cntItm;j++){
// 			if(i==j)continue;
// 			if(itmN[i].pn==itmN[j].pn&&itmN[i].cmd==itmN[j].cmd){
// 				printf("wrong ans\n");
// 			}
// 		}
// 	}
	int flgg =0;
    for(int t=0;t<lt;t++){
	for(int i=0;i<CN;i++) num[i]=0;
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
			if(itmN[j].pn==pnt[t].pn) {num[idx]+=3;flgg++;}
		}
	}
	int cnt =0;
	for(int i=0;i<pnt[t].ln;i++){
		int idx = pnt[t].cd[i].cmd;
		if((int(num[idx]))>=3){
			cnt++;
		}
	}
	if(cnt==0) continue;
	// printf("%d  ",pnt[t].pn);
	int flg =0;
	for(int i=0;i<pnt[t].ln;i++){
		int idx = pnt[t].cd[i].cmd;
		if((int(num[idx]))>=3){
			// if(flg == 0){
// 				flg ++;
// 			} else {
// 				printf(",");
// 			}
// 			printf("%d",pnt[t].cd[i].cmd);
			printf("%d %d\n",pnt[t].pn,pnt[t].cd[i].cmd);
		}
	}
	 // printf("\n");
	}
	// printf("%d\n",flgg);
	return 0;
}
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
struct B2B{
	int ln;
	int cmd[20];
	int cmdn[20];
	int rcm;
	int cnt;
}Buy[CN],coll[CN];
double num[CN];
int vist[CN],print[CN],vist1[CN],mutl[CN];
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
void setMutlBuy(int lgn){
	for(int i=0;i<lgn;i++){
		int cnt =0;
		if(lg[i].sc != 1) continue;
		for(int j=i+1;j<lgn;j++){
			if(lg[j].sc != 1) continue;
			if(lg[i].pn==lg[j].pn&&lg[i].cmd==lg[j].cmd){
				cnt++;
			}
		}
		if(cnt) vist[lg[i].cmd]=1;
	}
}
void setB2B(int lgn){
	for(int i=0;i<CN;i++){Buy[i].ln =0,Buy[i].rcm=-1;}
	for(int i=0;i<lgn;i++){
		if(lg[i].sc != 1) continue;
		int idx = lg[i].cmd;
		for(int j = i+1;j<lgn;j++){
			if(lg[j].sc != 1) continue;
			if(lg[i].cmd == lg[j].cmd) continue;
			if(lg[i].pn==lg[j].pn&&lg[i].dt == lg[j].dt){
				int flg =1;
				Buy[idx].cnt++;
				for(int t = 0;t<Buy[idx].ln;t++){
					if(Buy[idx].cmd[t]==lg[j].cmd){
						Buy[idx].cmdn[t]++;
						flg =0;
					}
				}
				if(Buy[idx].ln>=20) continue;
				if(flg){
					int lt = Buy[idx].ln;
					Buy[idx].cmd[lt]=lg[j].cmd;
					Buy[idx].cmdn[lt]=1;
				    Buy[idx].ln++;
				}
			}
		}
	}
	for(int i=0;i<CN;i++){
		int maxN =-1;
		int bestCmd = -1;
		for(int j=0;j<Buy[i].ln;j++){
			if(maxN<Buy[i].cmdn[j]&&Buy[i].cmdn[j]>2){
				bestCmd = Buy[i].cmd[j];
				maxN = Buy[i].cmdn[j];
			}
		}
		Buy[i].rcm = bestCmd;
	}
}
void setC2B(int lgn){
	for(int i=0;i<CN;i++){coll[i].ln =0,coll[i].rcm=-1;}
	for(int i=0;i<lgn;i++){
		if(lg[i].sc != 2) continue;
		int idx = lg[i].cmd;
		for(int j = 0;j<lgn;j++){
			if(lg[j].dt<lg[i].dt)continue;
			if(lg[j].sc != 1) continue;
			if(lg[i].cmd != lg[j].cmd) continue;
			if(lg[i].pn==lg[j].pn){
				int flg =1;
				coll[idx].cnt++;
				for(int t = 0;t<coll[idx].ln;t++){
					if(coll[idx].cmd[t]==lg[j].cmd){
						coll[idx].cmdn[t]++;
						flg =0;
					}
				}
				// if(coll[idx].ln>2) printf("YES\n");
				if(coll[idx].ln>=20) continue;
				if(flg){
					int lt = coll[idx].ln;
					coll[idx].cmd[lt]=lg[j].cmd;
					coll[idx].cmdn[lt]=1;
				    coll[idx].ln++;
				}
			}
		}
	}
	for(int i=0;i<CN;i++){
		int maxN =-1;
		int bestCmd = -1;
		for(int j=0;j<coll[i].ln;j++){
			// printf("cmd== %d\n",coll[i].cmd[j]);
			if(coll[i].cmd[j]==i&&coll[i].cmdn[j]>=2){
				// printf("cmd ==%d\n",i);
				bestCmd = coll[i].cmd[j];
				maxN = coll[i].cmdn[j];
			}
		}
		coll[i].rcm = bestCmd;
	}
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
		if(sc == 2) sc = 3;
		if(sc == 3) sc = 2;
		int flg = 0;
		for(int j=0;j<lt;j++){
			if(pnt[j].pn == pn){
				flg = 1;
				int idx = pnt[j].ln;
				int vt =1;
				for (int t = 0;t<pnt[j].ln;t++){
					if(pnt[j].cd[t].cmd == cmd&&vt){
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
	int flgg =0;
	for(int i=0;i<CN;i++) {vist[i]=0;}
	setMutlBuy(lgn);
	setB2B(lgn);
	setC2B(lgn);
    for(int t=0;t<lt;t++){
	for(int i=0;i<CN;i++) {num[i]=0;vist1[i]=0;mutl[i]= 0;}
	for(int i=1;i<lt;i++){
		if(i == t) continue;
		double ratio = getSim(pnt[t],pnt[i]);
		// if(ratio>0.5)	printf("ratio==%f\n",ratio);
		for(int j=0;j<pnt[i].ln;j++){
			int idx = pnt[i].cd[j].cmd;
			num[idx] += ratio*pnt[i].cd[j].sc;
		}
	}
	int cnt =0;
	int bmax = -1,bestb = -1;
	for(int i=0;i<pnt[t].ln;i++){
		int idx = pnt[t].cd[i].cmd;
		if(pnt[t].cd[i].sc>=9){
			mutl[idx] =1;
		}
		if(num[idx]>3){
			vist1[idx]=1;
		}
	}
	for(int i=0;i<lgn;i++){
		if(pnt[t].pn==lg[i].pn){
			int idx = lg[i].cmd;
			if(lg[i].sc == 1){
				if(Buy[idx].rcm !=-1&&mutl[idx]) vist1[Buy[idx].rcm]=1;
				if(vist[idx]){
					vist1[idx]=1;
				}
			}
			if(lg[i].sc == 2){
				if(coll[idx].rcm != -1) {vist1[coll[idx].rcm]=1;}
			}
		}
	}
	int cn =0;
	for(int i=0;i<CN;i++){if(vist1[i]) cn++;}
	if(cn ==0) continue;
	int flg = 0;
	printf("%d  ",pnt[t].pn);
	for(int i=0;i<CN;i++){
		if(vist1[i]){
			if(flg == 0){
				flg ++;
			} else {
				printf(",");
			}
			printf("%d",i);
			// printf("%d %d\n",pnt[t].pn,i);
		}
	}
	 printf("\n");
	}
	// printf("%d\n",flgg);
	return 0;
}
#include <stdio.h>
#include <iostream>
#define N 1009
using namespace std;
int map[N][N],qu[N],knum[N];
int vist[N],can[N];
int testNum[N];
int main()
{
	int n,t,m,x,y;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) map[i][j]=0;
		for(int i=0;i<=n;i++){qu[i]=0,knum[i]=0,vist[i]=-1,can[i]=1,testNum[i]=0;}
		for(int i=0;i<m;i++){
			scanf("%d%d",&x,&y);
			if(x==y)continue;
			if(map[x][y]==1) continue;
			knum[x]++;
			knum[y]++;
			qu[y]++;
			qu[x]++;
			map[x][y]=1;
			map[y][x]=1;
		}
		for(int i=1;i<=n;i++){
			for(int t=0;t<=n;t++) knum[t]=0;
			for(int t=1;t<=n;t++)for(int j=1;j<=n;j++) if(map[t][j]&&vist[j]==-1)knum[t]++;
			int besti = 0;
			int minq = n+1;
			for(int j=1;j<=n;j++)
			{
				if(can[j])
				{
					if(knum[j]<minq)
					{
						minq=knum[j];
						besti = j;
					} else 
						if (knum[j]==minq&&vist[j]!=-1)
						{
							besti = j;
						}
				}
			}
			if(besti == 0) break;
			can[besti]=0;
			if(vist[besti]==-1) vist[besti]=0;
			int flg =0;
			int km=0;
			for(int j=1;j<=n;j++){
				if(map[besti][j]&&vist[j]==vist[besti]) flg++;
				if(map[besti][j]&&vist[j]==-1)km++;
			}
			flg=flg%2;
			// printf("flg1 == %d\n",flg);
			if((flg+knum[besti])%2) flg = 1;
			else flg=0;
			// printf("btesti ==%d %d\n",besti,knum[besti]);
			for(int j=1;j<=n;j++){
				if(map[besti][j]&&vist[j]==-1){
					// printf("flg==%d\n",flg);
					if(flg) {vist[j]=vist[besti]^1,flg--;}
					else {vist[j]=vist[besti];}
					knum[j]--;
					// printf("test ==%d %d %d\n",vist[besti],vist[j],flg);
				}
			}
		}
		// for(int i=1;i<=n;i++)printf("%d",vist[i]);
		// printf("\n");
		int flag = 0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(map[i][j]&&vist[j]==vist[i]) testNum[i]++;
			}
		}
		flag =0;
		for(int i=1;i<=n;i++){
			if(testNum[i]%2) flag = 1;
		}
		if(flag)
			printf("ans wrong %d\n",t);
	}
	return 0;
}
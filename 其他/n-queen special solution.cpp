#include <cstdio>
int main()
{
    int n;
    scanf("%d",&n);
    if(n == 2 || n == 3){
        printf("-1");
        return 0;
    }
    if (n%6!=2&&n%6!=3)
    {
        for(int i=2;i<=n;i+=2)printf("%d ",i-1);
        for(int i=1;i<=n;i+=2)printf("%d ",i-1);
    }
    else
    {
        int k=n>>1;
        if (k&1)
        {
            for(int i=k;i<=n-1;i+=2)printf("%d ",i-1);
            for(int i=1;i<=k-1;i+=2)printf("%d ",i-1);
            for(int i=k+3;i<=n;i+=2)printf("%d ",i-1);
            for(int i=2;i<=k+1;i+=2)printf("%d ",i-1);
        }
        else
        {
            for(int i=k;i<=n;i+=2)printf("%d ",i-1);
            for(int i=2;i<=k-1;i+=2)printf("%d ",i-1);;
            for(int i=k+3;i<=n-1;i+=2)printf("%d ",i-1);
            for(int i=1;i<=k+1;i+=2)printf("%d ",i-1);
        }
        if (n&1)printf("%d ",n-1);;
    }
}

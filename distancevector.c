#include <stdio.h>
int costmatrix[20][20],n;
struct router{
    int distance[20];
    int nexthop[20];
}node[20];

void readmatrix()
{
    int i,j;
    printf("enter cost matrix");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&costmatrix[i][j]);
            if(i==j)
            {
                costmatrix[i][j]=0;
            }
            node[i].distance[j]=costmatrix[i][j];
            node[i].nexthop[j]=j;
        }
    }
}

void calcroutingtable()
{
    int i,j,l,k;
    for(l=1;l<n;l++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                for(k=0;k<n;k++)
                {
                    if(node[i].distance[k]+node[k].distance[j]<node[i].distance[j])
                    {
                        node[i].distance[j]=node[i].distance[k]+node[k].distance[j];
                        node[i].nexthop[j]=k;
                    }
                }
            }
        }
    }
}

void displayroute()
{
    int i,j;
    for(i=0;i<n;i++)
    {
        printf("\nRoute %d\n",i+1);
        for(j=0;j<n;j++)
        {
            printf("node %d via %d : distance %d\n",j+1,node[i].nexthop[j]+1,node[i].distance[j]);
        }
        printf("\n");
    }
}

int main()
{
    printf("Number of nodes: ");
    scanf("%d",&n);
    readmatrix();
    calcroutingtable();
    displayroute();
    return 0;
}

#include <cstdio>
//#include <cstring>
//#include <algorithm>

#define MAX_ROAD 2000000

int main(){
    int m,n;
    scanf("%d %d", &n, &m);
    unsigned int* weight = new unsigned int[n*n]();
    //std::fill(&weight[0], &weight[n*n-1], MAX_ROAD);
    int u, v, t;
    for (int i=0;i<m;i++){
        scanf("%d %d %d", &u, &v, &t);
        weight[(u-1)*n+v-1] = t;
        weight[(v-1)*n+u-1] = t;
    }

    bool flag;
    do {
        flag = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                //if (j == i)
                //    continue;
                unsigned int present = weight[i*n+j];
                if (present > 0){ // use i to update j
                    for (int k=0;k<n;k++){
                        unsigned int temp = weight[i*n+k];
                        if (temp > 0 && k != j) {
                            temp += present;
                            if (weight[j*n+k] > temp || weight[j*n+k] == 0){
                                weight[j*n+k] = temp;
                                flag = true;
                            }
                        }
                    }
                }
            }
        }
    } while (flag);

    int maxInLine, minInAll = MAX_ROAD;
    for (int i=0;i<n;i++){
        maxInLine = 0;
        for (int j=0;j<n;j++){
            //if (i == j)
            //    continue;
            //printf("%d ",weight[i*n+j]);
            if (weight[i*n+j] > maxInLine)
                maxInLine = weight[i*n+j];
        }
        if (maxInLine < minInAll)
            minInAll = maxInLine;
        //printf("\n");
    }
    printf("%d\n",minInAll);

    delete[] weight;
    return 0;
}

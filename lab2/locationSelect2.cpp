#include <cstdio>
//#include <cstring>
//#include <algorithm>

#define MAX_ROAD 2000000

int m,n;
int* weight, *maxDis, *maxDisNode;

struct Edge{
    int startPoint;
    int endPoint;
    int weight;
};
Edge* edges;

double minInAll;

void updateWeight(){
    bool flag;
    do {
        flag = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                //if (j == i)
                //    continue;
                int present = weight[i*n+j];
                if (present > 0){ // use i to update j
                    for (int k=0;k<n;k++){
                        int temp = weight[i*n+k];
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
}

double search(int edgeNum){
    int startPos = edges[edgeNum].startPoint;
    int endPos = edges[edgeNum].endPoint;
    int time = edges[edgeNum].weight;
    // For the node x=maxDisNode[endPos], distance(x, endPos) >= minInAll (already) and distance(x, startPos) >= minInAll,
    // so we can just skip it.
    if (weight[startPos*n+maxDisNode[endPos]] >= minInAll || weight[endPos*n+maxDisNode[startPos]] >= minInAll)
        return minInAll;
    double tempMax, minMax = minInAll;
    double k = 0.5;
    while (k<time){
        tempMax = 0;
        double newDis;
        for (int i=0;i<n;i++){
            if (weight[endPos*n+i]-weight[startPos*n+i]+time < 2*k)
                newDis = weight[endPos*n+i]+time-k;
            else
                newDis = weight[startPos*n+i]+k;

            if (newDis > tempMax)
                tempMax = newDis;
            if (tempMax > minMax) // No need to dig further for this k
                break;
        }

        if (minMax > tempMax)
            minMax = tempMax;
        k += 0.5;
    }
    return minMax;
}

int main(){
    scanf("%d %d", &n, &m);
    weight = new int[n*n];
    edges = new Edge[m];
    maxDis = new int[n]();  // init with 0
    maxDisNode = new int[n];
    minInAll = MAX_ROAD;
    //std::fill(&weight[0], &weight[n*n-1], MAX_ROAD);
    int u, v, t;
    for (int i=0;i<m;i++){  // Read the data
        scanf("%d %d %d", &u, &v, &t);
        weight[(u-1)*n+v-1] = t;
        weight[(v-1)*n+u-1] = t;
        edges[i].startPoint = u-1;
        edges[i].endPoint = v-1;
        edges[i].weight = t;
    }

    updateWeight();

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (weight[i*n+j] > maxDis[i]) {
                maxDis[i] = weight[i*n+j];
                maxDisNode[i] = j;
            }
        }
        if (minInAll > maxDis[i])
            minInAll = maxDis[i];
    }

    for (int i=0;i<m;i++){
        double temp = search(i);
        if (minInAll > temp)
            minInAll = temp;
    }

    if ((minInAll-(int)minInAll) < 0.1f)
        printf("%.0f\n", minInAll);
    else
        printf("%.1f\n",minInAll);

    delete[] weight;
    return 0;
}

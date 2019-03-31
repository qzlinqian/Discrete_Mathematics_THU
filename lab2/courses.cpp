#include <cstdio>
//#include <list>
#include <vector>
#include <stack>
#include <queue>

int main(){
    int n;
    scanf("%d",&n);
    int timeNeeded[n];
    //int* timeNeeded = new int[n];
    int depNum[n];
    std::vector<int> sons[n];
    int directFathers[n];
    int endTime[n];
    std::queue<int> waitingList;
    int lastEnded = -1, totalTime = 0;
    bool confluence[n+1];
    confluence[n] = false;

    // Read the constraints
    for (int i = 0; i < n; i++) {
        int time, dep;
        scanf("%d %d", &time, &dep);
        timeNeeded[i] = time;
        endTime[i] = time; // also init to avoid random status
        depNum[i] = dep;
        confluence[i] = false; // Init. If there are more than one key paths to a note, then make it true
        if (dep > 0) {
            int father;
            for (int j = 0; j < dep; j++) {
                scanf("%d", &father);
                sons[father - 1].push_back(i);   // Node number = course num - 1; record the node num for future use
            }
        } else{ // No dependencies, just put into stack & update end time
            waitingList.push(i);
            directFathers[i] = -1;
            if (endTime[i] > totalTime){ // update totalTime & last node number
                confluence[n] = false;
                totalTime = endTime[i];
                lastEnded = i;
            } else if (endTime[i] == totalTime){
                confluence[n] = true;
            }
        }
    }

    // Start calculate
    //int presentTime = 0;
    // There could be multiple key paths. Single note before the confluence note cannot change the total time
    while (!waitingList.empty()) {
        int current = waitingList.top();
        waitingList.pop(); // Pop first. Because another node would be pushed.
        for (int son:sons[current]) {
            depNum[son]--;
            int tempTime = endTime[current] + timeNeeded[son];
            if (endTime[son] < tempTime) {
                endTime[son] = tempTime;
                directFathers[son] = current;
                confluence[son] = false;
            } else if (endTime[son] == tempTime) {
                confluence[son] = true;
            }
            if (depNum[son] == 0){  // put into stack & update end time
                waitingList.push(son);
                if (endTime[son] > totalTime){ // update totalTime & last node number
                    confluence[n] = false;
                    totalTime = endTime[son];
                    lastEnded = son;
                } else if (endTime[son] == totalTime){
                    confluence[n] = true;
                }
            }
        }
    }

    bool* flag = new bool[n]();
    //int father = directFathers[lastEnded];
    //flag[lastEnded] = true;
    if (!confluence[n]){
        while (lastEnded > -1) {
            flag[lastEnded] = true;
            if (confluence[lastEnded])
                break;
            lastEnded = directFathers[lastEnded];
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", endTime[i]);
        if (flag[i]){
            printf("%d\n", 1);
        } else {
            printf("%d\n", 0);
        }
    }

    //delete[] timeNeeded;
    //delete[] depNum;
    //delete[] sons;
    //delete[] directFathers;
    //delete[] endTime;
    return 0;
}
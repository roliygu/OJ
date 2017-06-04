/**
 * author: Roliy
 * pat 1003 https://www.patest.cn/contests/pat-a-practise/1003
 * 题目需要注意：
 *      1. 虽然题目没有说清楚，但是，这是一个无向图；
 *      2. 有数据start==end，直接返回team[start]即可；
 * 思路：
 * 深搜+剪枝，不剪枝可能会被卡时间吧
 */

#include <iostream>
#include <limits>

using namespace std;

#define MAX_VERTEX_NUM 500

int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
int teamNums[MAX_VERTEX_NUM];
bool markVertex[MAX_VERTEX_NUM];
int avlCount = 0;
long minTotalLength = (numeric_limits<long>::max)();
long maxTotalTeamNum = -1;

void dfs(int vIndex, int endIndex, int vertexNum, long totalLength, long totalTeamNum) {
    markVertex[vIndex] = true;
    for (int i = 0; i != vertexNum; i++) {
        if (matrix[vIndex][i] > 0 && (!markVertex[i])) {
            long newTotalLength = totalLength + matrix[vIndex][i];
            if (newTotalLength > minTotalLength) {
                // 截止到终点i，总长度已经超过了当前最优解，所以直接剪枝
                continue;
            }
            long newTotalTeamNum = totalTeamNum + teamNums[i];
            // vIndex->i有通路,且i没有被访问过
            if (i == endIndex) {
                // i就是要找的终点
                if(newTotalLength<minTotalLength){
                    // 当前方案比已知的最优方案更优
                    avlCount = 1;
                    minTotalLength = newTotalLength;
                    maxTotalTeamNum = newTotalTeamNum;
                }else{
                    avlCount++;
                    maxTotalTeamNum = maxTotalTeamNum >= newTotalTeamNum ? maxTotalTeamNum : newTotalTeamNum;
                }
            } else {
                dfs(i, endIndex, vertexNum, newTotalLength, newTotalTeamNum);
            }
        }
    }
    markVertex[vIndex] = false;
}

int main() {
    int vertexNum, edgeNum, startIndex, endIndex;
    cin >> vertexNum >> edgeNum >> startIndex >> endIndex;
    for (int i = 0; i != vertexNum; i++) {
        cin >> teamNums[i];
    }
    for (int i = 0; i != edgeNum; i++) {
        int start, end, length;
        cin >> start >> end >> length;
        matrix[start][end] = length;
        matrix[end][start] = length;
    }
    if(startIndex == endIndex){
        cout<<1<<" "<<teamNums[startIndex]<<endl;
    }else{
        dfs(startIndex, endIndex, vertexNum, 0L, teamNums[startIndex]);
        cout<<avlCount<<" "<<maxTotalTeamNum<<endl;
    }
    return 0;
}
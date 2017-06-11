/**
 * author: Roliy
 * pat 1014 https://www.patest.cn/contests/pat-a-practise/1014
 * 按照题目要求建立模型模拟即可
 */
#include <iostream>
#include <queue>

using namespace std;

# define MAX_MINUTES 10000

class Window {
    int startTime = 0; // 上一个任务结束及这个任务开始的时间
    std::queue<int> queue;
public:
    int getStartTime() {
        return startTime;
    }

    std::queue<int> &getQueue() {
        return queue;
    }

    /**
     * 处理队首第一个元素，并更新StartTime
     * @return
     */
    int pop(int *processTimes) {
        if (queue.size() == 0) {
            return -1;
        }
        int header = queue.front();
        startTime += processTimes[header];
        queue.pop();
        return header;
    }

    inline int front() {
        if (queue.size() == 0) {
            return -1;
        }
        return queue.front();
    }
};

Window *chooseWindow(Window *windows, int windowsLength, int queueCap, int *processTimes) {
    Window *res = nullptr;
    int minQueLen = queueCap;
    for (int i = 0; i != windowsLength; i++) {
        minQueLen = minQueLen < windows[i].getQueue().size() ? minQueLen : windows[i].getQueue().size();
    }
    for (int i = 0; i != windowsLength; i++) {
        // 如果扫描第一遍发现有队列有空余位置，那么返回第一个空余的队列
        if ((windows[i].getQueue().size() < queueCap) && (windows[i].getQueue().size() == minQueLen)) {
            res = &windows[i];
            break;
        }
    }
    if (res != nullptr) {
        return res;
    }
    // 第二遍扫描，返回endTime最早的
    int minEndTime = MAX_MINUTES;
    for (int i = 0; i != windowsLength; i++) {
        Window *windowPtr = &windows[i];
        int header = windowPtr->front();
        int endTime = processTimes[header] + windowPtr->getStartTime();
        if (endTime < minEndTime) {
            minEndTime = endTime;
            res = windowPtr;
        }
    }
    return res;
}

void convert(int minutes, int customerId, int *processTimes) {
    if (minutes - processTimes[customerId] >= 540) {
        cout << "Sorry" << endl;
        return;
    }
    int minus = minutes % 60;
    int hour = (minutes / 60) + 8;
    if (hour < 10) {
        cout << '0';
    }
    cout << hour << ":";
    if (minus < 10) {
        cout << '0';
    }
    cout << minus << endl;
}

int main() {

    int windowsNum, queueCap, customerNum, queryNum;
    cin >> windowsNum >> queueCap >> customerNum >> queryNum;

    int *processTimes = new int[customerNum];
    int *queries = new int[queryNum];
    int *endTime = new int[queryNum];

    for (int i = 0; i != customerNum; i++) {
        cin >> processTimes[i];
    }

    Window *windows = new Window[windowsNum];

    for (int i = 0; i != customerNum; i++) {
        Window *thisCustomerWindow = chooseWindow(windows, windowsNum, queueCap, processTimes);
        if (thisCustomerWindow->getQueue().size() >= queueCap) {
            // 入队前容量已经达到上限，需要先出队
            int header = thisCustomerWindow->pop(processTimes);
            endTime[header] = thisCustomerWindow->getStartTime();
        }
        thisCustomerWindow->getQueue().push(i);
    }

    for (int i = 0; i != windowsNum; i++) {
        Window *thisCustomerWindow = &windows[i];
        while (thisCustomerWindow->getQueue().size() != 0) {
            int header = thisCustomerWindow->pop(processTimes);
            endTime[header] = thisCustomerWindow->getStartTime();
        }
    }

    for (int i = 0; i != queryNum; i++) {
        int customerId = queries[i] - 1;
        convert(endTime[customerId], customerId, processTimes);
    }

    return 0;

}
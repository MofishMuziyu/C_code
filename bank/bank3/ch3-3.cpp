#include "sim.h"

/*
问题三的策略：
    在第二问的基础上，
       打印出每个柜台服务过的VIP的人数和来插队的VIP人数    DONE
    1. 首先是窗口选择上进行改进，如果VIP窗口没有人，或者普通窗口排满了但是VIP窗口没有排满，则此时普通用户可以排VIP的队伍（窗口不闲置）DONE
    2. 对于需要插队的VIP， 选择插队的队列时，尽可能的选择人少的窗口                                                               
    3. 为所有的用户的depart事件增加一个被插队的次数（与普通用户的满意程度成反比）当被插队的次数过高时，该队伍不允许插队。


    4. 最重要的参数是： VIP的最大等待时间、VIP的比例、柜台的数量:  规划一个比较好的比例
    这三个值基本上决定了顾客的平均体验时间，需要明确的是VIP 的最大等待时间必须与VIP的比例和柜台的数量相符合
    否则就会出现，同一个队列插队人数过多，导致变得很长，或者VIP基本享受不到插队服务，无法体现插队的算法效果



*/
int main(void)
{
    // declare an object S for our simulation
    Simulation S;
    
    // run the simulation
    S.RunSimulation();
    
    // print the results
    S.PrintSimulationResults();

    return 1;
}

/*
<Run #1 of Program 5.7>

Enter the simulation time in minutes: 30
Enter the number of bank tellers: 2
Enter the range of arrival times in minutes: 6 10
Enter the range of service times in minutes: 18 20
Time:  0  arrival of customer 1
Time:  7  arrival of customer 2
Time: 16  arrival of customer 3
Time: 19  departure of customer 1
       Teller 1  Wait 0  Service 19
Time: 25  departure of customer 2
       Teller 2  Wait 0  Service 18
Time: 37  departure of customer 3
       Teller 1  Wait 3  Service 18

******** Simulation Summary ********
Simulation of 37 minutes
    No. of Customers:   3
    Average Customer Wait: 1 minutes
    Teller #1  % Working: 100
    Teller #2  % Working: 49

<Run #2 of Program 5.7>

Enter the simulation time in minutes  480
Enter the number of bank tellers  4
Enter the range of arrival times in minutes  2 5
Enter the range of service times in minutes  6 20

<arrival and departure of 137 customers>

******** Simulation Summary ********
Simulation of 521 minutes
    No. of Customers:  137
    Average Customer Wait: 2 minutes
    Teller #1  % Working: 89
    Teller #2  % Working: 86
    Teller #3  % Working: 83
    Teller #4  % Working: 86
*/
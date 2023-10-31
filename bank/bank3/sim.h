#ifndef SIMULATION_CLASS
#define SIMULATION_CLASS

#include <iostream>
#include <iomanip>
using namespace std;
#pragma hdrstop

#include "random.h"     // include random number generator

// specifies the two kinds of events
enum EventType {arrival, departure};

class Event                                         
{
    private: 
        // members that identify both customer and teller, as
        // well as maintain information on time of the event,
        // the event type, the length of service required by
        // the customer, and the amount of time customer is
        // forced to wait for service
        int time;
        EventType etype;
        int customerID;     // customers numbered 1, 2, 3,...
        int tellerID;       // tellers numbered 1, 2, 3,...
        int waittime;
        int servicetime;
        bool isvip;   //

        int agree;

    public:
        // constructors
        Event(void);
        Event(int t,EventType et,int cn,int tn,
              int wt,int st,bool isvip,int ag);
        
        // methods to retrieve private data
        bool Getvip(void) const;
        int GetTime(void) const;
        void Change_servicetime(int sert);
        void Change_agree(void);
        EventType GetEventType(void) const;
        int GetCustomerID(void) const;
        int GetTellerID(void) const;
        int GetWaitTime(void) const;
        int GetServiceTime(void) const;
        int Getagree(void) const;
        // void Changewaittime(int newtime) const;
};

// default constructor - data filled by assignment later
Event::Event(void)
{}

// constructor that initializes all data members of the event
Event::Event(int t,EventType et,int cn,int tn,
             int wt,int st, bool isvip,int ag): 
               time(t),etype(et),customerID(cn),tellerID(tn),
               waittime(wt),servicetime(st),isvip(isvip),agree(ag)
{}
    

//
bool Event::Getvip(void) const{
    return isvip;
}    
// return the time the event occurs
int Event::GetTime(void) const
{
    return time;
}
    
// return the type of event (arrival, departure)
EventType Event::GetEventType(void) const
{
    return etype;
}
    
// return the customer number
int Event::GetCustomerID(void) const
{
    return customerID;
}
    
void Event::Change_agree(void) 
{
    agree++;
}
//
int Event::Getagree(void) const
{
    return agree;
}

void  Event::Change_servicetime(int sert){
    servicetime = sert;
}
// return the teller number
int Event::GetTellerID(void) const
{
    return tellerID;
}
    
// return the time the customer waits for service
int Event::GetWaitTime(void) const
{
    return waittime;
}

// return the amount of teller time needed by customer
int Event::GetServiceTime(void) const
{
    return servicetime;
}

// void Event::Changewaittime(int newtime) const 
// {
//     waittime = newtime;
// }

// compare two Event objects using the time at 
// which the events occur. needed for the priority queue
int operator< (Event e1, Event e2)
{
    return e1.GetTime() < e2.GetTime();
}

typedef  Event  DataType;       // elements are Event objects

#include "apqueue.h"


// Structure for Teller Info    
struct TellerStats
{
    int finishService;      // when teller available
    int totalCustomerCount; // total of customers serviced
    int totalCustomerWait;  // total customer waiting time
    int totalService;       // total time servicing customers

    int vip_jump;   // number of vip jump
    int vip_count; // number of vip 

};

class Simulation
{
    private:
        // data used to run the simulation
        int simulationLength;        // simulation length
        int numTellers;              // number of tellers
        int nextCustomer;            // next customer ID
        int arrivalLow, arrivalHigh; // next arrival range
        int serviceLow, serviceHigh; // service range
        int vip_proportion;     // vip in ten customers
        int max_wait;           // max_time vip waiting

        TellerStats tstat[11];       // max 10 tellers
        PQueue pq;                   // priority queue
        PQueue jump_pq;                // vip jump queue
        RandomNumber rnd;            // use for arrival
                                     // and service times
                                        
        // private methods used by RunSimulation
        int NextArrivalTime(void);
        int GetServiceTime(void);
        int NextAvailableTeller(Event e);
    public:
        // constructor
        Simulation(void);
                
        void RunSimulation(void);           // execute study
        void PrintSimulationResults(void);  // print stats
};

// constructor initializes simulation data and prompts client
// for simulation parameters
Simulation::Simulation(void)
{
    int i;
    //Event firstevent;
    
    // Initialize Teller Information Parameters
    for(i = 1; i <= 10; i++)
    {
        tstat[i].finishService = 0; 
        tstat[i].totalService = 0;
        tstat[i].totalCustomerWait = 0;
        tstat[i].totalCustomerCount = 0;
        tstat[i].vip_count = 0;
        tstat[i].vip_jump = 0;

    }
    nextCustomer = 1;
    
    // reads client input for the study
    cout << "Enter the simulation time in minutes: ";
    cin >> simulationLength;
    cout << "Enter the number of bank tellers: ";
    cin >> numTellers;
    cout << "Enter the range of arrival times in minutes: ";
    cin >> arrivalLow >> arrivalHigh;
    cout << "Enter the range of service times in minutes: ";
    cin >> serviceLow >> serviceHigh;
    cout<< "Enter the vip number in ten customers: ";
    cin>> vip_proportion;
    cout << "Enter the maximum wait time for the vip" ;
    cin>> max_wait;

    
    // generate first arrival event
    // teller#/waittime/servicetime not used for arrival
    int j = rand()%10;
    bool isvip;
    if(j >= vip_proportion) isvip = false;
    else isvip = true;  

    pq.PQInsert(Event(0,arrival,1,0,0,0,isvip,0));
}

// determine random time of next arrival 
int Simulation::NextArrivalTime(void)
{
    return arrivalLow+rnd.Random(arrivalHigh-arrivalLow+1);
}

// determine random time for customer service
int Simulation::GetServiceTime(void)
{
    return serviceLow+rnd.Random(serviceHigh-serviceLow+1);
}

// return first available teller
int Simulation::NextAvailableTeller(Event e)
{
    // initially assume all tellers finish at closing time
   
    // assign random teller to customer who arrives
    // before closing but obtains service after closing
  
    int minfinish = tstat[2].finishService;
    int num[20], m, i;
    int minfinishindex = 2;
    m = 1;
    num[0] = 2;
    for(i = 3; i <= numTellers; i++)
        if (tstat[i].finishService < minfinish) {
            minfinish = tstat[i].finishService;
            num[0] = i;
            m = 1;
        }
        else {
            if(tstat[i].finishService == minfinish)
                num[m++] = i;
        }

    minfinishindex = num [rand() % m];
	if((tstat[1].finishService ==0 && minfinish!=0)||(minfinish>=simulationLength && minfinish>tstat[1].finishService))
	{
		minfinishindex=1;// 允许普通用户排没有人的VIP队，或是其他队伍中最短的队伍已经超出服务时间，同时VIP没有超出时间
	}

	else if(e.Getvip()==true)
		if(tstat[1].finishService <= tstat[minfinishindex].finishService)
			minfinishindex=1;
    return minfinishindex;
}

// implements the simulation
void Simulation::RunSimulation(void)
{
    Event e, newevent;
    int nexttime;
    int tellerID;
    int servicetime;
    int waittime;
    
    
    int agree[numTellers] = {0};

    
    // run till priority queue is empty
    while (!pq.PQEmpty())
    {
        // get next event (time measures the priority)
        e = pq.PQDelete();
        
        // handle an arrival event
        if (e.GetEventType() == arrival)
        {
            // compute time for next arrival.
            nexttime = e.GetTime() + NextArrivalTime();
            
            if (nexttime > simulationLength)
                // process events but don't generate any more
                continue;
            else
            {
                // generate arrival for next customer. put in queue
                nextCustomer++;
                bool isvip;
                int j = rand() % 10;
                if (j>= vip_proportion) isvip = false;
                else isvip = true;
                newevent = Event(nexttime, arrival, 
                                 nextCustomer, 0, 0, 0,isvip,0);
                pq.PQInsert(newevent);
            }
            
            cout << "Time: " << setw(2) << e.GetTime()
                 << "  " << "arrival of customer "
                 << e.GetCustomerID() <<"  isVip " <<e.Getvip()<< endl;
                
            // generate departure event for current customer
            
            // time the customer takes
            servicetime = GetServiceTime();
            
            // teller who services customer
            tellerID = NextAvailableTeller(e); //根据是否是VIP为其选择合适的teller

           
              // if teller free, update sign to current time
            if (tstat[tellerID].finishService == 0)
                tstat[tellerID].finishService = e.GetTime();

            // compute time customer waits by subtracting the
            // current time from time on the teller's sign

            waittime = tstat[tellerID].finishService -
                          e.GetTime();
           // if (waittime < 0) waittime = 0;
            
            if(e.Getvip()==true && waittime > max_wait){
                //cout <<"Time: " << setw(2) << e.GetTime()<< "arrival of customer "<<e.GetCustomerID()<<" isVip "<<e.Getvip()<<endl;
                //不用专门为需要插队的VIP用户打印到达信息，因为打印的到达信息其实只有谁来了，但是并没有提到到达的用户所去的窗口是哪个
                e.Change_servicetime(servicetime);
                jump_pq.PQInsert(e);
            }

            else{
                

            // 这是用户正常排队情况下的柜台变化情况
            tstat[tellerID].totalCustomerWait += waittime;
            tstat[tellerID].totalCustomerCount++;
            tstat[tellerID].totalService += servicetime;
            tstat[tellerID].finishService += servicetime;
            //cout<<tstat[2].finishService<<"  111  222  "<<servicetime<<endl;
            if (e.Getvip()==true) tstat[tellerID].vip_count++;
            
            // create a departure object and put in the queue

            newevent = Event(tstat[tellerID].finishService,
                        departure,e.GetCustomerID(),tellerID,
                        waittime,servicetime,e.Getvip(),0);

            
            pq.PQInsert(newevent);
            }
        }
        // handle a departure event
        else
        {
            //打印depart信息，最后判断如果离开的是该队伍最后一个人，那么就把该柜台的finishservice赋0
            cout << "Time: " << setw(2) << e.GetTime()
                 << "  " << "departure of customer "
                 << e.GetCustomerID() <<" isVip "<< e.Getvip()<<endl;
            cout << "       Teller " << e.GetTellerID()
                 << "  Wait " << e.GetWaitTime()
                 << "  Service " << e.GetServiceTime()
                 << endl;
            
            tellerID = e.GetTellerID();
            agree[tellerID] -= e.Getagree();//减去离开的人的愤怒值

            bool no_vip = true;  //判断这个柜台排队的人里面有没有VIP
            int i,j;
            for(i = 0;i<pq.PQLength();i++){
                Event tmp_event = pq.PQGetlist()[i];
                if (tmp_event.GetTellerID() == tellerID && tmp_event.Getvip()==true){
                    no_vip = false;
                    break;
                }
            }//判断结束

            bool can_jump = true;
            int max_angre = agree[2];
            int max_angre_index = 2;

            for(j = 1;j<=numTellers;j++){
                agree[j] = 0; //初始化愤怒值 
            for(i = 0;i<pq.PQLength();i++){
                Event tmp_event =  pq.PQGetlist()[i];
                if(tmp_event.GetEventType()== departure){
                    agree[tmp_event.GetTellerID()] += tmp_event.Getagree(); 
            }   
            }
            }
            
            int m = 0;
            for(j = 3;j<=numTellers;j++){
                if( agree[j] > max_angre)
                {
                    max_angre = agree[j];
                    max_angre_index = j;
                    m = 1;
                }
            }

            if (tellerID == max_angre_index) can_jump = false;



            if (jump_pq.PQEmpty()!=true && no_vip && can_jump){//如果需要插队的队列里面有VIP在等,并且当前被插队的队列没有VIP

            Event vip_event = jump_pq.PQDelete();

            int vip_st = vip_event.GetServiceTime();
            int vip_wt = e.GetTime() - vip_event.GetTime();  //因为要插队，所以插进去没有等待，只有在插队队列中的时间是VIP的等待时间

            int num = 0;
            for(num = 0; num < pq.PQLength(); num++){ //小于count
                Event event = pq.PQGetlist()[num];

                if(event.GetTellerID() == tellerID && event.GetEventType() == departure){//对后面的顾客的离开事件进行修改，修改等待时间和刻度时间
                    int  event_waittime = event.GetWaitTime() + vip_st;
                    newevent = Event(event.GetTime() + vip_st,event.GetEventType(),event.GetCustomerID(),event.GetTellerID(), event_waittime,event.GetServiceTime(),event.Getvip(),event.Getagree());
                    newevent.Change_agree();
                    pq.PQGetlist()[num] = newevent;
                }

             
               
            }

            
                //对该柜台的信息进行修改,其中柜台总的等待时间应该是对后面每一个用户都加上了
                tstat[tellerID].totalCustomerWait += vip_st; 
                tstat[tellerID].finishService += vip_st;
                tstat[tellerID].totalService += vip_st;
                tstat[tellerID].totalCustomerCount++;
                tstat[tellerID].vip_jump++;
                tstat[tellerID].vip_count++;

               //构造VIP的离开时间，加入队列中 
            Event vip_depart = Event(e.GetTime() + vip_st, departure, vip_event.GetCustomerID(), tellerID, vip_wt, vip_st, true,vip_event.Getagree());
            //cout<<"vip jump"<<endl;

            pq.PQInsert(vip_depart);
            //cout<<"vip jump"<<endl;
            }


            
            // if nobody waiting for teller, mark teller free
            if (e.GetTime() == tstat[tellerID].finishService)
                tstat[tellerID].finishService = 0;
            

        } 
    }
    
    // adjust simulation to account for overtime by tellers
    simulationLength = (e.GetTime() <= simulationLength)
                        ? simulationLength : e.GetTime();
}

// summarize the simulation results
void Simulation::PrintSimulationResults(void)
{
    int cumCustomers = 0, cumWait = 0, i;
    int avgCustWait, tellerWorkPercent;
    float tellerWork;

    for (i = 1; i <= numTellers; i++)
    {
        cumCustomers += tstat[i].totalCustomerCount;
        cumWait += tstat[i].totalCustomerWait;
    }

    cout << endl;
    cout << "******** Simulation Summary ********" << endl;
    cout << "Simulation of " << simulationLength
         << " minutes" << endl;
    cout << "   No. of Customers:  " << cumCustomers << endl;
    cout << "   Average Customer Wait: ";
    
    avgCustWait = int(float(cumWait)/cumCustomers + 0.5);
    cout << avgCustWait << " minutes" << endl;
    for(i=1;i <= numTellers;i++)
    {
        cout << "    Teller #" << i << "  % Working: ";
        // display percent rounded to nearest integer value
        tellerWork = float(tstat[i].totalService)/simulationLength;
        tellerWorkPercent =int( tellerWork * 100.0 + 0.5);
        
        cout << tellerWorkPercent << endl;
        cout << "     Served vip number: " << tstat[i].vip_count << endl;
        cout << "     Vip Jump number:   " << tstat[i].vip_jump <<endl;
    }
}

#endif  // SIMULATION_CLASS
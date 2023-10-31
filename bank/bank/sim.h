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
    public:
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

        float anger[2];
        float angertime;
    public:
        // constructors
        Event(void);
        Event(int t,EventType et,int cn,int tn,
              int wt,int st,bool isvip);
        
        // methods to retrieve private data
        bool Getvip(void) const;
        void add(int ti);
        int GetTime(void) const;
        EventType GetEventType(void) const;
        int GetCustomerID(void) const;
        int GetTellerID(void) const;
        int GetWaitTime(void) const;
        int GetServiceTime(void) const;
        int GetAngertime(void) const;
};

// default constructor - data filled by assignment later
Event::Event(void)
{}

// constructor that initializes all data members of the event
Event::Event(int t,EventType et,int cn,int tn,
             int wt,int st, bool isvip): 
               time(t),etype(et),customerID(cn),tellerID(tn),
               waittime(wt),servicetime(st),isvip(isvip)
{
    anger[0] = float(rand()%10/10);
    anger[1] = 0;
    angertime = 0;
}
    

//
bool Event::Getvip(void) const{
    return isvip;
}    
// return the time the event occurs
int Event::GetTime(void) const
{
    return time;
}
    

//
void Event::add(int ti)
{
    time += ti;
    waittime += ti;
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
    
//
int Event::GetAngertime(void) const
{
    return angertime;
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

    int totoalvipwait; //vip wait time
    int Vipcount; // number of vip
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
        int waithigh; // number of

        TellerStats tstat[11];       // max 10 tellers
        PQueue pq;                   // priority queue
        RandomNumber rnd;            // use for arrival
                                     // and service times
                                        
        // private methods used by RunSimulation
        int NextArrivalTime(void);
        int GetServiceTime(void);
        int NextAvailableTeller(Event e);

    public:
        // constructor
        Simulation(void);
        
        int Queuejump(Event e,Event storage);
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
        tstat[i].totoalvipwait = 0; 
        tstat[i].Vipcount = 0;
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
    cout<< "Enter the longgest waitting time vip can tolerant: ";
    cin>> waithigh;
    
    // generate first arrival event
    // teller#/waittime/servicetime not used for arrival
    int j = rand()%10;
    bool isvip;
    if(j >= vip_proportion) isvip = false;
    else isvip = true;  

    pq.PQInsert(Event(0,arrival,1,0,0,0,isvip));
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

//
int Simulation::Queuejump(Event e,Event storage){
    int windows[11][MaxPQSize];
	int a[11]={0},b[11]={0},bTime[11]={0};

	int i,j,k,temp;
	int mintime,num[10],m,min;
	int n;
	for(i=0;i<pq.PQLength();i++)
		if(pq.pqlist[i].GetEventType()==departure)
		{
			j=pq.pqlist[i].GetTellerID();
			windows[j][a[j]]=i;
			a[j]+=1;
		}
	for(i=1;i<=numTellers;i++)
	{
		for(j=0;j<a[i]-1;j++)
		{
			for(k=j+1;k<a[i];k++)
			{
				if(pq.pqlist[windows[i][k]].GetTime()<pq.pqlist[windows[i][k-1]].GetTime())
				{
					temp=windows[i][k];
					windows[i][k]=windows[i][k-1];
					windows[i][k-1]=temp;
				}
			}
		}
	}
	for(i=1;i<=numTellers;i++)
	{
		j=0; 
		b[i]=a[i];
		for(j=0;j<a[i];j++)
		{
			if(pq.pqlist[windows[i][j]].GetTime()-pq.pqlist[windows[i][j]].GetServiceTime()-e.time>=e.waittime)
				if(pq.pqlist[windows[i][j]].isvip==false)
				{ 
					b[i]=j;
					bTime[i]=pq.pqlist[windows[i][j]].GetTime()-pq.pqlist[windows[i][j]].GetServiceTime();
					break;
				}
		}
		if(b[i]==0)
		{
			bTime[i]=e.GetTime();
		}
		else if(b[i]==a[i])
		{
			bTime[i]= e.GetTime()>pq.pqlist[windows[i][j-1]].GetTime()?e.GetTime():pq.pqlist[windows[i][j-1]].GetTime();
		}
	}
	for(i=1;i<=numTellers;i++)
	{
		for(j=0;j<a[i];j++)
		{
			if(pq.pqlist[windows[i][j]].GetAngertime()>= e.waittime)
			{
				bTime[i]= pq.pqlist[windows[i][a[i]-1]].GetTime();
				break;
			}
		}
	}
	m=1,num[0]=1,mintime=bTime[1];
	for(i=2;i<=numTellers;i++)
	{
		if(bTime[i]<mintime)
		{
			mintime=bTime[i];
			m=1;
			num[0]=i;
		}
		else if(bTime[i]==mintime)
		{
			num[m++]=i;
		}
	}
	printf("mintime = %d\n",mintime);
 	min=num[rand()%m];
	n=0;
	for(j=b[min];j<a[min];j++)
	{
		pq.pqlist[windows[min][j]].add(e.servicetime);
		ChangeAnger(&(pq->pqlist[windows[min][j]]));
		n+=1;
	}
	storage->tellerID=min;
  	storage->waittime=mintime-e->time;
	storage->time=mintime+ e->servicetime;
	return n;
}

// implements the simulation
void Simulation::RunSimulation(void)
{
    Event e, newevent;
    int nexttime;
    int tellerID;
    int servicetime;
    int waittime;
    
    int n;

        
    // run till priority queue is empty
    while (!pq.PQEmpty())
    {
        // get next event (time measures the priority)
        e = pq.PQDelete();
        n =0 ;
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
                                 nextCustomer, 0, 0, 0,isvip);
                pq.PQInsert(newevent);
            }
            
            cout << "Time: " << setw(2) << e.GetTime()
                 << "  " << "arrival of customer "
                 << e.GetCustomerID() <<"  isVip " <<e.Getvip()<< endl;
                
            // generate departure event for current customer
            
            // time the customer takes
            servicetime = GetServiceTime();
            // teller who services customer
            tellerID = NextAvailableTeller(e);

            // if teller free, update sign to current time
            if (tstat[tellerID].finishService == 0)
                tstat[tellerID].finishService = e.GetTime();
        
            // compute time customer waits by subtracting the
            // current time from time on the teller's sign
            waittime = tstat[tellerID].finishService -
                          e.GetTime();
            
            
            e.servicetime = servicetime;
            // update teller statistics
            tstat[tellerID].totalCustomerWait += waittime;
            tstat[tellerID].totalCustomerCount++;
            tstat[tellerID].totalService += servicetime;
            tstat[tellerID].finishService += servicetime;

            // create a departure object and put in the queue

            newevent = Event(tstat[tellerID].finishService,
                        departure,e.GetCustomerID(),tellerID,
                        waittime,servicetime,e.Getvip());
            pq.PQInsert(newevent);
        }
        // handle a departure event
        else
        {
            cout << "Time: " << setw(2) << e.GetTime()
                 << "  " << "departure of customer "
                 << e.GetCustomerID() <<"isVIP"<< e.Getvip()<<endl;
            cout << "       Teller " << e.GetTellerID()
                 << "  Wait " << e.GetWaitTime()
                 << "  Service " << e.GetServiceTime()
                 << endl;
            tellerID = e.GetTellerID();
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
    }
}

#endif  // SIMULATION_CLASS
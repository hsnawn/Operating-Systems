#include<stdio.h>
// Function to find the waiting time for all
// processes
struct process
{
    char name;
    int AT,BT,WT,TAT,RT,CT;
}Q1[10],Q2[10],Q3[10];/*Three queues*/

int n;
void sortByArrival()
{
struct process temp;
int i,j;
for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
            {
                if(Q1[i].AT>Q1[j].AT)
                    {
                          temp=Q1[i];
                          Q1[i]=Q1[j];
                          Q1[j]=temp;
                    }
            }
    }
}

//function to find waiting time
void findWaitingTime(int processes[], int n,
						int bt[], int wt[])
{
	// waiting time for first process is 0
	wt[0] = 0;
	
	// calculating waiting time
	for (int i = 1; i < n ; i++ )
		wt[i] = bt[i-1] + wt[i-1] ;
}

	
// Function to calculate turn around time
void findTurnAroundTime( int processes[], int n,
				int bt[], int wt[], int tat[])
{
	// calculating turnaround time by adding
	// bt[i] + wt[i]
	for (int i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}
	
//Function to calculate average time
void findavgTime( int processes[], int n, int bt[])
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;
	
	//Function to find waiting time of all processes
	findWaitingTime(processes, n, bt, wt);
	
	//Function to find turn around time for all processes
	findTurnAroundTime(processes, n, bt, wt, tat);
	
	//Display processes along with all details
	printf("Pid\tBurst_time\tWaiting_time\tTurnatime\n");
	
	// Calculate total waiting time and total turn
	// around time
	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		printf(" %d \t",(i+1));
		printf(" %d\t\t ", bt[i] );
		printf("%d\t",wt[i] );
		printf("	 %d\n",tat[i] );
	}
	int s=(float)total_wt / (float)n;
	int t=(float)total_tat / (float)n;
	printf("Average waiting time = %d",s);
	printf("\n");
	printf("Average turn around time = %d ",t);
	printf("\n");
}
	
//main code
int main()
{
        int option;
        printf("Available Scheduling algorithms are:\n");
        printf("1: First Come First Serve\n");
        printf("2: Shortest Job First\n");
        printf("3: Priority Scheduling\n");
        printf("4: Round Robin\n");
        printf("5: Priority Based Round Robin\n");
		printf("6: Multilevel Queue\n");
		printf("Enter Your Integer Choice:");
		scanf("%d",&option);
		
	if(option==1)
	{
	int processes[] = { 1, 2, 3,4,5,6,7,8};
	int n = sizeof processes / sizeof processes[0];
	//Burst time of all processes
	int burst_time[] = {20, 25,25,15,20,10,30,25};
	findavgTime(processes, n, burst_time);
	}
	//SJF algo
	if(option==2)
	{
	int wait[20],tat[20];
    int i,j,total=0,temp1,temp;
    int processes[] = { 1, 2, 3,4,5,6,7,8};
    int burst_time[] = {20, 25,25,15,20,10,30,25};
    float avg_wt,avg_tat;
    int n = sizeof processes / sizeof processes[0];
   //sorting of burst times
    for(i=0;i<n;i++)
    {
        temp1=i;
        for(j=i+1;j<n;j++)
        {
            if(burst_time[j]<burst_time[temp1])
                temp1=j;
        }
  
        temp=burst_time[i];
        burst_time[i]=burst_time[temp1];
        burst_time[temp1]=temp;
  
        temp=processes[i];
        processes[i]=processes[temp1];
        processes[temp1]=temp;
    }
   
    wait[0]=0;            
  
   
    for(i=1;i<n;i++)
    {
        wait[i]=0;
        for(j=0;j<i;j++)
            wait[i]+=burst_time[j];
  
        total+=wait[i];
    }
  
    avg_wt=(float)total/n;      
    total=0;
  
    printf("Pid Burst Wait TurnaTime\n");
    for(i=0;i<n;i++)
    {
        tat[i]=burst_time[i]+wait[i];   
        total+=tat[i];
        printf("%d    %d   %d   %d  \n",processes[i],burst_time[i],wait[i],tat[i]);
    }
  
    avg_tat=(float)total/n;    
    printf("Average Waiting Time=%f\n",avg_wt);
    printf("Average Turnaround Time=%f\n",avg_tat);
	}
	//priority scheduling
    if(option==3)
	{
    int x,w[10],t[10],awt,atat,i;
   int processes[] = { 1, 2, 3,4,5,6,7,8};
   int n = sizeof processes / sizeof processes[0];
   int burst_time[] = {20, 25,25,15,20,10,30,25};
   int priority[]={4,3,3,5,5,1,3,10};
  for(i=0;i<n-1;i++)
   {
     for(int j=i+1;j<n;j++)
     {
       if(priority[i]<priority[j])
       {
         x=priority[i];
         priority[i]=priority[j];
         priority[j]=x;
         x=burst_time[i];
         burst_time[i]=burst_time[j];
         burst_time[j]=x;
         x=processes[i];
         processes[i]=processes[j];
         processes[j]=x;
      }
   }
}
w[0]=0;
awt=0;
t[0]=burst_time[0];
atat=t[0];
for(i=1;i<n;i++)
 {
   w[i]=t[i-1];
   awt+=w[i];
   t[i]=w[i]+burst_time[i];
   atat+=t[i];
 }
printf("\n\n Job \t Burst Time \t Wait Time \t Turn Around Time   Priority \n");
for(i=0;i<n;i++)
  printf("\n %d \t\t %d  \t\t %d \t\t %d \t\t %d \n",processes[i],burst_time[i],w[i],t[i],priority[i]);
awt/=n;
atat/=n;
printf("\n Average Wait Time : %d \n",awt);
printf("\n Average Turn Around Time : %d \n",atat);

    }
    
   //round robbin... 
    if(option==4)
	{
    int i, total = 0, x, counter = 0, time_quantum=10;
      int wait_time = 0, turnaround_time = 0, temp[10];
      float average_wait_time, average_turnaround_time;
      int processes[] = { 1, 2, 3,4,5,6,7,8};
      int n = sizeof processes / sizeof processes[0];
      int burst_time[] = {20, 25,25,15,20,10,30,25};
      int arrival_time[]={4,3,0,5,25,10,3,10};
      x = n;
      for(i = 0; i < n; i++)
      {
         temp[i] = burst_time[i];
      }
      printf("Pid \t\t Burst_time\t\tTurnaround_time\t\tWaiting_Time\n");
      for(total = 0, i = 0; x != 0;)
      {
            if(temp[i] <= time_quantum && temp[i] > 0)
            {
                  total = total + temp[i];
                  temp[i] = 0;
                  counter = 1;
            }
            else if(temp[i] > 0)
            {
                  temp[i] = temp[i] - time_quantum;
                  total = total + time_quantum;
            }
            if(temp[i] == 0 && counter == 1)
            {
                  x--;
                  printf("Process[%d]\t\t%d\t\t %d\t\t\t %d\n", processes[i], burst_time[i], total - arrival_time[i], total - arrival_time[i] - burst_time[i]);
                  wait_time = wait_time + total - arrival_time[i] - burst_time[i];
                  turnaround_time = turnaround_time + total - arrival_time[i];
                  counter = 0;
            }
            if(i == n - 1)
            {
                  i = 0;
            }
            else if(arrival_time[i + 1] <= total)
            {
                  i++;
            }
            else
            {
                  i = 0;
            }
      }
 
      average_wait_time = wait_time * 1.0 / n;
      average_turnaround_time = turnaround_time * 1.0 / n;
      printf("nnAverage Waiting Time:t%f", average_wait_time);
      printf("nAvg Turnaround Time:t%fn", average_turnaround_time);
    }
    //multilevel queue
    if(option==6)
	{
    int l,time=0,sum_bt=0;
     int i,j,k=0,r=0,tq1=5,tq2=8,flag=0;
     char c;
     printf("Enter no of processes:");
     scanf("%d",&n);
     for(i=0,c='A';i<n;i++,c++)
     {
         Q1[i].name=c;
         printf("\nEnter the arrival time and burst time of process %c: ",Q1[i].name);
         scanf("%d%d",&Q1[i].AT,&Q1[i].BT);
         Q1[i].RT=Q1[i].BT;/*save burst time in remaining time for each process*/
    }
sortByArrival();
time=Q1[0].AT;
printf("Process in first queue following RR with qt=5");
printf("\nProcess\t\tRT\t\tWT\t\tTAT\t\t");
for(i=0;i<n;i++)
{
  if(Q1[i].RT<=tq1)
  {
       time+=Q1[i].RT;/*from arrival time of first process to completion of this process*/
       Q1[i].RT=0;
       Q1[i].WT=time-Q1[i].AT-Q1[i].BT;/*amount of time process has been waiting in the first queue*/
       Q1[i].TAT=time-Q1[i].AT;/*amount of time to execute the process*/
       printf("\n%c\t\t%d\t\t%d\t\t%d",Q1[i].name,Q1[i].BT,Q1[i].WT,Q1[i].TAT);
  }
  else/*process moves to queue 2 with qt=8*/
  {
      Q2[k].WT=time;
      time+=tq1;
      Q1[i].RT-=tq1;
      Q2[k].BT=Q1[i].RT;
      Q2[k].RT=Q2[k].BT;
      Q2[k].name=Q1[i].name;
      k=k+1;
      flag=1;
   }
}
if(flag==1)
 {printf("\nProcess in second queue following RR with qt=8");
  printf("\nProcess\t\tRT\t\tWT\t\tTAT\t\t");
}for(i=0;i<k;i++)
   {
    if(Q2[i].RT<=tq2)
     {
       time+=Q2[i].RT;/*from arrival time of first process +BT of this process*/
       Q2[i].RT=0;
       Q2[i].WT=time-tq1-Q2[i].BT;/*amount of time process has been waiting in the ready queue*/
       Q2[i].TAT=time-Q2[i].AT;/*amount of time to execute the process*/
       printf("\n%c\t\t%d\t\t%d\t\t%d",Q2[i].name,Q2[i].BT,Q2[i].WT,Q2[i].TAT);
    }
    else/*process moves to queue 3 with FCFS*/
    {
      Q3[r].AT=time;
      time+=tq2;
      Q2[i].RT-=tq2;
      Q3[r].BT=Q2[i].RT;
      Q3[r].RT=Q3[r].BT;
      Q3[r].name=Q2[i].name;
      r=r+1;
      flag=2;
    }
  }
{if(flag==2)
printf("\nProcess in third queue following FCFS ");
}
for(i=0;i<r;i++)
{
    if(i==0)
            Q3[i].CT=Q3[i].BT+time-tq1-tq2;
        else
            Q3[i].CT=Q3[i-1].CT+Q3[i].BT;
}
for(i=0;i<r;i++)
    {
        Q3[i].TAT=Q3[i].CT;
        Q3[i].WT=Q3[i].TAT-Q3[i].BT;
        printf("\n%c\t\t%d\t\t%d\t\t%d\t\t",Q3[i].name,Q3[i].BT,Q3[i].WT,Q3[i].TAT);
    }
    }
	return 0;
}




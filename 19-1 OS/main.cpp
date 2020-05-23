#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <algorithm>
#include "process.h"
using namespace std;

int total_turnaround = 0;
int total_wait = 0;
int total_initial = 0;
int max_turnaround = 0;
int min_turnaround = 5000;
int max_wait;
int min_wait;
int max_initial;
int min_initial;


bool sorter(process a, process b)
{
	return a.get_cpu_burst() < b.get_cpu_burst();
}

bool sorter2(process a, process b)
{
	return a.get_priority() < b.get_priority();
}

bool sorter3(process a, process b)
{
	return a.get_arrival() < b.get_arrival();
}

void FCFS(vector <process> processes, int num_processes)
{
	int num_completed = 0;
	int clock = 0;
	int last_pid = 0;
	vector <process> queue;
	bool cswitch = false;
	unsigned int index = processes.size();

	while (num_completed != num_processes) // 모든 프로세스가 terminated 될 때 까지
	{
		index = processes.size();
		for (unsigned int i = 0; i < index; i++)
		{
			if (processes[i].get_arrival() <= clock)
			{
				queue.push_back(processes[i]);
				cout  << processes[i].get_arrival() << "\t" << processes[i].get_pid() << " arrived (requires " << processes[i].get_cpu_burst() << " CPU burst)"  << endl;
				processes.erase(processes.begin() + i);
				index--;
				i--;
			}

		}

		if (queue.size() != 0)
		{
			if (cswitch)
			{
				cout << "Context switch (process " << last_pid << " -> process " << queue[0].get_pid() << ")"  << endl;
				clock = clock + 7;
				cswitch = false;
			}
			if (queue[0].get_seen() == false)
			{
			
				int arriv = clock - queue[0].get_arrival();
				queue[0].seen(arriv);
				total_initial += arriv;

			}
			queue[0].dec_burst();
			if (queue[0].get_cpu_burst() == 0)
			{
				int fwait = ((clock + 1) - queue[0].get_cpu_burst() - queue[0].get_arrival());
				cout << clock + 1 << "\t" << queue[0].get_pid() << endl;
				last_pid = queue[0].get_pid();
				int turn = ((clock + 1) - queue[0].get_arrival());
				total_turnaround += turn;
				total_wait += fwait;
				
				queue.erase(queue.begin());
				num_completed++;

				if (queue.size() != 0)
				{
					cout << "Context switch (process " << last_pid << " -> process " << queue[0].get_pid() << ")" << endl;
				}
				else
				{
					cswitch = true;

					clock = clock + 7;
				}
			}
		}
		clock++;
	}
}


void SJF(vector <process> processes, int num_processes)
{
	int num_completed = 0;
	int clock = 0;
	int last_pid = 0;
	vector <process> queue;
	vector <process> temp;
	bool cswitch = false;
	unsigned int index = processes.size();

	while (num_completed != num_processes) // 모든 프로세스가 terminated 될 때 까지
	{
		index = processes.size();
		for (unsigned int i = 0; i < index; i++)
		{
			if (processes[i].get_arrival() <= clock)
			{
				temp.push_back(processes[i]);
				cout <<  clock << "\t" << processes[i].get_pid() << " arrived (requires " << processes[i].get_cpu_burst() << " CPU time)" << endl;
				processes.erase(processes.begin());
				index--;
				i--;
			}

		}

		sort(temp.begin(), temp.end(), sorter);
		for (unsigned int i = 0; i < temp.size(); i++)
		{
			queue.push_back(temp[i]);
		}
		temp.clear();
		if (!queue.empty()) {
			sort(queue.begin() + 1, queue.end(), sorter);
		}
		if (queue.size() != 0)
		{
			if (cswitch)
			{
				cout << clock - 7 << " Context switch (process " << last_pid << " ->  process " << queue[0].get_pid() << ")" << endl;
				clock = clock + 7;
				cswitch = false;
			}
			if (queue[0].get_seen() == false)
			{
				int arriv = clock - queue[0].get_arrival();
				queue[0].seen(arriv);
				total_initial += arriv;
				if (arriv < min_initial)
					min_initial = arriv;
				if (arriv > max_initial)
					max_initial = arriv;
				cout << clock << "\t" << queue[0].get_pid() << " (initial wait time " << queue[0].get_initial_wait() << ")" << endl;
			}

			queue[0].dec_burst();

			if (queue[0].get_cpu_burst() == 0)
			{
				int fwait = ((clock + 1) - queue[0].get_cpu_burst() - queue[0].get_arrival());
				cout <<  clock + 1 << "\t" << queue[0].get_pid() << "(turnaround time " << ((clock + 1) - queue[0].get_arrival()) << ", initial wait time " << queue[0].get_initial_wait() << ", total wait time " << fwait << ")" << endl;

				last_pid = queue[0].get_pid();
				int turn = ((clock + 1) - queue[0].get_arrival());
				total_turnaround += turn;
				total_wait += fwait;
				if (fwait < min_wait)
					min_wait = fwait;
				if (fwait > max_wait)
					max_wait = fwait;
				if (turn < min_turnaround)
					min_turnaround = turn;
				if (turn > max_turnaround)
					max_turnaround = turn;
				queue.erase(queue.begin());

				num_completed++;

				if (queue.size() != 0)
				{
					cout << "Context switch (process " << last_pid << " -> process " << queue[0].get_pid() << ")" << endl;
				}
				else
				{
					cswitch = true;
					clock = clock + 7;
				}
			}
		}
		clock++;
	}

}

void RR(vector <process> processes, int num_processes)
{
	int num_completed = 0;
	int clock = 0;
	int last_pid = 0;

	int timequantum = 10;
	int current_quantum = 0;
	vector <process> queue;
	unsigned int index = processes.size();
	bool cswitch = false;
	while (num_completed != num_processes) // 모든 프로세스가 terminated 될 때 까지
	{
		for (unsigned int i = 0; i < index; i++)
		{
			if (processes[i].get_arrival() <= clock)
			{
				queue.push_back(processes[i]);
				cout  << clock << "\t" << processes[i].get_pid() << " arrived (requires " << processes[i].get_cpu_burst() << " CPU time)" << endl;
				processes.erase(processes.begin());
				index--;
				i--;
			}

		}

		if (queue.size() != 0)
		{
			if (cswitch)
			{
				cout << clock - 7 << " Context switch (process " << last_pid << " -> process " << queue[0].get_pid() << ")" << endl;
				clock = clock + 7;
				cswitch = false;
			}
			if (queue[0].get_seen() == false)
			{

				int initial = (clock - queue[0].get_arrival());
				queue[0].seen(initial);
				total_initial += initial;
				if (initial  < min_initial)
					min_initial = initial;
				if (initial > max_initial)
					max_initial = initial;

				cout << clock << "\t" << queue[0].get_pid() << endl;
			}
			queue[0].dec_burst();
			current_quantum++;
			if (queue[0].get_io_burst() == 0)
			{
				int total_wait_p = ((clock + 1) - queue[0].get_arrival() - queue[0].get_cpu_burst());
				cout << clock + 1 << "\t" << queue[0].get_pid() << " (turnaround time " << ((clock + 1) - queue[0].get_arrival()) << ", initial wait time " << queue[0].get_initial_wait() << ", total wait time " << total_wait_p << ")" << endl;
				last_pid = queue[0].get_pid();
				int turnaround = ((clock + 1) - queue[0].get_arrival());
				total_turnaround += turnaround;
				total_wait += total_wait_p;
				if (total_wait_p < min_wait)
					min_wait = total_wait_p;
				if (total_wait_p > max_wait)
					max_wait = total_wait_p;
				if ((turnaround) < min_turnaround)
					min_turnaround = turnaround;
				if ((turnaround) > max_turnaround)
					max_turnaround = turnaround;
				queue.erase(queue.begin());
				num_completed++;
				if (queue.size() != 0)
				{
					cout << clock + 1 << " Context switch (process " << last_pid << " -> process " << queue[0].get_pid() << ")" << endl;
				}
				else
				{
					cswitch = true;
					clock = clock + 7;
				}
				current_quantum = 0;
			}
			else if (current_quantum == timequantum) // time_quantum을 모두 소모했을 때
			{
				last_pid = queue[0].get_pid();
				queue.push_back(queue[0]);
				queue.erase(queue.begin());
				current_quantum = 0;
				cout << clock + 1 << " Context switch (process " << last_pid << " -> process " << queue[0].get_pid() << ")" << endl;
			}
		}
		clock++;
	}

}


void priority(vector <process> processes, int num_processes)
{
	int num_completed = 0;
	int clock = 0;
	int last_pid = 0;


	vector <process> queue;
	vector <process> temp_queue;
	unsigned int index = processes.size();
	unsigned int index2;
	bool cswitch = false;
	int most_priority = 6;
	while (num_completed != num_processes)
	{
		for (unsigned int i = 0; i < index; i++)
		{
			if (processes[i].get_arrival() <= clock)
			{
				temp_queue.push_back(processes[i]);
				index2 = temp_queue.size();
				cout << clock << "\t" << processes[i].get_pid() << " arrived (requires " << processes[i].get_cpu_burst() << " CPU time  Priority: " << processes[i].get_priority() << ")" << endl;
				sort(temp_queue.begin(), temp_queue.end(), sorter2);
				//priority 기준 sort
				if (processes[i].get_priority() < most_priority)
					most_priority = processes[i].get_priority();
				processes.erase(processes.begin());
				index--;
				i--;
			}

		}
		index2 = temp_queue.size();
		for (unsigned int i = 0; i < index2; i++)
		{
			if (temp_queue[i].get_priority() == most_priority)
			{
				if (queue.size() != 0 && temp_queue[i].get_priority() < queue[0].get_priority())
				{
					cout <<  clock << " Context switch (process " << queue[0].get_pid() << " -> process " << temp_queue[i].get_pid() << ")" << endl;
					clock = clock + 14;
					for (unsigned int x = 0; x < queue.size(); x++)
					{
						temp_queue.push_back(queue[x]);
					}
					queue.clear();
				}
				queue.push_back(temp_queue[i]);
				temp_queue.erase(temp_queue.begin());
				index2--;
				i--;
			}

		}
		if (queue.size() != 0 && queue.size() > 1)
		{

			if (cswitch)
			{
				cout << clock - 7 << " Context switch (process " << last_pid << " -> process " << queue[0].get_pid() << ")" << endl;
				clock = clock + 7;
				cswitch = false;
			}
			if (queue[0].get_seen() == false)
			{
				int initial = (clock - queue[0].get_arrival());
				queue[0].seen(initial);
				total_initial += initial;
				if (initial  < min_initial)
					min_initial = initial;
				if (initial > max_initial)
					max_initial = initial;
				cout << clock << "\t " << queue[0].get_pid() << endl;
			}
			queue[0].dec_burst();

			if (queue[0].get_cpu_burst() == 0)
			{
				int total_wait_p = ((clock + 1) - queue[0].get_arrival() - queue[0].get_cpu_burst() - queue[0].get_io_burst());
				cout << clock + 1 << "\t" << queue[0].get_pid() << " (turnaround time " << ((clock + 1) - queue[0].get_arrival()) << ", initial wait time " << queue[0].get_initial_wait() << ", total wait time " << total_wait_p << ")" << endl;
				last_pid = queue[0].get_pid();
				int turnaround = ((clock + 1) - queue[0].get_arrival());
				total_turnaround += turnaround;
				total_wait += total_wait_p;
				if (total_wait_p < min_wait)
					min_wait = total_wait_p;
				if (total_wait_p > max_wait)
					max_wait = total_wait_p;
				if ((turnaround) < min_turnaround)
					min_turnaround = turnaround;
				if ((turnaround) > max_turnaround)
					max_turnaround = turnaround;
				queue.erase(queue.begin());
				num_completed++;
				if (queue.size() != 0)
				{
					cout << clock + 1 << " Context switch (process " << last_pid << " -> process " << queue[0].get_pid() << ")" << endl;
				}
				else
				{
					cswitch = true;

					clock = clock + 7;
					if (temp_queue.size() != 0)
						most_priority = temp_queue[0].get_priority();
					else
						most_priority++;
				}

			}
		}
		else if (queue.size() == 1)
		{
			if (cswitch)
			{
				cout << clock - 7 << " Context switch (process " << last_pid << " -> process " << queue[0].get_pid() << ")" << endl;
				clock = clock + 7;
				cswitch = false;
			}
			if (queue[0].get_seen() == false)
			{

				int arriv = clock - queue[0].get_arrival();
				queue[0].seen(arriv);
				total_initial += arriv;
				if (arriv < min_initial)
					min_initial = arriv;
				if (arriv > max_initial)
					max_initial = arriv;
	
				cout  << clock << "\t" << queue[0].get_pid() << endl;
			}
			queue[0].dec_burst();
			if (queue[0].get_cpu_burst() == 0)
			{
				int fwait = ((clock + 1) - queue[0].get_cpu_burst() - queue[0].get_arrival() - queue[0].get_cpu_burst());
				cout << clock + 1 << "\t" << queue[0].get_pid() << " (turnaround time " << ((clock + 1) - queue[0].get_arrival()) << ", initial wait time " << queue[0].get_initial_wait() << ", total wait time " << fwait << ")" << endl;
				last_pid = queue[0].get_pid();
				int turn = ((clock + 1) - queue[0].get_arrival());
				total_turnaround += turn;
				total_wait += fwait;
				if (fwait < min_wait)
					min_wait = fwait;
				if (fwait > max_wait)
					max_wait = fwait;
				if (turn < min_turnaround)
					min_turnaround = turn;
				if (turn > max_turnaround)
					max_turnaround = turn;
				queue.erase(queue.begin());
				num_completed++;
				if (queue.size() != 0)
				{
					cout << clock + 1 << " Context switch (process " << last_pid << " -> process " << queue[0].get_pid() << ")" << endl;
				}
				else
				{
					cswitch = true;
					clock = clock + 7;
					if (temp_queue.size() != 0)
						most_priority = temp_queue[0].get_priority();
					else
						most_priority++;
				}
			}
		}
		else if (queue.size() == 0)
		{
			if (temp_queue.size() != 0)
				most_priority = temp_queue[0].get_priority();
			else
				most_priority++;
		}
		clock++;
	}

}

int main()
{
	int num_processes;

	cout << "Simulate할 Process의 갯수를 입력하세요(1<= N <= 10)\n";
	do {
		cin >> num_processes;
		if (num_processes > 10 || num_processes < 1) {
			cout << "Process 갯수의 범위는 1 <= N <= 10 입니다. 다시 입력하세요\n";
		}
	} while (num_processes > 10 || num_processes < 1);

	int _arrivalTime;
	int _priority;
	int burstCount = 0;
	int _cpu_burst;
	int _io_burst;
	int _pid;
	int time = 0;
	int burstNum = 0;

	vector <process> processes; // memory

	for (int i = 0; i < num_processes; i++) {
		burstCount = 0;
		cout << "\nprocess " << i << " arrival time 입력 : ";
		cin >> _arrivalTime;
		time += _arrivalTime;
		do {
			cout << "process " << i << " priority 입력(1 ~ 9) : ";
			cin >> _priority;
			if (_priority > 9 || _priority < 1) {
				cout << "priority는 1 ~ 9의 범위를 가집니다. 다시 입력하세요.\n";
			}
		} while (_priority > 9 || _priority < 1);

		do {
			cout << "CPU burst time 입력(20개 이내, 현재 " << burstCount << "개) : ";
			cin >> _cpu_burst;

			if (_cpu_burst == 0 || burstCount >= 20) {
				break;
			}
			burstNum++;
			cout << "I/O burst time 입력 : ";
			cin >> _io_burst;

			if (burstCount == 0) {
				process temp(_cpu_burst, _io_burst, _arrivalTime, i, _priority); 
				processes.push_back(temp);
			}
			else {
				process temp(_cpu_burst, _io_burst, time, i, _priority); 
				processes.push_back(temp);
			}
			burstCount++;
			time += _cpu_burst + _io_burst;
		} while (burstCount < 20); // process 셋팅
	}

	
	sort(processes.begin(), processes.end(), sorter3); // arrival time에 따라 processSet sort

	



	cout << "------------------FCFS------------------" << endl << endl;
	FCFS(processes, burstNum);
	cout << endl;

	
	
	cout << "------------------SJF------------------" << endl << endl;
	SJF(processes, burstNum);
	cout << endl;



	cout << "------------------RR------------------" << endl << endl;
	RR(processes, num_processes);
	cout << endl;


	cout << "------------------Priority------------------" << endl << endl;

	priority(processes, burstNum);
	cout << endl;


	return 0;

}


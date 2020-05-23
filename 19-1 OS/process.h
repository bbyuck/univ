#ifndef PROCESS_H
#define PROCESS_H

class process {
private:
	int arrival_time;
	int cpu_burst;
	int io_burst;
	bool been_seen;
	int initial_wait;
	int total_wait;
	int priority;
	int pid;
public:
	process(int, int , int , int, int);
	int get_arrival();
	int get_cpu_burst();
	int get_priority();
	int get_io_burst();

	void set_arrival(int);
	void set_pid(int);
	void add_wait(int);
	void dec_burst();
	void seen(int);

	int get_initial_wait();
	int get_total_wait();
	bool get_seen();
	int get_pid();
};

#endif
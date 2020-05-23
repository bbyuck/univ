#include "process.h"

process::process(int _cpu_burst,int _io_burst, int _arrivalTime, int _pid, int _priority)
{
	pid = _pid;
	cpu_burst = _cpu_burst;
	io_burst = _io_burst;
	arrival_time = _arrivalTime;
	been_seen = false;
	priority = _priority;
	initial_wait = 0;
	total_wait = 0;
}

void process::set_pid(int num)
{
	pid = num;
}

bool process::get_seen()
{
	return been_seen;
}

int process::get_priority()
{
	return priority;
}

int process::get_cpu_burst()
{
	return cpu_burst;
}

int process::get_pid()
{
	return pid;
}

void process::set_arrival(int time)
{
	arrival_time = time;
}

int process::get_arrival()
{
	return arrival_time;
}

int process::get_io_burst()
{
	return io_burst;
}

void process::dec_burst()
{
	cpu_burst--;
}

int process::get_initial_wait()
{
	return initial_wait;
}

int process::get_total_wait()
{
	return total_wait;
}


void process::add_wait(int time)
{
	total_wait = total_wait + time;
}

void process::seen(int time)
{
	been_seen = true;
	initial_wait = time;
	total_wait = time;
}
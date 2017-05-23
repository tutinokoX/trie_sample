#ifndef XSDA_TRIES_PROCESSTIMER
#define XSDA_TRIES_PROCESSTIMER

#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cmath>


struct TimerConf {

	std::vector<long> time;
	std::string name;
	int no;
	int suffix;
};

class ProcessTimer
{
private:

	std::vector<TimerConf> save_time;
	std::chrono::time_point<std::chrono::system_clock> current_time;

	void AddTimer(TimerConf timer , long time);
	double SuffixConvertValue(int timer_suffix);
	std::string SuffixConvertStr(int timer_suffix);

public:

	ProcessTimer(){}
	~ProcessTimer(){}

	void StartTimer();
	void Measure(int process_no );

	void AddTimerName(size_t porcess_no , std::string process_name);
	void AddTimerSuffix(size_t process_no, int suffix);

	void AddTimerConf(size_t process_no, std::string process_name = "null" , int suffix = 0);

	void Output();
	std::string DataOutput(size_t mode);
};



void ProcessTimer::AddTimer( TimerConf timer , long time)
{
	size_t timer_no = static_cast<size_t>(timer.no);
	if (save_time.size() <= timer_no ) {
		save_time.resize( timer_no + 1 );
	}
	save_time[timer_no].time.push_back(time);
}

void ProcessTimer::StartTimer()
{
	current_time = std::chrono::system_clock::now();
}

void ProcessTimer::Measure(int process_no)
{

	auto search = std::chrono::system_clock::now();
	auto dur = search - current_time;
	long long msec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
	TimerConf timer;
	timer.no = process_no;

	AddTimer(timer, msec);
	StartTimer();

}


void ProcessTimer::AddTimerName(size_t process_no, std::string process_name)
{

	if (save_time.size() <= process_no) {
		save_time.resize(process_no + 1);
	}
	save_time[process_no].name = process_name;

}

void ProcessTimer::AddTimerSuffix(size_t process_no, int suffix) {

	if (save_time.size() <= process_no) {
		save_time.resize(process_no + 1);
	}
	save_time[process_no].suffix = suffix;
}

void ProcessTimer::AddTimerConf(size_t process_no, std::string process_name, int suffix)
{
	AddTimerName(process_no, process_name);
	AddTimerSuffix(process_no, suffix);
}

double ProcessTimer::SuffixConvertValue( int timer_suffix){

	switch(timer_suffix){

		case 0: return 1.0;
		case 1: return 1000.0;
		case 2: return 1000.0*1000.0;
		default :
			std::cerr << "err : ProcessTimer::SuffixConvertValue >> not faund case" << std::endl;
			exit(1);
	}

}

std::string ProcessTimer::SuffixConvertStr( int timer_suffix){

	switch(timer_suffix){

		case 0: return " [micro sec]";
		case 1: return " [m sec]";
		case 2: return " [sec]";
		default :
			std::cerr << "err : ProcessTimer::SuffixConvertStr >> not faund case" << std::endl;
			exit(1);
	}

}



void ProcessTimer::Output()
{

	int timer_count = 0;
	for (auto timer : save_time) {
		timer_count++;

		double all_time = 0;
		for (auto time : timer.time) all_time+= time / SuffixConvertValue(timer.suffix);

		double test_data = all_time / static_cast<double>(timer.time.size());
		//float test_data = ((float)all_time / (float)timer.time.size());
		std::cout << "timer[" << timer_count << "]	:  "
				  << std::fixed << std::setprecision(3)
				  << test_data
				  << SuffixConvertStr(timer.suffix)
				  << "	( " << timer.name << " ) "
				  << std::endl;

	}
}

std::string ProcessTimer::DataOutput( size_t mode )
{

	if(mode >= save_time.size()){
		std::cerr << "ProcessTimer::DataOutput -> not faund mode" << std::endl;
		return 0;
	}

	double all_time = 0;
	for (auto time : save_time[mode].time) all_time+= time / SuffixConvertValue(save_time[mode].suffix);
	double test_data = all_time / static_cast<double>( save_time[mode].time.size() );


	return std::to_string(test_data) + "	" + SuffixConvertStr( save_time[mode].suffix);
}



#endif // XSDA_TRIES_PROCESSTIMER
#ifndef XSDA_TRIES_STAUTEOUT
#define XSDA_TRIES_STAUTEOUT

#include <iostream>
#include <sstream>

class StateOut
{
private:
	size_t MAX_STATE;
	int SPLIT_SIZE;
	int NOW_STATE;

	std::string OUTCHAR;

public:
	StateOut();
	~StateOut();

	void SetConf();
	void AddMaxState(size_t max_state){ MAX_STATE = max_state; }
	void Output(const uint64_t &current);
	void StartSet();
};

StateOut::StateOut()
{
	SPLIT_SIZE = 2;
	OUTCHAR = "c";
	NOW_STATE = SPLIT_SIZE;
}


StateOut::~StateOut()
{
}

void StateOut::Output(const uint64_t &current){

	if(static_cast<double>(current*(100.0 / MAX_STATE)) >= NOW_STATE ){

		NOW_STATE += SPLIT_SIZE;
		std::cout << OUTCHAR << std::flush;
		// cout << OUTCHAR;
	}
}

void StateOut::StartSet(){

	NOW_STATE = SPLIT_SIZE;
	std::cout << "MS : " << MAX_STATE;

	std::cout << "\n\t|";
	for(int i = 0 ; i < 100 / SPLIT_SIZE ; i ++) std::cout << "-";
	std::cout << "|\n\t";
}


#endif // XSDA_TRIES_STAUTEOUT
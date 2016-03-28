#include<iostream>
#include<string>
#include<vector>
using namespace std;

#define SIZE 100

class ProblemD{

	char line[SIZE];
	vector<vector<string>> parse;
	vector<vector<string>> allpath;

	//---Simulator section---// 
	vector<vector<int>> sim; //for store the current simulate output
	vector<vector<int>> _allinvec;
	vector<vector<int>> _alloutvec;

public:

	void run();
	int input_check(string str); 
	vector<pair<int, string>> split_(string str, char* delim, bool _Makeinout); 	
	void parsefunc();
	bool find_next(vector<pair<int, int>> &pos, int row, int col, string tar);
	void find_path();

	//---Simulator section---// 
	void Veri_simulator();
	void _make_intout(char *pch, vector<int> &_inout_vec);
};
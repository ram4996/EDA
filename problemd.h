#ifndef PROBLEMD_H
#define PROBLEMD_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <stdio.h> 
#define PAUSE {printf("Press Enter key to continue..."); cin.ignore(); cin.get();}
typedef std::chrono::high_resolution_clock Clock;
using namespace std;

#define SIZE 100

class ProblemD{

	char line[SIZE];
	vector<vector<string>> parse; //Circuit description parsed from verilog file.

	//---Find all path section---//
	vector<vector<string>> allpath;

	//---Simulator section---// 
	vector<vector<int>> sim; //For store the current simulate output
	vector<vector<int>> _allinvec; //Input
	vector<vector<int>> _alloutvec; //Output

public:

	//---Neutral section---//
	template<typename T>
	void print_vec(vector<vector<T>> &vec);
	string remove_(string str, char remove_c[]);
	bool input_check(string str);
	vector<pair<int, string>> split_(string str, char* delim, bool _Makeinout, bool _simu); 	
	void parsefunc();
	void run();

	//---Find all path section---//
	bool find_next(vector<pair<int, int>> &pos, int row, int col, string tar);
	void find_path();


	//---Simulator section---// 
	void _make_inout(char *pch, vector<int> &_inout_vec, bool isOut);
	void Veri_simulator();
	bool logic_output(string func_str, vector<int> &vec);
	void SimTable_update(string tar, bool in);
	bool check_2DrowReady(vector<vector<int>> &vec);
	bool check_1DrowReady(vector<int> &vec);
};
#endif
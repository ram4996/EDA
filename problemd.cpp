#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include "problemd.h"
using namespace std;

void ProblemD::run(){
	parsefunc();
	find_path();
	//Veri_simulator();
}

int ProblemD::input_check(string str){ 
	/** Check the string is input or not.
	*/
	return (str[0] >= 'A' && str[0] <= 'Z' && str.size() > 0);
}

vector<pair<int, string>> ProblemD::split_(string str, char *delim, bool _Makeinout){ 

   /**\brief split_(string str, char *delim, bool _Makeinout) can split the string into two parts.
	*  By given a delim, then using bool _Makeinout adjust the split type.
	*  For now, notice the return type vector<pair<int, string>>, you have to using stoi() convert your typename.
	*/

	vector<pair<int, string>> split;

	char *otherPath_delim = delim;
	char *otherPath_pchU; //for Unit
	int Unit; //the covert Uint number will assign to Uint
	char *otherPath_pchn; //for wire 'n'
	char *cstr = new char[str.length()+1];
	strcpy_s(cstr, str.length()+1, str.c_str()); //C++11 

	otherPath_pchU = strtok(cstr, otherPath_delim);
	otherPath_pchn = strtok(NULL, otherPath_delim);

	string str_pchU(otherPath_pchU); //You need to remove the first char so we have to cover 'otherPath_pchU'to string

	if(_Makeinout == false){
		str_pchU.erase(0,1); //remove the char 'U'
	}
	else if(_Makeinout == true){
		istringstream is_second(otherPath_pchn);
		is_second>>otherPath_pchn;
	}
	istringstream is_first(str_pchU); //covert string to int 
	is_first>>Unit;

	split.push_back(make_pair(Unit, otherPath_pchn));

	//printf ("%d\n",Unit);
	//printf ("%s\n",otherPath_pchn);
	delete [] cstr;

	return split;
}

bool ProblemD::find_next(vector<pair<int, int>> &pos, int row, int col, string tar){ 

	/** \brief Given a begin position (row, column) try to find the exact element,
	*	if found then store position as pos.push_back(make_pair(rowPosition, colPosition)), 
	*	also return the result as bool.
	*/

	vector<vector<string>>::iterator itRow;
	vector<string>::iterator itCol;
	bool found = false;

	for(itRow = parse.begin()+row; itRow != parse.end(); itRow++){		 

		itCol = find( itRow->begin()+2, itRow->end()-1, tar);
		if(itCol != itRow->end()-1){

			//cout<<*(itRow->end()-1)<<endl; //print the itRow->end()
			int rowPosition = distance(parse.begin(), itRow);
			int colPosition = distance(itRow->begin(), itCol);
			pos.push_back(make_pair(rowPosition, colPosition));
			found = true;
			break;
		}
	}

	return found;
}

void ProblemD::find_path(){

	/** \brief We find all path in this function.
	*	We are using deepest first search in each input e.g. A[1].
	*   But we aren't consider the rising/falling signal which following to ProblemD, and some of output
	*	style might change but describe the path well.
	*/

	vector<string> path;
	vector<pair<int, int>> pos;
	vector<pair<int, string>> split;
	string tar;
	int row = 0; //row is a start point to find element
	int col = 0;
	bool new_path = false;

	for(size_t i = 0; i < parse.size(); i++){ //find the path in U1~U11
		for(size_t j = 2; j < parse[i].size()-1; j++){

			if(input_check(parse[i][j])){

				//cout<<"Is input:"<<ans[i][j]<<"in "<<i<<", "<<j<<endl;
				path.push_back("U"+to_string(i+1)+"/"+parse[i][j]);
				//path.push_back("U"+to_string(i+1)+"/");

				if( (parse[i][parse[i].size()-1])[0] == 'M'){

					//tar = parse[i][parse[i].size()-1];
					//path.push_back("U"+to_string(i+1)+"/"+tar); 
					path.push_back(parse[i][parse[i].size()-1]);
					allpath.push_back(path);
				}
				else{

					tar = parse[i][parse[i].size()-1];
					//cout<<"tar: "<<tar<<", "<<i+1<<endl;
					path.push_back("start"); //**It will be pop in !new_path  

					while(!path.empty()){

						//Here just find the target once but all excist in ans vector
						//pos will return all first route in input that are not just 1 steps.
						if(find_next(pos, row, col, tar)){ 

							if(!new_path) { // && (path.size()>2)

								new_path = true;
								path.pop_back();
							}

							path.push_back("U"+to_string(pos[0].first+1)+"/"+tar);
							row = pos[0].first; 
							tar = parse[row][parse[row].size()-1]; //change target
							path.push_back("U"+to_string(pos[0].first+1)+"/"+tar);

							row = 0; //it's first path, must have find the next from begining
							pos.pop_back(); //reset the pos for next 

							if(tar[0] == 'M'){

								allpath.push_back(path);
								path.pop_back();

								//A vector vector<pair<int, string>> will carry the result from split_ function
								//You can using the pair by split[0].first, split[0].second
								split = split_(path[path.size()-1], "/", false); 

								//reset the row and tar
								row = split[0].first; //we don't have to +1 because we already
								tar = split[0].second;
								new_path = false;
							}
						}
						else{

							path.pop_back();
							if(!path.empty()) 
								path.pop_back();

							if(!path.empty() && (path.size() != 1))
							{
								split = split_(path[path.size()-1], "/", false); 

								//reset the row and tar
								row = split[0].first; //we don't have to +1 because we already
								tar = split[0].second;
								//cout<<row<<", "<<tar<<endl;
							}
						} //End of find_next
					}//End of While
				}
			}
			path.clear();
			row = 0;
		}
	}

	cout<<"Total Path is: "<<allpath.size()<<endl;

	for(size_t i = 0; i < allpath.size(); i++){ 
		for(size_t j = 0; j < allpath[i].size(); j++){  

			cout<<allpath[i][j]<<" ";
		}
		cout<<endl;
	}
}

void ProblemD::parsefunc(){ 

	/** \brief parsefunc() is to parse gate-level file.
	*    All the logic relation will store in (vector<vector<string>> parse;)
	*    All Initialized input will store in (vector<vector<int>> _allinvec;)
	*    All Initialized output will store in (vector<vector<int>> _alloutvec;)
	*/

	char *pch;
	bool start_parse = 0; //check when start to parse
	vector<string> str;
	vector<int> _int_sim; //For initial  vector<vector<int>> sim 
	char remove_c[] = ".,()";
	vector<int> _inout_vec;

	//Open File
	fstream fin;
	fin.open("gate-level.txt",ios::in);

	while(fin.getline(line,sizeof(line),'\n')){

		string strline(line);
		if(strline.empty()){ start_parse = true; }
		else if(start_parse){

			pch = strtok(line, " ");

			while (pch != NULL){

				if(strcmp(pch, ");") != 0 && strcmp(pch, "endmodule") != 0 && strcmp(pch, "(") != 0 ){	//We don't need such string

					string strpch(pch);
					for (unsigned int i = 0; i < strlen(remove_c); i++) //remove the char = ".,()"
						strpch.erase(remove( strpch.begin(), strpch.end(), remove_c[i] ), strpch.end());
					
					str.push_back(strpch);
				}

				if(strcmp(pch, ");") == 0){ //");" means newline

					//---sim init---//
					_int_sim.reserve(str.size()-2); //The vector won't reallocation
					for(size_t i = 0; i < str.size()-2; i++) 
						_int_sim.push_back(-1);
					sim.push_back(_int_sim);
					_int_sim.clear();

					parse.push_back(str);
					str.clear();
				}
				pch = strtok(NULL, " "); //Need this line to stop parsing
			}			 
		}else{

			//This region is for parsing input/output
			pch = strtok(line, " ");
			while (pch != NULL){

				//if pch == input then make input vector
				if(strcmp(pch, "input") == 0){

					pch = strtok(NULL, " ");
					_make_intout(pch, _inout_vec); //it will push a default in/out vector to all(in/out)vec
					_allinvec.push_back(_inout_vec);
					_inout_vec.clear();
				}else if(strcmp(pch, "output") == 0){

					pch = strtok(NULL, " ");
					_make_intout(pch, _inout_vec);
					_alloutvec.push_back(_inout_vec);
					_inout_vec.clear();
				}
				pch = strtok(NULL, " ");
			}
		}
	}

	//Erase the input/output AB/Y
	for(size_t i = 0; i < parse.size(); i++){ 
		for(size_t j = 0; j < parse[i].size(); j++){  
			if(j>1){ parse[i][j].erase(0,1); }
		}
	}
}

void ProblemD::_make_intout(char *pch, vector<int> &_inout_vec){ 

	/** \brief A parse function will call _make_inout while meet a input/output string.
	*	Then char *pch will contain the in/out range such as [1:0].
	*   _make_inout will initial the input/output vector all to '0'.
	*/

	char remove_c[] = "[]";
	vector<pair<int, string>> split;
	string strpch(pch);
	int sub;

	for(unsigned int i = 0; i < strlen(remove_c); i++) //remove the char = "[]"
		strpch.erase(remove( strpch.begin(), strpch.end(), remove_c[i] ), strpch.end());
	
	split = split_(strpch, ":", true); 

	sub = split[0].first - stoi(split[0].second);
	_inout_vec.reserve(sub+1);

	for(int i = 0; i <= sub; i++) 
		_inout_vec.emplace_back(0); //C++11
}

void ProblemD::Veri_simulator(){ 
}


 
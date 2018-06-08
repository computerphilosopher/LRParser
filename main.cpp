#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

enum COUNT {

	TERMINAL_COUNT = 6,
	NONTERMINAL_COUNT = 7,
	STATE_COUNT = 11
};

enum Terminal {
	ID = 11,
	PLUS,
	MUL,
	LEFT_PAREN,
	RIGHT_PAREN,
	END_OF_STRING
};

enum NonTerminal {
	E = 100,
	T,
	F
};

class Action {

private:
	string type; //shift or reduce;
	int num; // state or rule number

public:
	Action() {

	}
	
	Action(string type, int num) {
		
		try {
			this->type = type;
			if (type != "shift" && type != "reduce") {
				throw type;
			}
		}
		catch (string exception) {
			cout << "타입은 shift와  reduce중 하나여야 합니다" << endl;
		}
		this->num = num;
	}

	string GetType(){
		return type;
	}

	int GetState() {
		return num;
	}

	int GetRuleNumber() {
		GetState();
	}
};

const Action actionTable[STATE_COUNT][TERMINAL_COUNT] = {
	Action("shift", 5),
};

class Rule {

private:
public:
	Rule() {

	}

	static int getRHSCount(int ruleNumber){

		switch (ruleNumber) {
		case 1:
			return 3;
			break;
		case 2:
			return 1;
			break;
		case 3:
			return 3;
			break;
		case 4:
			return 1;
			break;
		case 5:
			return 3;
			break;
		case 6:
			return 2;
			break;
		}
	}

	static vector<int> getLHS(const vector<int> &rhs) {
 
	}
	
	static int getLHS(int rhs) {
 
		switch (rhs) {
		case T:
			return E;
			break;
		case F:
			return T;
			break;
		case ID:
			return F;
			break; 
		}
	}

};


class LRParser {
private:
	string input;
	stack<int> stack;

	int curr_input_ptr;

public:
	LRParser(string input) {
		this->input = input;

		curr_input_ptr = 0;
	}

	void Shift() {

	}

	void Reduce() {

	}

	int GetAction() {

	}

};


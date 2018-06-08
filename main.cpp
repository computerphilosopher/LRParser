#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

enum COUNT {
	TERMINAL_COUNT = 6,
	NONTERMINAL_COUNT = 7,
	STATE_COUNT = 12
};

enum STATE {
	ERROR = -1,
	ACCEPT = 12
};

enum Terminal {
	ID = 11,
	ADD,
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
		
			this->type = type;
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
	//0
	Action("shift", 5), Action("error", ERROR), Action("error", ERROR), Action("shift", 4), Action("error", ERROR), Action("error", ERROR),
	//1
	Action("error", ERROR), Action("shift", 6), Action("error", ERROR), Action("error", ERROR), Action("error", ERROR), Action("accept", ACCEPT),
	//2
	Action("error", ERROR), Action("reduce", 2), Action("shift", 7), Action("error", ERROR), Action("reduce", 2),  Action("reduce", 2),
	//3
	Action("error", ERROR), Action("reduce",4), Action("reduce", 4), Action("error", ERROR), Action("reduce", 4), Action("reduce", 4),
	//4
	Action("shift", 5), Action("error", ERROR), Action("error", ERROR), Action("shift", 4), Action("error", ERROR), Action("error", ERROR),
	//5
	Action("error", ERROR), Action("reduce", 6), Action("reduce",6), Action("error", ERROR), Action("reduce",6), Action("reduce", 6),
	//6
	Action("shift", 5), Action("error", ERROR), Action("error", ERROR), Action("shift", 4), Action("error", ERROR), Action("error", ERROR),
	//7
	Action("shift", 5), Action("error", ERROR), Action("error", ERROR), Action("shift", 4), Action("error", ERROR), Action("error", ERROR),
	//8
	Action("error", ERROR), Action("shift", 6), Action("error", ERROR), Action("error", ERROR), Action("shift", 11), Action("error", ERROR),
	//9
	Action("error", ERROR), Action("reduce", 1), Action("shift", 7), Action("error", ERROR), Action("reduce", 1), Action("reduce", 1),
	//10
	Action("error", ERROR), Action("reduce", 3), Action("reduce", 3), Action("error", ERROR), Action("reduce", 3), Action("reduce", 3),
	//11
	Action("error", ERROR), Action("reduce", 5), Action("reduce", 5), Action("error", ERROR), Action("reduce", 5), Action("reduce", 5),
};

class Rule {

private:
public:
	Rule() {

	}

	static int getRHSCount(Action action){

		int ruleNumber = action.GetRuleNumber();

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
			return 1;
			break;
		}
	}

	static int getLHS(Action action) {

		int ruleNumber = action.GetRuleNumber();

		switch (ruleNumber) {
		
		case 1:
			return E;
			break;
		case 2:
			return E;
			break;
		case 3:
			return T;
			break;
		case 4:
			return T;
			break;
		case 5:
			return F;
			break;
		case 6:
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


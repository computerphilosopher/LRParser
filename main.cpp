#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include "enums.h" 

using namespace std;
 
class Action {

private:
	string type; //shift or reduce;
	int num; // state or rule number

public:
	
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
		return GetState();
	}
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
	stack<int> parsingStack;

	Action actionTable[STATE_COUNT][TERMINAL_COUNT] = {
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

	const int gotoTable[STATE_COUNT][NONTERMINAL_COUNT] = {
		1, 2, 3,
		ERROR, ERROR, ERROR,
		ERROR, ERROR, ERROR,
		ERROR, ERROR, ERROR,
		8, 2, 3,
		ERROR, ERROR, ERROR,
		ERROR, 9, 3,
		ERROR, ERROR, 10,
		ERROR, ERROR, ERROR,
		ERROR, ERROR, ERROR,
		ERROR, ERROR, ERROR,
		ERROR, ERROR, ERROR,
	};

public:
	
	LRParser(string input) {
		this->input = input;
	}

	void Reduce(){

	}

	int GetSymbol(char c) {
		switch (c) {
		case 'a':
			return ID;
			break;
		case '+':
			return ADD;
			break;
		case '*':
			return MUL;
			break;
		case '(':
			return LEFT_PAREN;
			break;
		case ')':
			return RIGHT_PAREN;
			break;
		}
		
		return ERROR;
	}

	string PrintStack() {
		stack <int> temp;
		temp = parsingStack;

		string ret;

		while (!temp.empty()) {
			int k = temp.top();

			switch (k) {
			case ID:
				ret.append("a");
				break;
			case ADD:
				ret.append("+");
				break;
			case MUL:
				ret.append("*");
				break;
			case LEFT_PAREN:
				ret.append("(");
				break;
			case RIGHT_PAREN:
				ret.append("(");
				break;
			case E:
				ret.append("E");
				break;
			case T:
				ret.append("T");
				break;
			case F:
				ret.append("F");
				break;
			default:
				std::string out_string;
				std::stringstream ss;
				ss << k;
				ret.append(ss.str());
			}
			temp.pop();
		}

		string reverse;

		int j = 0;
		
		for (int i = ret.length()-1; i >= 0; i--) {	
			reverse.append(ret.substr(i, 1));
		}
		return reverse;
	}

	string PrintInput(int idx) {
		return input.substr(idx, input.length() - idx);
	}

	string PrintAction(Action action) {
		return action.GetType() + " ";
	}

	Action GetAction(int state, char c) {

		int symbol = GetSymbol(c);

		if (symbol == ERROR) {
			return Action("error", ERROR);
		}
		else {
			return actionTable[state][symbol-ID];
		}
	}

	void Run() {

		int i = 0;
		int cur_state = 0;

		int step = 0;

		parsingStack.push(cur_state);

		while (input[i] != '\0') {

			int symbol = GetSymbol(input[i]);
			Action action = GetAction(cur_state, input[i]);

			if (action.GetType() == "shift") {

				cur_state = action.GetState();

				parsingStack.push(symbol);
				parsingStack.push(action.GetState());

				i++;
			}

			else if (action.GetType() == "reduce") {

				int k = Rule::getRHSCount(action);

				for (int j = 0; j < k * 2; j++) {
					parsingStack.pop();
				}

				cur_state = parsingStack.top();
				int lhs = Rule::getLHS(action);
				parsingStack.push(lhs);

			//	cout << "goto[" << cur_state  << "][" << lhs-E <<"]"<< endl; 
				int new_state = gotoTable[cur_state][lhs-E];
				parsingStack.push(new_state);
				cur_state = new_state;
			}

			else if (action.GetType() == "accept") {
				cur_state = ACCEPT;
			}
			else if (action.GetType() == "error") {
				cur_state = ERROR;
			}
			else {
				cur_state = ERROR;
			}

			cout << PrintStack() <<"\t" << PrintInput(i) << "\t" << PrintAction(action) << "\t" << action.GetState() << endl;

			step++;
			if (cur_state == ERROR || cur_state == ACCEPT) {
				cout << cur_state << endl;
				break;
			}

		}
	}

};

int main() {

	string input = "a*a+a";
	LRParser parser(input);

	parser.Run();

	getchar();

}


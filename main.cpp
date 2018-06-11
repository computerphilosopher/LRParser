#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include "enums.h" 
#include "Class.h" 

using namespace std;
 
Action::Action(int type, int num) {
	this->type = type;
	this->num = num;
}

int Action::GetType() {
	return type;
}

string Action::GetTypeString() {
	switch (type) {
	case shift:
		return "shift";
		break;
	case reduce:
		return "shift";
		break;
	case accept:
		return "accept";
		break;
	case error:
		return "error";
		break;
	}
}

int Action::GetState() {
	return num;
}

int Action::GetRuleNumber() {
	return GetState();
}

Rule::Rule() {

}

int Rule::GetRHSCount(Action action) {

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

int Rule::GetLHS(Action action) {

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



LRParser::LRParser(string input) {
	this->input = input;
}


int LRParser::GetSymbol(char c) {
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
	case '\0':
		return END_OF_STRING;
	}

	return ERROR;
}

string LRParser::PrintStack() {
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
		case END_OF_STRING:
			ret.append("$");
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

	for (int i = ret.length() - 1; i >= 0; i--) {
		reverse.append(ret.substr(i, 1));
	}
	return reverse;
}

string LRParser::PrintInput(int idx) {
	return input.substr(idx, input.length() - idx);
}

string LRParser::PrintAction(Action action) {
	return action.GetType() + " ";
}

Action LRParser::GetAction(int state, char c) {

	int symbol = GetSymbol(c);

	if (symbol == ERROR) {
		return Action(error, ERROR);
	}
	else {
		return actionTable[state][symbol - ID];
	}
}

int LRParser::Shift(Action action, int symbol) {
	
	int cur_state = action.GetState();

	parsingStack.push(symbol);
	parsingStack.push(action.GetState());

	return cur_state;
 }

int LRParser::Reduce(Action action) {
	int k = Rule::GetRHSCount(action);
	int cur_state = 0;

	for (int j = 0; j < k * 2; j++) {
		parsingStack.pop();
	}

	cur_state = parsingStack.top();
	int lhs = Rule::GetLHS(action);
	parsingStack.push(lhs);

	int new_state = gotoTable[cur_state][lhs - E];
	parsingStack.push(new_state);
	cur_state = new_state;

	return cur_state;
}

string LRParser::Run() {

	int i = 0;
	int cur_state = 0;

	int step = 0;

	parsingStack.push(cur_state);

	string t = "\t";
	string result = "Stack" + t + "Input" + t + "Action\n";

	while (true) {

		int symbol = GetSymbol(input[i]);
		Action action = GetAction(cur_state, input[i]);

		int actionType = action.GetType();

		switch (actionType) {
		case shift:
			cur_state = Shift(action, symbol);
			i++;
			break;


		case reduce:
			cur_state = Reduce(action);
			break;
		

		case accept:
			cur_state = STATE::ACCEPT;
			break;
		case error:
			cur_state = ERROR;
			break;
		default:
			cur_state = ERROR;
			break;
		}

		char stateNum = action.GetState() + '0';
		result.append(PrintStack() + t + PrintInput(i) + t + action.GetTypeString() + " " + t + stateNum + "\n");
		step++;

		if (cur_state == ERROR) {
			result.append("error string");
			break;
		}

		if (cur_state == ACCEPT) {
			result.append("Accept!");
			break;
		}
	}

	return result;
}

FileWriter::FileWriter(string path, string target) {

	this->path = path;
	this->target = target;

	fout = new ofstream(path);

	if (!fout) {
		std::cout << "file no exists" << endl;
		return;
	}

}

FileWriter::FileWriter() {}

FileWriter::~FileWriter() {

	fout->close();
	free(fout);
}

void FileWriter::Write() {
	*fout << target;
}

int main() {

	int loopCount = 1;

	while (1) {
		string input;
		cout << "\ninput test string>>";

		cin >> input;

		if (input == "exit" || input == "quit") {
			break;
		}

		LRParser parser(input);

		string result = parser.Run();

		cout << result;

		FileWriter fileWriter("out.txt", result);

		fileWriter.Write();
		loopCount++;

	}

	getchar();
}


#pragma once

#include <fstream>
using namespace std;

class Action {

private:
	string type; //shift or reduce;
	int num; // state or rule number

public:

	Action(string type, int num);

	string GetType();

	int GetState();

	int GetRuleNumber();
};

class Rule {

private:
public:
	Rule();

	static int GetRHSCount(Action action);

	static int GetLHS(Action action);
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

	LRParser(string input);

	int Reduce(Action action);
	int Shift(Action action, int symbol);

	int GetSymbol(char c);

	string PrintStack();
	string PrintInput(int idx);

	string PrintAction(Action action);

	Action GetAction(int state, char c);

	void Run();

};


class FileWriter {

private:
	string target;
	string path;
	ofstream *fout;

public:
	FileWriter(string path, string target);
	FileWriter();

	void Write();
 
};
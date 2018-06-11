#pragma once
enum COUNT {
	TERMINAL_COUNT = 6,
	NONTERMINAL_COUNT = 3,
	STATE_COUNT = 12
};

enum STATE {
	ERROR = -1,
	ACCEPT = 12
};

enum Terminal {
	ID = 21,
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

enum ActionEnum{
	shift,
	reduce,
	error,
	accept

};


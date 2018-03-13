#pragma once

typedef char(* _printToChat)(char * args0);

struct GameFunctions {
	static _printToChat printToChat;
};
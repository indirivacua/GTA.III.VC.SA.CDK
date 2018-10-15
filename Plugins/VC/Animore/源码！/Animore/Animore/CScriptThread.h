#pragma once
#include <stdint.h>

//bool (__stdcall *RegOpcodes)(void *,int);

#pragma pack(push, 1)

/* 来自老外的IDA，其实我自己也做了一份而且在这个插件里还是够用的。。。。。。真的是真的啦！我那个做成易语言模块了喔！
00000000 next            dd ?                    ; offset
00000004 prev            dd ?                    ; offset
00000008 threadName      db 8 dup(?)
00000010 _ip             dd ?
00000014 stack           dd 6 dup(?)
0000002C _sp             dw ?
0000002E __pad           dw ?
00000030 local_vars      dd 18 dup(?)
00000078 IsActive        db ?
00000079 CondResult      db ?
0000007A IsMissionThread db ?
0000007B notSleeps       db ?
0000007C wakeTime        dd ?
00000080 IfOp            dw ?
00000082 notFlag         db ?
00000083 wbCheck         db ?
00000084 WastedOrBusted  db ?
00000085 missionFlag     db ?
00000086 __padding       dw ?
*/

class CScriptThread
{
public:
	CScriptThread *next;
	CScriptThread *prev;
	char threadName[8];
	int _ip;
	char stack[6];
	short _sp;
	short __pad;
	int local_vars[17];
	char IsActive;
	char CondResult;
	char IsMissionThread;
	char notSleeps;
	int wakeTime;
	short IfOp;
	char notFlag;
	char wbCheck;
	char WastedOrBusted;
	char missionFlag;
	short __padding;
};

#pragma pack(pop)

bool RegOpcode(void *func,int opcode)
{
	//MessageBox(NULL,"test","test",0);
	return ((bool (__stdcall *)(void *,int))((int)GetModuleHandle("cleo.asi") + 0x1B37))(func,opcode); //某RJY还是某ZYN来着: 卧槽！指针狂魔！
}

int getIntParam(CScriptThread *thread)
{
	((void (__thiscall *)(CScriptThread *,int,int))0x451010)(thread,((int)thread)+0x10,1);
	return *(int *)0x7D7438;
}

char * getTextParam(CScriptThread *thread)
{
	char textSize = *(char *)(thread->_ip+0x821281);
	char *ret = new char[textSize];
	strncpy(ret,(char *)(thread->_ip+0x821282),textSize);
	ret[textSize] = 0;
	thread->_ip += (textSize+2);
	return ret;
}
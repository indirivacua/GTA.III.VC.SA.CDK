// dllmain.cpp : 定义 DLL 应用程序的入口点。
// 被注释掉的地方都是我亲自写来捣乱你们看代码的！喵~~~~~~~~~~~~~~~！
#include "stdafx.h"
#include "CAnimGroup.h"
#include "CPatch.h"
#include "CScriptThread.h"
//#include "CAnimation.h"

//void (__thiscall *LoadAnimData)(CAnimation *,char * IFPName,int testmodel,char ** list,int count) = (void (__thiscall *)(CAnimation *,char *,int,char**,int))0x4012A0;
void *(__cdecl *RwStreamOpen)(int32_t, int32_t, const char *) = (void *(__cdecl *)(int32_t, int32_t, const char *))0x6459C0;
void (__cdecl *LoadIfp)(void *, int32_t, int32_t) = (void (__cdecl *)(void *, int32_t, int32_t))0x404A50;
void (__cdecl *RwStreamClose)(void *, int32_t) = (void (__cdecl *)(void *, int32_t))0x6458F0;
//void (__cdecl *gtalog)(char *,...) = (void(__cdecl *)(char *,...))0x401000;
void (__cdecl *PlayAnimation)(int,int,int,int) = (void (__cdecl *)(int,int,int,int))0x405640;
int (__thiscall *CPool_CPed__AtHandle)(void *,int) = (int (__thiscall *)(void *,int))0x451CB0;
//int32_t (__cdecl *getTestModel)(void);

void CustomIFPList();
void GetIFPData(char * IFPName);
void LoadNewIFP();
int __stdcall Opcode_0843(CScriptThread *thread);
int __stdcall Opcode_0844(CScriptThread *thread);

vector<char *> IFPList(0);
vector<CAnimGroup> AnimGroup(61);
//int AnimGroupNumber = 61;
//vector<CAnimation> animations(61);

void PatchAnimGroup()
{
	CustomIFPList();
	//这一部分是Clans提供的源码，嗯，最重要的一部分！
	CAnimGroup *DefaultPool = (CAnimGroup *)0x6857B0;
	for (int i = 0;i < 61;i++)
	{
		AnimGroup[i] = DefaultPool[i];
	}
	for (unsigned int i = 0;i < IFPList.size();i++)
		GetIFPData(IFPList[i]);
	//之所以先搞定AnimGroup再修改地址是因为对AnimGroup的修改会导致其本身地址的改变
	CPatch::SetPointer(0x40598A, &AnimGroup[0].groupName);
	CPatch::SetPointer(0x40545F, &AnimGroup[0].ifpName);
	CPatch::SetPointer(0x405531, &AnimGroup[0].ifpName);
	CPatch::SetPointer(0x4054C3, &AnimGroup[0].testModel);
	CPatch::SetPointer(0x405519, &AnimGroup[0].animsCount);
	CPatch::SetPointer(0x40551F, &AnimGroup[0].animsNamesList);
	CPatch::SetPointer(0x4054FF, &AnimGroup[0].animsIndeces);
	CPatch::SetPointer(0x405559, &AnimGroup[0].animsIndeces);

	CPatch::SetChar(0x4049C9, AnimGroup.size());
	CPatch::SetChar(0x4055CB, AnimGroup.size());
	CPatch::SetChar(0x40560C, AnimGroup.size());
	CPatch::SetInt(0x40561A, 8 + 0x14 * AnimGroup.size());
	CPatch::SetInt(0x48BD84, AnimGroup.size());
	CPatch::SetChar(0x48BE63, AnimGroup.size());
	//gtalog("CAnimGroup Hook Success! New Address:%d, Anim Group Count:%d",&AnimGroup[0].groupName,AnimGroup.size()); //卖萌的= =可以删
	LoadNewIFP();
}

/*
void PatchAnimations()
{
	int temp = (int)&animations[0].AnimGroupName;
	__asm
	{
		mov eax,temp;
		mov ds:[0x9B5F0C],eax
	}
}*/

/*
void animaddtest()
{
	char *tempAnimName = "sance";
	AnimIndece indece = { 0x200, 0x162 };
	char ifpPath[] = "anim\\sance.ifp";
	CAnimGroup temp = { "sance", "sance", 1, 1, &tempAnimName, &indece };
	AnimGroup.push_back(temp);
	AnimGroupNumber++;
	void *RwStream = RwStreamOpen(2, 1, ifpPath);
	LoadIfp(RwStream, 1, 0);
	RwStreamClose(RwStream, 0);
	CAnimation temp2 = {0,0,0,0,0};
	animations.push_back(temp2);
	PatchAnimations();
	int *mem1 = (int *)0x13AC004;
	mem1 = (int *)*mem1;
	mem1 = (int *)(*mem1 + 0xC);
	mem1 = (int *)*mem1;
	getTestModel = (int32_t (__cdecl *)(void))mem1;
		(int32_t (__cdecl *)(void))
		((int *)(((int *)((int *)0x92D4CC))+0xC));
	LoadAnimData(&animations[61],
		AnimGroup[61].ifpName,
		getTestModel(),
		AnimGroup[61].
		animsNamesList,
		AnimGroup[61].animsCount);
}
*/
__declspec(naked) void Hook_405604()
{
	__asm
	{
		mov eax, 6458F0h;
		call eax;
		pop ecx;
		pop ecx;
	}
	PatchAnimGroup();
	__asm
	{
		mov eax, 40560Bh;
		jmp eax;
	}
}
/*__declspec(naked) void Hook_40562D()
{
	PatchAnimations();
	//animaddtest();
	__asm
	{
		mov eax,0x405632
		jmp eax
	}
}*/

/*
4055C7 cmp [esp+0x14],61
4055CC

4049C7 cmp ebp,61&jl 0x4049B1
4049CC

48BD83 mov ebp,61
48BD88

48BE61 cmp esi,61&jl 48BE40
48BE66


__declspec(naked) void Patch_4055C7()
{
	__asm
	{
		mov eax,AnimGroupNumber
		cmp [esp+0x14],eax
		mov eax,0x4055CC
		jmp eax
	}
}
__declspec(naked) void Patch_4049C7()
{
	__asm
	{
		add esi,0x14
		cmp AnimGroupNumber,ebp
		jl jll
		mov eax, 0x4049CC
		jmp eax
jll:
		mov eax, 0x4049B1
		jmp eax
	}
}
__declspec(naked) void Patch_48BD83()
{
	__asm
	{
		mov ebp,AnimGroupNumber
		mov eax,0x48BD88
		jmp eax
	}
}
__declspec(naked) void Patch_48BE61()
{
	__asm
	{
		cmp esi,AnimGroupNumber
		jl jll
		mov eax, 0x48BE66
		jmp eax
jll:
		mov eax, 0x48BE40
		jmp eax
	}
}
__declspec(naked) void Patch_405BBF()
{
	__asm
	{
		mov eax,0x405C90
		call eax
		mov eax,0
		mov ds:[0x9B5F0C],eax
		mov eax,0x405BDF
		jmp eax
	}
}*/

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//MessageBox(NULL,"1","Animore",0); 猜猜这些MessageBox当时是干嘛的？因为我当时不知道ul_reason_for_call是干嘛的=w=
		CPatch::RedirectJump(0x405604,Hook_405604);
/*
		我把CAnimation也hook了，不过看起来没啥用= =所以注释掉了
		CPatch::RedirectJump(0x40562D,Hook_40562D);
		CPatch::RedirectJump(0x4049C7,Patch_4049C7);
		CPatch::RedirectJump(0x4055C7,Patch_4055C7);
		CPatch::RedirectJump(0x48BD83,Patch_48BD83);
		CPatch::RedirectJump(0x48BE61,Patch_48BE61);
		CPatch::RedirectJump(0x405BBF,Patch_405BBF);
*/
		RegOpcode(Opcode_0843,0x843);
		RegOpcode(Opcode_0844,0x844);
		break;
	case DLL_THREAD_ATTACH:
		//MessageBox(NULL,"2","Animore",0);
		break;
	case DLL_THREAD_DETACH:
		//MessageBox(NULL,"3","Animore",0);
		break;
	case DLL_PROCESS_DETACH:
		//MessageBox(NULL,"4","Animore",0);
		break;
	default:break;
	}
	return TRUE;
}

void CustomIFPList() //获取CLEO\CLEO_ANIM目录下的IFP文件列表
{
	WIN32_FIND_DATA FileData;
	HANDLE hFind;
	char * CurPath = new char[512];
	GetCurrentDirectory(512,CurPath);
	char * IFPath = "\\CLEO\\CLEO_ANIM\\*.ifp";
	strcat(CurPath,IFPath);
	//gtalog("\n%s\n",CurPath);
	hFind = FindFirstFile(CurPath,&FileData);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		IFPList.push_back(new char[sizeof(FileData.cFileName)]);
		strcpy(IFPList[IFPList.size()-1],FileData.cFileName);
		while(FindNextFile(hFind, &FileData) != 0)
		{
			IFPList.push_back(new char[sizeof(FileData.cFileName)]);
			strcpy(IFPList[IFPList.size()-1],FileData.cFileName);
		}
		/*for (unsigned int i = 0;i < IFPList.size();i++)
		{
			gtalog("\\CLEO\\CLEO_ANIM\\%s",IFPList[i]);
		}
		gtalog("%d %d",&IFPList[0],IFPList.size());*/
	}
	FindClose(hFind);
}

void GetIFPData(char *IFPName)  //从IFP文件中获取AnimGroup名以及Animation的名字，用winhex一点一点找的呢
{
	CAnimGroup temp;
	temp.testModel = 1;
	vector<char *> *templist = new vector<char *>(0);
	vector<AnimIndece> *tempindex = new vector<AnimIndece>(0);
	temp.ifpName = new char[strlen(IFPName)-4];
	strncpy(temp.ifpName,IFPName,strlen(IFPName)-4);
	temp.ifpName[strlen(IFPName)-4] = 0;
	char * CurPath = new char[512];
	GetCurrentDirectory(512,CurPath);
	char * IFPath = "\\CLEO\\CLEO_ANIM\\";
	strcat(CurPath,IFPath);
	strcat(CurPath,IFPName);
	FILE *ifp;
	if(ifp = fopen(CurPath,"rb"))
	{
		fseek(ifp,0xC,SEEK_SET);
		int strsize;
		//std::cout << "1" << std::endl;
		fread(&strsize,4,1,ifp);
		fseek(ifp,4,SEEK_CUR);
		temp.groupName = new char[strsize - 4];
		fgets(temp.groupName,strsize - 3,ifp);
		if(strsize % 4 != 0)
			fseek(ifp,4-(strsize % 4),SEEK_CUR);
		int i = 0;
		char *NAME = new char[5];
		NAME[4] = 0;
		//std::cout << "2" << std::endl;
		fread(NAME,4,1,ifp);
		while(!(feof(ifp)))
		{
			if(strcmp(NAME,"NAME") != 0)
				break;
			//std::cout << "3" << std::endl;
			fread(&strsize,4,1,ifp);
			//std::cout << strsize << std::endl;
			char * tempchar = new char[strsize];
			fgets(tempchar,strsize + 1,ifp);
			templist->push_back(tempchar);
			AnimIndece temind = {i,2};
			tempindex->push_back(temind);
			//std::cout << "Animation" << i << " Name:" << ifpgroupname << std::endl;
			if(strsize % 4 != 0)
				fseek(ifp,4-(strsize % 4),SEEK_CUR);
			fseek(ifp,4,SEEK_CUR);
			//std::cout << "4" << std::endl;
			fread(&strsize,4,1,ifp);
			fseek(ifp,strsize,SEEK_CUR);
			i++;
			//std::cout << "5" << std::endl;
			fread(NAME,4,1,ifp);
		}
		fclose(ifp);
		temp.animsCount=i;
		temp.animsNamesList=&((*templist)[0]);
		temp.animsIndeces=&((*tempindex)[0]);
		AnimGroup.push_back(temp);
	}
	delete[]CurPath;
}

void LoadNewIFP() //啊啊，加载也不是我的，喵。。。。。。最重要的都不是我的，喵呜。。。。。。
{
	for (unsigned int i=0;i < IFPList.size();i++)
	{
		char * tempchr = new char[sizeof(IFPList[i])+16];
		strcpy(tempchr,"CLEO\\CLEO_ANIM\\");
		strcat(tempchr,IFPList[i]);
		//gtalog(tempchr);
		void *RwStream = RwStreamOpen(2, 1, tempchr);
		LoadIfp(RwStream,1,0);
		RwStreamClose(RwStream,0);
		delete[]tempchr;
	}
}

int __stdcall Opcode_0843(CScriptThread *thread) //特喵的居然是stdcall。。。。。。CLEO作者我恨你！
{
	//0843=4,actor %1d% play_animation %2h% ifp_name %3h% framedelta %4d%
	int pedHandle = getIntParam(thread);
	int pedrwobject = *(int *)(CPool_CPed__AtHandle((void *)(*(int *)0x97F2AC),pedHandle) + 0x4C);
	char *anim = getTextParam(thread);
	char *ifp = getTextParam(thread);
	int framedelta = getIntParam(thread); //我知道不是int是float，反正这样省事还节省代码= =
	int groupID,animID;
	bool FUUUUUUUUUUUUUUUUCK = false;
	for(unsigned int i=0;i<AnimGroup.size();i++)
	{
		if(strnicmp(AnimGroup[i].ifpName,ifp,strlen(ifp)) == 0)
		{
			for(int j=0;j<AnimGroup[i].animsCount;j++)
			{
				if(strnicmp(AnimGroup[i].animsNamesList[j],anim,strlen(anim)) == 0)
				{
					groupID = i;
					animID = j;
					FUUUUUUUUUUUUUUUUCK = true;
					delete[]anim;
					delete[]ifp;
					break;
				}
			}
			if(FUUUUUUUUUUUUUUUUCK) //意识到这里还有个break时作者暴走了所以请不要搜这个单词的意思反正你也搜不到=w=
				break;
		}
	}
	if(!FUUUUUUUUUUUUUUUUCK)
	{
		return 0;
	}
	animID = AnimGroup[groupID].animsIndeces[animID].ID;
	PlayAnimation(pedrwobject,groupID,animID,framedelta);
	return 0;
}

int __stdcall Opcode_0844(CScriptThread *thread) //临时编的，想着或许。。。。。。没用
{
	int pedHandle = getIntParam(thread);
	int pedrwobject = *(int *)(CPool_CPed__AtHandle((void *)(*(int *)0x97F2AC),pedHandle) + 0x4C);
	int animID = getIntParam(thread);
	int groupID = getIntParam(thread);
	int framedelta = getIntParam(thread);
	PlayAnimation(pedrwobject,groupID,animID,framedelta);
	return 0;
}
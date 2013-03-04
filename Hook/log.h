#pragma once
#include <tchar.h>

#include <iostream>
#include <fstream>
#include <string>
#include <xstring>
using namespace std;
//============Log====================
#define DEBUG
#ifdef DEBUG
#define LOGFILE(text)		\
							{ofstream log;\
							log.open("D:\\log.txt", ios::app);\
							log << (text);\
							log.close();}
#define DXLOG(text)		\
							{ofstream log;\
							log.open("D:\\log.txt", ios::app);\
							log << (text);\
							log.close();}
#else
#define LOGFILE(text)
#endif
//===========Log========================

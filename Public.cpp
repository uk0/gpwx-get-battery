#include "stdafx.h"
#include "Public.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
// windows core
#include <io.h>
#include <fcntl.h>
#include <cstdio> //C++
// for readability
void Debug_TRACE(CString strInBuf)
{
	CString strBuf;

	strBuf += "[";
	strBuf += strInBuf;
	strBuf += "]";
	TRACE(strBuf + "\n");
}

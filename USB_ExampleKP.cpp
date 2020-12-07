/** 
* \file USB_Example.cpp
* This example allows to connect to the target through USB Bootloader interface and execute some operations to the internal STM32 Flash memory. \n
*		- Connect to the device via USB interface.
*		- File programming + verification step.
*		- Read 64 bytes from 0x08000000.
*		- Option bytes programming : BOR level.
*		- Display option bytes.
*.
* Go to the source code : \ref USB_Bootloader
\example USB_Bootloader
* This example allows to connect to the target through USB Bootloader interface and execute some operations to the internal STM32 Flash memory. \n
*		- Connect to the device via USB interface.
*		- File programming + verification step.
*		- Read 64 bytes from 0x08000000.
*		- Option bytes programming : BOR level.
*		- Display option bytes.
*  \code{.cpp}
**/


#include <USB_Example.h>
#include <DisplayManager.h>
#include <CubeProgrammer_API.h>
#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <limits>
using namespace std; // ustawiam wykorzystanie przestrzeni nazwy std, ¿eby nie trzeba by³o pisaæ ci¹gle np. std::cout, std::cin, std::endl

#pragma warning(suppress : 4996)

static wchar_t* charToWChar(const char* text)
{
	const size_t size = strlen(text) + 1;
	wchar_t* wText = new wchar_t[size];
	mbstowcs(wText, text, size);
	return wText;
}

int USB_Example(void) {
	

	logMessage(Title, "\n SEZO FIRMWARE UPDATER:\n");

	
	generalInf* genInfo;
	dfuDeviceInfo* dfuList;
	DIR* di;
	char* ptr1, * ptr2;
	int retn;
	struct dirent* dir;
	int n=1;
	char local[100]="SEZO_FW/"; // OK
	char* next_token;
	char wybor[50][50];

	int numer = 0;
	int choosen = 0;
	do
	{
		logMessage(Info, "\n Avaliable firmware versions:\n");
		di = opendir("SEZO_FW/."); //specify the directory name
		if (di)
		{
			while ((dir = readdir(di)) != NULL)
			{
				ptr1 = strtok_s(dir->d_name, ".", &next_token);
				ptr2 = strtok_s(NULL, ".", &next_token);
				//	logMessage(Title, "%s \t", ptr1);
				if (ptr2 != NULL)
				{
					retn = strcmp(ptr2, "hex");
					if (retn == 0)
					{
						strcpy(wybor[n], ptr1);
						//strncpy(names[n], ptr1,  10);
						logMessage(Title, "%d. %s.hex \n", n, ptr1);
						n++;
					}
				}
			}
			closedir(di);
		}

	

	do{
		logMessage(Title, "\nChoose firmware version (1-%d):\n", n-1);
		cin >> numer;
	} while (numer < 1 || numer>n-1);
		n = 1;

	//	n = 1; //w razie odwolania
		char userAnswer[10];
		

		int success = 0;
		do
		{
			logMessage(GreenInfo, "\nType 'YES' if you are sure to update with %s.hex file \n", wybor[numer]);
			logMessage(Error, "Type 'NO' to choose again \nType 'QUIT' to close program \n");
			std::cin >> userAnswer;

			if (strcmp(userAnswer, "YES") == 0) { success = 1; choosen = 1; }
			if (strcmp(userAnswer, "yes") == 0) { success = 1; choosen = 1;}
			if (strcmp(userAnswer, "no") == 0) { success = 1; choosen = 0; }
			if (strcmp(userAnswer, "NO") == 0) { success = 1; choosen = 0; }
			if (strcmp(userAnswer, "QUIT") == 0) { return 0; }	if (strcmp(userAnswer, "quit") == 0) { return 0; }

		} while (success == 0);
	} while (choosen == 0);

	/* Download File + verification */
#ifdef _WIN32
	const wchar_t* filePath = L"data.hex";
#else
	const wchar_t* filePath = L"../api/test file/data.hex";
#endif
	//const char* loc = "/SEZO_FW";
	
	strcat(local, wybor[numer]); //dodanie lokalizacji
	strcat(local, ".hex"); //dodanie .hex
	//logMessage("%s", local);
	filePath = charToWChar(local);
//	wprintf(filePath);

	//logMessage("%s", filePath);




	int getDfuListNb = getDfuDeviceList(&dfuList);

	if (getDfuListNb == 0)
	{
		logMessage(Error, "No USB DFU available\n");
		Sleep(10000);
		return 0;
	}
	else {
		logMessage(Title, "\n------------- USB DFU List --------------\n");
		for (int i = 0; i < getDfuListNb; i++)
		{
			logMessage(Normal, "USB Port %d \n",i);
			logMessage(Info, "	USB index   : %s \n", dfuList[i].usbIndex);
			logMessage(Info, "	USB SN      : %s \n", dfuList[i].serialNumber);
			logMessage(Info, "	DFU version : 0x%02X ", dfuList[i].dfuVersion);
		}
		logMessage(Title, "\n-----------------------------------------\n\n");
	}
	disconnect();
	/* Target connect, choose the adequate USB port by indicating its index that is already mentioned in USB DFU List above */
	int usbConnectFlag = connectDfuBootloader(dfuList[0].usbIndex); 
	if (usbConnectFlag != 0) 
	{
		
		logMessage(GreenInfo, "\n--- Device NOT Connected --- \n");
		Sleep(5000);
		disconnect();
		return 0;
	}
	else {
	
		logMessage(GreenInfo, "\n--- Device Connected --- \n");
		Sleep(5000);
	}

	/* Display device informations */
	genInfo = getDeviceGeneralInf();
	logMessage(Normal, "\nDevice name : %s ", genInfo->name);
	logMessage(Normal, "\nDevice type : %s ", genInfo->type);
	logMessage(Normal, "\nDevice CPU  : %s \n", genInfo->cpu);
	wprintf(filePath);
	Sleep(5000);
		//strcpy(filePath, wybor[numer]);
	unsigned int isVerify = 1; //add verification step	
	unsigned int isSkipErase = 0; // no skip erase
	int downloadFileFlag = downloadFile(filePath, 0x08000000, isSkipErase, isVerify, L"");
	if (downloadFileFlag != 0)
	{
		logMessage(GreenInfo, "\n--- Update Fail --- \n");
		disconnect();
		Sleep(5000);
		return 0;
	}


	logMessage(GreenInfo, "\n--- UpdateOk --- \n");
	Sleep(5000);
	/* Process successfully Done */
	disconnect();
	deleteInterfaceList();
	return 1;
}


/** \endcode **/

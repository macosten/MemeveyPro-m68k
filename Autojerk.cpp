#include "Autojerk.h"
#include "Error.h"

Markov _markov;



void OpenAutojerkSourceFile(Point originPoint){

	StandardFileReply reply; //A struct that will contain our result.
	SFTypeList autojerkTypeList = {'TEXT','    ','    ','    '}; //The list of appropriate types we're okay with opening. These, I think, are the 4-letter creator codes?
	
	short fileID;
	
	StandardGetFile(NULL, 1, autojerkTypeList, &reply);
	
	if (!reply.sfGood) {
		//Str255 errorDescription = 
		PikaAlertWithText("\pThere was an error opening that file. Perhaps another application may have locked it?");
	}
	else {
		//Read no more than 75% of the memory available to the application into memory.
		//...though this won't take into account any changes made to the memory size made by the user.
		
		OSErr err;
		ControlRef control;
		
		long count = 0.4 * programSize;
		
		_markov.setRefNumber(reply.sfFile.vRefNum);
		
		
		//Attempt to open the file's data fork.
		err = FSpOpenDF(&reply.sfFile, fsRdPerm, &reply.sfFile.vRefNum);
		if (err != noErr) PikaAlertWithText("\pFSpOpenDF failed in OpenAutojerkSourceFile, so nothing can be read.");

		//Set our file position to the start of the file.
		SetFPos(reply.sfFile.vRefNum, fsFromStart, 0);
		

		char * readBuffer = (char *)calloc(count+1, sizeof(char));
		if (readBuffer == NULL) PikaAlertWithText("\pThe read buffer could not be allocated. You or the application may be out of memory.");
		
		
		err = FSRead(_markov.getRefNumber(), &count, readBuffer); //Read bytes into readBuffer EOF or count bytes have been read, whichever is less.
		if (err != noErr && err != eofErr) PikaAlertWithText("\pAn error (other than reaching the end of the file) occurred while reading the file.");
		
		_markov.create(readBuffer, 3, 100);
		
		
		
		
		free(readBuffer);
	}
	
} 
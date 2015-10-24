
#ifndef __MAGICAL_BOOK_FILE_MANAGER_H__
#define __MAGICAL_BOOK_FILE_MANAGER_H__

#include "CatGameLib.h"

#define DTCNT  ((sizeof stage)/(sizeof(stage_inf)))

namespace MagicalBook 
{

class FileManager
{
public:
	static FileManager* readMapFile(const char* fileName);

	std::vector<unsigned char>& getMapData(void);

	void fileOutput(void);

	int getSizeValue(void);
	int getBGNumber(void);
	int getBGMNumber(void);

	int writeFile();

private:


	void loadFile(const char* fileName);

	std::vector<unsigned char> mapData;

	FileManager();
	~FileManager();
	
};

}

#endif // __MAGICAL_BOOK_FILE_MANAGER_H__

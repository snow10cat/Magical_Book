
#ifndef __MAGICAL_BOOK_FILE_MANAGER_H__
#define __MAGICAL_BOOK_FILE_MANAGER_H__

#define BOOST_FILESYSTEM_VERSION 3

#include "CatGameLib.h"
#include "ResourceManager.h"
#include <boost/filesystem.hpp>

#define DTCNT  ((sizeof stage)/(sizeof(stage_inf)))

namespace MagicalBook 
{

class StageFile;

class FileManager
{
public:
	static FileManager* getInstance(void)
	{
		static FileManager* instance = nullptr;
		if(!instance) {instance = new FileManager();}
		return instance;
	}
	FileManager(const FileManager&) = delete;
	const FileManager& operator=(const FileManager&) = delete;
	~FileManager();

	int getFileCount(void);
	const char* getFileName(int number);

	StageFile* loadFile(const char* fileName);
	void saveFile(StageFile* file);

private:
	int stageFileCount;
	boost::filesystem::path currentPath;

	std::vector<std::string> fileNameArray;
	FileManager();
};

class StageFile
{
public:
	enum FileMode
	{
		Load,
		Save,
	};

	static StageFile* create(void);
	~StageFile();

	CatGameLib::LibVector2	getStageSize(void);
	ResourceManager::BgName getBGNumber(void);
	ResourceManager::BgmNum getMusicNumber(void);
	std::vector<unsigned char>& getStageData(void);

	void setStageSize(CatGameLib::LibVector2 vector);
	void setBGNumber(ResourceManager::BgName bgName);
	void setMusicNumber(ResourceManager::BgmNum musicNum);
	void setStageData(std::vector<unsigned char>& stageData);

private:
	FileMode mode;
	CatGameLib::LibVector2  stageSize;
	ResourceManager::BgName bgNumber;
	ResourceManager::BgmNum musicNumber;
	std::vector<unsigned char> stageData;

	StageFile();
};

}

#endif // __MAGICAL_BOOK_FILE_MANAGER_H__


#include <sstream>
#include <boost/foreach.hpp>
#include <boost/filesystem/fstream.hpp>
#include "FileManager.h"

#define FILE_NAME "Stage"

using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;
using namespace boost::filesystem;

FileManager::FileManager() : stageFileCount( 0),
							 currentPath( boost::filesystem::current_path())
{
	stageFileCount = getFileCount();
}

int FileManager::getFileCount(void)
{
	stageFileCount = 0;
	fileNameArray.clear();

	path dir( currentPath.string() + "/ResourceFile/Stage/");
	

	BOOST_FOREACH(const path& p, make_pair( directory_iterator( dir), directory_iterator()))
	{
		if (!is_directory(p))
		{
			string fileName = p.filename().string();
			fileNameArray.push_back( fileName);
			fileName.erase( 0, fileName.rfind( '.', fileName.size()));
			if( fileName == ".stage")
			{
				stageFileCount++;
			}
		}
	}

	return stageFileCount;
}


const char* FileManager::getFileName( int number)
{
	return fileNameArray[number].c_str();
}


StageFile* FileManager::loadFile(const char* fileName)
{
	StageFile* file = StageFile::create();

	string filePass = currentPath.string() + "/ResourceFile/Stage/" + fileName;
	boost::filesystem::ifstream inStream( filePass);
	if( inStream.fail())
	{
		return nullptr;
	}

	string buf;
	vector<unsigned char> vec;
	for( int i = 0; getline( inStream, buf); i++)
	{
		istringstream str( buf);
		string temp;
		int x;
		int y;
		switch( i)
		{
		case 0: // ステージサイズ
			getline( str, temp, ',');
			x = atoi( temp.c_str());
			getline( str, temp);
			y = atoi( temp.c_str());
			file -> setStageSize( LibVector2( x, y));
			break;

		case 1: // 背景
			getline( str, temp);
			file -> setBGNumber( (ResourceManager::BgName)atoi( temp.c_str()));
			break;

		case 2: // BGM
			getline( str, temp);
			file -> setMusicNumber( (ResourceManager::BgmNum)atoi( temp.c_str()));
			break;
		}
		if( i >= 3)
		{
			while( getline( str, temp, ','))
			{
				vec.push_back( atoi( temp.c_str()));
			}
		}

	}
	file -> setStageData( vec);

	return file;
}


void FileManager::saveFile(StageFile* file)
{
	string fileName = currentPath.string() + "/ResourceFile/Stage/" + FILE_NAME + to_string( fileNameArray.size() + 1) + ".stage";

	boost::filesystem::ofstream outStream( fileName);
	outStream << file -> getStageSize().x << "," << file -> getStageSize().y << "\n";
	outStream << file -> getBGNumber() << "\n";
	outStream << file -> getMusicNumber() << "\n";

	for( int y = 0; y < file -> getStageSize().y; y++)
	{
		for( int x = 0; x < file -> getStageSize().x; x++)
		{
			outStream << file -> getStageData()[y * file -> getStageSize().x + x] << ",";
		}
		outStream << "\n";
	}

	outStream.close();
}




StageFile* StageFile::create( void)
{
	StageFile* file = new (nothrow)StageFile();

	if( !file)
	{
		return nullptr;
	}

	return file;
}


StageFile::StageFile() : stageSize( LibVector2( 0, 0)),
						 bgNumber( ResourceManager::BgName::BG_Castle),
						 musicNumber( ResourceManager::BgmNum::BGM_1),
						 stageData()
{
}

StageFile::~StageFile()
{
}


LibVector2	StageFile::getStageSize(void)
{
	return stageSize;
}


ResourceManager::BgName StageFile::getBGNumber(void)
{
	return bgNumber;
}


ResourceManager::BgmNum StageFile::getMusicNumber(void)
{
	return musicNumber;
}


vector<unsigned char>& StageFile::getStageData(void)
{
	return stageData;
}


void StageFile::setStageSize(CatGameLib::LibVector2 vector)
{
	stageSize = vector;
}


void StageFile::setBGNumber(ResourceManager::BgName bgName)
{
	bgNumber = bgName;
}


void StageFile::setMusicNumber(ResourceManager::BgmNum musicNum)
{
	musicNumber = musicNum;
}


void StageFile::setStageData(std::vector<unsigned char>& stageData)
{
	this -> stageData = stageData;
}

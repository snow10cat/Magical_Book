#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

#include <stdio.h>
#include <stdlib.h>
#include"FileManager.h"


using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;


void fileOutput()
{
}


bool GetContents(const string& filename, vector<vector<string>>& table,
				 const char delimiter = ',')
{
	//�t�@�C�����J��
	fstream filestream(filename);
	if(!filestream.is_open())
	{
		//�t�@�C�����J���Ȃ������ꍇ
		return false;
	}

	//�t�@�C���ǂݍ���
	while(!filestream.eof())
	{
		//1�s�ǂݍ���
		string buffer;
		filestream >> buffer;

		//�t�@�C������ǂݍ���1�s�̕��������؂蕶���ŕ����ă��X�g�ɒǉ�����
		vector<string> record;					//1�s���̕�����̃��X�g
		istringstream streambuffer(buffer);		//������X�g���[��
		string token;							//1�Z�����̕�����

		while(getline(streambuffer, token, delimiter))
		{
			//1�Z�����̕���������X�g�ɒǉ�����
			record.push_back(token);
		}

		//1�s���̕�������o�͈����̃��X�g�ɒǉ�����
		table.push_back(record);
	}
	return true;
}


static FileManager* readMapFile(const char* fileName)
{
	bool status = false;			//���\�b�h�̃X�e�[�^�X
	string filename = "test.csv";	//�t�@�C����
	vector<vector<string>> table;	//�ǂݍ���CSV�t�@�C���̓��e

	//CSV�t�@�C���̓��e���擾����
	status = GetContents(filename, table);
	if(!status)
	{
		//�擾�Ɏ��s�����ꍇ�̓G���[�I������
		return false;
	}

	//�m�F�̂��߂ɃR���\�[���ɓ��e���o�͂���
	for(int row = 0; row < table.size(); row++)
	{
		vector<string> record;	//1�s���̓��e
		record = table[row];	//1�s���ǂݍ���

		//1�Z�����ǂݍ���ŃR���\�[���ɏo�͂���
		for(int column = 0; column < record.size(); column++)
		{
			cout << record[column];
			//�����̗�łȂ��ꍇ�̓J���}���o�͂���
			if(column < record.size() -1)
			{
				cout << ",";
			}
		}
		cout << endl;
	}
	return 0;
}
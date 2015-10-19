#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

bool GetContents(const string& filename, vector<vector<string>>& table,
				 const char delimiter = ',')
{
	//ファイルを開く
	fstream filestream(filename);
	if(!filestream.is_open())
	{
		//ファイルが開けなかった場合
		return false;
	}

	//ファイル読み込み
	while(!filestream.eof())
	{
		//1行読み込む
		string buffer;
		filestream >> buffer;

		//ファイルから読み込んだ1行の文字列を区切り文字で分けてリストに追加する
		vector<string> record;					//1行分の文字列のリスト
		istringstream streambuffer(buffer);		//文字列ストリーム
		string token;							//1セル分の文字列

		while(getline(streambuffer, token, delimiter))
		{
			//1セル分の文字列をリストに追加する
			record.push_back(token);
		}

		//1行分の文字列を出力引数のリストに追加する
		table.push_back(record);
	}
	return true;
}


//読み込み

int CsvRead(int argc, const char * argv[])
{
	bool status = false;			//メソッドのステータス
	string filename = "test.csv";	//ファイル名
	vector<vector<string>> table;	//読み込んだCSVファイルの内容

	//CSVファイルの内容を取得する
	status = GetContents(filename, table);
	if(!status)
	{
		//取得に失敗した場合はエラー終了する
		return -1;
	}

	//確認のためにコンソールに内容を出力する
	for(int row = 0; row < table.size(); row++)
	{
		vector<string> record;	//1行分の内容
		record = table[row];	//1行分読み込む

		//1セルずつ読み込んでコンソールに出力する
		for(int column = 0; column < record.size(); column++)
		{
			cout << record[column];
			//末尾の列でない場合はカンマを出力する
			if(column < record.size() -1)
			{
				cout << ",";
			}
		}
		cout << endl;
	}
	return 0;
}
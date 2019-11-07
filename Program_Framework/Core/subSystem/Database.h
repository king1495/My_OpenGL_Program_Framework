#pragma once
#include "Singleton.h"

class Database final : public Singleton<Database>
{
public:
	Database()
	{
		LoadDB();
	}
	virtual ~Database()
	{
		SaveDB();
	}

	void SaveDB()
	{
		BinaryWriter bw;
		bw.Open(L"./config.dat");

		bw.Close();
	}
	void LoadDB()
	{
		BinaryReader br;
		if (br.Open(L"./config.dat")) {

			br.Close();
		}
		else {
			cout << "Load Fail" << endl;
		}
	}

public:
};
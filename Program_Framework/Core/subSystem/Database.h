#pragma once
#include "ISubSystem.h"

class Database final : public ISubSystem
{
public:
	static Database& GetInstance() {
		static Database* _instance = new Database();
		return *_instance;
	}

private:
	Database()
		: calPackPath(L"")
		, whitePath(L""), darkPath(L"")
		, left_port(1), right_port(2)
		, lidarOffset(50)
		, maskX(0, 0)
		, maskY(0, 0)
		, frameRate(30), exposureTime(30)
		, spectralBin(0), spatialBin(0)
		, arduino_port(3)
	{
		LoadDB();
	}
	virtual ~Database()
	{
		SaveDB();
	}

public:

	void SaveDB()
	{
		BinaryWriter bw;
		bw.Open(L"./config.dat");

		bw.WString(calPackPath);
		bw.WString(whitePath);
		bw.WString(darkPath);
		bw.Int(left_port);
		bw.Int(right_port);
		bw.Double(lidarOffset);
		bw.Vector2(maskX);
		bw.Vector2(maskY);
		bw.Double(exposureTime);
		bw.Double(frameRate);
		bw.Int(spectralBin);
		bw.Int(spatialBin);
		bw.Int(arduino_port);

		bw.Close();
	}
	void LoadDB()
	{
		BinaryReader br;
		if (br.Open(L"./config.dat")) {

			calPackPath = br.WString();
			whitePath = br.WString();
			darkPath = br.WString();
			left_port = br.Int();
			right_port = br.Int();
			lidarOffset = br.Double();
			maskX = br.Vector2();
			maskY = br.Vector2();
			exposureTime = br.Double();
			frameRate = br.Double();
			spectralBin = br.Int();
			spatialBin = br.Int();
			arduino_port = br.Int();

			br.Close();
		}
		else {
			cout << "Load Fail" << endl;
		}
	}

public:
	wstring calPackPath;
	wstring whitePath;
	wstring darkPath;

	int left_port, right_port;
	double lidarOffset;
	vec2 maskX;
	vec2 maskY;

	double exposureTime;
	double frameRate;
	int spatialBin;
	int spectralBin;

	int arduino_port;
};

#define _DB Database::GetInstance()
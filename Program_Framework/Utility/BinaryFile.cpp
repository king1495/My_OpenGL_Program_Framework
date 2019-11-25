#include "stdafx.h"
#include "BinaryFile.h"

bool BinaryWriter::Open(IN const wstring & filePath, IN const UINT & openOption)
{
	assert(filePath.length() > 0);
	fileHandle = CreateFile
	(
		filePath.c_str()
		, GENERIC_WRITE
		, 0
		, nullptr
		, openOption
		, FILE_ATTRIBUTE_NORMAL
		, nullptr
	);

	bool bChecked = fileHandle != INVALID_HANDLE_VALUE;
	return bChecked;
	//assert(bChecked);
}

void BinaryWriter::Close()
{
	if (fileHandle != nullptr)
	{
		CloseHandle(fileHandle);
		fileHandle = nullptr;
	}
}

void BinaryWriter::Bool(IN const bool & data)
{
	WriteFile(fileHandle, &data, sizeof(bool), &size, nullptr);
}

void BinaryWriter::Word(IN const WORD & data)
{
	WriteFile(fileHandle, &data, sizeof(WORD), &size, nullptr);
}

void BinaryWriter::Int(IN const int & data)
{
	WriteFile(fileHandle, &data, sizeof(int), &size, nullptr);
}

void BinaryWriter::UInt(IN const UINT & data)
{
	WriteFile(fileHandle, &data, sizeof(UINT), &size, nullptr);
}

void BinaryWriter::Float(IN const float & data)
{
	WriteFile(fileHandle, &data, sizeof(float), &size, nullptr);
}

void BinaryWriter::Double(IN const double & data)
{
	WriteFile(fileHandle, &data, sizeof(double), &size, nullptr);
}

void BinaryWriter::Vector2(IN const vec2 & data)
{
	WriteFile(fileHandle, &data, sizeof(vec2), &size, nullptr);
}

void BinaryWriter::Vector3(IN const vec3 & data)
{
	WriteFile(fileHandle, &data, sizeof(vec3), &size, nullptr);
}

void BinaryWriter::Vector4(IN const vec4 & data)
{
	WriteFile(fileHandle, &data, sizeof(vec4), &size, nullptr);
}

void BinaryWriter::Matrix4(IN const mat4 & data)
{
	WriteFile(fileHandle, &data, sizeof(mat4), &size, nullptr);
}

void BinaryWriter::String(IN const string & data)
{
	UInt(data.size());

	const char* str = data.c_str();
	WriteFile(fileHandle, str, data.size(), &size, nullptr);
}

void BinaryWriter::WString(IN const wstring & data)
{
	UInt(data.size());

	const wchar_t* str = data.c_str();
	WriteFile(fileHandle, str, data.size() * 2, &size, nullptr);
}

void BinaryWriter::Byte(IN void * data, IN const UINT & dataSize)
{
	WriteFile(fileHandle, data, dataSize, &size, nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool BinaryReader::Open(IN const wstring& filePath)
{
	assert(filePath.length() > 0);
	fileHandle = CreateFile
	(
		filePath.c_str()
		, GENERIC_READ
		, FILE_SHARE_READ
		, nullptr
		, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL
		, nullptr
	);

	bool isChecked = fileHandle != INVALID_HANDLE_VALUE;
	return isChecked;
	//assert(isChecked);
}

void BinaryReader::Close()
{
	if (fileHandle != nullptr)
	{
		CloseHandle(fileHandle);
		fileHandle = nullptr;
	}
}

const bool BinaryReader::Bool()
{
	bool temp = false;
	ReadFile(fileHandle, &temp, sizeof(bool), &size, nullptr);

	return temp;
}

const WORD BinaryReader::Word()
{
	WORD temp = 0;
	ReadFile(fileHandle, &temp, sizeof(WORD), &size, nullptr);

	return temp;
}

const int BinaryReader::Int()
{
	int temp = 0;
	ReadFile(fileHandle, &temp, sizeof(int), &size, nullptr);

	return temp;
}

const UINT BinaryReader::UInt()
{
	UINT temp = 0;
	ReadFile(fileHandle, &temp, sizeof(UINT), &size, nullptr);

	return temp;
}

const float BinaryReader::Float()
{
	float temp = 0.0f;
	ReadFile(fileHandle, &temp, sizeof(float), &size, nullptr);

	return temp;
}

const double BinaryReader::Double()
{
	double temp = 0.0f;
	ReadFile(fileHandle, &temp, sizeof(double), &size, nullptr);

	return temp;
}

const vec2 BinaryReader::Vector2()
{
	float x = Float();
	float y = Float();

	return vec2(x, y);
}

const vec3 BinaryReader::Vector3()
{
	float x = Float();
	float y = Float();
	float z = Float();

	return vec3(x, y, z);
}

const vec4 BinaryReader::Vector4()
{
	float x = Float();
	float y = Float();
	float z = Float();
	float w = Float();

	return vec4(x, y, z, w);
}

const mat4 BinaryReader::Matrix4()
{
	mat4 matrix;

	matrix[0][0] = Float(); matrix[0][1] = Float(); matrix[0][2] = Float(); matrix[0][3] = Float();
	matrix[1][0] = Float(); matrix[1][1] = Float(); matrix[1][2] = Float(); matrix[1][3] = Float();
	matrix[2][0] = Float(); matrix[2][1] = Float(); matrix[2][2] = Float(); matrix[2][3] = Float();
	matrix[3][0] = Float(); matrix[3][1] = Float(); matrix[3][2] = Float(); matrix[3][3] = Float();

	return mat4();
}

const string BinaryReader::String()
{
	UINT size = UInt();

	char* temp = new char[size + 1];
	ReadFile(fileHandle, temp, sizeof(char) * size, &this->size, NULL); //데이터 읽기
	temp[size] = '\0';

	return temp;
}

const wstring BinaryReader::WString()
{
	UINT size = UInt();

	wchar_t* temp = new wchar_t[size + 1];
	ReadFile(fileHandle, temp, sizeof(wchar_t) * size, &this->size, NULL); //데이터 읽기
	temp[size] = L'\0';

	return temp;
}

void BinaryReader::Byte(void ** data, const UINT & dataSize)
{
	ReadFile(fileHandle, *data, dataSize, &size, NULL);
}
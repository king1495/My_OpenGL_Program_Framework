#pragma once

class BinaryWriter
{
public:
	BinaryWriter() : fileHandle(nullptr), size(0) {}
	virtual ~BinaryWriter() {}

	bool Open(IN const wstring & filePath, IN const UINT & openOption = CREATE_ALWAYS);
	void Close();

	void Bool(IN const bool& data);
	void Word(IN const WORD& data);
	void Int(IN const int& data);
	void UInt(IN const UINT& data);
	void Float(IN const float& data);
	void Double(IN const double& data);
	void Vector2(IN const vec2& data);
	void Vector3(IN const vec3& data);
	void Vector4(IN const vec4& data);
	void Matrix4(IN const mat4& data);

	template<typename T>
	void Write(IN const T& data) {
		//fileHandle.write((char*)data, sizeof(T));
		WriteFile(fileHandle, &data, sizeof(T), &size, nullptr);
	}

	void String(IN const string& data);
	void WString(IN const wstring& data);
	void Byte(IN void* data, IN const UINT& dataSize);

	bool isOpen() { return fileHandle; }

protected:
	HANDLE fileHandle;
	DWORD size;
};

/////////////////////////////////////////////////////////////////////////////////////////

class BinaryReader
{
public:
	BinaryReader() : fileHandle(nullptr), size(0) {}
	virtual ~BinaryReader() {}

	bool Open(IN const wstring& filePath);
	void Close();

	const bool Bool();
	const WORD Word();
	const int Int();
	const UINT UInt();
	const float Float();
	const double Double();
	const vec2 Vector2();
	const vec3 Vector3();
	const vec4 Vector4();
	const mat4 Matrix4();
	const string String();
	const wstring WString();
	void Byte(IN void** data, IN const UINT& dataSize);

	bool isOpen() { return fileHandle != nullptr; }

protected:
	HANDLE fileHandle;
	DWORD size;
};
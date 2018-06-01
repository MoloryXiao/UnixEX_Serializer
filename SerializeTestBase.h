#pragma once

class SerializeTestBase{
public:
	int objectType;
	virtual bool Serialize(const char* pFilePath)=0;
	virtual bool Deserialize(const char* pFilePath)=0;
	virtual bool Serialize(int fd)=0;
	virtual bool Deserialize(int fd)=0;
	virtual void print()=0;
	virtual int GetType() = 0;
};
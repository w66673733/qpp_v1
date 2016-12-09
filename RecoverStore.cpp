#include"RecoverStore.h"

CRecoverStore::CRecoverStore()
{

}
string CRecoverStore::getFileName(string path)
{
    int firstSlash = path.find_last_of("\\") + 1;
    return path.substr(firstSlash);
}

FILE* CRecoverStore::getFileByKey(string key)
{
    FILE* fp = NULL;
    fp = fileMap[fileName];
    return fp;
}

bool CRecoverStore::fileIsExist(string path)
{
    string fileName = getFileName(path);
    FILE* fp = getFileByKey(fileName);
    if(fp)
    {
        return true;
    }else
    {
        return false;
    }
}

FILE* CRecoverStore::getFile(string path,const char* openType)
{
    string fileName = getFileName(path);
    FILE* fp = getFileByKey(fileName);
    if(fp)
    {
        return fp;
    }else
    {
        return fopen(path.c_str(), openType);
    }
}

int CRecoverStore::closeFile(string path)
{
    string fileName = getFileName(path);
    FILE* fp = getFileByKey(fileName);
    if(fp)
    {
        fclose(fp);
        fileMap.erase(fileName);
        return 0;
    }
    return -1;
}

CRecoverStore::closeFile(FILE* fp)
{
    map<string, FILE*>::iterator it;
    for(it = fileMap.begin(); it != fileMap.end(); ++it)
    {
        if(it->second == fp)
        {
            fclose(fp);
            fileMap.erase(it);
            return 0;
        }
    }
    retrun -1;
}

CRecoverStore::~CRecoverStore()
{

}

#ifndef _RECOVERSTORE_H_
#define _RECOVERSTORE_H_

#include<map>
#include<string>

using namespace std;

class CRecoverStore
{
    public:
        CRecoverStore();
        string getFileName(string path);
        FILE* getFileByKey(string key);
        bool fileIsExist(string path);
        FILE* getFile(string path, const char* openType);
        int closeFile(string path);
        int closeFile(FILE* fp);
        ~CRecoverStore(); 
    private:
        map<string, FILE*>  fileMap;   
}
#endif

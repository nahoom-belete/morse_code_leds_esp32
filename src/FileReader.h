#include <Arduino.h>
using namespace std;

class FileReader 
{
    public:
        FileReader(String fname);
        String readFile();

    private:
        String fileName;
}; 
#include <vector>
#include <string>
#include <dirent.h>

void listdir(std::string& path, std::vector<std::string>& files) {
    DIR *dir = opendir(path.c_str());
    if(!dir) {
        return;
    }
    struct dirent* f;
    while((f = readdir(dir)) != 0) {
        if(strcmp(".", f->d_name) != 0 && strcmp("..", f->d_name) != 0) {
            files.push_back(std::string(f->d_name));
        }
    }
    return;
}
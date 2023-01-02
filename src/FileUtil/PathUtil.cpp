#include "PathUtil.h"

std::string GetNameFromPath(std::string path) {
    int slashcount = path.find_last_of('/');
    if(slashcount == -1) return path;
    return path.substr(slashcount+1);
}

std::string GetPathFromPath(std::string path) {
    int slashcount = path.find_last_of('/');
    if(slashcount == -1) return "";
    return path.substr(0, slashcount+1);
}
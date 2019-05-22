#ifndef OBJREADER_H
#define OBJREADER_H

#include <string>
#include "geometry.h"


class OBJReader
{
public:
    static Geometry readObjFile(std::string path);
};

#endif // OBJREADER_H

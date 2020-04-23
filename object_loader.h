//
// Created by neptune on 22-04-20.
//

#include <fstream>
#include <iostream>
#include <vector>
#include "common_method.h"
#include "ray.h"

#ifndef BASIC_RAY_TRACER_OBJECT_LOADER_H
#define BASIC_RAY_TRACER_OBJECT_LOADER_H

vector<vec3> vertices;
vector<vec3> normals;
vector<unsigned int> indices;

void parse(const char* filepath){
    FILE* fp;
    float x,y,z;
    float fx, fy, fz, ignore;
    int c1, c2;
    float minY = infinity, minZ = infinity;
    float maxY = -infinity, maxZ = -infinity;

    fp = fopen(filepath, "rb");

    if(fp == NULL) {
        std::cout << "Error loading file" << std::endl;
        exit(-1);
    }

    while(!feof(fp)) {
        c1  = fgetc(fp);
        while(!(c1 == 'v' || c1 == 'f')){
            c1 = fgetc(fp);
            if(feof(fp))
                break;
        }
        c2 = fgetc(fp);

        if((c1 == 'v') && (c2 == ' ')){
            fscanf(fp, "%f %f %f", &x, &y, &z);
            vertices.push_back(vec3(x, y, z));
            if (y < minY) minY = y;
            if (z < minZ) minZ = z;
            if (y > maxY) maxY = y;
            if (z > maxZ) maxZ = z;
        } else if ((c1 == 'v') && (c2 == 'n')) {
            fscanf(fp, "%f %f %f", &x, &y, &z);
            normals.push_back(unit_vec(vec3(x, y, z)));
        }
        else if (c1 == 'f')
        {
            fscanf(fp, "%f//%f %f//%f %f//%f", &fx, &ignore, &fy, &ignore, &fz, &ignore);
            indices.push_back(fx - 1);
            indices.push_back(fy - 1);
            indices.push_back(fz - 1);
        }
    }

    fclose(fp); // Finished parsing
}


#endif //BASIC_RAY_TRACER_OBJECT_LOADER_H

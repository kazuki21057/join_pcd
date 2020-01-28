/**
 * @file join_pcd.cpp
 * @author your name (you@domain.com)
 * @brief -if: input file names, -id: directory which has input files, -of: output file name (default: merged_pointcloud), -od: output file directory (default: -io)
 * @version 0.1
 * @date 2020-01-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <vector>
#include <string>
#include "file_controller.h"
#include "merge_pcd.h"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cerr << "set correct arguments" << std::endl;
        return 1;
    }

    std::cout << "start to search files" << std::endl;
    FileController fc(argc, argv);
    std::vector<std::string> file_names;
    if (!fc.getPcdFile(file_names))
    {
        std::cout << "failed!! try again!" << std::endl;
        return 1;
    }

    std::cout << "start to merge clouds" << std::endl;
    MergePcd mp(file_names);
    pcl::PointCloud<pcl::PointXYZI> cloud_merged;
    mp.mergeCloud(cloud_merged);
    mp.savePcdFile(fc.getOutputFilePath(), cloud_merged);

    std::cout << "complete!" << std::endl;

    return 0;
}





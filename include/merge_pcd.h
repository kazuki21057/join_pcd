#ifndef MERGE_PCD_H
#define MERGE_PCD_H

#include <iostream>
#include <string>
#include <vector>
/* PCL */
#include <pcl/io/pcd_io.h>
#include <pcl/io/io.h>
#include <pcl/point_types.h>


class MergePcd
{
private:
    std::vector<std::string> file_names_;
    std::vector<pcl::PointCloud<pcl::PointXYZI>> clouds_;
public:
    MergePcd (const std::vector<std::string>& c_file_names);
    void mergeCloud (pcl::PointCloud<pcl::PointXYZI>& cloud_merged);
    void savePcdFile (const std::string& c_output_file_path, const pcl::PointCloud<pcl::PointXYZI>& c_cloud_output);
};

#endif //MERGE_PCD_H
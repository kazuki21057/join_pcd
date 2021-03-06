#include "merge_pcd.h"

using PclPoint = pcl::PointCloud<pcl::PointXYZI>;

MergePcd::MergePcd(const std::vector<std::string>& c_file_names)
{
    clouds_.resize(c_file_names.size());
    /* PCDファイルを読込 */
    for (int i=0; i<c_file_names.size(); ++i)
    {
        std::printf("load %s\n", c_file_names[i].c_str());
        if (pcl::io::loadPCDFile(c_file_names[i], clouds_[i]) == -1)
        {
            std::printf("shutdown...\n");
            exit(0);
        }
    }
}

void MergePcd::mergeCloud (pcl::PointCloud<pcl::PointXYZI>& cloud_merged)
{
    for (auto& cloud: clouds_)
    {
        if (&cloud - &clouds_[0] == 0)
            cloud_merged = cloud;
        cloud_merged += cloud;
    }
    return;
}

void MergePcd::savePcdFile (const std::string& c_output_file_path, const pcl::PointCloud<pcl::PointXYZI>& c_cloud_output)
{
    try
    {
        pcl::io::savePCDFileBinary(c_output_file_path, c_cloud_output);        
    }
    catch(const pcl::IOException& e)
    {
        std::cerr << e.what() << '\n';
        exit(0);
    }    
    std::printf("save merged clouds to %s\n", c_output_file_path.c_str());
    return;
}

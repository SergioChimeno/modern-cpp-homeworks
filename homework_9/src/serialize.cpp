#include "serialize.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void ipb::serialization::Serialize(const cv::Mat& m, const std::string& filename){

    fs::path filePath = filename;
    if(filePath.extension() != ".bin"){
        // Extension must be ".bin"
        filePath.replace_extension(".bin");
    }

    std::ofstream outFile(filePath, std::ios_base::out | std::ios_base::binary);

    int cols = m.cols;
    int rows = m.rows;
    int type = m.type();
    int nBytes = 0;
    uchar* data = nullptr;

    if(m.isContinuous()){
        data = m.data;
    }else{
        data = m.clone().data;
        std::cout << __func__ << ": The matrix is not continuous\n";
    }

    nBytes = m.total()*m.elemSize()*m.elemSize1();

    outFile.write(reinterpret_cast<char*>(&type),sizeof(type));
    outFile.write(reinterpret_cast<char*>(&rows),sizeof(rows));
    outFile.write(reinterpret_cast<char*>(&cols),sizeof(cols));
    outFile.write(reinterpret_cast<char*>(&nBytes),sizeof(nBytes));
    outFile.write(reinterpret_cast<char*>(data),nBytes);

    std::cout <<__func__<< ": rows:" << rows << ", cols:" << cols << ", channels:" << m.elemSize() 
        << ", element size:" << m.elemSize1() << ", nBytes:" << m.elemSize1() << ", out file:" << filePath << std::endl;
}

cv::Mat ipb::serialization::Deserialize(const std::string& filename){
    
    fs::path filePath = filename;
    if(filePath.extension() != ".bin"){
        // Extension must be ".bin"
        filePath.replace_extension(".bin");
    }

    std::ifstream fileIn(filePath, std::ios_base::in | std::ios_base::binary);

    if(!fileIn){
        return cv::Mat();
    }

    int cols = 0;
    int rows = 0;
    int type = 0;
    int nBytes = 0;

    fileIn.read(reinterpret_cast<char*>(&type),sizeof(type));
    fileIn.read(reinterpret_cast<char*>(&rows),sizeof(rows));
    fileIn.read(reinterpret_cast<char*>(&cols),sizeof(cols));
    fileIn.read(reinterpret_cast<char*>(&nBytes),sizeof(nBytes));

    uchar* data = new uchar[nBytes];
    fileIn.read(reinterpret_cast<char*>(data),nBytes);

    cv::Mat m = cv::Mat(rows,cols,type,data);

    std::cout <<__func__<< ": rows:" << rows << ", cols:" << cols << ", channels:" << m.elemSize() 
        << ", element size:" << m.elemSize1() << ", nBytes:" << m.elemSize1() <<", Type:" << m.type() << ", input file:" << filePath << std::endl;

    return m;
}
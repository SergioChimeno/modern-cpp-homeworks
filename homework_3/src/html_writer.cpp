#include "html_writer.hpp"
#include <iostream>
#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;

void html_writer::OpenDocument(){
    cout << "<!DOCTYPE html> " << endl;
    cout << "<html> " << endl;
}

void html_writer::CloseDocument(){
    cout << "</html> " << endl;
}

void html_writer::AddCSSStyle(const std::string& stylesheet){
    cout << "\t<head>" << endl;
    cout << "\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"" << stylesheet << "\" />" << endl;
    cout << "\t</head>" << endl;
}

void html_writer::AddTitle(const std::string& title){
    cout << "\t<title>" << title << "</title>" << endl;
}

void html_writer::OpenBody(){
    cout << "\t<body>" << endl;
}

void html_writer::CloseBody(){
    cout << "\t</body>" << endl;
}

void html_writer::OpenRow(){
    cout << "\t\t<div class=\"row\">" << endl;
}

void html_writer::CloseRow(){
    cout << "\t\t</div>" << endl;
}

bool isFileFormatSupported(const std::string& img_path){
    std::size_t lastDotPos = img_path.find_last_of('.');
    if (lastDotPos == std::string::npos){
        return false;
    }

    std::string extension = img_path.substr(lastDotPos);
    if ( extension != ".png" && extension != ".jpg"){
        return false;
    }

    return true;
}

std::string getFileName(const std::string& img_path){

    std::string fileName;

    std::size_t startNamePos = img_path.find_last_of('/');
    if (startNamePos == std::string::npos){
        fileName = img_path;
    }else{
        fileName = img_path.substr(startNamePos+1);
    }

    return fileName;
}

void html_writer::AddImage(const std::string& img_path, float score, bool highlight){
    
    if( !isFileFormatSupported(img_path) ){
        cerr << "Error: File Format not supported!!!" << endl;
    }

    std::string fileName = getFileName(img_path);

    //Print Image
    cout << "\t\t\t<div class=\"column\"";
    if(highlight){
        cout << "style=\"border: 5px solid green;\"";
    } 
    cout << ">" << endl;

    cout << "\t\t\t\t<h2>" << fileName << "</h2>" << endl;
    cout << "\t\t\t\t<img src=\"" << img_path <<"\"/>" << endl;
    cout << "\t\t\t\t<p>score = " << std::setprecision(2) << std::fixed << score << "</p>" << endl;

    cout << "\t\t\t</div>" << endl;
}

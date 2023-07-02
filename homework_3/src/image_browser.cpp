#include "html_writer.hpp"
#include "image_browser.hpp"

using std::get;

void image_browser::AddFullRow(const ImageRow& row, bool first_row){

    html_writer::OpenRow();

    bool firstRowImage = true;
    for(const ScoredImage& image:row){
        html_writer::AddImage(get<0>(image),get<1>(image),first_row && firstRowImage);
        if(firstRowImage) firstRowImage = false;
    }

    html_writer::CloseRow();
}

void image_browser::CreateImageBrowser(const std::string& title, const std::string& stylesheet,
                        const std::vector<ImageRow>& rows){

    html_writer::OpenDocument();

    html_writer::AddTitle(title);
    html_writer::AddCSSStyle(stylesheet);

    html_writer::OpenBody();
    
    bool firstRow = true;
    for (const ImageRow& row:rows){
        AddFullRow(row,firstRow);
        if(firstRow) firstRow = false;
    }

    html_writer::CloseBody();
    html_writer::CloseDocument();

}
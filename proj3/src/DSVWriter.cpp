#include "DSVWriter.h"
#include <iostream>



struct CDSVWriter::SImplementation {
    std::shared_ptr<CDataSink> Sink; 
    char Delimiter; 
    bool QuoteAll; 

   
    SImplementation(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall): Sink(sink), Delimiter(delimiter), QuoteAll(quoteall) {}


    bool WriteRow(const std::vector<std::string>& row) {
       
        if (!Sink) return false; 
      
        if (row.empty()) {
            return Sink->Put('\n');
        }
 
        for (size_t i = 0; i < row.size(); ++i) {
            bool quote = QuoteAll || row[i].find(Delimiter) != std::string::npos ||
                              row[i].find('"') != std::string::npos || row[i].find('\n') != std::string::npos;
            
            if (quote) {
                
                if (!Sink->Put('"')) return false; 
      
                for (char c : row[i]) {
                    if (c == '"') {
                        if (!Sink->Put('"') || !Sink->Put('"')) return false;
                    } else {
                     
                        if (!Sink->Put(c)) return false;
                    }
                }
   
                if (!Sink->Put('"')) return false; 
        
            } else {
                for (char c : row[i]) {
                    if (!Sink->Put(c)) return false;
                }
            }
          
            if (i < row.size() - 1) {
                if (!Sink->Put(Delimiter)) return false; 
            }
        }
     
        return Sink->Put('\n'); 
    }
};

CDSVWriter::CDSVWriter(std::shared_ptr<CDataSink> sink, char delimiter, bool quoteall)
    : DImplementation(std::make_unique<SImplementation>(sink, delimiter, quoteall)) {}

CDSVWriter::~CDSVWriter() = default;


bool CDSVWriter::WriteRow(const std::vector<std::string>& row) {
    return DImplementation->WriteRow(row);
}
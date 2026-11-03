#pragma once
#include <istream>
#include <string>
#include <vector>

// reads csv record, returns false when file has no more records (movies)
inline bool readRecord(std::istream& in, std::vector<std::string>& fields) {
    fields.clear();
    std::string field;

    bool inQuotes = false, readAnything = false;
    char c;

    while (in.get(c)) {
        readAnything = true;
        if (inQuotes) {
            if (c == '"') {

                // turns "" into literal quotations
                if (in.peek() == '"') {
                    field += '"';
                    in.get();
                }

                // closes quote
                else
                    inQuotes = false;
            }

            // keeps commas and newlines as text
            else {
                field += c;
            }
        }

        else {
            
            // "" opens quote
            if (c == '"')
                inQuotes = true;
            
            // comma outside quotes indicates end of field
            else if (c == ',') {
                fields.push_back(std::move(field));
                field.clear();
            }

            // newline outside quotes indicates end of record
            else if (c == '\n') {
                fields.push_back(std::move(field));
                return true;
            }

            // extra precaution for Windows-style newlines
            else if (c == '\r') {
                fields.push_back(std::move(field));
                return true;
            }

            // any other character is part of the field/regular data
            else {
                field += c;
            }
    }
}

    // checks for newline in last line of the file
    if (readAnything) {
        fields.push_back(std::move(field));
        return true;
    }

    return false;
}

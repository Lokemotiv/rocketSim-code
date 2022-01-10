#ifndef databaseCode_hpp
#define databaseCode_hpp

#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>

std::String toS(long double x){
    return std::to_string(x);
}

void ErrorMsg(std::string ErrorMsg, std::string ErrorFungtion, std::vector<std::string> ErrorFungtionInput)
{
    std::string error = "Database: Error: " + ErrorMsg + ". Error was thrown at " + ErrorFungtion + "(";
    for (int i = 0; i < ErrorFungtionInput.size() - 1; i++)
        error += "\"" + ErrorFungtionInput[i] + "\", ";
    error += "\"" + ErrorFungtionInput[ErrorFungtionInput.size() - 1] + "\");\n";
    std::cout << error;
}

class dataBaseReadFile
{
public:
    int nextColumnNumber = 0;
    std::unordered_map<std::string, int> mapOfColumns = {};
    std::ifstream file;
    std::string filename;

    dataBaseReadFile(std::string filename)
    {
        dataBaseReadFile::filename = filename;
        file.open(filename);
        bool firstLine = true;
        std::string text, splitElement = "|", token;
        size_t pos;
        getline(file, text);
        while ((pos = text.find(splitElement)) != std::string::npos)
        {
            token = text.substr(0, pos);
            text.erase(0, pos + splitElement.length());
            mapOfColumns[token] = nextColumnNumber;
            nextColumnNumber++;
        }
        mapOfColumns[text] = nextColumnNumber;
        file.close();
    }

    std::vector<long double> getAllDataFromColumnLongDouble(std::string columnName)
    {
        if (mapOfColumns[columnName] == 0)
        {
            ErrorMsg("Not a column name", "getAllDataFromColumnLongDouble", {columnName});
            return {};
        }
        std::vector<long double> x;
        file.open(filename);
        long long int j = 0;
        std::string text, splitElement = "|", token;
        size_t pos;
        bool firstline = true;
        int l = 1;
        while (getline(file, text))
        {
            if (!firstline)
            {
                while (j <= mapOfColumns[columnName])
                {
                    pos = text.find(splitElement);
                    token = text.substr(0, pos);
                    text.erase(0, pos + splitElement.length());
                    j++;
                }
                for (char i : token)
                {
                    if (i != '0' && i != '1' && i != '2' && i != '3' && i != '4' && i != '5' && i != '6' && i != '7' && i != '8' && i != '9' && i != '.' && i != '-')
                    {
                        ErrorMsg("The column has a caracter at line: " + l, "getAllDataFromColumnLongDouble", {columnName});
                        return {};
                    }
                }
                x.push_back(std::stold(token));
            }
            firstline = false;
            l++;
        }
        file.close();
        return x;
    }

    std::vector<std::string> getAllDataFromColumnString(std::string columnName)
    {
        if (mapOfColumns[columnName] == 0)
        {
            ErrorMsg("Not a column name", "getAllDataFromColumnLongDouble", {columnName});
            return {};
        }
        std::vector<std::string> x;
        file.open(filename);
        long long int j = 0;
        std::string text, splitElement = "|", token;
        size_t pos;
        bool firstline = true;
        while (getline(file, text))
        {
            if (!firstline)
            {
                while (j <= mapOfColumns[columnName])
                {
                    pos = text.find(splitElement);
                    token = text.substr(0, pos);
                    text.erase(0, pos + splitElement.length());
                    j++;
                }
                x.push_back(token);
            }
            firstline = false;
        }
        file.close();
        return x;
    }

    /*std::vector<std::vector<std::string>> getAllRowsWhereColumnIsEqualeToAValue(std::string columnName, std::string value){
        if (mapOfColumns[columnName] == 0)
        {
            ErrorMsg("Not a column name", "getAllRowsWhereColumnIsEqualeToAValue", {columnName, value});
            return {{}};
        }
        file.open(filename);
        std::vector<std::vector<std::string>> x = {};
        std::string text;
        bool firstline = true;
        int j = 0;
        while (getline(file, text))
        {
            if (!firstline)
            {
                while (j <= mapOfColumns[columnName])
                {
                    pos = text.find(splitElement);
                    token = text.substr(0, pos);
                    text.erase(0, pos + splitElement.length());
                    j++;
                }
                x.push_back(token);
            }
            firstline = false;
        }

    }*/
};

class dataBaseWriteFile
{
public:
    std::unordered_map<std::string, int> mapOfColumns = {};
    int nextColumnNumber = 0;
    std::ofstream file;
    bool addedData = false;
    std::string filename;
    dataBaseWriteFile(std::string filename)
    {
        dataBaseWriteFile::filename = filename;
        file.open(filename);
    }

    void closeFile()
    {
        file.close();
    }

    void addColumn(std::string columnName)
    {
        if (addedData)
        {
            ErrorMsg("Can't add column data has been added", "addColumn", {columnName});
            return;
        }
        mapOfColumns[columnName] = nextColumnNumber;
        nextColumnNumber++;
        if (nextColumnNumber == 1)
        {
            file << columnName;
            return;
        }
        file << "|" << columnName;
    }

    void addColumnArray(std::vector<std::string> columnNames)
    {
        if (addedData)
        {
            ErrorMsg("Can't add column data has been added", "addColumnArray", columnNames);
            return;
        }
        for (std::string columnName : columnNames)
        {
            mapOfColumns[columnName] = nextColumnNumber;
            nextColumnNumber++;
            if (nextColumnNumber == 1)
            {
                file << columnName;
            }
            else
            {
                file << "|" << columnName;
            }
        }
    }

    void addData(std::vector<std::string> data)
    {
        file << std::endl;
        addedData = true;
        if (mapOfColumns.size() > data.size())
        {
            ErrorMsg("More columns then data, Column count: " + toS(mapOfColumns.size()) + " Data count: " + toS(data.size()), "addData", data);
            return;
        }
        if (mapOfColumns.size() < data.size())
        {
            ErrorMsg("Less columns then data, Column count: " + toS(mapOfColumns.size()) + " Data count: " + toS(data.size()), "addData", data);
            return;
        }
        bool first = true;
        for (std::string i : data)
        {
            if (!first)
                file << "|";
            file << i;
            first = false;
        }
    }
};

#endif

#ifndef _CONFIG_PARSER_H_
#define _CONFIG_PARSER_H_

#include <string>
#include <map>
 
class ConfigValue
{
public:
    ConfigValue(std::string & value);
 
    std::string asString(const std::string & defValue = "") const;
    int32_t asInt32(int32_t defValue = 0) const;
    int64_t asInt64(int64_t defValue = 0) const;
private:
    std::string & m_value;
};
 
class ConfigKey
{
public:
    ConfigKey(std::map<std::string, std::string> & keys);
 
    ConfigValue operator[](const std::string& key_name);
private:
    std::map<std::string, std::string> & m_keys;
};
 
class ConfigParser
{
public:
    ConfigParser(std::string filename);
 
    std::map<std::string, std::string> & get_section(const std::string& section_name);
 
    ConfigKey operator[](const std::string& section_name);
 
    void dump(FILE* log_file);
private:
    std::string read_header(const std::string& line);
 
    void read_configuration(const std::string& line, const std::string& header);
 
    // trim from start (in place)
    void ltrim(std::string &s);
 
    // trim from end (in place)
    void rtrim(std::string &s);
 
    // trim from both ends (in place)
    void trim(std::string &s);
 
    // trim from start (copying)
    std::string ltrim_copy(std::string s);
 
    // trim from end (copying)
    std::string rtrim_copy(std::string s);
 
    // trim from both ends (copying)
    std::string trim_copy(std::string s);
 
private:
    std::map<std::string, std::map<std::string, std::string> > m_sections;
};
#endif
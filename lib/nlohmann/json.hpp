// This is a minimal JSON header stub for nlohmann/json
// In production, download from: https://github.com/nlohmann/json/releases
// Place full json.hpp in this location

#ifndef NLOHMANN_JSON_HPP
#define NLOHMANN_JSON_HPP

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace nlohmann {
    
class json {
public:
    enum class value_type {
        null, object, array, string, number, boolean
    };
    
    json() : type_(value_type::null) {}
    json(bool b) : type_(value_type::boolean), boolean_(b) {}
    json(int i) : type_(value_type::number), number_(static_cast<double>(i)) {}
    json(double d) : type_(value_type::number), number_(d) {}
    json(const std::string& s) : type_(value_type::string), string_(s) {}
    json(const char* s) : type_(value_type::string), string_(s) {}
    
    bool is_array() const { return type_ == value_type::array; }
    bool is_object() const { return type_ == value_type::object; }
    bool is_string() const { return type_ == value_type::string; }
    bool is_number() const { return type_ == value_type::number; }
    bool is_boolean() const { return type_ == value_type::boolean; }
    bool is_null() const { return type_ == value_type::null; }
    
    bool contains(const std::string& key) const;
    
    json& operator[](const std::string& key);
    json& operator[](size_t index);
    const json& operator[](size_t index) const;
    
    template<typename T>
    T value(const std::string& key, const T& default_value) const;
    
    std::string dump(int indent = -1) const;
    size_t size() const;
    
    static json array() { return json(); }
    static json object() { return json(); }
    
    friend std::istream& operator>>(std::istream& is, json& j);
    friend std::ostream& operator<<(std::ostream& os, const json& j);
    
private:
    value_type type_;
    std::map<std::string, json> object_;
    std::vector<json> array_;
    std::string string_;
    double number_ = 0;
    bool boolean_ = false;
};

} // namespace nlohmann

#endif // NLOHMANN_JSON_HPP

#include "json.hpp"
#include <sstream>

namespace nlohmann {

bool json::contains(const std::string& key) const {
    return object_.find(key) != object_.end();
}

json& json::operator[](const std::string& key) {
    if (type_ != value_type::object) {
        type_ = value_type::object;
        object_.clear();
    }
    return object_[key];
}

const json& json::operator[](const std::string& key) const {
    static json null_json;
    auto it = object_.find(key);
    if (it != object_.end()) {
        return it->second;
    }
    return null_json;
}

json& json::operator[](size_t index) {
    if (type_ != value_type::array) {
        type_ = value_type::array;
        array_.clear();
    }
    if (index >= array_.size()) {
        array_.resize(index + 1);
    }
    return array_[index];
}

const json& json::operator[](size_t index) const {
    static json null_json;
    if (type_ != value_type::array || index >= array_.size()) {
        return null_json;
    }
    return array_[index];
}

std::string json::dump(int indent) const {
    std::stringstream ss;
    
    switch (type_) {
        case value_type::null:
            ss << "null";
            break;
        case value_type::boolean:
            ss << (boolean_ ? "true" : "false");
            break;
        case value_type::number:
            ss << number_;
            break;
        case value_type::string:
            ss << "\"" << string_ << "\"";
            break;
        case value_type::array: {
            ss << "[";
            for (size_t i = 0; i < array_.size(); ++i) {
                if (i > 0) ss << ",";
                if (indent >= 0) ss << "\n" << std::string(indent + 2, ' ');
                ss << array_[i].dump(indent >= 0 ? indent + 2 : -1);
            }
            if (indent >= 0 && !array_.empty()) ss << "\n" << std::string(indent, ' ');
            ss << "]";
            break;
        }
        case value_type::object: {
            ss << "{";
            bool first = true;
            for (const auto& pair : object_) {
                if (!first) ss << ",";
                first = false;
                if (indent >= 0) ss << "\n" << std::string(indent + 2, ' ');
                ss << "\"" << pair.first << "\":";
                if (indent >= 0) ss << " ";
                ss << pair.second.dump(indent >= 0 ? indent + 2 : -1);
            }
            if (indent >= 0 && !object_.empty()) ss << "\n" << std::string(indent, ' ');
            ss << "}";
            break;
        }
    }
    
    return ss.str();
}

size_t json::size() const {
    if (type_ == value_type::array) {
        return array_.size();
    } else if (type_ == value_type::object) {
        return object_.size();
    }
    return 0;
}

std::istream& operator>>(std::istream& is, json& j) {
    std::string content((std::istreambuf_iterator<char>(is)),
                        std::istreambuf_iterator<char>());
    
    // Simple JSON parser - handles basic cases
    size_t pos = 0;
    
    auto skipWhitespace = [&content](size_t& p) {
        while (p < content.size() && std::isspace(content[p])) p++;
    };
    
    std::function<json(const std::string&, size_t&)> parseValue;
    
    parseValue = [&](const std::string& str, size_t& p) -> json {
        skipWhitespace(str, p);
        
        if (p >= str.size()) return json();
        
        char c = str[p];
        
        // null
        if (str.substr(p, 4) == "null") {
            p += 4;
            return json();
        }
        
        // true/false
        if (str.substr(p, 4) == "true") {
            p += 4;
            return json(true);
        }
        if (str.substr(p, 5) == "false") {
            p += 5;
            return json(false);
        }
        
        // string
        if (c == '"') {
            p++;
            std::string s;
            while (p < str.size() && str[p] != '"') {
                if (str[p] == '\\') {
                    p++;
                    if (p < str.size()) {
                        s += str[p];
                        p++;
                    }
                } else {
                    s += str[p];
                    p++;
                }
            }
            if (p < str.size()) p++;
            return json(s);
        }
        
        // number
        if (c == '-' || (c >= '0' && c <= '9')) {
            std::string num;
            while (p < str.size() && (str[p] == '-' || str[p] == '+' || 
                   str[p] == '.' || str[p] == 'e' || str[p] == 'E' ||
                   (str[p] >= '0' && str[p] <= '9'))) {
                num += str[p];
                p++;
            }
            return json(std::stod(num));
        }
        
        // array
        if (c == '[') {
            p++;
            json arr = json::array();
            skipWhitespace(str, p);
            
            if (p < str.size() && str[p] != ']') {
                size_t idx = 0;
                while (p < str.size()) {
                    arr[idx] = parseValue(str, p);
                    idx++;
                    skipWhitespace(str, p);
                    
                    if (p < str.size() && str[p] == ',') {
                        p++;
                    } else {
                        break;
                    }
                }
            }
            
            skipWhitespace(str, p);
            if (p < str.size() && str[p] == ']') p++;
            return arr;
        }
        
        // object
        if (c == '{') {
            p++;
            json obj = json::object();
            skipWhitespace(str, p);
            
            if (p < str.size() && str[p] != '}') {
                while (p < str.size()) {
                    skipWhitespace(str, p);
                    
                    // Parse key
                    if (p >= str.size() || str[p] != '"') break;
                    p++;
                    std::string key;
                    while (p < str.size() && str[p] != '"') {
                        if (str[p] == '\\') {
                            p++;
                            if (p < str.size()) key += str[p++];
                        } else {
                            key += str[p++];
                        }
                    }
                    if (p < str.size()) p++;
                    
                    skipWhitespace(str, p);
                    if (p >= str.size() || str[p] != ':') break;
                    p++;
                    
                    // Parse value
                    obj[key] = parseValue(str, p);
                    
                    skipWhitespace(str, p);
                    if (p < str.size() && str[p] == ',') {
                        p++;
                    } else {
                        break;
                    }
                }
            }
            
            skipWhitespace(str, p);
            if (p < str.size() && str[p] == '}') p++;
            return obj;
        }
        
        return json();
    };
    
    j = parseValue(content, pos);
    return is;
}

std::ostream& operator<<(std::ostream& os, const json& j) {
    os << j.dump();
    return os;
}

} // namespace nlohmann

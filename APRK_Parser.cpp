#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

using namespace std::literals;


class Parser {
public:
	Parser(std::ifstream& aprk) {
        std::string line;
        std::string key;
        std::string value;
        size_t pos;
        while (std::getline(aprk, line)) {
            if (line == "[DIMS]") {
                std::vector<std::string> dims;
                std::getline(aprk, line);
                while (line != "") {
                    pos = line.find('=');
                    key = line.substr(0, pos);
                    if (key == "dimsHEAD") {
                        value = line.substr(pos + 1);
                        dims = SplitIntoWords(value);
                        break;
                    }
                    std::getline(aprk, line);
                }
                auto pos_file = std::find(dims.begin(), dims.end(), "CADfile");
                dims_cad = std::distance(dims.begin(), pos_file);
            }
            if (line == "[DIMS.T]") {
                std::getline(aprk, line);
                while (line != "") {
                    pos = line.find('=');
                    key = line.substr(0, pos);
                    if (key == "dimsHEAD") {
                        value = line.substr(pos + 1);
                        dims_t = SplitIntoWords(value);
                        break;
                    }
                    std::getline(aprk, line);
                }
                auto pos_file = std::find(dims_t.begin(), dims_t.end(), "CADfile");
                dims_t_cad = std::distance(dims_t.begin(), pos_file);
            }
            if (line == "[dimsPARAM]") {
                std::getline(aprk, line);
                pos = line.find('=');
                value = line.substr(pos + 1);
                auto dims_param = SplitIntoWords(value);
                detail_ = dims_param[dims_cad];
            }
            if (line == "[dimsPARAM.T]") {
                std::getline(aprk, line);
                while (line != "") {
                    pos = line.find('=');
                    value = line.substr(pos + 1);
                    std::vector<std::string> params = SplitIntoWords(value);
                    dims_param_t_.push_back(params);
                    std::getline(aprk, line);
                }
            }
            if (line == "[GRAPHIT-TM]") {
                std::vector<std::string> etp_op;
                std::vector<std::string> etp_al;
                std::getline(aprk, line);
                while (line != "") {
                    pos = line.find('=');
                    key = line.substr(0, pos);
                    if (key == "ETOPERATIONSLAYOUT") {
                        value = line.substr(pos + 1);
                        etp_op = SplitIntoWords(value);
                        
                    }
                    if (key == "ETPALIAS") {
                        value = line.substr(pos + 1);
                        etp_al = SplitIntoWords(value);
                        
                    }
                    std::getline(aprk, line);
                }
                std::transform(etp_op.begin(), etp_op.end(), etp_al.begin(), std::inserter(etp_, etp_.begin()), [](const auto& key, const auto& value) {
                    return std::make_pair(std::stoi(key), value);
                    });
            }
            if (line == "[OPTIONS]") {
                do {
                    std::getline(aprk, line);
                    pos = line.find('=');
                    key = line.substr(0, pos);
                } while (key != "PROJECT_DIR" );
                if (key == "PROJECT_DIR") {
                    path_ = line.substr(pos + 1);
                }
            }
            
        }
	}

    const std::map<int, std::string>& GetEtp() const {
        return etp_;
    }

    const std::vector<std::vector<std::string>>& GetDims() const {
        return dims_param_t_;
    }

    const std::string& GetDetail() const {
        return detail_;
    }

    const std::string& GetPath() const {
        return path_;
    }

    const std::vector<std::string>& GetDimsAlias() const {
        return dims_t;
    }

    const size_t GetDimsTCad() const {
        return dims_t_cad;
    }
private:
    std::map<int, std::string> etp_;
    std::vector<std::vector<std::string>> dims_param_t_;
    std::vector<std::string> dims_t;
    size_t dims_t_cad{};
    size_t dims_cad{};
    std::string detail_;
    std::string path_;

    std::vector<std::string> SplitIntoWords(const std::string& text) {
        std::vector<std::string> words;
        std::string word;
        for (int i = 0; i < text.size(); ++i) {
            if (text[i] == ' ') {
                if (text[i + 1] == ',') {
                    word += '0';
                }
                continue;
            }
            if (text[i] == ',') {
                if (!word.empty()) {
                    words.push_back(word);
                    word.clear();
                }
            }
            else {
                word += text[i];
            }
        }
        if (!word.empty()) {
            words.push_back(word);
        }

        return words;
    }
};



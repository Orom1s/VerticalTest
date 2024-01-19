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
            if (line == "[dimsPARAM]") {
                std::getline(aprk, line);
                pos = line.find_last_of(' ');
                detail_ = line.substr(pos);
            }
            if (line == "[dimsPARAM.T]") {
                std::getline(aprk, line);
                while (line != "") {
                    pos = line.find('=');
                    key = line.substr(0, pos);
                    value = line.substr(pos + 1);
                    std::vector<std::string> params = SplitIntoWords(value);
                    dims_param_t_.emplace(std::stoi(key), params);
                    std::getline(aprk, line);
                }
            }
            if (line == "[GRAPHIT-TM]") {
                pos = line.find('=');
                key = line.substr(0, pos);
                if (key == "ETOPERATIONSLAYOUT") {
                    value = line.substr(pos + 1);
                    std::vector<std::string> etp_op = SplitIntoWords(value);
                    std::getline(aprk, line);
                    pos = line.find('=');
                    value = line.substr(pos + 1);
                    std::vector<std::string> etp_al = SplitIntoWords(value);
                    std::transform(etp_op.begin(), etp_op.end(), etp_al.begin(), std::inserter(etp_, etp_.begin()), [](const auto& key, const auto& value) {
                        return std::make_pair(std::stoi(key), value);
                        });
                }
            }
        }
	}
private:
    std::map<int, std::string> etp_;
    std::map<int, std::vector<std::string>> dims_param_t_;
    std::string detail_;

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



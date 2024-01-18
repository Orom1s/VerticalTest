#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <utility>
#include <algorithm>

using namespace std::literals;


/*
std::vector<std::string_view> SplitIntoWordsView(std::string_view str) {
    std::vector<std::string_view> result;
    str.remove_prefix(std::min(str.size(), str.find_first_not_of(' ')));
    const int64_t pos_end = str.npos;

    while (!str.empty()) {
        int64_t space = str.find(' ');
        result.push_back(space == pos_end ? str.substr(0, str.size()) : str.substr(0, space));
        str.remove_prefix(std::min(str.size(), str.find_first_not_of(' ', space)));
    }

    return result;
}
*/
class Parser {
public:
	Parser(std::ifstream& aprk) {
        std::string line;
        while (std::getline(aprk, line)) {
            auto pos = line.find('=');
            line.substr(0, pos);
            if (line == "ETOPERATIONSLAYOUT") {
                std::vector<std::string> etp_op = SplitIntoWords(line);
                std::getline(aprk, line);
                auto pos = line.find_first_of('=');
                line.substr(0, pos);
                std::vector<std::string> etp_al = SplitIntoWords(line);
                std::transform(etp_op.begin(), etp_op.end(), etp_al.begin(), std::inserter(etp_, etp_.end()), [](const auto& key, const auto& value) {
                    return std::make_pair( std::stoi(key), value );
                    });
            }
            

        }
	}
private:
    std::map<int, std::string> etp_;
    std::map<int, std::vector<std::vector<std::string>>> dims_param_t_;
    std::string detail_;

    std::vector<std::string> SplitIntoWords(const std::string& text) {
        std::vector<std::string> words;
        std::string word;
        for (const char c : text) {
            if (c == ' ') {
                if (!word.empty()) {
                    words.push_back(word);
                    word.clear();
                }
            }
            else if (c == ',' && word.empty()) {
                word += '0';
            }
            else {
                word += c;
            }
        }
        if (!word.empty()) {
            words.push_back(word);
        }

        return words;
    }
};



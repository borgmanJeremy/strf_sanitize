#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

std::vector<std::string> split(std::string const& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<char> create_specifier_list()
{

    std::vector<char> allowed_specifier;

    allowed_specifier.push_back('Y');
    allowed_specifier.push_back('H');

    return allowed_specifier;
}

std::string replace_all(std::string const& input,
                        std::string const& to_find,
                        std::string const& to_replace)
{
    size_t pos = 0;
    std::string output = input;
    while ((pos = input.find(to_find, pos)) != std::string::npos) {
        output.replace(pos, to_find.length(), to_replace);
        pos += to_replace.length();
    }

    return output;
}

std::vector<char> match_specifiers(std::string const& specifier,
                                   std::vector<char> allowed_specifier)
{

    std::vector<char> spec_list;

    for (uint i = 0; i < specifier.size() - 1; i++) {
        if (specifier[i] == '%') {
            spec_list.push_back(specifier[i + 1]);
        }
    }

    std::sort(spec_list.begin(), spec_list.end());
    std::sort(allowed_specifier.begin(), allowed_specifier.end());

    std::vector<char> overlap;
    std::set_intersection(spec_list.begin(),
                          spec_list.end(),
                          allowed_specifier.begin(),
                          allowed_specifier.end(),
                          back_inserter(overlap));

    return overlap;
}

int main()
{
    std::time_t t = std::time(nullptr);
    char buff[100];

    std::string specifier = "ss_%Y_%j_%H";
    std::cout << "Starting Specifier: " << specifier << std::endl;

    auto allowed_specifier = create_specifier_list();

    auto overlap = match_specifiers(specifier, allowed_specifier);

    // Create "Safe" string for strftime which is the specfiers delimited by *
    std::string lookup_string;
    for (auto const& e : overlap) {
        lookup_string.push_back('%');
        lookup_string.push_back(e);
        lookup_string.push_back('*');
    }

    auto size = std::strftime(
      buff, sizeof(buff), lookup_string.c_str(), std::localtime(&t));

    std::map<char, std::string> lookup_table;
    auto result = split(buff, '*');

    for (size_t i = 0; i < result.size(); i++) {
        lookup_table.emplace(std::make_pair(overlap[i], result[i]));
    }

    // Sub into original string
    std::string delim = "%";
    for (auto const& row : lookup_table) {
        auto to_find = delim + row.first;
        specifier = replace_all(specifier, to_find, row.second);
    }
    std::cout << specifier;
}

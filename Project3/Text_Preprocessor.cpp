#include "Text_Preprocessor.h"
Text_Preprocessor::Text_Preprocessor(string const& openfile) {
    obj.open(openfile);
}
void Text_Preprocessor::preprocess_text() {
    if (obj.is_open()) {
        string a[3] = { "an ", "a ", "the " };
        string p[9] = { "on ", "in ", "since ", "for ", "at ", "before ", "ago ", "to ", "by " };
        string text_line;
        while (getline(obj, text_line)) {
            text_line.erase(remove_if(text_line.begin(),text_line.end(),
                   [] (const char& letter) {
                        if (letter == ',' || letter == ';' || letter == '\"' ||
                            letter == ':' || letter == '.' || letter == '?' ||
                            letter == '!') {
                            return true;
                        }
                        return false;
                    }),

                text_line.end());

            for_each(text_line.begin(), text_line.end(), [](char& letter) {
                letter = tolower(letter);
                });
            for (int i = 0; i < 3; i++) {
                size_t found = string::npos;
                while ((found = text_line.find(a[i])) != string::npos) {
                    text_line.erase(found,a[i].length());
                }
            }
            for (int i = 0; i < 9; i++) {
               size_t found = string::npos;
                while ((found = text_line.find(p[i])) != string::npos) {
                    text_line.erase(found, p[i].length());
                }
            }
            cout << text_line << endl;
        }
    }
    else {
        cout << "File not Found" << endl;
    }
}

int Text_Preprocessor::search_word(const string& word) {
    if (obj.is_open()) {
        int index = 1;
        string str;
        while (getline(obj, str)) {
            while ((str.find(word)) != std::string::npos) {
                return index;
            }
            index++;
        }
    }
    return 0;
}
Text_Preprocessor::~Text_Preprocessor() {
    obj.close();
}


#include <typeinfo>

#include "./Header/MainLoop.h"

int main() {
    string num = "101101";
    deque<bool> a;
    int temp;
    for (size_t i = 0; i < num.length(); i++) {
        cout << num[i];
        if (num[i] == '1')
            a.push_back(1);
        else
            a.push_back(0);
    }
    cout << endl;
    cout << endl;
    string result;
    for (auto bit = cbegin(a); bit != cend(a); bit++) {
        result.push_back(*bit);
    }
    cout << result;

    return 0;
}
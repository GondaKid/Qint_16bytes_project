#include "../Header/Conversions.h"

string Conversion::convertBinToDec(const string& BinarySrc) {
    string Decimal = "0";
    for (int i = 0; i < BinarySrc.size(); i++) {
        if (BinarySrc[i] == '1')
            Decimal = AddNumberString(MultiplyNumberString(Decimal, "2"), "1");
        else
            Decimal = AddNumberString(MultiplyNumberString(Decimal, "2"), "0");
    }

    return Decimal;
}

string Conversion::MultiplyNumberString(string a, string b) {
    string Result = "0";
    string TempStr;
    int Temp = 0;
    bool Negative = false;

    if (a[0] == '-' && b[0] != '-') {
        Negative = true;
        a.erase(a.begin());
    }
    if (b[0] == '-' && a[0] != '-') {
        Negative = true;
        b.erase(b.begin());
    }

    for (int i = 0; i < b.size(); i++) {
        for (int j = a.size() - 1; j > -1; j--) {
            Temp = Temp + (a[j] - '0') * (b[b.size() - i - 1] - '0');
            TempStr.push_back((Temp % 10) + '0');
            Temp = Temp / 10;
        }
        if (Temp != 0)  //Nếu vẫn còn Temp.
        {
            TempStr.push_back(Temp + '0');
            Temp = 0;
        }

        //Đảo chuỗi.
        reverse(TempStr.begin(), TempStr.end());

        //Thêm các số 0 cần thiết vào sau.
        for (int j = 0; j < i; j++) {
            TempStr.push_back('0');
        }

        //Cộng Result và Temp.
        Result = AddNumberString(Result, TempStr);
        TempStr.clear();  //Dọn chuỗi tạm để dùng cho các bước tiếp theo.
    }

    if (Negative == true) {
        Result.insert(Result.begin(), '-');
    }

    return Result;
}

string Conversion::AddNumberString(string a, string b) {
    if (a[0] == '-' && b[0] != '-') {
        a.erase(a.begin());
        a = SubNumberString(b, a);
    } else {
        if (b[0] == '-' && a[0] != '-') {
            b.erase(b.begin());
            a = SubNumberString(a, b);
        } else {
            int Temp = 0;
            bool Negative = false;

            if (a[0] == '-' && b[0] == '-') {
                Negative = true;
            }

            //Thêm các số 0 vào đầu mỗi chuỗi.
            if (a.size() > b.size()) {
                while (a.size() != b.size()) {
                    b.insert(b.begin(), '0');
                }
            } else {
                while (a.size() != b.size()) {
                    a.insert(a.begin(), '0');
                }
            }

            //Tiến hành cộng.
            for (int i = a.size() - 1; i > -1; i--) {
                Temp = Temp + a[i] + b[i] - 2 * '0';
                a[i] = (Temp % 10) + '0';
                Temp = Temp / 10;
            }

            //Nếu vẫn còn dư (Temp != 0)
            if (Temp != 0) {
                a.insert(a.begin(), Temp + '0');
                Temp = 0;
            }
        }
    }

    //Xóa các số 0 thừa.
    while (a[0] == '0') {
        a.erase(a.begin());
    }

    return a;
}

string Conversion::SubNumberString(string a, string b) {
    int Temp = 0;
    bool Negative = false;

    //Thêm các số 0 vào đầu mỗi chuỗi.
    if (a.size() > b.size()) {
        while (a.size() != b.size()) {
            b.insert(b.begin(), '0');
        }
    } else {
        while (a.size() != b.size()) {
            a.insert(a.begin(), '0');
        }
    }

    //Kiểm tra a hay b lớn hơn và chuyển a thành số lớn hơn.
    if (strcmp(a.c_str(), b.c_str()) < 0) {
        string TempStr = a;
        a = b;
        b = TempStr;
        Negative = true;  //a < b => a - b < 0
    }

    //Thực hiện phép trừ.
    for (int i = a.size() - 1; i > -1; i--) {
        if ((a[i] - Temp) < b[i]) {
            a[i] = (10 + a[i] - b[i] - Temp) + '0';
            Temp = 1;
        } else {
            a[i] = a[i] - b[i] - Temp + '0';
            Temp = 0;
        }
    }

    //Xóa các số 0 thừa.
    while (a[0] == '0') {
        a.erase(a.begin());
    }

    //Nếu vẫn còn dư (Temp != 0)
    if (Negative == true) {
        a.insert(a.begin(), '-');
    }

    return a;
}
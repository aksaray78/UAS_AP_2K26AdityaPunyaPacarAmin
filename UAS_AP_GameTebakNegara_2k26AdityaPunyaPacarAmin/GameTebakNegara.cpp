#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

vector<string> negara = {
    "India", "China", "United States", "Indonesia", "Pakistan", "Nigeria", "Brazil", "Bangladesh", "Russia", "Ethiopia", 
    "Mexico", "Japan", "Egypt", "Philippines", "DR Kongo", "Vietnam", "Iran", "Turkey", "Germany", "Tanzania", 
    "Thailand", "United Kingdom", "France", "South Africa", "Italy", "Kenya", "Myanmar", "Colombia", "Sudan", "Uganda",
    "South Korea", "Algeria", "Iraq", "Spain", "Argentina", "Afghanistan", "Yemen", "Canada", "Angola", "Ukraine", 
    "Morocco", "Poland", "Uzbekistan", "Mozambique", "Malaysia", "Ghana", "Saudi Arabia", "Peru", "Madagascar", "Cote d'Ivoire", 
    "Cameroon", "Nepal", "Niger", "Venezuela", "Australia", "North Korea", "Syria", "Mali", "Burkina Faso", "Sri Lanka", 
    "Malawi", "Zambia", "Chad", "Kazakhstan", "Somalia", "Chili", "Senegal", "Guatemala", "Romania", "Netherlands", 
    "Ecuador", "Cambodia", "Zimbabwe", "Guinea", "Benin", "Rwanda", "Burundi", "Bolivia", "South Sudan", "Tunisia", 
    "Haiti", "Belgium", "Dominican Repuublic", "Jordan", "United Arab Emirates", "Honduras", "Tajikistan", "Papua New Guinea", "Cuba", "Sweden", 
    "Czech Republic", "Azerbaijan", "Portugal", "Togo", "Greece", "Israel", "Hungary", "Austria", "Switzerland", "Sierra Leone", 
    "Belarus", "Laos", "Turkmenistan", "Libya", "Kyrgyzstan", "Nicaragua", "Paraguay", "Bulgaria", "Serbia", "Congo", 
    "El Salvador", "Denmark", "Singapore", "Lebanon", "Liberia", "Central African Republic", "State Of Palestina", "Oman", "Norway", "Finland",
    "Mauritania", "Slovakia", "Ireland", "New Zealand", "Costa Rica", "Kuwait", "Panama", "Croatia", "Georgia", "Eritrea", 
    "Mongolia", "Uruguay", "Qatar", "Namibia", "Bosnia and Herzegovina", "Moldova", "Armenia", "Gambia", "Jamaica", "Lithuania", 
    "Albania", "Gabon", "Botswana", "Lesotho", "Guinea-Bissau", "Slovenia", "Equatorial Guinea", "Latvia", "North Macedonia", "Bahrain", 
    "Trinidad and Tobago", "Timor-Leste", "Cyprus", "Estonia", "Eswatini", "Mauritius", "Djibouti", "Fiji", "Comoros", "Solomon Islands", 
    "Guyana", "Bhutan", "Luxembourg", "Suriname", "Montenegro", "Malta", "Maldives", "Cabo Verde", "Brunei", "Belize", 
    "Bahamas", "Iceland", "Vanuatu", "Barbados", "Sao Tome & Principe", "Samoa", "Saint Lucia", "Kiribati", "Seychelles", "Grenada", 
    "Micronesia", "Tonga", "St. Vincent & Grenadines", "Antigua and Barbuda", "Andorra", "Dominica", "Saint Kitts & Nevis", "Liechtenstein", "Monaco", "Marshall Island", 
    "San Marino", "Palau", "Nauru", "Tuvalu", "Holy See"
};

string HurufDisembunyikan(string negara){
    vector<int> indeks;
    for(int i = 0; i < negara.size(); i++){
        if(negara[i] != ' ' && negara[i] != '-' && negara[i] != '\''){
            indeks.push_back(i);
        }
    }

    int persen = rand() % 21 + 30;
    int jlhSembunyi = indeks.size() * persen/100;

    if(jlhSembunyi < 1){
        jlhSembunyi = 2;
    }

    for(int i = indeks.size() -1; i > 0; i--){
        int j = rand() % (i + 1);
        swap(indeks[i], indeks[j]);
    }

    for(int i = 0; i < jlhSembunyi; i++){
        negara[indeks[i]] = '_';
    }

    return negara;
}

string ToLower(string huruf){
    transform(huruf.begin(), huruf.end(), huruf.begin(), ::tolower);
    return huruf;
}

int main(){
    srand(time(0));
    int skor = 0;
    char ulang;
    string jawaban;

    system("cls");
    do{
        int indexNegara = rand() % negara.size();
        string Tebaknegara = negara[indexNegara];

        string soal = HurufDisembunyikan(Tebaknegara);
        cout << "\nTebak Negara: " << soal;
        cout << "\nNegara apakah yang dimaksud? "; getline(cin, jawaban);

        if(ToLower(jawaban) == ToLower(Tebaknegara)){
            skor++;
            cout << "Selamat! Anda benar.\n";
        } else {
            cout << "Maaf, jawaban Anda salah. Coba lagi.\n";
        }
        cout << "Skor Anda: " << skor << endl;

        cout << "Ingin bermain lagi? (y/n): "; cin >> ulang;
        cin.ignore();
    } while(ulang == 'y' || ulang == 'Y');
    cout << "\nGame Selesai :D\n";
    return 0;
}
/**
 
    baştan savma yazdım okunurluğu biraz dusuk ama yapıcak bir sey yok :D
    bir sonrakinde bilgisayara karşı yarışma ve okunaklığı arttırmaya çalışırım. 
    bide işaretçi bağımlısıyım maalesef illaki olcak her projede.

**/


#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

static char MASA[] = "      |      |      \n" \
            "   1  |   2  |   3  \n" \
            "------+------+------\n" \
            "      |      |      \n" \
            "   4  |   5  |   6  \n" \
            "------+------+------\n" \
            "      |      |      \n" \
            "   7  |   8  |   9  \n";

            static char MASAFRESH[] = "      |      |      \n" \
            "   1  |   2  |   3  \n" \
            "------+------+------\n" \
            "      |      |      \n" \
            "   4  |   5  |   6  \n" \
            "------+------+------\n" \
            "      |      |      \n" \
            "   7  |   8  |   9  \n";

            static int kazan[8][3] = {
                {24, 31, 38},   // 1-2-3 (üst sıra)
                {87, 94, 101},  // 4-5-6 (orta sıra)
                {150, 157, 164},// 7-8-9 (alt sıra)
                {24, 87, 150},  // 1-4-7 (sol sütun)
                {31, 94, 157},  // 2-5-8 (orta sütun)
                {38, 101, 164}, // 3-6-9 (sağ sütun)
                {24, 94, 164},  // 1-5-9 (çapraz)
                {38, 94, 150}   // 3-5-7 (çapraz)
            };

typedef struct{string ad; int puan;}player; static player player1; static player player2;

void setMasa(char, string);
bool kazanmaKontrolu(char);
void fresh(char*);

bool iceriyormu(const std::vector<int>& vec, int value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

int main() {
    int tur;
    const char *p = MASA;
    cout << "Kaç tur oynayacaksınız: "; cin >> tur; cout << endl;
    cout << "1. oyuncunun adını girin: "; cin >> player1.ad; cout << "\n2. oyuncunun adını girin: "; cin >> player2.ad;

    char bolge = '0'; string init = ""; bool turBitti = false; vector<int> vec;

    for (int i = 1; i <= tur; i++) {
        cout << "\n=== " << i << "." << " TUR ===\n";
        fresh(MASA); cout << MASA << endl; turBitti = false; vec.clear();
        while (!turBitti) {
            do {
                cout << player1.ad << " oyuncusunun sırası: "; 
                cin >> bolge; 
                cout << endl; 
                if (cin && bolge >= '1' && bolge <= '9' && !iceriyormu(vec, bolge - '0')) break;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Girişiniz geçersiz.\n";
            } while (true);
            setMasa(bolge, player1.ad); 
            vec.push_back(bolge - '0');
            if (kazanmaKontrolu('X')) { 
                cout << player1.ad << " oyuncusu turu kazandı. \n ====================" << endl; 
                turBitti = true; 
                player1.puan += 10; 
                break; 
            }
            do {
                cout << player2.ad << " oyuncusunun sırası: "; 
                cin >> bolge; 
                cout << endl; 
                if (cin && bolge >= '1' && bolge <= '9' && !iceriyormu(vec, bolge - '0')) break;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Geçersiz giriş! Lütfen 1-9 arasında bir sayı girin ve boş bir yer seçin.\n";
            } while (true);
            setMasa(bolge, player2.ad); 
            vec.push_back(bolge - '0');
            if (kazanmaKontrolu('O')) { 
                cout << player2.ad << " oyuncusu turu kazandı. \n ====================" << endl; 
                turBitti = true; 
                player2.puan += 10; 
                break; 
            }
        }
    }
    if (player1.puan > player2.puan) {cout << "\n\n" << player1.ad << " oyunu kazandı!!\n" << endl;}
    else if (player2.puan > player1.puan) {cout << "\n\n" << player2.ad << " oyunu kazandı!!\n" << endl;}
    else {cout << "\n\nOyun berabere!!\n" << endl;}

    return 0;
}

void setMasa(char bolge, string oyuncu) {
    char *p = MASA;
    if (oyuncu == player1.ad) {
        while (1) {if (*p == bolge) {*p = 'X'; cout << MASA << endl; break;}p++;}
    } else if (oyuncu == player2.ad) {
        while (1) {if (*p == bolge) {*p = 'O'; cout << MASA << endl; break;}p++;}
    }
}

bool kazanmaKontrolu(char sembol) {
    for (int i = 0; i < 8; i++) {
        if (MASA[kazan[i][0]] == sembol &&
            MASA[kazan[i][1]] == sembol &&
            MASA[kazan[i][2]] == sembol) {
            return true;
        }
    }
    return false;
}

void fresh(char *MASA) {
    char *ptr = MASA;
    for (int i = 0; i < 169; i++) {
        *ptr = MASAFRESH[i];
        ptr++;
    }
}
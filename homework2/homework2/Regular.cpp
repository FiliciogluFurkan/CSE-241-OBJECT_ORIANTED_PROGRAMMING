#include "Regular.h"
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

    int Regular::calculatesize() {
        s = readfile();
        int counter = 0;
        for (row = s.begin(); row != s.end(); ++row) {
            counter++;
        }
        counter--;//calculates how many folders there are.
        std::string dosyaAdi = "deneme3.txt";
        // Dosyayı aç
        std::ifstream dosya(dosyaAdi.c_str(), std::ios::binary);
        // Dosyanın sonuna gidip konumunu al
        dosya.seekg(0, std::ios::end);
        std::streampos boyut = dosya.tellg();
        dosya.close();
        size = counter * (1024) + boyut;
        return size;//calculates the size

    }
    int Regular::getsize() {
        return calculatesize();
    }

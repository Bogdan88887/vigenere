#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

// Функция для шифрования с использованием шифра Виженера
std::wstring vigenereEncrypt(const std::wstring& plaintext, const std::wstring& keyword) {
    std::wstring encrypted;
    std::wstring keywordRepeated;

    // Повторяем ключевое слово до нужной длины
    while (keywordRepeated.length() < plaintext.length()) {
        keywordRepeated += keyword;
    }
    keywordRepeated = keywordRepeated.substr(0, plaintext.length());

    for (size_t i = 0; i < plaintext.length(); ++i) {
        wchar_t p = plaintext[i];
        wchar_t k = keywordRepeated[i];

        if (std::iswalpha(p)) {
            if (p >= L'А' && p <= L'Я') {  // Русский верхний регистр
                int shift = (k - L'А') % 32;
                wchar_t encryptedChar = (p - L'А' + shift) % 32 + L'А';
                encrypted += encryptedChar;
            } else if (p >= L'а' && p <= L'я') {  // Русский нижний регистр
                int shift = (k - L'а') % 32;
                wchar_t encryptedChar = (p - L'а' + shift) % 32 + L'а';
                encrypted += encryptedChar;
            } else if (p >= L'A' && p <= L'Z') {  // Английский верхний регистр
                int shift = (k - L'A') % 26;
                wchar_t encryptedChar = (p - L'A' + shift) % 26 + L'A';
                encrypted += encryptedChar;
            } else if (p >= L'a' && p <= L'z') {  // Английский нижний регистр
                int shift = (k - L'a') % 26;
                wchar_t encryptedChar = (p - L'a' + shift) % 26 + L'a';
                encrypted += encryptedChar;
            }
        } else {
            encrypted += p;  // Если не буква, не изменяем символ
        }
    }

    return encrypted;
}

// Функция для расшифровки с использованием шифра Виженера
std::wstring vigenereDecrypt(const std::wstring& ciphertext, const std::wstring& keyword) {
    std::wstring decrypted;
    std::wstring keywordRepeated;

    // Повторяем ключевое слово до нужной длины
    while (keywordRepeated.length() < ciphertext.length()) {
        keywordRepeated += keyword;
    }
    keywordRepeated = keywordRepeated.substr(0, ciphertext.length());

    for (size_t i = 0; i < ciphertext.length(); ++i) {
        wchar_t c = ciphertext[i];
        wchar_t k = keywordRepeated[i];

        if (std::iswalpha(c)) {
            if (c >= L'А' && c <= L'Я') {  // Русский верхний регистр
                int shift = (k - L'А') % 32;
                wchar_t decryptedChar = (c - L'А' - shift + 32) % 32 + L'А';
                decrypted += decryptedChar;
            } else if (c >= L'а' && c <= L'я') {  // Русский нижний регистр
                int shift = (k - L'а') % 32;
                wchar_t decryptedChar = (c - L'а' - shift + 32) % 32 + L'а';
                decrypted += decryptedChar;
            } else if (c >= L'A' && c <= L'Z') {  // Английский верхний регистр
                int shift = (k - L'A') % 26;
                wchar_t decryptedChar = (c - L'A' - shift + 26) % 26 + L'A';
                decrypted += decryptedChar;
            } else if (c >= L'a' && c <= L'z') {  // Английский нижний регистр
                int shift = (k - L'a') % 26;
                wchar_t decryptedChar = (c - L'a' - shift + 26) % 26 + L'a';
                decrypted += decryptedChar;
            }
        } else {
            decrypted += c;  // Если не буква, не изменяем символ
        }
    }

    return decrypted;
}

// Вспомогательная функция для проверки, что строка содержит только буквы
bool isAlpha(const std::wstring& s) {
    for (wchar_t ch : s) {
        if (!std::iswalpha(ch)) {
            return false;
        }
    }
    return true;
}

// Функция для конвертации строки из std::string в std::wstring
std::wstring toWideString(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

// Функция для конвертации строки из std::wstring в std::string
std::string toNarrowString(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

int main() {
    setlocale(LC_ALL, "");  // Для поддержки русского языка

    std::string choice;
    std::cout << "Выберите действие: 1 - шифрование, 2 - расшифровка\n";
    std::cin >> choice;

    if (choice != "1" && choice != "2") {
        std::cout << "Неверный выбор!" << std::endl;
        return 1;
    }

    std::cin.ignore(); // Чтобы игнорировать оставшийся символ новой строки

    std::string inputText, inputKeyword;
    std::cout << "Введите текст: ";
    std::getline(std::cin, inputText);
    std::cout << "Введите ключевое слово (только буквы): ";
    std::getline(std::cin, inputKeyword);

    std::wstring text = toWideString(inputText);
    std::wstring keyword = toWideString(inputKeyword);

    if (!isAlpha(keyword)) {
        std::cout << "Ключевое слово должно содержать только буквы!" << std::endl;
        return 1;
    }

    if (choice == "1") {
        std::wstring result = vigenereEncrypt(text, keyword);
        std::cout << "Зашифрованное сообщение: " << toNarrowString(result) << std::endl;
    } else {
        std::wstring result = vigenereDecrypt(text, keyword);
        std::cout << "Расшифрованный текст: " << toNarrowString(result) << std::endl;
    }

    return 0;
}

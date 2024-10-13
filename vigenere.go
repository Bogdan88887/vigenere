package main

import (
 "fmt"
 "unicode"
)

// Функция шифрования с использованием шифра Виженера
func vigenereEncrypt(plaintext, keyword string) string {
 var encrypted []rune
 keywordRepeated := repeatKeyword(keyword, len(plaintext))

 for i, p := range plaintext {
  k := rune(keywordRepeated[i])

  if unicode.IsLetter(p) {
   if unicode.Is(unicode.Latin, p) {
    shift := unicode.ToUpper(k) - 'A'
    encryptedChar := (unicode.ToUpper(p) - 'A' + shift) % 26 + 'A'
    if unicode.IsLower(p) {
     encrypted = append(encrypted, unicode.ToLower(encryptedChar))
    } else {
     encrypted = append(encrypted, encryptedChar)
    }
   } else if unicode.Is(unicode.Cyrillic, p) {
    shift := unicode.ToUpper(k) - 'А'
    encryptedChar := (unicode.ToUpper(p) - 'А' + shift) % 32 + 'А'
    if unicode.IsLower(p) {
     encrypted = append(encrypted, unicode.ToLower(encryptedChar))
    } else {
     encrypted = append(encrypted, encryptedChar)
    }
   }
  } else {
   encrypted = append(encrypted, p) // Если символ не буква, не изменяем
  }
 }

 return string(encrypted)
}

// Функция расшифровки с использованием шифра Виженера
func vigenereDecrypt(ciphertext, keyword string) string {
 var decrypted []rune
 keywordRepeated := repeatKeyword(keyword, len(ciphertext))

 for i, c := range ciphertext {
  k := rune(keywordRepeated[i])

  if unicode.IsLetter(c) {
   if unicode.Is(unicode.Latin, c) {
    shift := unicode.ToUpper(k) - 'A'
    decryptedChar := (unicode.ToUpper(c) - 'A' - shift + 26) % 26 + 'A'
    if unicode.IsLower(c) {
     decrypted = append(decrypted, unicode.ToLower(decryptedChar))
    } else {
     decrypted = append(decrypted, decryptedChar)
    }
   } else if unicode.Is(unicode.Cyrillic, c) {
    shift := unicode.ToUpper(k) - 'А'
    decryptedChar := (unicode.ToUpper(c) - 'А' - shift + 32) % 32 + 'А'
    if unicode.IsLower(c) {
     decrypted = append(decrypted, unicode.ToLower(decryptedChar))
    } else {
     decrypted = append(decrypted, decryptedChar)
    }
   }
  } else {
   decrypted = append(decrypted, c) // Если символ не буква, не изменяем
  }
 }

 return string(decrypted)
}

// Вспомогательная функция для повторения ключевого слова
func repeatKeyword(keyword string, length int) string {
 repeated := keyword
 for len(repeated) < length {
  repeated += keyword
 }
 return repeated[:length]
}

func main() {
 var choice string
 fmt.Println("Выберите действие: 1 - шифрование, 2 - расшифровка")
 fmt.Scan(&choice)

 if choice != "1" && choice != "2" {
  fmt.Println("Неверный выбор!")
  return
 }

 var text, keyword string
 fmt.Println("Введите текст:")
 fmt.Scan(&text)
 fmt.Println("Введите ключевое слово (только буквы):")
 fmt.Scan(&keyword)

 // Проверяем, что ключевое слово содержит только буквы
 if !isAlpha(keyword) {
  fmt.Println("Ключевое слово должно содержать только буквы!")
  return
 }

 if choice == "1" {
  result := vigenereEncrypt(text, keyword)
  fmt.Println("Зашифрованное сообщение:", result)
 } else {
  result := vigenereDecrypt(text, keyword)
  fmt.Println("Расшифрованный текст:", result)
 }
}

// Вспомогательная функция для проверки, что строка состоит только из букв
func isAlpha(s string) bool {
 for _, r := range s {
  if !unicode.IsLetter(r) {
   return false
  }
 }
 return true
}

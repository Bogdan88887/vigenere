def vigenere_encrypt(plaintext, keyword):
    """Шифрование с помощью шифра Виженера."""
    encrypted = []
    keyword_repeated = (keyword * (len(plaintext) // len(keyword))) + keyword[:len(plaintext) % len(keyword)]

    for p, k in zip(plaintext, keyword_repeated):
        if p.isalpha():  # Проверяем, является ли символ буквой
            if 'A' <= p <= 'Z' or 'a' <= p <= 'z':  # Английский алфавит
                shift = ord(k.upper()) - ord('A')
                encrypted_char = chr((ord(p.upper()) - ord('A') + shift) % 26 + ord('A'))
                # Сохраняем исходный регистр символа
                encrypted.append(encrypted_char.lower() if p.islower() else encrypted_char.upper())
            elif 'А' <= p <= 'Я' or 'а' <= p <= 'я':  # Русский алфавит
                shift = ord(k.upper()) - ord('А')
                encrypted_char = chr((ord(p.upper()) - ord('А') + shift) % 32 + ord('А'))
                encrypted.append(encrypted_char.lower() if p.islower() else encrypted_char.upper())
        else:
            encrypted.append(p)  # Если символ не буква, добавляем его без изменений

    return ''.join(encrypted)


def vigenere_decrypt(ciphertext, keyword):
    """Расшифровка с помощью шифра Виженера."""
    decrypted = []
    keyword_repeated = (keyword * (len(ciphertext) // len(keyword))) + keyword[:len(ciphertext) % len(keyword)]

    for c, k in zip(ciphertext, keyword_repeated):
        if c.isalpha():  # Проверяем, является ли символ буквой
            if 'A' <= c <= 'Z' or 'a' <= c <= 'z':  # Английский алфавит
                shift = ord(k.upper()) - ord('A')
                decrypted_char = chr((ord(c.upper()) - ord('A') - shift) % 26 + ord('A'))
                decrypted.append(decrypted_char.lower() if c.islower() else decrypted_char.upper())
            elif 'А' <= c <= 'Я' or 'а' <= c <= 'я':  # Русский алфавит
                shift = ord(k.upper()) - ord('А')
                decrypted_char = chr((ord(c.upper()) - ord('А') - shift) % 32 + ord('А'))
                decrypted.append(decrypted_char.lower() if c.islower() else decrypted_char.upper())
        else:
            decrypted.append(c)  # Если символ не буква, добавляем его без изменений

    return ''.join(decrypted)


def main():
    print("Выберите действие: 1 - шифрование, 2 - расшифровка")
    choice = input()

    if choice not in ['1', '2']:
        print("Неверный выбор!")
        return

    text = input("Введите текст: ")
    keyword = input("Введите ключевое слово (только буквы): ")

    if not keyword.isalpha():  # Проверяем, что ключ состоит только из букв
        print("Ключевое слово должно содержать только буквы!")
        return

    if choice == '1':
        result = vigenere_encrypt(text, keyword)
        print("Зашифрованное сообщение:", result)
    else:
        result = vigenere_decrypt(text, keyword)
        print("Расшифрованный текст:", result)


if __name__ == "__main__":
    main()

import requests

START_INDEX = 11
END_INDEX = 34
LETTER_INDEX = 99
EXTRACT_PASSWORD = 1
FIND_SENTENCE = 2


def extract_password_from_site():
    """from a bounch of file it get the password
    :return: the password
    :rtype: string"""
    URL = "http://webisfun.cyber.org.il/nahman/"
    password = ""
    NEW_URL = ""
    for i in range(START_INDEX, END_INDEX + 1):
        NEW_URL = URL + f"files/file{i}.nfo"
        response = requests.get(NEW_URL)
        html = response.text
        password += html[LETTER_INDEX]
    return password


def find_most_common_words(URL, senLen):
    """the function makee a sentence from the most comon words in a site
    :param URL: the url to the words
    :type URL: string
    :param senLen: the len of the sentence
    :type senLen: int
    :return: the sentence
    :rtype: string"""
    words_list = requests.get(URL).text.split(" ")
    words_dic = {}
    sentence = ""
    for word in words_list:
        if word in words_dic:
            words_dic[word] += 1
        else:
            words_dic[word] = 1
    words_sorted = sorted(words_dic.items(), key=lambda item: item[1])
    end = -1 * senLen -1 # the amount of words but negative -1 so it will take the last senLen words
    for i in range(-1, end, -1):
        sentence += words_sorted[i][0]
        if i != -6:
            sentence += " "

    return sentence


def main():
    choise = int(
        input("Enter 1 for the password\nEnter 2 for the sentence\nYour choise: "))
    if choise == EXTRACT_PASSWORD:
        password = extract_password_from_site()
        print(password)
    if choise == FIND_SENTENCE:
        sentence = find_most_common_words(
            "http://webisfun.cyber.org.il/nahman/final_phase/words.txt", 6)
        print(sentence)
    return

if __name__ == "__main__":
    main()

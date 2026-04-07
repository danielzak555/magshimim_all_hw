import socket
from datetime import date

LIS_PORT = 9090
FILM_IP = "54.71.128.194"
FILM_PORT = 92
SUB_THE_WORD_YEAR = 4

def main():
    request_text = "GETMOVIE#genre:Adventure&year:1990-1999&country:France"
    country_index =request_text.find("country")
    year_index = request_text.find("year")
    the_years = request_text[year_index +  5: country_index - 1]
    first_year = the_years[:the_years.find("-")]
    second_year = the_years[the_years.find("-") + 1:]
    print(the_years)
    print(first_year)
    print(second_year)
if __name__ == "__main__":
    main()
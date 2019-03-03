# Gra Snake
Projekt końcowy z przedmiotu "Wstęp do programowania w języku C" na Uniwersytecie Wrocławskim w roku akademickim 2018/19.

## Instalacja
Gra korzysta z biblioteki Allegro5, która jest niezbędna do jej uruchomienia.

### Ubuntu
```bash
sudo apt install liballegro*5.2 liballegro*5-dev
```
### Pozostałe systemy
[Allegro Quickstart](https://github.com/liballeg/allegro_wiki/wiki/Quickstart#installation)

### Kompilacja i uruchomienie
Po zainstalowaniu Allegro5, wystarczy pobrać to repozytorium i wydać polecenie
```bash
make
```
a następnie
```bash
./snake
```

## Użytkowanie
Po uruchomieniu gry zostanie otwarty konfigurator. Użytkownik za pomocą klawiatury, może wpierw wybrać wielkość planszy, a następnie prędkość poruszania się węża (gdzie 1 znaczy najwolniej, a 3 najszybciej).
Wybory zatwierdza się enterem.

Po tych czynnościach zostanie otwarte nowe okno z grą. Gracz porusza wężem za pomocą strzałek na klawiaturze.

### Zasady
Celem gracza jest zebranie jak największej ilości znajdziek - myszy. Po najechaniu głową węża na znajdźkę, wąż wydłuża się, a liczba punktów się powiększa. Gra kończy się gdy wąż wpadnie na ścianę, lub spróbuje zjeść sam siebie.

Liczba zebranych punktów wyświetla się nad planszą, razem z czasem jaki upłynął od rozpoczęcia gry.

Po przegranej gracz może nacisnąć klawisz R, by rozpocząć ponownie grę z taką samą konfiguracją, lub dowolny inny klawisz, by znów przejść do konfiguratora.

## Opis struktury programu
Gra korzysta z modułów:
- init - zawiera funkcje inicjalizujące działanie biblioteki Allegro, konfigurujące wielkość wyświetlanego okna, sprawdzające poprawność inicjalizacji oraz niszczące zmienne z których korzystał program;
- startmenu - konfigurator gry;
- game - zawiera większość kodu odpowiedzialnego za rysowanie gry, zbieranie informacji o wciśniętych klawiszach, losowanie znajdziek i tworzenie zmiennych;
- plansza - tworzy ściany na planszy (tablicy dwuwymiarowej);
- snake - definiuje strukturę w postaci zmodyfikowanej listy jednokierunkowej, która służy do reprezentowania węża. Zawiera funkcję inicjalizującą węża o długości 2, a także funkcje odpowiedzialne za przesuwanie węża i rozszerzenie go. Moduł zawiera także funkcje sprawdzające czy wąż 
złapał znajdźkę oraz czy uderzył w ścianę lub się przegryzł.

Główną strukturą jest zmodyfikowana lista jednokierunkowa, która składa się ze struktury głównej, posiadającej wskaźniki na pierwszy i ostatni element listy oraz ze struktur-elementów, które tworzą tę listę. Elementy listy to odpowiednio bloki węża. Każdy z nich zawiera informację o swojej pozycji, kierunku w jakim zmierza, kierunku w jakim zmierza jego następnik oraz wskaźnik na następny element. Dzięki takim danym rysowanie odpowiednich tekstur jest bardzo proste. Poruszanie wężem działa zaś następująco: kiedy chcę poruszyć się w daną stronę przepinam ostatni element węża jako pierwszy (pozostałych nie ruszam), kiedy zaś chcę go powiększyć, dodaję nowy element jako pierwszy element listy.

Ważną częścią gry jest także "podkładka" w postaci tablicy dwuwymiarowej liczb całkowitych. Znajdują się w niej informacje czy na danym polu znajduje się znajdźka, ściana, wąż, lub czy to pole jest wolne. Gdy przesuwam wężem, aktualizuję nie tylko jego strukturę, ale także jego reprezentację w tablicy. Dzięki temu łatwo sprawdzić, czy nastąpiła kolizja z dowolnym obiektem.

## Autor
Bartosz Jaśkiewicz
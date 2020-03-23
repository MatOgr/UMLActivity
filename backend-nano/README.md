# backend-nano
## Klasa Nano
### Metody
- `void bind(std::string str, std::function<void()> func, std::string help)` - tworzy BindingString na podstawie podanych parametrów. Format str: `#nano\<KEY\>Litera%opis funkcji!Komunikat do wyświetlenia w okienku${Nazwa pola(entry) do którego ma zostać wczytana wartość}`. Obsługiwane klawisze (KEY):
    - Ctrl
    - Shift
    - F1-F12 - wszystkie kolejne klawisze nie łączą się z literami
    - Delete(DEL)
    - Backspace(BS)
    - Strzałki(LARROW, RARROW, UARROW, DARROW)
    - EDITION - jest to implementacja odpowiedzi toola na wciśnięcie dowolnego przycisku nie objętego bindem. Wartość wciśniętego przycisku przekazywana jest toolowi poprzez funkcję `setEntry("KEY", a)`, gdzie `a` to wciśnięty przycisk. Klawisze specjalne, np Delete, Backspace, są przekazywane w nawiasach ostrych, np `<DEL>` i `<BS>`.\
W nawiasach podane są nazwy, których trzeba użyć przy wpisywaniu do funkcji bind(w nawiasach ostrych <>).\
Nie można używać skrótów łączonych, np. `<CTRL><SHIFT>N`, `<SHIFT><DEL>`
- `void start()` - funkcja obsługująca całą komunikację między toolem a sprzętem
- `std::vector<char> GetBindTab()` - pomocnicza funkcja zwracająca tablicę z skrótami klawiszowymi
- `void draw_bottom_line()` - pomocnicza funkcja, wypisująca skróty klawiszowe i ich nazwy w otatnim wierszu terminalu
- `void re_bind(std::string old_bind, std::string new_bind)` - funkcja zmieniająca skrót klawiszowy realizujący daną funkcję. Może również służyć do pozbycia się zczytywania wartości do wpisu.\
Przykład:\
Jeśli skrót podany był jako `<CTRL>e%Example!Input:${EXAMPLE}`, do funkcji re_bind jako old_bind podajemy `CTRL+e`. Wielkość liter ma znaczenie. Do pola new_bind podajemy skrót i jego nazwę, oraz ewentualny tekst do wyświetlenia w okienku przy czytaniu wartości, np `CTRL+f-New!Input2${EXAMPLE2}`
## Skróty zaimplementowane
- CTRL+Q - wyłącza program, póki co wyświetla tylko okienko z wiadomością o niezapisanym pliku (program można zamknąć naciskając klawisz 'F')
- CTRL+H - wyświetla okienko z wszystkimi skrótami i pomocą do każdego z nich

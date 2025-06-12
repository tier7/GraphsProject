# GraphsProject
Algorytmy i złożoność obliczeniowa — Projekt 2

# Plik konfiguracyjny

1. Generowanie losowego grafu:

   random [liczba_wierzcholkow] [gestosc] [minWaga] [maxWaga] [reprezentacja]

   - reprezentacja:     matrix | list

   Typ grafu (directed/undirected) ustalany automatycznie na podstawie trybu problemu

   Przykład:
   problem MST  
   random 10 0.25 1 10 matrix  
   Losowy graf nieskierowany o 10 wierzchołkach, gęstości 25%, wagach od 1 do 10, reprezentacja macierzowa


2. Wczytanie grafu z pliku:

   file [nazwa_pliku] [reprezentacja]  
   Przykład:
   problem SP  
   file graf.txt list  
   Wczytuje graf skierowany z pliku


3. Wyświetlenie grafu:

   show  
   wypisuje aktualny graf


4. Algorytm Prima:

   prim  
   Oblicza MST algorytmem Prima


5. Algorytm Kruskala:

   kruskal  
   Oblicza MST algorytmem Kruskala


6. Algorytm Dijkstry:

   dijkstra [start]  
   Oblicza najkrotsze sciezki algorytmem Dijkstry od podanego wierzcholka  
   Przykład:  
   dijkstra 0


7. Algorytm Bellmana-Forda:

   bellman [start]  
   Oblicza najkrotsze sciezki algorytmem Bellmana-Forda od podanego wierzcholka  
   Przykład:  
   bellman 3


8. Ustawienie trybu problemu:

   problem [typ_problemu]
   - MST graf nieskierowany, algorytmy: Prim, Kruskal
   - SP graf skierowany, algorytmy: Dijkstra, Bellman-Ford

   Przykład:

   problem MST

   problem SP

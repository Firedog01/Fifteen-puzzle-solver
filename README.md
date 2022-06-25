## Fifteen puzzle solver ##

### Polski ###

Program napisany w C++ rozwiązujący zagadkę "piętnastka" poprzez przeglądanie przestrzenii stanów. 

Zaimplementowane zostały algorytmy ślepe BFS (Breadth-First Search) oraz DFS (Depth-First Search) oraz heurystyczna A* (A star).
Dla metod ślepych można wybrać dowolną kolejność operatorów (np. dla LRUD program będzie szedł w lewo w pierwszej kolejności). Dla metody A* można wybrać jedną z heurystyk: Hamminga (ilość elemetów układanki w złym miejscu) lub Manhattan (suma odległości elementów układanki od ich docelowego położenia).

Program przygotowany na przedmiot Sztuczna Inteligencja i Systemy Ekspertowe.

### English ###

C++ program that solves fiftheen puzzle by state space search.

Program implements blind algorithms BFS (Breadth-First Search) and DFS (Depth-First Search) as well as heuristic algorithm A* (A star).
For blind methods user may choose operator order (ex. for LRUD program will go left first). For A* method user may choose one of heuristics: Hamming (total count of missplaced puzzle elements) or Manhattan (sum of distances between puzzle elements and their goal position).

Program was made for subject Arificial Intelligence and Expert Systems.

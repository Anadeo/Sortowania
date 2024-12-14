#include<iostream>
#include<cstdlib>
#include<time.h>
#include<SDL.h>
#include<thread>
#include<windows.h>
using namespace std;
unsigned long long porownania, zamiany;
bool nie_skonczone = true;
int czerwone[] = { -1, -1 };
void wypisz_liczby(int ile, int liczby[]);
void moj_sposob(int liczby[], int ile, int predkosc);
void sortowanie_naiwne(int liczby[], int ile, int predkosc);
void sortowanie_babelkowe(int liczby[], int ile, int predkosc);
void sortowanie_wybor(int liczby[], int ile, int predkosc);
void sortowanie_wstawianie(int liczby[], int ile, int predkosc);
void sortowanie_scalanie(int liczby[], int p, int k, int predkosc);
void sortowanie_szybkie(int liczby[], int p, int k, int predkosc);
void sortowanie_kubelkowe(int liczby[], int ile, int predkosc);
void sortowanie_poprzez_kopcowanie(int liczby[], int ile, int predkosc);
void sprawdzenie_poprawnosci_kopca(int liczby[], int ile, int i, int predkosc);
void sortowanie_binarne(int liczby[], int ile, int predkosc);
void sortowanie_muszelkowe(int liczby[], int ile, int predkosc);
void sortowanie_koktailem(int liczby[], int ile, int predkosc);
void sortowanie_szybkie_odwrotne(int liczby[], int p, int k);
void sortowanie_zwariowane(int tab[], int rozmiar, int predkosc);
void sortowanie_bk(int tablica[], int dlugosc, int predkosc);
void tasowanie(int liczby[], int ile) {
	int pomoc, losowa;
	for (short i = 0; i < ile; i++) {
		losowa = rand() % ile;
		pomoc = liczby[i];
		liczby[i] = liczby[losowa];
		liczby[losowa] = pomoc;
	}
}
void wizualizacja(short szerokosc_okna, int liczby[], int ile) {
	SDL_Window* window = SDL_CreateWindow("Sortowanie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc_okna, 1000, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Rect prostokat;
	SDL_Event event;
	short szerokosc_paska = szerokosc_okna / ile, wysokosc_paska;
	prostokat.w = szerokosc_paska;
	while (nie_skonczone) {
		for (short i = 0; i < ile; i++) {
			if (czerwone[0] == i || czerwone[1] == i) {
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
			}
			else if (liczby[i] == i + 1) {
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			}
			prostokat.x = i * szerokosc_paska;
			wysokosc_paska = liczby[i] * 1000 / ile;
			prostokat.y = 1000 - wysokosc_paska;
			prostokat.h = wysokosc_paska;
			SDL_RenderFillRect(renderer, &prostokat);
		}
		SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_PollEvent(&event);
		SDL_RenderClear(renderer);
	}
	SDL_DestroyWindow(window);
}
int main(int argc, char* argv[]) {
	srand((unsigned int)time(0));
	int ile, predkosc;
	char wybor, pytanie, ulozenie;
	long double start, stop;
	cout << "Ile bedzie liczb do posortowania: ";
	cin >> ile;
	int* liczby = new int[ile];
	cout << "Jak szybko ma byc wykonywane sortowanie?" << endl;
	cin >> predkosc;
	cout << "Jak maja byc poukladanie liczby?" << endl << "1-Losowo" << endl << "2-Odwrotnie posortowane" << endl << "3-liczby juz posortowane" << endl << "Wybierasz: ";
	cin >> ulozenie;
	cout << "Twozenie odpowiednich liczb..." << endl;
	for (int i = 0; i < ile; i++) {
		liczby[i] = i + 1;
	}
	switch (ulozenie) {
		case '1':
			tasowanie(liczby, ile);
		break;
		case '2':
			sortowanie_szybkie_odwrotne(liczby, 0, ile - 1);
		break;
	}
	/*cout << "Gotowe. Czy wyswietlic je teraz?" << endl << "tak 't' nie 'n': ";
	cin >> pytanie;
	if (pytanie == 't') {
		wypisz_liczby(ile, liczby);
	}*/
	cout << endl << "Ktorym sposobem maja zostac posortowane liczby?" << endl << "1-Moim autorskim sposobem" << endl << "2-Sortowanie naiwne" << endl << "3-Sortowanie babelkowe" << endl << "4-Sortowanie poprzez wybor" << endl << "5-Sortowanie przez wstawianie" << endl << "6-Sortowanie przez scalanie" << endl << "7-Sortowanie szybkie" << endl << "8-Sortowanie kubelkowe" << endl << "9-Sortowanie poprzez kopcowanie" << endl << "a-Sortowanie binarne" << endl << "b-Sortowanie muszelkowe" << endl << "c-Sortowanie koktailem" << endl << "d-Sortowanie zwariowane" << endl << "e-najprostrze sortowanie jakie mozna napisac" << endl << "Wybierasz: ";
	cin >> wybor;
	cout << endl << endl << "Po naciscieciu dowolnego przycisku program zacznie sortowac te liczby..." << endl;
	system("pause");
	cout << "Sortowanie..." << endl;
	//znalezienie szerokosci okna
	short szerokosc_okna;
	for (short i = 1; i * ile <= 1920; i++) {
		szerokosc_okna = i * ile;
	}
	thread t1(wizualizacja, szerokosc_okna, liczby, ile);
	switch (wybor) {
	case '1': {
		start = clock();
		moj_sposob(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case '2': {
		start = clock();
		sortowanie_naiwne(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case '3': {
		start = clock();
		sortowanie_babelkowe(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case '4': {
		start = clock();
		sortowanie_wybor(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case '5': {
		start = clock();
		sortowanie_wstawianie(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case '6': {
		start = clock();
		sortowanie_scalanie(liczby, 0, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case '7': {
		start = clock();
		sortowanie_szybkie(liczby, 0, ile - 1, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case '8': {
		start = clock();
		sortowanie_kubelkowe(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case '9': {
		start = clock();
		sortowanie_poprzez_kopcowanie(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case 'a': {
		start = clock();
		sortowanie_binarne(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case 'b': {
		start = clock();
		sortowanie_muszelkowe(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case 'c': {
		start = clock();
		sortowanie_koktailem(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case 'd': {
		start = clock();
		sortowanie_zwariowane(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	case 'e': {
		start = clock();
		sortowanie_bk(liczby, ile, predkosc);
		stop = (clock() - start) / CLOCKS_PER_SEC;
		break;
	}
	}
	nie_skonczone = false;
	t1.join();
	cout << "Gotowe! (" << stop << "s)" << endl << "Porownania: " << porownania << endl << "Zamiany: " << zamiany << endl;
	system("pause");
	/*wypisz_liczby(ile, liczby);
	cout << endl;
	system("pause");*/
	return 0;
}
void wypisz_liczby(int ile, int liczby[]) {
	for (int i = 0; i < ile; i++) {
		cout << liczby[i] << " ";
	}
}
void moj_sposob(int liczby[], int ile, int predkosc) {
	int licznik = 0;
	int save;
	int liczba1;
	int liczba2;
	while (licznik < ile - 1) {
		liczba1 = licznik;
		for (int i = licznik; i < ile - 1; i++) {
			liczba2 = i + 1;
			porownania++;
			czerwone[0] = liczba1;
			czerwone[1] = liczba2;
			Sleep(predkosc);
			czerwone[0] = -1;
			czerwone[1] = -1;
			if (liczby[liczba1] > liczby[liczba2]) {
				save = liczby[liczba1];
				liczby[liczba1] = liczby[liczba2];
				liczby[liczba2] = save;
				zamiany++;
				Sleep(predkosc);
			}
		}
		licznik++;
	}
}
void sortowanie_naiwne(int liczby[], int ile, int predkosc) {
	int save;
	for (int i = 1; i < ile; i++) {
		porownania++;
		czerwone[0] = i - 1;
		czerwone[1] = i;
		Sleep(predkosc);
		czerwone[0] = -1;
		czerwone[1] = -1;
		if (liczby[i - 1] > liczby[i]) {
			save = liczby[i];
			liczby[i] = liczby[i - 1];
			liczby[i - 1] = save;
			zamiany++;
			Sleep(predkosc);
			i = 0;
		}
	}
}
void sortowanie_babelkowe(int liczby[], int ile, int predkosc) {
	int save;
	bool zmiana = true;
	while (zmiana) {
		zmiana = false;
		for (int i = 0; i < ile - 1; i++) {
			porownania++;
			czerwone[0] = i;
			czerwone[1] = i + 1;
			Sleep(predkosc);
			czerwone[0] = -1;
			czerwone[1] = -1;
			if (liczby[i] > liczby[i + 1]) {
				save = liczby[i];
				liczby[i] = liczby[i + 1];
				liczby[i + 1] = save;
				zamiany++;
				Sleep(predkosc);
				zmiana = true;
			}
		}
		ile--;
	}
}
void sortowanie_wybor(int liczby[], int ile, int predkosc) {
	int min, save, numer, koniec = ile - 1;
	bool lepsza;
	for (int j = 0; j < koniec; j++) {
		czerwone[0] = j;
		Sleep(predkosc);
		czerwone[0] = -1;
		min = liczby[j];
		numer = j;
		lepsza = false;
		for (int i = j + 1; i < ile; i++) {
			porownania++;
			czerwone[0] = i;
			Sleep(predkosc);
			czerwone[0] = -1;
			if (min > liczby[i]) {
				czerwone[0] = i;
				Sleep(predkosc);
				czerwone[0] = -1;
				min = liczby[i];
				numer = i;
				lepsza = true;
			}
		}
		if (lepsza) {
			save = liczby[j];
			liczby[j] = liczby[numer];
			liczby[numer] = save;
			zamiany++;
			Sleep(predkosc);
		}
	}
}
void sortowanie_wstawianie(int liczby[], int ile, int predkosc) {
	int save;
	for (int i = 0; i < ile - 1; i++) {
		for (int j = i; j >= 0; j--) {
			porownania++;
			czerwone[0] = j;
			czerwone[1] = j + 1;
			Sleep(predkosc);
			czerwone[0] = -1;
			czerwone[1] = -1;
			if (liczby[j] > liczby[j + 1]) {
				save = liczby[j];
				liczby[j] = liczby[j + 1];
				liczby[j + 1] = save;
				zamiany++;
				Sleep(predkosc);
			}
			else {
				j = 0;
			}
		}
	}
}
void sortowanie_scalanie(int liczby[], int p, int k, int predkosc) {
	if (p < k - 1) {
		int s = (k + p) / 2, prawa, licznik = 0, lewa;
		sortowanie_scalanie(liczby, p, s, predkosc);
		sortowanie_scalanie(liczby, s, k, predkosc);
		int* pomoc = new int[k - p];
		lewa = p;
		prawa = s;
		while (lewa < s && prawa < k) {
			porownania++;
			czerwone[0] = lewa;
			czerwone[1] = prawa;
			Sleep(predkosc);
			czerwone[0] = -1;
			czerwone[1] = -1;
			if (liczby[lewa] > liczby[prawa]) {
				pomoc[licznik] = liczby[prawa];
				prawa++;
			}
			else {
				pomoc[licznik] = liczby[lewa];
				lewa++;
			}
			licznik++;
		}
		while (lewa < s) {
			czerwone[0] = lewa;
			Sleep(predkosc);
			czerwone[0] = -1;
			pomoc[licznik] = liczby[lewa];
			lewa++;
			licznik++;
		}
		for (int i = 0; i < licznik; i++) {
			liczby[p + i] = pomoc[i];
			Sleep(predkosc);
		}
	}
}
void sortowanie_szybkie(int liczby[], int p, int k, int predkosc) {
	if (p < k) {
		czerwone[0] = k;
		Sleep(predkosc);
		czerwone[0] = -1;
		int pwot = liczby[k], save, zmiana = p;
		for (int i = p; i < k; i++) {
			porownania++;
			czerwone[0] = i;
			Sleep(predkosc);
			czerwone[0] = -1;
			if (liczby[i] < pwot) {
				save = liczby[i];
				liczby[i] = liczby[zmiana];
				liczby[zmiana] = save;
				zamiany++;
				Sleep(predkosc);
				zmiana++;
			}
		}
		liczby[k] = liczby[zmiana];
		liczby[zmiana] = pwot;
		zamiany++;
		Sleep(predkosc);
		sortowanie_szybkie(liczby, p, zmiana - 1, predkosc);
		sortowanie_szybkie(liczby, zmiana + 1, k, predkosc);
	}
}
void sortowanie_kubelkowe(int liczby[], int ile, int predkosc) {
	int min = liczby[0], max = liczby[0], rozmiar_kubelkow, licznik = 0;
	for (int i = 1; i < ile; i++) {
		porownania++;
		czerwone[0] = i;
		Sleep(predkosc);
		czerwone[0] = -1;
		if (min > liczby[i]) {
			czerwone[0] = i;
			Sleep(predkosc);
			czerwone[0] = -1;
			min = liczby[i];
		}
		porownania++;
		czerwone[0] = i;
		Sleep(predkosc);
		czerwone[0] = -1;
		if (max < liczby[i]) {
			czerwone[0] = i;
			Sleep(predkosc);
			czerwone[0] = -1;
			max = liczby[i];
		}
	}
	rozmiar_kubelkow = max - min + 1;
	int* kubelki = new int[rozmiar_kubelkow];
	for (int i = 0; i < rozmiar_kubelkow; i++) {
		kubelki[i] = 0;
	}
	for (int i = 0; i < ile; i++) {
		czerwone[0] = i;
		Sleep(predkosc);
		czerwone[0] = -1;
		kubelki[liczby[i] - min]++;
	}
	for (int i = 0; i < rozmiar_kubelkow; i++) {
		while (kubelki[i] > 0) {
			liczby[licznik] = i + min;
			zamiany++;
			Sleep(predkosc);
			kubelki[i]--;
			licznik++;
		}
	}
}
void sortowanie_poprzez_kopcowanie(int liczby[], int ile, int predkosc) {
	int save;
	for (int i = ile / 2 - 1; i >= 0; i--) {
		sprawdzenie_poprawnosci_kopca(liczby, ile, i, predkosc);
	}
	for (int i = ile - 1; i > 0; i--) {
		save = liczby[0];
		liczby[0] = liczby[i];
		liczby[i] = save;
		zamiany++;
		Sleep(predkosc);
		ile--;
		sprawdzenie_poprawnosci_kopca(liczby, ile, 0, predkosc);
	}
}
void sprawdzenie_poprawnosci_kopca(int liczby[], int ile, int i, int predkosc) {
	int save, lewy_rodzic = i * 2 + 1, prawy_rodzic = i * 2 + 2;
	if (prawy_rodzic < ile) {
		porownania++;
		czerwone[0] = prawy_rodzic;
		czerwone[1] = lewy_rodzic;
		Sleep(predkosc);
		czerwone[0] = -1;
		czerwone[1] = -1;
		if (liczby[prawy_rodzic] > liczby[lewy_rodzic]) {
			porownania++;
			czerwone[0] = prawy_rodzic;
			czerwone[1] = i;
			Sleep(predkosc);
			czerwone[0] = -1;
			czerwone[1] = -1;
			if (liczby[prawy_rodzic] > liczby[i]) {
				save = liczby[prawy_rodzic];
				liczby[prawy_rodzic] = liczby[i];
				liczby[i] = save;
				zamiany++;
				Sleep(predkosc);
				sprawdzenie_poprawnosci_kopca(liczby, ile, prawy_rodzic, predkosc);
			}
		}
		else {
			porownania++;
			czerwone[0] = lewy_rodzic;
			czerwone[1] = i;
			Sleep(predkosc);
			czerwone[0] = -1;
			czerwone[1] = -1;
			if (liczby[lewy_rodzic] > liczby[i]) {
				save = liczby[lewy_rodzic];
				liczby[lewy_rodzic] = liczby[i];
				liczby[i] = save;
				zamiany++;
				Sleep(predkosc);
				sprawdzenie_poprawnosci_kopca(liczby, ile, lewy_rodzic, predkosc);
			}
		}
	}
	else {
		if (lewy_rodzic < ile) {
			porownania++;
			czerwone[0] = lewy_rodzic;
			czerwone[1] = i;
			Sleep(predkosc);
			czerwone[0] = -1;
			czerwone[1] = -1;
			if (liczby[lewy_rodzic] > liczby[i]) {
				save = liczby[lewy_rodzic];
				liczby[lewy_rodzic] = liczby[i];
				liczby[i] = save;
				zamiany++;
				Sleep(predkosc);
				sprawdzenie_poprawnosci_kopca(liczby, ile, lewy_rodzic, predkosc);
			}
		}
	}
}
void sortowanie_binarne(int liczby[], int ile, int predkosc) {
	int* pomoc = new int[ile];
	bool* bity = new bool[ile];
	czerwone[0] = 0;
	Sleep(predkosc);
	czerwone[0] = -1;
	int max = liczby[0], licznik;
	for (int i = 1; i < ile; i++) {
		porownania++;
		czerwone[0] = i;
		Sleep(predkosc);
		czerwone[0] = -1;
		if (max < liczby[i]) {
			czerwone[0] = i;
			Sleep(predkosc);
			czerwone[0] = -1;
			max = liczby[i];
		}
	}
	int ostatni_bit = log2(max);
	for (int i = 0; i <= ostatni_bit; i++) {
		for (int j = 0; j < ile; j++) {
			czerwone[0] = j;
			Sleep(predkosc);
			czerwone[0] = -1;
			pomoc[j] = liczby[j];
		}
		for (int j = 0; j < ile; j++) {
			bity[j] = pomoc[j] & (1 << i);
		}
		licznik = 0;
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < ile; k++) {
				porownania++;
				if (bity[k] == j) {
					Sleep(predkosc);
					liczby[licznik] = pomoc[k];
					licznik++;
				}
			}
		}
	}
}
void sortowanie_muszelkowe(int liczby[], int ile, int predkosc) {
	int save;
	for (int dystans = ile / 2; dystans > 0; dystans /= 2) {
		for (int przesuniecie = 0; przesuniecie + dystans < ile; przesuniecie++) {
			for (int j = przesuniecie; j >= 0; j = j - dystans) {
				porownania++;
				czerwone[0] = j;
				czerwone[1] = j + dystans;
				Sleep(predkosc);
				czerwone[0] = -1;
				czerwone[1] = -1;
				if (liczby[j] > liczby[j + dystans]) {
					save = liczby[j];
					liczby[j] = liczby[j + dystans];
					liczby[j + dystans] = save;
					zamiany++;
					Sleep(predkosc);
				}
				else {
					j = 0;
				}
			}
		}
	}
}
void sortowanie_koktailem(int liczby[], int ile, int predkosc) {
	int min = 0, max = ile - 1, save;
	while (min < max) {
		for (int i = min; i < max; i++) {
			porownania++;
			czerwone[0] = i;
			czerwone[1] = i + 1;
			Sleep(predkosc);
			czerwone[0] = -1;
			czerwone[1] = -1;
			if (liczby[i] > liczby[i + 1]) {
				save = liczby[i];
				liczby[i] = liczby[i + 1];
				liczby[i + 1] = save;
				zamiany++;
				Sleep(predkosc);
			}
		}
		max--;
		for (int i = max; i > min; i--) {
			porownania++;
			czerwone[0] = i;
			czerwone[1] = i - 1;
			Sleep(predkosc);
			czerwone[0] = -1;
			czerwone[1] = -1;
			if (liczby[i] < liczby[i - 1]) {
				save = liczby[i];
				liczby[i] = liczby[i - 1];
				liczby[i - 1] = save;
				zamiany++;
				Sleep(predkosc);
			}
		}
		min++;
	}
}
void sortowanie_szybkie_odwrotne(int liczby[], int p, int k) {
	if (p < k) {
		int pwot = liczby[k], save, zmiana = p;
		for (int i = p; i < k; i++) {
			if (liczby[i] > pwot) {
				save = liczby[i];
				liczby[i] = liczby[zmiana];
				liczby[zmiana] = save;
				zmiana++;
			}
		}
		liczby[k] = liczby[zmiana];
		liczby[zmiana] = pwot;
		sortowanie_szybkie_odwrotne(liczby, p, zmiana - 1);
		sortowanie_szybkie_odwrotne(liczby, zmiana + 1, k);
	}
}
void sortowanie_zwariowane(int tab[], int rozmiar, int predkosc)
{
	srand(time(0));
	int i = 0, posortowano = 0, pomoc, los1, los2;
	while (posortowano == 0)
	{
		czerwone[0] = i;
		czerwone[1] = i + 1;
		Sleep(predkosc);
		czerwone[0] = -1;
		czerwone[1] = -1;
		porownania++;
		if (tab[i] > tab[i + 1])
		{
			for (int j = 0; j < rozmiar * 3; j++)
			{
				los1 = rand() % rozmiar;
				los2 = rand() % rozmiar;
				pomoc = tab[los1];
				tab[los1] = tab[los2];
				tab[los2] = pomoc;
				Sleep(predkosc);
				zamiany++;
			}
			i = 0;
		}
		else
		{
			i++;
			if (i == rozmiar - 1)
				posortowano = 1;
		}
	}
}
void sortowanie_bk(int tablica[], int dlugosc, int predkosc) {
	int zapasowa;
	for (int i = 0; i < dlugosc; i++) {
		for (int j = 0; j < dlugosc; j++) {
			czerwone[0] = i;
			czerwone[1] = j;
			Sleep(predkosc);
			czerwone[0] = -1;
			czerwone[1] = -1;
			porownania++;
			if (tablica[j] > tablica[i]) {
				Sleep(predkosc);
				zamiany++;
				zapasowa = tablica[j];
				tablica[j] = tablica[i];
				tablica[i] = zapasowa;
			}
		}
	}
}
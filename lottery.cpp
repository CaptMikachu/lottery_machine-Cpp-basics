


#include<iostream>
#include<algorithm>

using namespace std;



void prizes();

int menu();

void comparer(int ticket[], int sizeint, int ticketBonus[], int size2);

void randomizer();





int main() {

	setlocale(LC_ALL, "fi_FI");



	cout << "Tervetuloa helppoon lottoon, voiton saaminen on helppoa!" << endl << endl;

	while (true)
	{
		switch (menu()) {


		case 0:

			cout << "--------------------------------------------------------------------------------\n\n"
				<< "Tervetuloa uudestaan.";

			return 0;
			break;


		case 1:

			prizes();
			// cout << "\n\ntest 1\n\n";

			cout << "\n--------------------------------------------------------------------------------\n\n";
			break;


		case 2:

			//cout << "\n\ntest 2\n\n";
			randomizer();;

			cout << "\n--------------------------------------------------------------------------------\n\n";
			break;


		case 3:

			//cout << "\n\ntest 3\n\n";

			cout << "\n--------------------------------------------------------------------------------\n\n";
			break;

		}
	}




	return 0;
}



// -------------------------------------------------------------------------------------------------------------------


int menu() {

	int action = 0;

	cout << "Mitä haluaisit tehdä? (Syöta numero 1-4)" << endl
		<< "1: Katso palkintosummat" << endl
		<< "2: Pelaa koneen arpomalla rivillä" << endl
		<< "3: Pelaa omilla numeroilla" << endl
		<< "4: Lopeta pelaaminen" << endl;

	cin >> action;




	if (action > 0 && action < 5)
	{

		switch (action)
		{

		case 1:
			return 1;

		case 2:
			return 2;

		case 3:
			return 3;

		case 4:
			return 0;

		}
	}

	else
	{
		cin.clear(); //clear bad input flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
		cout << "\nVirheellinen syöte!\n\n";

	}


	return 0;
}

// -------------------------------------------------------------------------------------------------------------------

void prizes() {

	cout << endl
		<< "Numeroita + lisänumeroita oikein    Voittosumma" << endl
		<< "7                                   10 000 000 e" << endl
		<< "6+1                                 1 000 000 e" << endl
		<< "6                                   100 000 e" << endl
		<< "5                                   2000 e" << endl
		<< "4                                   50 e" << endl
		<< "3+1                                 10 e" << endl
		<< "2                                   2 e" << endl
		<< "1                                   1 e";

}





// -------------------------------------------------------------------------------------------------------------------

void randomizer() {

	//int ticket[7] = { 2, 3, 10, 26, 29, 32, 37 };
	//int ticketBonus[3] = { 11, 17, 27 };

	int ticket[7] = { 0 };
	int ticketBonus[3] = { 0 };
	int random;

	// Käytetään aikaa randomisoinnin seed-arvona
	srand((unsigned)time(NULL));



	for (int i = 0; i < 7; i++) // Luodaan ensimmäiset 7 numero arrayhin
	{
		// Luodaan random-numero seedin perusteella
		random = 1 + rand() % 40;


		// Tarkistetaan onko numero jo arrayssa
		int n = sizeof(ticket) / sizeof(*ticket);

		bool exists = find(ticket, ticket + n, random) != ticket + n;
		if (exists) { // Jos numero löytyy arraystä, pysytään samassa solussa ja arvotaan uusi
			i--;
		}
		else {
			ticket[i] = random; // Jos ei löydy jo arraystä, asetetaan se sinne
		}


	}



	for (int i = 0; i < 3; i++) // Luodaan bonusnumerot
	{
		// Luodaan random-numero seedin perusteella
		random = 1 + (rand() % 40); // eka numero on rangen alku, vika on rangen loppu

		// Tarkistetaan onko numero jo perusnumeroissa mukana

		int n = sizeof(ticket) / sizeof(*ticket);

		bool exists = find(ticket, ticket + n, random) != ticket + n;
		if (exists) {
			i--; // Jos on jo perusnumeroissa, yritetään uudestaan
		}
		else {


			int n = sizeof(ticketBonus) / sizeof(*ticketBonus); // Tarkistetaan onko jo bonusnumeroissa

			bool exists = find(ticketBonus, ticketBonus + n, random) != ticketBonus + n;
			if (exists) {
				i--; // Jos on jo BONUSnumeroissa, yritetään uudestaan
			}
			else {

				ticketBonus[i] = random;
			}
		}


	}


// Järjestetään norminumerot pienimmästä suurimpaan
	size_t len = sizeof(ticket) / sizeof(ticket[0]);
	// Käytetään sorttia
	sort(ticket, ticket + len);


	// Järjestetään bonusnumerot pienimmästä suurimpaan
	size_t lenB = sizeof(ticketBonus) / sizeof(ticketBonus[0]);
	// Käytetään sorttia
	sort(ticketBonus, ticketBonus + lenB);



	cout << "\nLottorivisi on: ";

	for (int i = 0; i < 7; i++)
	{
		cout << ticket[i] << ", ";
	}

	cout << "ja bonusnumerot " << ticketBonus[0] << ", " << ticketBonus[1] << ", " << ticketBonus[2] << "." << endl << endl;



	comparer(ticket, 7, ticketBonus, 3); // Kutsutaan vertailija-funktiota


}



// -------------------------------------------------------------------------------------------------------------------


void comparer(int ticket[], int sizeint, int ticketBonus[], int size2) {



	int win7 = 10000000,
		win61 = 1000000,
		win6 = 100000,
		win5 = 2000,
		win4 = 50,
		win31 = 10,
		win2 = 2,
		win1 = 1,
		winSum = 0;

	int numbersWin[7] = { 2, 3, 10, 26, 29, 32, 37 };
	int bonusWin[3] = { 11, 17, 27 };

	int hits = 0;
	int hitsB = 0;

	// Tarkistetaan onko numero jo arrayssa
	int n = sizeof(numbersWin) / sizeof(*numbersWin);



	for (int i = 0; i < 7; i++)
	{
		bool exists = find(numbersWin, numbersWin + n, ticket[i]) != numbersWin + n;
		if (exists) { // Jos numero löytyy arraystä, lisätään yksi piste
			hits += 1;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		bool exists = find(bonusWin, bonusWin + n, ticketBonus[i]) != bonusWin + n;
		if (exists) { // Jos numero löytyy arraystä, lisätään yksi piste
			hitsB += 1;
		}
	}


	cout << "Ja voittonumerot ovat... ";

	for (int i = 0; i < 7; i++)
	{
		cout << numbersWin[i] << ", ";
	}

	cout << "ja bonusnumerot " << bonusWin[0] << ", " << bonusWin[1] << ", " << bonusWin[2] << ".\n\n";



	if (hitsB != 0)
	{

		cout << "Sait " << hits << "+" << hitsB << " oikein!" << endl;
	}
	else
	{
		cout << "Sait " << hits << " oikein!" << endl;
	}

	if (hits > 0)
	{


		if (hits == 1)
		{
			winSum = win1;
		}


		else if (hits == 2)
		{
			winSum = win2;
		}

		else if (hits == 3 && hitsB == 1)
		{
			winSum = win31;
		}

		else if (hits == 4)
		{
			winSum = win4;
		}

		else if (hits == 5)
		{
			winSum = win5;
		}

		else if (hits == 6 && hitsB == 0)
		{
			winSum = win6;
		}

		else if (hits == 6 && hitsB == 1)
		{
			winSum = win61;
		}

		else if (hits == 7)
		{
			winSum = win7;
		}


		cout << "Olet voittanut " << winSum << " euroa!" << endl;


	}

	else
	{
		cout << "Ei voittoa tällä kertaa." << endl;
	}


	// cout << "\n\ntest-comparer\n\n";

}
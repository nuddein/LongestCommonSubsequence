#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ADD 0
#define SKIPX 1
#define SKIPY 2
#define DEFSKIP 3
/*
@brief iki degisken arasindan buyuk olanini donduren fonksiyon

@param ilk degisken
@param ikinci degisken
@return buyuk olanini dondurme 
*/
int max(int a, int b) {
    if (a>b){
    	return a;
	}
	else {
		return b;
	}
}
/*
@brief benzersiz kelimeyi bastiran fonksiyon (ayni kelimenin iki kez bastirilmasini onler)

@param lcs dizisi
@param benzersiz kelimeyi temsil eden dizi
@param benzersizlik kontrolu icin sayac
@return
*/

void printUniqueLCS(char lcsAlgo[], char** uniqueLCS, int* uniqueCount) {
    // Check if the LCS has already been printed
    int k;
    for (k = 0; k < *uniqueCount; k++) {
        if (strcmp(lcsAlgo, uniqueLCS[k]) == 0) {
            return;  // Zaten bastirilmishsa, tekrar bastirimadan return ishlemi
        }
    }
    // Eger bastirilmamishsa bastirir
    strcpy(uniqueLCS[(*uniqueCount)++], lcsAlgo);
    printf("LCS: %s\n", lcsAlgo);
}
/*
@brief LCS islemlerini (Add,skipY,skipX) bulan ve matrix'leri ekrana bastirlan fonksiyon

@param ilk kelime dizisi
@param ikinci kelime dizisi
@param LCS tablosu(matrixi)
@param tablonun satir sayisi
@param tablonun sutun sayisi

@return tabloyu donduren islem
*/

	int** selectionTable(char S1[], char S2[], int** LCS_table, int satir, int sutun)
{
	printf ("Dinamik Matrisin ilk hali: \n");
    printMatrix(S1,S2,satir, sutun, LCS_table);
    printf ("\n");
    int i, j, **table = NULL;
    table = (int**)calloc(satir + 1, sizeof(int*));

    for (i = 0; i <= satir; i++) {
        table[i] = (int*)calloc(sutun + 1, sizeof(int));
    }

    for (i = 1; i <= satir; i++) {
        for (j = 1; j <= sutun; j++) {
            if (S1[i - 1] == S2[j - 1]) {
                table[i][j] = ADD;
            } else {
                if (LCS_table[i - 1][j] > LCS_table[i][j - 1]) {
                    table[i][j] = SKIPX;
                } else if (LCS_table[i - 1][j] < LCS_table[i][j - 1]) {
                    table[i][j] = SKIPY;
                } else {
                    table[i][j] = DEFSKIP;		//skipX ile skipY ayni oldugunda hangisinin oldugu bilinmedigi ichin
                }
            }
            
    		
        }
        printf("%d. satir ichin En uzun ifadenin boyutu: %d\n\n",i, LCS_table[i][sutun]);
       
         printf("%d. satir icin LCSmatris :\n", i);
        printMatrix(S1,S2,i, sutun, LCS_table);
        printf("\n\n");
        
        printf("%d. satir icin Selection Matris :\n", i);
        printMatrix(S1,S2,i, sutun, table);
        printf ("\n\n");
    }
    

    return table;
}
/*
@brief girilen iki kelimeden LCS islemine gore en buyuk sonuclari bulan ve ekrana bastiran fonksiyon

@param ilk kelime dizisi
@param ikinci kelime dizi
@param ilk diziyi kontrol etmek icin sayac
@param ikinci diziyi kontrol etnek icin sayac
@param kelimeyi tutan dizi
@param kelimenin indeksi
@param LCS tablosu(matrix'i)
@param benzersiz kelimeyi tutan tablo
@benzersizlik kontrolu 

@return
*/

void printAllLCS(char S1[], char S2[], int boyut1, int boyut2, char lcsAlgo[], int index, int** LCS_table, char** uniqueLCS, int* uniqueCount) {
    if (boyut1 == 0 || boyut2 == 0) {
        printUniqueLCS(lcsAlgo, uniqueLCS, uniqueCount);
        return;
    }

    if (S1[boyut1 - 1] == S2[boyut2 - 1]) {
        lcsAlgo[index - 1] = S1[boyut1 - 1];
        printAllLCS(S1, S2, boyut1 - 1, boyut2 - 1, lcsAlgo, index - 1, LCS_table, uniqueLCS, uniqueCount);
    } else {
        if (LCS_table[boyut1 - 1][boyut2] >= LCS_table[boyut1][boyut2 - 1])
            printAllLCS(S1, S2, boyut1 - 1, boyut2, lcsAlgo, index, LCS_table, uniqueLCS, uniqueCount);
        if (LCS_table[boyut1][boyut2 - 1] >= LCS_table[boyut1 - 1][boyut2])
            printAllLCS(S1, S2, boyut1, boyut2 - 1, lcsAlgo, index, LCS_table, uniqueLCS, uniqueCount);
    }
}

/*
@brief LCS islemini yapan fonksiyon

@param ilk kelime dizisi
@param ikinci kelime dizisi
@param ilk kelime boyutu
@param ikinci kelime boyutu
@param LCS boyutu(degeri)

@return LCS tablosu
*/

int** lcsAlgo(char S1[], char S2[], int m, int n, int* lcsValue) {
    int** LCS_table;

    // LCS_table tablosu ichin dinamik bellek ayrimi
    LCS_table = (int**)malloc((m + 1) * sizeof(int*));
    int i;
    for (i = 0; i <= m; i++) {
        LCS_table[i] = (int*)malloc((n + 1) * sizeof(int));
    }

    // LCS tablosunu Initialize etme ishlemi
    for (i = 0; i <= m; i++) {
        int j;
        for (j = 0; j <= n; j++) {
            LCS_table[i][j] = 0;
        
        }
    }
    
    //  LCS_table tablosunun olushturulmasi
    for (i = 1; i <= m; i++) {
        int j;
        for (j = 1; j <= n; j++) {
            if (S1[i - 1] == S2[j - 1]) {
                LCS_table[i][j] = 1 + LCS_table[i - 1][j - 1];
            } else {
                LCS_table[i][j] = max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
            }
        }
    }
    // uniqueLCS ichin dinamik bellek ayrimi
    char** uniqueLCS = (char**)malloc(100 * sizeof(char*));
    for (i = 0; i < 100; i++) {
        uniqueLCS[i] = (char*)malloc((m + n + 1) * sizeof(char));
    }

    // Tum LCS'leri bulma ve Bastirma
    int index = LCS_table[m][n];
    char lcsAlgo[index + 1];
    lcsAlgo[index] = '\0';
    int uniqueCount = 0;

    printAllLCS(S1, S2, m, n, lcsAlgo, index, LCS_table, uniqueLCS, &uniqueCount);

// Set the value for lcsValue
    *lcsValue = index;

    return LCS_table;
}

/*
@brief matrix'leri bastiran fonksiyon

@param matrixin satir boyutu
@param matrixin sutun boyutu
@param  LCS dizi matrix'i

@return
*/
void printMatrix(char S1[], char S2[], int m, int n, int** LCS_table) {
    // Ilk satir baslik olarak kelime2'nin elemanlarini ekle
    printf("    ");
    int j;
    for (j = 0; j < n; j++) {
        printf("%c ", S2[j]);
    }
    printf("\n");
	int i;
    for ( i = 0; i <= m; i++) {
        if (i == 0) {
            printf("  ");
        } else {
            printf("%c ", S1[i - 1]);
        }

        for ( j = 0; j <= n; j++) {
            printf("%d ", LCS_table[i][j]);
        }
        printf("\n");
    }
}


/*
@brief algoritmayi calistiran ana fonksiyon

@param Arr array that contains the values to be sorted
@param n array lenght
@param orderType determines the type of ording, if 0 Ascending, if 1 Descending.

@return
*/

int main() {
    char kelime1[50];					// kullanicidan alinacak ilk kelime
    char kelime2[50];					//kullanicidan alinacak ikinci kelime

    printf("Ilk kelimeyi giriniz: ");	
    scanf("%s", kelime1);				//scanf ile kullanicidan ilk kelimenin alinmasi
    scanf("%*[^\n]%*c");
    printf ("\n");

    printf("Ikinci kelimeyi giriniz: ");
    scanf("%s", kelime2);				//scanf ile kullanicidan ikinci kelimenin alinmasi
    scanf("%*[^\n]%*c");
    printf ("\n");

    int boyut1 = strlen(kelime1);		// ilk kelimenin boyutunu strlen fonskiyonuyla hesaplanip boyut1 degiskenine atanmasi
    int boyut2 = strlen(kelime2);		// ikinci kelimenin boyutunun strlen fonskiyonuyla hesaplanip boyu2 degiskenine atanmasi

    int lcsValue;						// iki kelimenin ortak en buyuk alt dizi(veya dizilerinin) boyutu
    int** LCS_table = lcsAlgo(kelime1, kelime2, boyut1, boyut2, &lcsValue);		//boyutun LCS_table'dan donen degere gore atanmasi

    printf("En uzun ifadenin boyutu:: %d\n", lcsValue);											// boyutu ekrana bastirma islemi	
	printf ("\n");
	printf ("Selection Matris Ishlemleri: \n");
	printf ("ADD ishlemi = 0  SKIPX ishlemi = 1  SKIPY ishlemi = 2 DEFAULT SKIP ishlemi = 3 \n\n");
     selectionTable (kelime1, kelime2,LCS_table, boyut1, boyut2);				//  matrisleri ekrana bastirma islemi

    return 0;
}


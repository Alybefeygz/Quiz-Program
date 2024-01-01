#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Soru 
{
    char soruMetni[100];
};

struct Cevap 
{
    char cevapMetni[100];
};

void dosyadanSatirlariOku(const char *dosyaAdi, struct Soru sorular[], struct Cevap cevaplar[], int *soruSayisi);
void kaydetVerilenCevaplar(const char *dosyaAdi, const struct Cevap kullaniciCevaplar[], int soruSayisi);
int cevaplariKarsilastirma(struct Soru sorular[], struct Cevap cevaplar[], struct Cevap kullaniciCevaplar[], int soruSayisi);

int main() 
{
	
    const char *soruDosyaAdi = "Sorular.txt";
    const char *cevapDosyaAdi = "Cevaplar.txt";

    struct Soru sorular[100];
    struct Cevap cevaplar[100]; 
    struct Cevap kullaniciCevaplar[100]; 
    int soruSayisi = 0;

    dosyadanSatirlariOku(soruDosyaAdi, sorular, cevaplar, &soruSayisi);

    int topPuan = cevaplariKarsilastirma(sorular, cevaplar, kullaniciCevaplar, soruSayisi);
    printf("Toplam Puan: %d\n", topPuan);

    return 0;
    
}

void dosyadanSatirlariOku(const char *dosyaAdi, struct Soru sorular[], struct Cevap cevaplar[], int *soruSayisi) 
{
	
    FILE *dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) 
	{
		
        perror("Dosya açma hatasý");
        exit(EXIT_FAILURE);
        
    }
    
	int i;
	
    for (i = 0; fscanf(dosya, "%99[^\n]\n", sorular[i].soruMetni) != EOF; i++) 
	{
		
        (*soruSayisi)++;
        
    }

    fclose(dosya);

    dosya = fopen("Cevaplar.txt", "r");
    
    if (dosya == NULL) 
	{
		
        perror("Dosya açma hatasý");
        exit(EXIT_FAILURE);
        
    }
    
	int j;
    for (j = 0; fscanf(dosya, "%99[^\n]\n", cevaplar[j].cevapMetni) != EOF; j++) 
	{
        
    }

    fclose(dosya);
}

void kaydetVerilenCevaplar(const char *dosyaAdi, const struct Cevap kullaniciCevaplar[], int soruSayisi) 
{
	
    FILE *dosya = fopen(dosyaAdi, "w");
    
    if (dosya == NULL) 
	{
		
        perror("Dosya açma hatasý");
        exit(EXIT_FAILURE);
        
    }
    
	int k;
    for (k = 0; k < soruSayisi; k++) 
	{
		
        fprintf(dosya, "%s\n", kullaniciCevaplar[k].cevapMetni);
        
    }

    fclose(dosya);
    
}

int cevaplariKarsilastirma(struct Soru sorular[], struct Cevap cevaplar[], struct Cevap kullaniciCevaplar[], int soruSayisi) 
{
	
    int topPuan = 0;
	int f;
    for (f = 0; f < soruSayisi; f++) 
	{
		
        printf("%s", sorular[f].soruMetni);

        fgets(kullaniciCevaplar[f].cevapMetni, sizeof(kullaniciCevaplar[f].cevapMetni), stdin);
        kullaniciCevaplar[f].cevapMetni[strcspn(kullaniciCevaplar[f].cevapMetni, "\n")] = '\0';

        if (strcmp(kullaniciCevaplar[f].cevapMetni, cevaplar[f].cevapMetni) == 0) 
		{
			
            printf("Doðru cevap verdiniz.\n");
            topPuan += 50;
            
        } 
        
		else 
		{
			
            printf("Yanlýþ cevap verdiniz.\n");
            
        }
        
    }

    kaydetVerilenCevaplar("verilenCevaplar.txt", kullaniciCevaplar, soruSayisi);

    return topPuan;
}

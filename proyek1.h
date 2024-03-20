#define MAX_KARYAWAN 100
#define MAX_PANJANG_NAMA 50


typedef struct {
    char nama[MAX_PANJANG_NAMA];
    
    long int gaji;       // Gaji pokok
    long int tunjanganJabatan;
    long int pajak;      // Pajak
    long int gajiBersih; // Gaji bersih
    int jabatan;
} Karyawan;

// Function Prototype
void tambahKaryawan(Karyawan karyawan[], int *jumlahKaryawan);
long int hitungPajak(long int gajiKotorBulanan);
void buatSlipGaji(Karyawan karyawan[], int jumlahKaryawan);
long int tunjanganJabatan(int input);
void cetakDataKaryawan(Karyawan karyawan[], int jumlahKaryawan);
void ubahDataKaryawan(Karyawan karyawan[], int *jumlahKaryawan);
void loadDataKaryawan(Karyawan karyawan[], int *jumlahKaryawan);
void simpanDataKaryawan(Karyawan karyawan[], int jumlahKaryawan);
void hapusSpasiBelakang(char *str);
void sortKaryawan(Karyawan karyawan[], int jumlahKaryawan, int mode, int type);
void searchNama(Karyawan karyawan[], int jumlahKaryawan, const char* key);

// Print instruksi pemakaian program
void help(){
	printf("\033[1;36m");
    printf("\n=====================================================================================\n");
    printf("|  			Papan Bantuan Sistem Manajemen Gaji Bulanan  		    |\n");
    printf("=====================================================================================\n");
    printf("\033[0m");
    printf("| Program ini berfungsi untuk membantu mengatur data gaji dari karyawan.	    |\n");
    printf("| Untuk memasukkan data karyawan baru, gunakan opsi 1.			  	    |\n");
    printf("| Untuk mencetak slip gaji yang akan dicetak pada file slipGaji.txt, gunakan opsi 2.|\n");
    printf("| Untuk melihat data-data yang sudah ada, gunakan opsi 3.			    |\n");
    printf("| Untuk mencari data dari sebuah karyawan, gunakan opsi 4.                          |\n");
    printf("| Untuk mengubah data dari sebuah karyawan, gunakan opsi 5.			    |\n");
    printf("+-----------------------------------------------------------------------------------+\n\n");
}

// Menambahkan karyawan ke dalam database
void tambahKaryawan(Karyawan karyawan[], int *jumlahKaryawan) {
    if (*jumlahKaryawan >= MAX_KARYAWAN) {
        printf("Jumlah karyawan maksimum tercapai.\n");
        return;
    }

    Karyawan karyawanBaru;
    printf("Masukkan nama pekerja	: ");
    scanf(" %[^\n]s", &karyawanBaru.nama);
	hapusSpasiBelakang(karyawanBaru.nama);        

    do{
		printf("List jabatan		: \n");
		printf("1. Direktur\n");
		printf("2. Manajer\n");
		printf("3. Sekretaris\n");
		printf("4. Staf\n");
		printf("Pilih jabatan (masukkan angka 1-4): ");
		scanf("%d", &karyawanBaru.jabatan);
	} while (karyawanBaru.jabatan < 1 && karyawanBaru.jabatan > 4);
    printf("Masukkan gaji pokok	: ");
    scanf("%ld", &karyawanBaru.gaji);

    // Hitung gaji
    karyawanBaru.tunjanganJabatan = tunjanganJabatan(karyawanBaru.jabatan);
    karyawanBaru.pajak = hitungPajak(karyawanBaru.gaji+karyawanBaru.tunjanganJabatan);
    karyawanBaru.gajiBersih = karyawanBaru.gaji + karyawanBaru.tunjanganJabatan - karyawanBaru.pajak; // Menghitung gaji setelah dipotong oleh pajak
    karyawan[*jumlahKaryawan] = karyawanBaru;
    (*jumlahKaryawan)++;
    printf("Karyawan berhasil ditambahkan.\n");
}

// Function untuk menghitung pajak dari gaji bulanan
long int hitungPajak(long int gajiKotorBulanan) {
    long int pajak = 0.0;

    if (gajiKotorBulanan <= 4166666) {
        pajak = gajiKotorBulanan * 0.05;
    } else if (gajiKotorBulanan <= 20833333) {
        pajak = (4166666 * 0.05) + ((gajiKotorBulanan - 4166666) * 0.15);
    } else if (gajiKotorBulanan <= 41666666) {
        pajak = (4166666 * 0.05) + (16666667 * 0.15) + ((gajiKotorBulanan - 20833333) * 0.25);
    } else {
        pajak = (4166666 * 0.05) + (16666667 * 0.15) + (20833333 * 0.25) + ((gajiKotorBulanan - 41666666) * 0.30);
    }

    return pajak;
}

//Function untuk menghitung tunjangan dari jabatan
long int tunjanganJabatan(int input){
	switch (input){
		case 1:
			return 10000000;
			break;
		case 2:
			return 5000000;
			break;
		case 3:
			return 1700000;
			break;
		case 4:
			return 1500000;
			break;
		default:
			break;
	}
}

// Memberikan output string dari int jabatan dari struct Karyawan
const char * jabatanString(int input){
	switch (input){
		case 1:
			return "Direktur";
			break;
		case 2:
			return "Manajer";
			break;
		case 3:
			return "Sekretaris";
			break;
		case 4:
			return "Staf";
			break;
		default:
			break;
	}
}

// Pembuatan slip gaji yang akan disimpan di sebuah text file bernama "SlipGaji.txt"
void buatSlipGaji(Karyawan karyawan[], int jumlahKaryawan) {
	int i;
	FILE *file = fopen("SlipGaji.txt", "w");
    if (file != NULL) {
    	for (i = 0; i < jumlahKaryawan; i++) {
	        fprintf(file, "======================== Slip Gaji ========================\n");
	        fprintf(file, "Nama Karyawan	  : %s\n", karyawan[i].nama);
	        fprintf(file, "Jabatan		  : %s\n", jabatanString(karyawan[i].jabatan));
	        fprintf(file, "Gaji Kotor	  : Rp %ld\n", karyawan[i].gaji);
	        fprintf(file, "Tunjangan Jabatan : Rp %ld\n", tunjanganJabatan(karyawan[i].jabatan));
	        fprintf(file, "Pajak Dibayar	  : Rp %ld\n", karyawan[i].pajak); 
	        fprintf(file, "Gaji Bersih	  : Rp %ld\n", karyawan[i].gajiBersih);
	        fprintf(file, "===========================================================\n\n");
		}
		fclose(file);
    } else {
        printf("Gagal membuka file slipGaji.txt\n");
    }
}

// Print data karyawan di dalam console
void cetakDataKaryawan(Karyawan karyawan[], int jumlahKaryawan) {
    int i;
    printf("\033[1;32m");
    
    printf("=====================================================================================================================\n");
    printf("|%-25s | %-15s | %-15s | %-15s | %-15s | %-13s|\n", 
           "Nama", "Gaji Kotor", "Tunjangan Jabatan", "Pajak", "Gaji Bersih", "Jabatan");
    printf("=====================================================================================================================\n");
    printf("\033[0m"); 

    for (i = 0; i < jumlahKaryawan; i++) {
        printf("|%-25s | Rp %-12.ld | Rp %-14.ld | Rp %-12.ld | Rp %-12.ld | %-13s|\n", 
            karyawan[i].nama, karyawan[i].gaji, tunjanganJabatan(karyawan[i].jabatan), karyawan[i].pajak, karyawan[i].gajiBersih, jabatanString(karyawan[i].jabatan));
        printf("+--------------------------+-----------------+-------------------+-----------------+-----------------+--------------+\n");

    }
    printf("\n"); 
}

// Function untuk menghapus spasi belakang, ketika ada kesalahan saat load data dari text file.
void hapusSpasiBelakang(char *str) {
    int index, i;
    index = -1;
    i = 0;
    // Mencari indeks karakter terakhir yang bukan spasi
    while(str[i] != '\0') {
        if(str[i] != ' ') index = i;
        i++;
    }
    // Akhiri string setelah karakter terakhir yang bukan spasi
    str[index + 1] = '\0';
    
}

// Function untuk mencari data karyawan tertentu
void searchNama(Karyawan karyawan[], int jumlahKaryawan, const char* key) {
	int i, j;
    int found = 0;
    printf("\033[1;32m");
	printf("====================================================================================================================\n");
	printf("%-25s | %-15s | %-15s | %-15s | %-15s | %-13s\n", 
	       "Nama", "Gaji Kotor", "Tunjangan Jabatan", "Pajak", "Gaji Bersih", "Jabatan");
	printf("====================================================================================================================\n");
    printf("\033[0m");     
    for (i = 0; i < jumlahKaryawan; i++) {
        char nameCopy[MAX_PANJANG_NAMA];
        strcpy(nameCopy, karyawan[i].nama);

        // Mengubah kedua string agar jadi lower-case
        for(j = 0; nameCopy[j]; j++){
          nameCopy[j] = tolower(nameCopy[j]);
        }
        char keyCopy[strlen(key) + 1];
        strcpy(keyCopy, key);
        for(j = 0; keyCopy[j]; j++){
          keyCopy[j] = tolower(keyCopy[j]);
        }
		if (strstr(nameCopy, keyCopy) != NULL) {
		    printf("%-25s | Rp %-12.ld | Rp %-14.ld | Rp %-12.ld | Rp %-12.ld | %-13s\n", 
		            karyawan[i].nama, karyawan[i].gaji, tunjanganJabatan(karyawan[i].jabatan), karyawan[i].pajak, karyawan[i].gajiBersih, jabatanString(karyawan[i].jabatan));
            found = 1;
        }
    }

    if (!found) {
        printf("No match found.\n");
    }
}

// Function untk mengubah data dari karyawan
void ubahDataKaryawan(Karyawan karyawan[], int *jumlahKaryawan) {
	int i, j;
	int opsi;
    char key[MAX_PANJANG_NAMA];
    printf("Masukkan nama lengkap karyawan yang ingin diubah: ");
    scanf(" %[^\n]s", &key);
    hapusSpasiBelakang(key);
    
    
    int index = -1;
    for (i = 0; i < *jumlahKaryawan; i++) {
    	
    	char nameCopy[MAX_PANJANG_NAMA];
        strcpy(nameCopy, karyawan[i].nama);
        
    	// Mengubah kedua string menjadi lowercase agar mempermudah perbandingan
        for(j = 0; nameCopy[j]; j++){
          nameCopy[j] = tolower(nameCopy[j]);
        }
        char keyCopy[strlen(key) + 1];
        strcpy(keyCopy, key);
        for(j = 0; keyCopy[j]; j++){
          keyCopy[j] = tolower(keyCopy[j]);
        }
        
        // Hapus spasi belakang (jika ada) pada setiap nama sebelum membandingkan
        hapusSpasiBelakang(karyawan[i].nama);
        if (strcmp(nameCopy, keyCopy) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Karyawan '%s' tidak ditemukan.\n", key);
        return;
    }
    
    printf("1. Update data karyawan\n");
	printf("2. Hapus data karyawan\n");
	printf("0. Batal, kembali ke menu awal\n");
	printf("Masukkan opsi yang diinginkan lalu tekan enter: ");
    do{
		scanf("%d", &opsi);
	    // Jika karyawan ditemukan, minta data baru
	    switch (opsi){
	    	case 1:
				printf("Mengubah data untuk %s:\n\n", karyawan[index].nama);
				printf("Masukkan gaji bulanan baru: ");
				scanf("%ld", &karyawan[index].gaji);
				printf("Masukkan jabatan baru (dalam angka): \n");
				printf("List jabatan: \n");
				printf("1. Direktur\n");
				printf("2. Manajer\n");
				printf("3. Sekretaris\n");
				printf("4. Staf\n");
				scanf("%d", &karyawan[index].jabatan);
				karyawan[index].tunjanganJabatan = tunjanganJabatan(karyawan[index].jabatan);
				karyawan[index].pajak = hitungPajak(karyawan[index].gaji + karyawan[index].tunjanganJabatan);
				karyawan[index].gajiBersih = karyawan[index].gaji + karyawan[index].tunjanganJabatan - karyawan[index].pajak; // Menghitung gaji setelah dipotong oleh pajak
				
				printf("Data karyawan untuk %s berhasil diperbarui.\n", karyawan[index].nama);	
				opsi = 0;
				printf("Kembali ke menu awal...\n");
				break;
			case 2:
		        for (i = index; i < *jumlahKaryawan - 1; i++) {
		            karyawan[i] = karyawan[i + 1];
		        }
		        (*jumlahKaryawan)--;
		        printf("Data karyawan '%s' telah dihapus.\n", key);
		        printf("Kembali ke menu awal...\n");
		        opsi = 0;
		        break;
		    case 0:
		    	printf("Kembali ke menu awal...\n");
		    	break;
		    default:
		    	printf("Input salah, silahkan ulangi: ");
		    	break;
		}    		
	}
	while(opsi!=0);
	

    

}

// Function untuk menerima data dari karyawan untuk dibaca
void loadDataKaryawan(Karyawan karyawan[], int *jumlahKaryawan) {
    FILE *file = fopen("karyawan.txt", "r");
    if (file == NULL) {
        printf("Tidak dapat membuka karyawan.txt untuk dibaca.\n");
        return;
    }

    while (fscanf(file, "%49[^0-9] %ld %ld %ld %ld %d\n",
	 karyawan[*jumlahKaryawan].nama, &karyawan[*jumlahKaryawan].gaji, &karyawan[*jumlahKaryawan].tunjanganJabatan, &karyawan[*jumlahKaryawan].pajak, &karyawan[*jumlahKaryawan].gajiBersih, &karyawan[*jumlahKaryawan].jabatan) == 6) {
    	
		karyawan[*jumlahKaryawan].nama[strcspn(karyawan[*jumlahKaryawan].nama, "\n")] = 0; // Hapus karakter baris baru jika terbaca dengan bantuan strcspn
		hapusSpasiBelakang(karyawan[*jumlahKaryawan].nama);        
		(*jumlahKaryawan)++;
        if (*jumlahKaryawan >= MAX_KARYAWAN) break; // Untuk mencegah kelebihan array
    }
    fclose(file);
}

// Function untuk overwrite data di karyawan.txt dengan data terbaru
void simpanDataKaryawan(Karyawan karyawan[], int jumlahKaryawan) {
	int i;
    FILE *file = fopen("karyawan.txt", "w");
    if (file == NULL) {
        printf("Tidak dapat membuka karyawan.txt untuk ditulis.\n");
        system("pause");
        return;
    }

    for (i = 0; i < jumlahKaryawan; i++) {
		fprintf(file, "%s %ld %ld %ld %ld %d\n", karyawan[i].nama, karyawan[i].gaji, karyawan[i].tunjanganJabatan, karyawan[i].pajak, karyawan[i].gajiBersih, karyawan[i].jabatan);
    }

    fclose(file);
}

// Function untuk mensortir dari data karyawan sesuai dengan kebutuhan (nama, gaji, jabatan)
void sortKaryawan(Karyawan karyawan[], int jumlahKaryawan, int mode, int type) {
    int i, j;
    Karyawan temp;

    for (i = 0; i < jumlahKaryawan - 1; i++) {
        for (j = 0; j < jumlahKaryawan - i - 1; j++) {
            if (strcmp(karyawan[j].nama, karyawan[j + 1].nama) > 0  && mode == 1 && type == 1) {
                temp = karyawan[j];
                karyawan[j] = karyawan[j + 1];
                karyawan[j + 1] = temp;
            }
            
            if (strcmp(karyawan[j].nama, karyawan[j + 1].nama) < 0  && mode == 1 && type == 2) {
                temp = karyawan[j];
                karyawan[j] = karyawan[j + 1];
                karyawan[j + 1] = temp;
            }
            
            if (karyawan[j].jabatan > karyawan[j + 1].jabatan && mode == 2 && type == 0) {
                temp = karyawan[j];
                karyawan[j] = karyawan[j + 1];
                karyawan[j + 1] = temp;
            }
            
            if (karyawan[j].gajiBersih > karyawan[j + 1].gajiBersih && mode == 3 && type == 1) {
                temp = karyawan[j];
                karyawan[j] = karyawan[j + 1];
                karyawan[j + 1] = temp;
            }
            
            if (karyawan[j].gajiBersih < karyawan[j + 1].gajiBersih && mode == 3 && type == 2) {
                temp = karyawan[j];
                karyawan[j] = karyawan[j + 1];
                karyawan[j + 1] = temp;
            }
        }
    }
}



/*
	Proyek 1 Pemograman Lanjut
	Sistem Manajemen Gaji Bulanan Karyawan
	Version 2.00

	Tanggal : Rabu, 27 Maret 2024

	Kelompok 6:
		Jeremy Wijanarko Mulyono	2306267132
		Reyhan Ahnaf Deannova		2306267100
		
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proyek1.h"


// Main function berupa penampilan awal dan juga menu untuk menggunakan program
int main(void) {
	int i;
    Karyawan karyawan[MAX_KARYAWAN];
    int jumlahKaryawan = 0;
    
    int index = 0;
	char ch;
	char str[256] = {0};
	
    // Load data karyawan yang ada dari berkas
    loadDataKaryawan(karyawan, &jumlahKaryawan);
	char searchKey[MAX_PANJANG_NAMA];
    int pilihan;
    int pilihan2;
    int pilihan3;
    do {
    	system("cls");
        printf("\033[1;36m"); // Mengubah warna teks menjadi cyan
        printf("\n===================================\n");
        printf("|  Sistem Manajemen Gaji Bulanan  |\n");
        printf("|   (silahkan maximize window)    |\n");
        printf("===================================\n");
        printf("\033[0m"); // Reset warna teks
        printf("\033[1;33m"); // Mengubah warna teks menjadi kuning
        printf("| 1. |	Tambah Karyawan Baru   	  |\n");
		printf("+----+----------------------------+\n");
        printf("| 2. |	Buat Slip Gaji	   	  |\n");
        printf("+----+----------------------------+\n");
        printf("| 3. |	Lihat Data Karyawan	  |\n");
        printf("+----+----------------------------+\n");
        printf("| 4. |	Search nama karyawan	  |\n");
        printf("+----+----------------------------+\n");
        printf("| 5. |	Ubah Data Karyawan	  |\n");
        printf("+----+----------------------------+\n");
        printf("| 6. |	Bantuan			  |\n");
        printf("+----+----------------------------+\n");
        printf("| 0. |	Keluar dari program	  |\n");
        printf("+----+----------------------------+\n\n");
        printf("\033[0m"); // Reset warna teks
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
            	system("cls");
                tambahKaryawan(karyawan, &jumlahKaryawan);
                system("pause");
                break;
            case 2:
                buatSlipGaji(karyawan, jumlahKaryawan);
                printf("Slip gaji berhasil dibuat di file SlipGaji.txt\n");
                system("pause");
                break;
            case 3:
            	do{
	            	system("cls");
	                cetakDataKaryawan(karyawan, jumlahKaryawan);
	                printf("\n=========================================================\n");
       				printf("|			Menu Sortir  			|\n");
        			printf("=========================================================\n");
	                printf("|1.| Sortir berdasarkan nama 				|\n");
	                printf("+--+----------------------------------------------------+\n");
	                printf("|2.| Sortir berdasarkan jabatan				|\n");
	                printf("+--+----------------------------------------------------+\n");
	                printf("|3.| Sortir berdasarkan gaji bersih			|\n");
	                printf("+--+----------------------------------------------------+\n");
	                printf("|0.| Kembali ke menu awal				|\n");
	                printf("+--+----------------------------------------------------+\n\n");
	                printf("Masukkan pilihan	: ");
	                scanf("%d", &pilihan2);
	                switch(pilihan2){
	                	case 1:
	                		system("cls");
	                		cetakDataKaryawan(karyawan, jumlahKaryawan);
			                printf("\n=========================================================\n");
		       				printf("|		Sortir berdasarkan nama  		|\n");
		        			printf("=========================================================\n");
			                printf("|1.| Alphabetically ascending 				|\n");
			                printf("+--+----------------------------------------------------+\n");
			                printf("|2.| Alphabetically descending				|\n");
			                printf("+--+----------------------------------------------------+\n");
			                printf("|0.| Kembali ke menu sebelumnya				|\n");
			                printf("+--+----------------------------------------------------+\n\n");	                		
	                		
	                		printf("Masukkan pilihan	: ");
	                		scanf("%d", &pilihan3);
							switch (pilihan3){
								case 1:
									sortKaryawan(karyawan, jumlahKaryawan, 1, 1);
									break;
								case 2:
									sortKaryawan(karyawan, jumlahKaryawan, 1, 2);
									break;
								default:
									printf("Input salah, kembali ke menu sebelumnya...\n");
									break;
							}
	                		break;
	                	case 2:
	                		sortKaryawan(karyawan, jumlahKaryawan, 2, 0);
	                		break;
	                	case 3:
	                		system("cls");
	                		cetakDataKaryawan(karyawan, jumlahKaryawan);
			                printf("\n=========================================================\n");
		       				printf("|		Sortir berdasarkan gaji bersih 		|\n");
		        			printf("=========================================================\n");
			                printf("|1.| Gaji bersih ascending 				|\n");
			                printf("+--+----------------------------------------------------+\n");
			                printf("|2.| Gaji bersih descending				|\n");
			                printf("+--+----------------------------------------------------+\n");
			                printf("|0.| Kembali ke menu sebelumnya				|\n");
			                printf("+--+----------------------------------------------------+\n\n");	                		
	                		
	                		printf("Masukkan pilihan	: ");
	                		scanf("%d", &pilihan3);
							switch (pilihan3){
								case 1:
									sortKaryawan(karyawan, jumlahKaryawan, 3, 1);
									break;
								case 2:
									sortKaryawan(karyawan, jumlahKaryawan, 3, 2);
									break;
								default:
									printf("Input salah, kembali ke menu sebelumnya...\n");
									break;
							}
	                		break;
	                	case 0:
	                		break;
	                	default:
	                		break;
					}
				} 
				while (pilihan2 != 0);
                break;
            case 4:
            	system("cls");
			    cetakDataKaryawan(karyawan, jumlahKaryawan);
			    printf("\nKetik nama yang ingin dicari, lalu tekan enter untuk berhenti: ");
			    while (1) {
			        ch = _getch();
			        if (ch == '\r') {
			            printf("\n");
			            break;
			        } else if (ch == '\b') {
			            if (index > 0) {
			            	system("cls");
			                str[index++] = '\0';
			                str[index] = '\0';
			                str[index--] = '\0';
			                
			                index--;
			                searchNama(karyawan, jumlahKaryawan, str);
			        		printf("\nKetik nama yang ingin dicari, lalu tekan enter untuk berhenti: ");
			        		printf("%s", str);
			            }
			            if(index == 0){
			            	system("cls");
			                str[index] = '\0';
			                searchNama(karyawan, jumlahKaryawan, str);
			        		printf("\nKetik nama yang ingin dicari, lalu tekan enter untuk berhenti: ");
			        		printf("%s", str);		            	
						}
			        } else {
			            if (index < sizeof(str) - 1) {
			                str[index++] = ch;
			                system("cls");
			        		//printf("%s", str);
			        		searchNama(karyawan, jumlahKaryawan, str);
			        		printf("\nKetik nama yang ingin dicari, lalu tekan enter untuk berhenti: ");
			        		printf("%s", str);
			            }
			        }
			    }
			    printf("Kembali ke menu awal...\n");
			    system("pause");
            	break;
            case 5:
            	system("cls");
            	cetakDataKaryawan(karyawan, jumlahKaryawan);
                ubahDataKaryawan(karyawan, &jumlahKaryawan);
                system("pause");
                break;
            case 6:
            	system("cls");
            	help();
            	system("pause");
            	break;
            case 0:
                // Menyimpan kembali data-data dari karyawan ke dalam karyawan.txt
                simpanDataKaryawan(karyawan, jumlahKaryawan);
                printf("Data mentah disimpan di karyawan.txt\n");
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan masukkan angka antara 0 dan 6.\n");
        }
    } while(pilihan != 0);

    return 0;
}


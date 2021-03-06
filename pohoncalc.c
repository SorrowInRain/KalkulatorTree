#include "pohoncalc.h"
#include <stdio.h>
/* *** Konstruktor *** */
BinTree Tree(infotype Akar, BinTree L, BinTree R, BinTree P){
	BinTree T;
	
	T = AlokNode(Akar);
	if(T != Nil){
		Left(T) = L;
		Right(T) = R;
		Parent(T) = P;
		
		return T;
	}
	else{
		return Nil;
	}
}
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
void MakeTree(infotype Akar, BinTree L, BinTree R, BinTree P, BinTree *T){
	*T = Tree(Akar,L,R,P);
}
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R 
		jika alokasi berhasil. P = Nil jika alokasi gagal. */

/* Manajemen Memory */
addrNode AlokNode(infotype X){
	BinTree T;
	
	T = (addrNode) malloc (sizeof(Node));
	if(T != Nil){
		Akar(T) = X;
		Left(T) = Nil;
		Right(T) = Nil;
		Parent(T) = Nil;
		
		return T;
	}
	else{
		return Nil;
	}
}
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokNode(addrNode P){
	free(P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */

/* *** Predikat-Predikat Penting *** */
bool IsTreeEmpty(BinTree P){
	return(P == Nil);
}
/* Mengirimkan true jika P adalah pohon biner kosong */
bool IsTreeOneElmt(BinTree P){
	return((Right(P) == Nil) && (Left(P) == Nil));
}
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
bool IsUnerLeft(BinTree P){
	return((Right(P) == Nil) && (Left(P) != Nil));
}
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
bool IsUnerRight(BinTree P){
	return((Right(P) != Nil) && (Left(P) == Nil));
}
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
bool IsBiner(BinTree P){
	return((Right(P) != Nil) && (Left(P) != Nil));
}
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/

/* *** Operasi lain *** */
void ChangeAkar(BinTree *P, infotype X, bool kiri){
	addrNode M;
	
	M = AlokNode(X);
	
	if (*P != Nil){
		if (kiri) {
			Left(M) = *P;
		}
		else {
			Right(M) = *P;
		}

		Parent(M) = Parent(*P);
		Parent(*P) = M;

		if (Parent(M) != Nil) {
			if (Left(Parent(M)) == *P) {
				Left(Parent(M)) = M;
			}
			else {
				Right(Parent(M)) = M;
			}
		}
	}
	
	*P = M;
}

void AddDaun(BinTree *P, infotype X, bool Kiri){
	addrNode M;
	
	M = AlokNode(X);
	
	if(IsTreeEmpty(*P)){
		*P = M;
	}
	else{
		if(Kiri){
			Left(M) = Left(*P);
			if(Left(M) != Nil){
				Parent(Left(*P)) = M;
			}
			Left(*P) = M;
		}
		else{
			Left(M) = Right(*P);
			if(Left(M) != Nil){
				Parent(Right(*P)) = M;
			}
			Right(*P) = M;
		}
		
		Parent(M) = *P;
	}
}
/* I.S. P tidak kosong, X adalah salah satu daun Pohon Biner P */
/* F.S. P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri = true), atau 
        sebagai anak Kanan X (jika Kiri = false) */
/*		Jika ada > 1 daun bernilai X, diambil daun yang paling kiri */

void PrintTree (BinTree T) {
	if (IsTreeEmpty(T)) {
		printf("[]");
	}
	else {
		printf("[%.2f(%c)", (Akar(T)).value, (Akar(T)).operand);
		PrintTree(Left(T));
		printf(" ");
		PrintTree(Right(T));
		printf("]");
	}
}
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara preorder: akar, pohon kiri, dan pohon
kanan. Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup (). */
/* Contoh: (a (b (d () ()) ()) (c () ())) */
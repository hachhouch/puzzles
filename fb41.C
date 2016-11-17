// Pb:
// ---
// 
// Given array A of size N, using function Random(returns random number between 0 and 1) implement function that will return array of size N with randomly shuffled elements of the array A. 
// You shoul give only algo.
// 
// Sol:
// ----
// 
// Given an integer array 'a' of the length 'N' the problem can be solved as follows:
// For each 'i' in 0 to N-1: 
// (i) generate a random number 'k' that is betweem 'i' and N-1
// (ii) swap elements a[i] and a[k]
// 
// 
// public static void shuffle(int[] a) {
// 	int N = a.length;
// 
// 	for (int i = 0; i < N; i++) {
// 		int k = i + random()*(N-i)  	// random in (i, N-1)
// 		int aux = a[i];
// 		a[i] = a[k];
// 		a[k] = aux;
// 	}
// }




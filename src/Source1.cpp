import std;

using namespace std;

vector<vector<double>> readMatrix(const string& filename) {
	ifstream file(filename);

	if (!file.is_open()) {
		throw runtime_error("file's can't be opened! file:" + filename);
	}

	int n;
	file >> n;

	vector<vector<double>> matrix(n, vector<double>(n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			file >> matrix[i][j];
		}
	}

	return matrix;
}

vector<vector<double>> umnozenie(const vector<vector<double>>& A, const vector<vector<double>>& B) {
	int n = A.size();
	vector<vector<double>> C(n, vector<double>(n, 0.0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	return C;
}

void writeMatrix(const string& filename, const vector<vector<double>>& matrix) {

	ofstream file(filename);
	int n = matrix.size();
	file << n << "\n";

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			file << matrix[i][j];

			if (j + 1 < n) {
				file << " ";
			}
		}

		file << "\n";
	}

}

int main() {

	try {

		auto A = readMatrix("data/matrix_A.txt");
		auto B = readMatrix("data/matrix_B.txt");

		if (A.size() != B.size()) {
			throw runtime_error("sizes difference! cannot proceed!");
		}

		int n = A.size();

		std::println("Matrix size equals:{} x {}", n, n);

		auto start = chrono::high_resolution_clock::now();
		auto C = umnozenie(A, B);
		auto finish = chrono::high_resolution_clock::now();

		chrono::duration<double> time = finish - start;

		writeMatrix("results/matrix_C.txt", C);

		std::println("execution time:{} seconsd", time.count());

		std::println("elements count:{}", n * n);

		std::println("multiplication result:{}", static_cast<long long>(n) * n * n);
	}

	catch (const exception& e) {
		cerr << "Err:" << e.what() << '\n';
		return 1;
	}

	return 0;
}